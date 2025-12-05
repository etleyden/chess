#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <exception>
#include <typeinfo>

namespace SimpleTest {

enum class TestStatus {
    NORMAL,
    EXPECTED_FAIL,
    SKIP
};

struct TestCase {
    std::string name;
    std::function<void()> func;
    TestStatus status;
};

class TestRegistry {
public:
    static TestRegistry& instance() {
        static TestRegistry reg;
        return reg;
    }
    
    void add(const std::string& name, std::function<void()> func, TestStatus status = TestStatus::NORMAL) {
        tests.push_back({name, func, status});
    }
    
    int run() {
        int passed = 0;
        int failed = 0;
        int expected_fail = 0;
        int unexpected_pass = 0;
        int skipped = 0;

        const std::string green = "\033[32m";   // Green color
        const std::string red = "\033[31m";     // Red color
        const std::string yellow = "\033[33m";  // Yellow color
        const std::string cyan = "\033[36m";    // Cyan color
        const std::string reset = "\033[0m";    // Reset color
        
        std::cout << "Running " << tests.size() << " tests...\n\n";
        
        for (const auto& test : tests) {
            if (test.status == TestStatus::SKIP) {
                std::cout << cyan << "[ SKIP ] " << test.name << reset << std::endl;
                skipped++;
                continue;
            }
            
            std::cout << "[ RUN  ] " << test.name << std::endl;
            
            bool test_passed = false;
            std::string error_msg;
            
            try {
                test.func();
                test_passed = true;
            } catch (const std::exception& e) {
                error_msg = e.what();
                test_passed = false;
            }
            
            if (test.status == TestStatus::EXPECTED_FAIL) {
                if (test_passed) {
                    std::cout << yellow << "[ UPASS] " << test.name << " (expected to fail, but passed)" << reset << std::endl;
                    unexpected_pass++;
                } else {
                    std::cout << yellow << "[ XFAIL] " << test.name << reset << std::endl;
                    if (!error_msg.empty()) {
                        std::cout << "  " << error_msg << std::endl;
                    }
                    expected_fail++;
                }
            } else {
                if (test_passed) {
                    std::cout << green << "[ PASS ] " << test.name << reset << std::endl;
                    passed++;
                } else {
                    std::cout << red << "[ FAIL ] " << test.name << reset << "\n  " << error_msg << std::endl;
                    failed++;
                }
            }
        }
        
        std::cout << "\n";
        std::cout << "=== Test Summary ===\n";
        
        if (passed > 0) {
            std::cout << green << passed << " passed" << reset;
        } else {
            std::cout << passed << " passed";
        }
        
        if (failed > 0) {
            std::cout << ", " << red << failed << " failed" << reset;
        } else {
            std::cout << ", " << failed << " failed";
        }
        
        if (expected_fail > 0) {
            std::cout << ", " << yellow << expected_fail << " expected failures" << reset;
        }
        
        if (unexpected_pass > 0) {
            std::cout << ", " << yellow << unexpected_pass << " unexpected passes" << reset;
        }
        
        if (skipped > 0) {
            std::cout << ", " << cyan << skipped << " skipped" << reset;
        }
        
        std::cout << "\n";
        
        // Return non-zero if there are actual failures or unexpected passes
        return failed + unexpected_pass;
    }
    
private:
    std::vector<TestCase> tests;
};

class TestRegistrar {
public:
    TestRegistrar(const std::string& name, std::function<void()> func, TestStatus status = TestStatus::NORMAL) {
        TestRegistry::instance().add(name, func, status);
    }
};

class AssertionError : public std::runtime_error {
public:
    AssertionError(const std::string& msg) : std::runtime_error(msg) {}
};

template<typename T, typename U>
void assert_eq(const T& expected, const U& actual, const char* file, int line) {
    if (expected != actual) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Expected " << expected << ", got " << actual;
        throw AssertionError(oss.str());
    }
}

template<typename T, typename U>
void assert_gt(const T& lhs, const U& rhs, const char* file, int line) {
    if (!(lhs > rhs)) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Assertion failed: " << lhs << " > " << rhs;
        throw AssertionError(oss.str());
    }
}

template<typename T, typename U>
void assert_lt(const T& lhs, const U& rhs, const char* file, int line) {
    if (!(lhs < rhs)) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Assertion failed: " << lhs << " < " << rhs;
        throw AssertionError(oss.str());
    }
}

template<typename T, typename U>
void assert_gteq(const T& lhs, const U& rhs, const char* file, int line) {
    if (!(lhs >= rhs)) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Assertion failed: " << lhs << " >= " << rhs;
        throw AssertionError(oss.str());
    }
}

template<typename T, typename U>
void assert_lteq(const T& lhs, const U& rhs, const char* file, int line) {
    if (!(lhs <= rhs)) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Assertion failed: " << lhs << " <= " << rhs;
        throw AssertionError(oss.str());
    }
}

template<typename T>
void assert_true(const T& condition, const char* file, int line) {
    if (!condition) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Assertion failed: expected true";
        throw AssertionError(oss.str());
    }
}

template<typename T>
void assert_false(const T& condition, const char* file, int line) {
    if (condition) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Assertion failed: expected false";
        throw AssertionError(oss.str());
    }
}

template<typename ExceptionType, typename Callable>
void assert_throws(Callable func, const char* file, int line) {
    try {
        func();
    } catch (const ExceptionType&) {
        return; // Test passes if the correct exception is thrown
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Expected exception of type " << typeid(ExceptionType).name() << ", but got " << typeid(e).name();
        throw AssertionError(oss.str());
    } catch (...) {
        std::ostringstream oss;
        oss << file << ":" << line << ": Expected exception of type " << typeid(ExceptionType).name() << ", but got an unknown exception type.";
        throw AssertionError(oss.str());
    }

    std::ostringstream oss;
    oss << file << ":" << line << ": Expected exception of type " << typeid(ExceptionType).name() << ", but no exception was thrown.";
    throw AssertionError(oss.str());
}

} // namespace SimpleTest

// Macros for easy test definition
#define TEST(name) \
    void test_##name(); \
    static SimpleTest::TestRegistrar registrar_##name(#name, test_##name); \
    void test_##name()

#define TEST_XFAIL(name) \
    void test_##name(); \
    static SimpleTest::TestRegistrar registrar_##name(#name, test_##name, SimpleTest::TestStatus::EXPECTED_FAIL); \
    void test_##name()

#define TEST_SKIP(name) \
    void test_##name(); \
    static SimpleTest::TestRegistrar registrar_##name(#name, test_##name, SimpleTest::TestStatus::SKIP); \
    void test_##name()

#define ASSERT_EQ(expected, actual) \
    SimpleTest::assert_eq(expected, actual, __FILE__, __LINE__)

#define ASSERT_GT(lhs, rhs) \
    SimpleTest::assert_gt(lhs, rhs, __FILE__, __LINE__)

#define ASSERT_LT(lhs, rhs) \
    SimpleTest::assert_lt(lhs, rhs, __FILE__, __LINE__)

#define ASSERT_GTEQ(lhs, rhs) \
    SimpleTest::assert_gteq(lhs, rhs, __FILE__, __LINE__)

#define ASSERT_LTEQ(lhs, rhs) \
    SimpleTest::assert_lteq(lhs, rhs, __FILE__, __LINE__)

#define ASSERT_TRUE(condition) \
    SimpleTest::assert_true(condition, __FILE__, __LINE__)

#define ASSERT_FALSE(condition) \
    SimpleTest::assert_false(condition, __FILE__, __LINE__)

#define ASSERT_THROWS(exception_type, func) \
    SimpleTest::assert_throws<exception_type>(func, __FILE__, __LINE__)

#define RUN_ALL_TESTS() \
    SimpleTest::TestRegistry::instance().run()

#endif // SIMPLE_TEST_H

/*
 * USAGE EXAMPLE:
 * 
 * // test_example.cpp
 * #include "simple_test.h"
 * 
 * TEST(addition_works) {
 *     ASSERT_EQ(4, 2 + 2);
 * }
 * 
 * TEST(comparisons) {
 *     ASSERT_GT(5, 3);
 *     ASSERT_LT(3, 5);
 *     ASSERT_GTEQ(5, 5);
 *     ASSERT_LTEQ(3, 3);
 * }
 * 
 * TEST(exception_test) {
 *     ASSERT_THROWS(std::runtime_error, []() { throw std::runtime_error("Error"); });
 * }
 * 
 * // Test that is expected to fail (not yet implemented)
 * TEST_XFAIL(feature_not_implemented_yet) {
 *     ASSERT_EQ(42, get_answer());  // get_answer() doesn't exist yet
 * }
 * 
 * // Test that should be skipped
 * TEST_SKIP(slow_integration_test) {
 *     ASSERT_TRUE(run_slow_operation());
 * }
 * 
 * int main() {
 *     return RUN_ALL_TESTS();
 * }
 * 
 * OUTPUT EXAMPLE:
 * Running 5 tests...
 * 
 * [ RUN  ] addition_works
 * [ PASS ] addition_works
 * [ RUN  ] comparisons
 * [ PASS ] comparisons
 * [ RUN  ] exception_test
 * [ PASS ] exception_test
 * [ RUN  ] feature_not_implemented_yet
 * [ XFAIL] feature_not_implemented_yet
 * [ SKIP ] slow_integration_test
 * 
 * === Test Summary ===
 * 3 passed, 0 failed, 1 expected failures, 1 skipped
 */