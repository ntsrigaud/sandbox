# Google Test Compilation Shortcuts

This directory contains examples and documentation for the Google Test compilation shortcuts added to your shell configuration.

## Available Commands

### 1. `comp-test` (Basic Alias)

Simple compilation alias for Google Test files.

**Usage:**

```bash
comp-test <source_files> -o <output_name>
```

**Example:**

```bash
comp-test example_test.cpp -o my_tests
./my_tests
```

**What it does:**

- Compiles C++ files with Google Test support
- Uses C++17 standard
- Includes proper Google Test headers and libraries
- Links against gtest, gtest_main, and pthread

### 2. `comp-test-run` (Advanced Function)

Cross-platform compilation function that compiles AND runs tests automatically.

**Usage:**

```bash
comp-test-run [options] <source_files>
```

**Options:**

- `-o <name>`: Specify output executable name (default: "test_runner")

**Example:**

```bash
comp-test-run example_test.cpp
comp-test-run example_test.cpp -o custom_tests
```

**What it does:**

- Automatically detects your OS (macOS/Linux)
- Finds Google Test installation paths
- Compiles the test files
- Runs the tests automatically if compilation succeeds
- Shows clear test results

## Cross-Platform Support

The shortcuts automatically handle different Google Test installation paths:

### macOS (Homebrew)

- Apple Silicon: `/opt/homebrew/opt/googletest`
- Intel Mac: `/usr/local/opt/googletest`

### Linux

- Standard locations: `/usr/include/gtest`
- Package manager installations

## Example Test File Structure

See `example_test.cpp` for a comprehensive example that includes:

- Basic test cases with `TEST()` macro
- Test fixtures using `TEST_F()` macro
- Various assertion types: `EXPECT_EQ`, `ASSERT_TRUE`, etc.
- String comparisons with `ASSERT_STREQ`
- Container testing
- Setup/TearDown methods

## Common Google Test Assertions

```cpp
// Equality checks
EXPECT_EQ(expected, actual);
ASSERT_EQ(expected, actual);

// Boolean checks
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);
ASSERT_TRUE(condition);

// Comparison checks
EXPECT_GT(val1, val2);  // Greater than
EXPECT_LT(val1, val2);  // Less than
EXPECT_GE(val1, val2);  // Greater or equal
EXPECT_LE(val1, val2);  // Less or equal

// String checks
EXPECT_STREQ("expected", actual.c_str());
EXPECT_STRNE("not this", actual.c_str());

// Exception checks
EXPECT_THROW(statement, exception_type);
EXPECT_NO_THROW(statement);
```

## Difference Between EXPECT and ASSERT

- **EXPECT\_\***: Test continues even if assertion fails
- **ASSERT\_\***: Test stops immediately if assertion fails

## Tips

1. **For quick testing**: Use `comp-test-run` - it compiles and runs in one command
2. **For build automation**: Use `comp-test` to just compile, then run manually
3. **Multiple test files**: Both commands support multiple `.cpp` files
4. **Custom output names**: Use `-o` flag to specify executable name

## Troubleshooting

If compilation fails:

1. Make sure Google Test is installed: `brew install googletest` (macOS)
2. Check if paths are correct for your system
3. Ensure all required headers are included in your test files
4. Verify C++ standard compatibility (tests use C++17)

## Integration with Neovim

The shortcuts work perfectly with the Neovim configuration that includes Google Test support:

- Write tests in Neovim with full syntax highlighting
- Use `comp-test-run` to quickly compile and test
- Get immediate feedback on test results
