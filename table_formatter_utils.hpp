#ifndef TABLE_FORMATTER_UTILS_HPP
#define TABLE_FORMATTER_UTILS_HPP

// Проверяем, что таблица не пустая
inline bool simpleValidate(int rows, int cols) {
    return rows > 0 && cols > 0;
}

#endif // TABLE_FORMATTER_UTILS_HPP