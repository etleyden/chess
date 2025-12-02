#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <sstream>

namespace SimpleTest {

struct TestCase {
    std::string name;
    std::function<void()> func;
};

class TestRegistry {
public:
    static TestRegistry& instance() {
        static TestRegistry reg;
        return reg;
    }
    
    void add(const std::string& name, std::function<void()> func) {
        tests.push_back({name, func});
    }
    
    int run() {
        int passed = 0;
        int failed = 0;

        const std::string green = "\033[32m"; // Green color
        const std::string red = "\033[31m";   // Red color
        const std::string reset = "\033[0m";  // Reset color
        
        std::cout << "Running " << tests.size() << " tests...\n\n";
        
        for (const auto& test : tests) {
            std::cout << "[ RUN  ] " << test.name << std::endl;
            try {
                test.func();
                std::cout << "[ PASS ] " << test.name << std::endl;
                passed++;
            } catch (const std::exception& e) {
                std::cout << "[ FAIL ] " << test.name << "\n  " << e.what() << std::endl;
                failed++;
            }
        }
        
        std::cout << "\n";
        if(passed > 0) {
            std::cout << green << passed << " passed" << reset << ", ";
        } else {
            std::cout << passed << " passed, ";
        }
        if (failed > 0) {
            std::cout << red << failed << " failed" << reset << "\n";
        } else {
            std::cout << failed << " failed\n";
        }
        return failed;
    }
    
private:
    std::vector<TestCase> tests;
};

class TestRegistrar {
public:
    TestRegistrar(const std::string& name, std::function<void()> func) {
        TestRegistry::instance().add(name, func);
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

} // namespace SimpleTest

// Macros for easy test definition
#define TEST(name) \
    void test_##name(); \
    static SimpleTest::TestRegistrar registrar_##name(#name, test_##name); \
    void test_##name()

#define ASSERT_EQ(expected, actual) \
    SimpleTest::assert_eq(expected, actual, __FILE__, __LINE__)

#define ASSERT_TRUE(condition) \
    SimpleTest::assert_true(condition, __FILE__, __LINE__)

#define ASSERT_FALSE(condition) \
    SimpleTest::assert_false(condition, __FILE__, __LINE__)

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
 * TEST(strings_concatenate) {
 *     std::string result = std::string("Hello") + " World";
 *     ASSERT_EQ(std::string("Hello World"), result);
 * }
 * 
 * TEST(boolean_logic) {
 *     ASSERT_TRUE(5 > 3);
 *     ASSERT_FALSE(2 > 10);
 * }
 * 
 * int main() {
 *     return RUN_ALL_TESTS();
 * }
 */