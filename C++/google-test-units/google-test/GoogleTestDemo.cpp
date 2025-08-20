// GoogleTestDemo.cpp
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <ostream>
#include <stdexcept>

constexpr int AMNT = 100;

struct BankAccount {
  int balance = 0;

  BankAccount() = default;

  explicit BankAccount(const int bal) : balance{bal} {};
  void deposit(int amount) {
    if (amount <= 0) {
      throw std::invalid_argument("deposing negative or no amount");
    }

    balance += amount;
  };

  bool withdraw(int amnt) {
    if (amnt > 0 && amnt <= balance) {
      balance -= amnt;
      return true;
    }

    return false;
  };
};

struct BankAccountTest : testing::Test {
  BankAccount *account;

  BankAccountTest() { account = new BankAccount; };

  virtual ~BankAccountTest() { delete account; };
};

TEST_F(BankAccountTest, BankAccountStartsEmpty) {
  EXPECT_EQ(0, account->balance);
};

TEST_F(BankAccountTest, CanDepositMoney) {
  account->deposit(AMNT);
  EXPECT_EQ(AMNT, account->balance);
};

struct account_state {
  int initial_balance;
  int withdraw_amount;
  int final_balance;
  bool success;

  friend std::ostream &operator<<(std::ostream &os, const account_state &obj) {
    return os << "initial balance: " << obj.initial_balance
              << " withdraw amount: " << obj.withdraw_amount
              << " final balance: " << obj.final_balance
              << " success: " << obj.success;
  }
};

struct WithdrawAccountTest : BankAccountTest,
                             testing::WithParamInterface<account_state> {
  WithdrawAccountTest() { account->balance = GetParam().initial_balance; };
};

TEST_P(WithdrawAccountTest, FinalBalance) {
  auto as = GetParam();
  auto success = account->withdraw(as.withdraw_amount);
  EXPECT_EQ(as.final_balance, account->balance);
  EXPECT_EQ(as.success, success);
};

INSTANTIATE_TEST_SUITE_P(Default, WithdrawAccountTest,
                         testing::Values(account_state{120, 20, 100, true},
                                         account_state{100, 200, 100, false}));

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
