#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <print>

TEST_CASE("std::println works") {
    // This will compile only if libstdc++exp is linked (GCC ≥15)
    std::println("Test output via std::println");
}