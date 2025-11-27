#include "table_formatter_utils.hpp"
#include <limits>
#include <format>
#include <utf8.h>

// Типы данных определены в table_data.hpp транзитивно

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

    // Проверка: количество строк помещается в int32_t
    if (data.size() > std::numeric_limits<std::int32_t>::max()) {
        log.push_back({
            TableFormatterResult::LogEntry::Type::Warning,
            "Слишком много строк (превышен лимит int32_t)"
        });
    }

    std::size_t first_row_columns = data[0].size();

    for (std::size_t i = 0; i < data.size(); ++i) {
        const auto& row = data[i];

        // Проверка: количество столбцов совпадает с первой строкой
        if (i > 0 && row.size() != first_row_columns) {
            log.push_back({
                TableFormatterResult::LogEntry::Type::Warning,
                std::format("Строка {} содержит {} столбцов, ожидалось {}",
                    i, row.size(), first_row_columns),
                i
            });
        }

        std::int64_t row_width_sum = 0;

        for (std::size_t j = 0; j < row.size(); ++j) {
            const std::string& cell = row[j];

            // Проверка: строка содержит корректный UTF-8
            if (!utf8::is_valid(cell.begin(), cell.end())) {
                log.push_back({
                    TableFormatterResult::LogEntry::Type::Warning,
                    std::format("Строка {}, столбец {}: некорректный UTF-8", i, j),
                    i
                });
                continue;
            }

            // Вычисляем ширину ячейки в символах (кодовых позициях)
            std::int64_t cell_width = utf8::distance(cell.begin(), cell.end());
            row_width_sum += cell_width;
        }

        // Проверка: сумма ширин столбцов помещается в int32_t
        if (row_width_sum > std::numeric_limits<std::int32_t>::max()) {
            log.push_back({
                TableFormatterResult::LogEntry::Type::Warning,
                std::format("Строка {}: суммарная ширина превышает лимит int32_t", i),
                i
            });
        }
    }

    return log;
}
