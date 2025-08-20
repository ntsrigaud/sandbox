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

## Mocking Without Deriving From a Class

It is not necessary to do create a derived class in order to mock the behaviour of an interface as we did previously with `MockDB` which is derived from `DatabaseConnect`. We can directly use `DatabaseConnect` as `MockDB` as in the following:

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

TEST(MyDBTest, LoginTest) {
    // Arrange
    DatabaseConnect mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login(_, _)).Times(AtLeast(1)).WillOnce(Return(true));

    // Act
    int retValue = db.Init("John Doe", "sample password");

    // Assert
    EXPECT_EQ(retValue, 1);
};

```

> [!IMPORTANT]
> This can be useful in cases where you might want to mock direct methods as well as non-virtual methods.

## Invoking Original and Other Implementations

In some cases, we might want to ensure that a `MOCK_METHOD` calls a particular member function _from a derived class_. This can be done by `using ::testing::Invoke`.

### Invoking Original Implementation

```C++
TEST(MyDBTest, LoginTest) {
  // Arrange
  MockDB mdb; // Tell the behavior of the class
  MyDatabase db(mdb);
  DatabaseConnect dbTest;

  // Setup the mock behaviour
  EXPECT_CALL(mdb, login(_, _))
      .Times(AtLeast(1))
      .WillOnce(Invoke(&dbTest, &DatabaseConnect::login));

  // Act
  int retValue = db.Init("John Doe", "sample password");

  // Assert
  EXPECT_EQ(retValue, SUCCESS);
};

```

### Invoking Other Implementations

> [!NOTE]
> Invoking other implementations can be used when you are creating some supporting steps for the mock.

#### Invoking a Function Inside a `struct` Or a `class`

> [!NOTE]
> `Invoke()` can call anything, it is not a requirement for the given instance parameter type to be the derived class.

```C++
struct testOriginalImplementation {
  bool dummyLogin(std::string u, std::string p) {
    LOG("CALLING DUMMY LOGIN...");
    UNUSED(u);
    UNUSED(p);
    return true;
  };
};

TEST(MyDBTest, LoginTest) {
  // Arrange
  MockDB mdb; // Tell the behavior of the class
  MyDatabase db(mdb);
  testOriginalImplementation dbTest;

  // Setup the mock behaviour
  EXPECT_CALL(mdb, login(_, _))
      .Times(AtLeast(1))
      .WillOnce(Invoke(&dbTest, &testOriginalImplementation::dummyLogin));

  // Act
  int retValue = db.Init("John Doe", "sample password");

  // Assert
  EXPECT_EQ(retValue, SUCCESS);
};

```

#### Invoking a Function Outside a `struct` Or a `class`

This can be done by `using ::testing::InvokeWithoutArgs`.

> [!IMPORTANT]
> If you want to call a `global` function, it **has** to be without any argument.

```C++
bool globalDummyFn() {
    LOG("CALLING GLOBAL DUMMY FUNCTION...");
    return true;
};

TEST(MyDBTest, GlobalDummyFn) {
  // Arrange
  MockDB mdb; // Tell the behavior of the class
  MyDatabase db(mdb);

  // Setup the mock behaviour
  EXPECT_CALL(mdb, login(_, _))
      .Times(AtLeast(1))
      .WillOnce(InvokeWithoutArgs(globalDummyFn));

  // Act
  int retValue = db.Init("John Doe", "sample password");

  // Assert
  EXPECT_EQ(retValue, SUCCESS);
};

```

## Setting Default Actions for Function Calls

In some situations, you might need that `EXPECT_CALL` executes multiple times, maybe to verify multiple conditions. A simple solution to this problem is to set the `Invoke()` statement in a particular place and it should be called _by default_ whenever `EXPECT_CALL` executes.

We can do this by using `ON_CALL` to set up the default behaviour and use `DoDefault` as argument for the `EXPECT_CALL` whenever it executes as it follows:

```C++
TEST(MyDBTest, LoginTestDefaultBehavior) {
  // Arrange
  MockDB mdb; // Tell the behavior of the class
  MyDatabase db(mdb);
  testOtherImplementation dbTest;

  // Setup the mock behaviour
  ON_CALL(mdb, login(_, _)).WillByDefault(Invoke(&dbTest, &testOtherImplementation::dummyLogin));
  EXPECT_CALL(mdb, login(_, _))
      .Times(AtLeast(1))
      .WillOnce(DoDefault());

  // Act
  int retValue = db.Init("John Doe", "sample password");

  // Assert
  EXPECT_EQ(retValue, SUCCESS);
};

```

## Performing Multiple Actions
