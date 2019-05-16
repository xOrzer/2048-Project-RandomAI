#include "Doubler.hpp"
#include <CppUTest/CommandLineTestRunner.h>
TEST_GROUP(GroupTest) { };
TEST(GroupTest, test_doubler_1) { // premier test unitaire
    int result = doubler(21);
    CHECK_EQUAL(42, result);
}
TEST(GroupDoubler, test_doubler_2) { // deuxième test unitaire
    int result = doubler(0);
    CHECK_EQUAL(0, result);
}
