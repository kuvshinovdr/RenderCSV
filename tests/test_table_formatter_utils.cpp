#include "../table_formatter_utils.hpp"
#include "../table_formatter_utils.cpp"
#include <cassert>
#include <iostream>
#include <limits>

void test_valid_table() {
    TableData table = {
        {"Name", "Age"},
        {"Alice", "25"},
        {"Bob", "30"}
    };
    auto log = simpleValidate(table);
    assert(log.empty());
    std::cout << "OK\n";
}

void test_different_columns() {
    TableData table = {
        {"A", "B", "C"},
        {"1", "2"},
        {"3", "4", "5"}
    };
    auto log = simpleValidate(table);
    assert(log.size() == 1);
    std::cout << "OK\n";
}

void test_invalid_utf8() {
    TableData table = {
        {"A", "B"},
        {"1", std::string("\xFF")}
    };
    auto log = simpleValidate(table);
    assert(log.size() >= 1);
    std::cout << "OK\n";
}

int main() {
    test_valid_table();
    test_different_columns();
    test_invalid_utf8();

    std::cout << "Тесты пройдены\n";

    return 0;
}
