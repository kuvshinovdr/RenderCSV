#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <limits>
#include <utf8.h>

// Типы данных
using TableData = std::vector<std::vector<std::string>>;
using TableColumnWidths = std::vector<std::int32_t>;

namespace TableFormatterResult {
    struct LogEntry {
        enum class Type { Warning, Error };
        Type type;
        std::string message;
        std::size_t row = 0;
    };
    using Log = std::vector<LogEntry>;
}

// Виды предупреждений:
// 1. Строки разной ширины в столбцах -- на каждой строке, количество столбцов в которой отличается от предыдущей.
// 2. Количество строк и суммы ширин столбцов каждой строки в символах должны помещаться в int32_t.
// 3. Строки не содержат корректную UTF-8.
auto simpleValidate(TableData const& data)
    -> TableFormatterResult::Log
{
    TableFormatterResult::Log log;

    if (data.empty()) {
        return log;
    }

    //  количество строк помещается в int32_t
    if (data.size() > std::numeric_limits<std::int32_t>::max()) {
        log.push_back({
            TableFormatterResult::LogEntry::Type::Warning,
            "Слишком много строк (не помещается в int32_t)"
        });
    }

    std::size_t first_row_columns = data[0].size();

    for (std::size_t i = 0; i < data.size(); ++i) {
        const auto& row = data[i];

        //  количество столбцов совпадает с первой строкой
        if (i > 0 && row.size() != first_row_columns) {
            log.push_back({
                TableFormatterResult::LogEntry::Type::Warning,
                "Строка " + std::to_string(i) + ": " +
                std::to_string(row.size()) + " столбцов, ожидалось " +
                std::to_string(first_row_columns),
                i
            });
        }

        std::int64_t row_width_sum = 0;

        for (std::size_t j = 0; j < row.size(); ++j) {
            const std::string& cell = row[j];

            // строка содержит корректный UTF-8
            if (!utf8::is_valid(cell.begin(), cell.end())) {
                log.push_back({
                    TableFormatterResult::LogEntry::Type::Warning,
                    "Строка " + std::to_string(i) + ", столбец " +
                    std::to_string(j) + ": некорректный UTF-8",
                    i
                });
                continue;
            }

            // Вычисляем ширину ячейки в символах (кодовых позициях)
            std::int64_t cell_width = utf8::distance(cell.begin(), cell.end());
            row_width_sum += cell_width;
        }

        // сумма ширин столбцов помещается в int32_t
        if (row_width_sum > std::numeric_limits<std::int32_t>::max()) {
            log.push_back({
                TableFormatterResult::LogEntry::Type::Warning,
                "Строка " + std::to_string(i) +
                ": суммарная ширина слишком большая (не помещается в int32_t)",
                i
            });
        }
    }

    return log;
}

auto computeColumnWidthsUtf8(TableData const& data)
    -> TableColumnWidths
{
    if (data.empty()) {
        return {};
    }

    // Находим максимальное количество столбцов
    std::size_t max_columns = 0;
    for (const auto& row : data) {
        if (row.size() > max_columns) {
            max_columns = row.size();
        }
    }

    TableColumnWidths widths(max_columns, 0);

    // Для каждого столбца находим максимальную ширину
    for (const auto& row : data) {
        for (std::size_t i = 0; i < row.size(); ++i) {
            const std::string& cell = row[i];

            // Проверяем корректность UTF-8
            if (!utf8::is_valid(cell.begin(), cell.end())) {
                continue;
            }

            // Вычисляем ширину в символах UTF-8
            std::int32_t width = static_cast<std::int32_t>(
                utf8::distance(cell.begin(), cell.end())
            );

            if (width > widths[i]) {
                widths[i] = width;
            }
        }
    }

    return widths;
}

// Пример использования
int main() {
    std::cout << "Тест 1: Нормальная таблица" << std::endl;
    TableData table1 = {
        {"Имя", "Возраст", "Город"},
        {"Алиса", "25", "Москва"},
        {"Боб", "30", "Лондон"},
        {"Чарли", "35", "Париж"}
    };

    auto log1 = simpleValidate(table1);
    if (log1.empty()) {
        std::cout << "Ошибок не найдено" << std::endl;
    } else {
        for (const auto& entry : log1) {
            std::cout << "  " << entry.message << std::endl;
        }
    }

    auto widths1 = computeColumnWidthsUtf8(table1);
    std::cout << "Ширины столбцов: ";
    for (auto w : widths1) {
        std::cout << w << " ";
    }
    std::cout << std::endl << std::endl;


    std::cout << "Тест 2: Разное количество столбцов" << std::endl;
    TableData table2 = {
        {"A", "B", "C"},
        {"1", "2"},      // Только 2 столбца - будет предупреждение
        {"3", "4", "5"}
    };

    auto log2 = simpleValidate(table2);
    for (const auto& entry : log2) {
        std::cout << "  " << entry.message << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Тест 3: UTF-8 символы" << std::endl;
    TableData table3 = {
        {"Название", "Описание"},
        {"Привет", "Мир"},
        {"Hello", "World"},
        {"你好", "世界"}  // Китайские символы
    };

    auto log3 = simpleValidate(table3);
    if (log3.empty()) {
        std::cout << "UTF-8 корректен" << std::endl;
    }

    auto widths3 = computeColumnWidthsUtf8(table3);
    std::cout << "Ширины столбцов (в символах): ";
    for (auto w : widths3) {
        std::cout << w << " ";
    }
    std::cout << std::endl << std::endl;


    std::cout << "Тест 4: Некорректный UTF-8" << std::endl;
    TableData table4 = {
        {"Test"},
        {std::string("\xFF\xFE")}  // Некорректная UTF-8 последовательность
    };

    auto log4 = simpleValidate(table4);
    for (const auto& entry : log4) {
        std::cout << " " << entry.message << std::endl;
    }

    return 0;
}