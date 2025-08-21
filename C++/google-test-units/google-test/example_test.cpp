#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

// Example functions to test
int add(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

std::string reverse_string(const std::string &str) {
  std::string result = str;
  std::reverse(result.begin(), result.end());
  return result;
}

// Test cases
TEST(MathTest, Addition) {
  EXPECT_EQ(add(2, 3), 5);
  EXPECT_EQ(add(-1, 1), 0);
  EXPECT_EQ(add(0, 0), 0);
  ASSERT_GT(add(5, 5), 9);
}

TEST(MathTest, Multiplication) {
  EXPECT_EQ(multiply(3, 4), 12);
  EXPECT_EQ(multiply(-2, 3), -6);
  EXPECT_EQ(multiply(0, 5), 0);
  ASSERT_NE(multiply(2, 3), 0);
}

TEST(StringTest, ReverseString) {
  EXPECT_EQ(reverse_string("hello"), "olleh");
  EXPECT_EQ(reverse_string(""), "");
  EXPECT_EQ(reverse_string("a"), "a");
  ASSERT_STREQ(reverse_string("test").c_str(), "tset");
}

TEST(VectorTest, VectorOperations) {
  std::vector<int> vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[4], 5);

  vec.push_back(6);
  ASSERT_EQ(vec.size(), 6);
  EXPECT_EQ(vec.back(), 6);
}

// Test with fixtures
class CalculatorTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Code here will be called immediately after the constructor
    calculator_value = 0;
  }

  void TearDown() override {
    // Code here will be called immediately after each test
  }

  int calculator_value;
};

TEST_F(CalculatorTest, AddNumbers) {
  calculator_value = add(calculator_value, 5);
  EXPECT_EQ(calculator_value, 5);

  calculator_value = add(calculator_value, 10);
  EXPECT_EQ(calculator_value, 15);
}

TEST_F(CalculatorTest, MultiplyNumbers) {
  calculator_value = 2;
  calculator_value = multiply(calculator_value, 3);
  EXPECT_EQ(calculator_value, 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
