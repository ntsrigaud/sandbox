# Unit Testing Using Google Test

Google Test is a testing framework for writing unit tests in C++. The structure of all unit tests must follow a specific pattern. This ensures that each unit test is **independent**, **small**, and **fast**.

## Unit Test Structure

- **Arrange**: Arrange the requirements for running the tests.
- **Act**: Set of code or statements you want to test.
- **Assert**: Testing the result of **Act**.

## Writing a Unit Test

Unit test are written using a _macro_ (`TEST`, `TEST_F`, ...etc.) where we can specify the **test suite name**, and the **test name** as argument to the macro.

```C++
TEST(TEST_SUITE_NAME, TEST_NAME) {
    std::cout << "This is a sample test unit\n";
}
```

> [!IMPORTANT]
> A **test name** can be used only once in a test suite.

### Assertions

Unit tests are built on assertions, meaning that they only assert the output of a function by comparing it to the expected output.

When writing assertions, one has to consider to kind of failures:

- Non-fatal failures (`EXPECT_*`)
- Fatal failures (`ASSERT_*`)

> [!NOTE]
> **Non-fatal failures** do not stop the execution of a unit test whereas **fatal failures** do.

### Test Fixtures

Used whenever the **arrange** section of multiple unit tests are the same. To solve this issue, we need to use a `struct` to create a _test fixture_ which derives from `testing::Test` where we have to defined two functions `SetUp()` and `TearDown()` as follows:

```C++

struct TF : public testing::Test {
    ObjectToBeTested* instance;     // Will be used in all test fixtures
    void SetUp() { instance = new ObjectToBeTested() };
    void TearDown() { delete instance; };
};

```

[GoogleTestPrimer | Google Test](https://google.github.io/googletest/primer.html)
