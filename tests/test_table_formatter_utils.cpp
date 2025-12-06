#include "../table_formatter_utils.hpp"
#include <doctest.h>

TEST_SUITE("table_formatter_utils")
{

    TEST_CASE("valid table")
    {
        TableData table = {
            {"Name", "Age"},
            {"Alice", "25"},
            {"Bob", "30"}
        };
        auto log = simpleValidate(table);

        CHECK(log.empty());
    }

    TEST_CASE("different columns")
    {
        TableData table = {
            {"A", "B", "C"},
            {"1", "2"},
            {"3", "4", "5"}
        };
        auto log = simpleValidate(table);

        CHECK(log.size() == 1);
    }

    TEST_CASE("invalid utf8")
    {
        TableData table = {
            {"A", "B"},
            {"1", std::string("\xFF")}
        };
        auto log = simpleValidate(table);

        CHECK(log.size() >= 1);
    }

}