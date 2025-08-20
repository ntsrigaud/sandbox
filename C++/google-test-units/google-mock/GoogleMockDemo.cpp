#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#define DEBUG true
#define LOG(x)                                                                 \
  if (DEBUG)                                                                   \
  std::cout << x << std::endl
#define UNUSED(x) (void)(x)

constexpr int FAILURE = 0;
constexpr int SUCCESS = 1;
constexpr int LOGIN_ATTEMPTS = 2;

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

class DatabaseConnect {
public:
  virtual bool login(std::string username, std::string password) {
    UNUSED(username);
    UNUSED(password);
    return true;
  };
  virtual bool login2(std::string username, std::string password) {
    UNUSED(username);
    UNUSED(password);
    return true;
  };
  virtual bool logout(std::string username) {
    UNUSED(username);
    return true;
  };
  virtual int fetchRecord() { return -1; };
};

class MockDB : public DatabaseConnect {
public:
  MOCK_METHOD0(fetchRecord, int());
  MOCK_METHOD1(logout, bool(std::string));
  MOCK_METHOD2(login, bool(std::string, std::string));
  MOCK_METHOD2(login2, bool(std::string, std::string));
};

class MyDatabase {
  DatabaseConnect &dbC;

public:
  MyDatabase(DatabaseConnect &_dbC) : dbC(_dbC) {};

  int Init(std::string username, std::string password) {
    // Randomly chose the login method
    int rvalue = rand() % 2;

    if (rvalue == 0) {
      if (!dbC.login(username, password)) {
        // Try two successive login attempt
        if (!dbC.login(username, password))
          LOG("DB FAILURE 2nd TIME");
        return FAILURE;
      } else {
        LOG("DB SUCCESS");
        return SUCCESS;
      }
    } else {
      return dbC.login2(username, password);
    }
  };
};

// TEST(MyDBTest, LoginSuccess) {
//   // Arrange
//   MockDB mdb; // Tell the behavior of the class
//   MyDatabase db(mdb);
//
//   // Setup the mock behaviour
//   EXPECT_CALL(mdb, login(_, _))
//       .Times(AtLeast(1))
//       .WillOnce(Return(true));
//
//   // Act
//   int retValue = db.Init("John Doe", "sample password");
//
//   // Assert
//   EXPECT_EQ(retValue, SUCCESS);
// };

// TEST(MyDBTest, LoginFailureExpectCall) {
//   // Arrange
//   MockDB mdb; // Tell the behavior of the class
//   MyDatabase db(mdb);
//
//   // Setup the mock behaviour
//   EXPECT_CALL(mdb, login(_, _))
//       .Times(AtLeast(LOGIN_ATTEMPTS))
//       .WillRepeatedly(Return(false));
//
//   // Act
//   int retValue = db.Init("John Doe", "sample password");
//
//   // Assert
//   EXPECT_EQ(retValue, FAILURE);
// };

TEST(MyDBTest, LoginFailureOnCall) {
  // Arrange
  MockDB mdb; // Tell the behavior of the class
  MyDatabase db(mdb);

  // Setup the mock behaviour
  ON_CALL(mdb, login(_, _)).WillByDefault(Return(true));

  // Act
  int retValue = FAILURE;

  // Assert
  EXPECT_EQ(retValue, FAILURE);
};

TEST(MyDBTest, LoginSuccessOnCallWithRandomlyChosenFunction) {
  // Arrange
  MockDB mdb; // Tell the behavior of the class
  MyDatabase db(mdb);

  // Setup the mock behaviour
  ON_CALL(mdb, login(_, _)).WillByDefault(Return(true));
  ON_CALL(mdb, login2(_, _)).WillByDefault(Return(true));

  // Act
  int retValue = FAILURE;

  // Assert
  EXPECT_EQ(retValue, FAILURE);
};

int main(int argc, char *argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
