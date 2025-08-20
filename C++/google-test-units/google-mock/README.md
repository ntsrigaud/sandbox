# Google Mock - The C++ Mocking Framework

Mocks are used for testing the behaviour of API(s) / Interfaces which will be used in components under tests.

## Writing a Mock Unit test

To write a mock for an API or Interface we need to derive from the _same_ class as in the following:

```C++
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
    return true; };
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

```

> [!NOTE]
> All the mock methods have to be written in the `public` section.

> [!IMPORTANT]
> We will use the same number of parameters of the method of the function we are trying to mock.

### `EXPECT_CALL` and `ON_CALL`

We have to use mock using two macros: `EXPECT_CALL` and `ON_CALL`.

- `EXPECT_CALL`: Sets the behaviour of the particular function we are going to call and this function **must be executed**.
- `ON_CALL`: Almost the same as `EXPECT_CALL`, but the function is **not required to be executed**, but if it does we can assert the behaviour.
