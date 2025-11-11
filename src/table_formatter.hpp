/// @file  table_formatter.hpp
/// @brief Интерфейс функций, выполняющих формирование таблицы в некотором формате.
#ifndef RENDER_CSV_TABLE_FORMATTER_HPP_INCLUDED
#define RENDER_CSV_TABLE_FORMATTER_HPP_INCLUDED

#include <cstdint>
#include <vector>
#include <functional>
#include "table_data.hpp"

namespace render_csv
{

    /// @brief Результат конвертирования таблицы в некоторый текстовый формат: протокол предупреждений и вывод (output).
    struct TableFormatterResult
    {
        struct LogEntry
        {
            using RowNumber = std::int32_t;

            RowNumber   rowNumber       {-1};
            String      description;
        };

        using Log =
            std::vector<LogEntry>;

        Log    warnings;
        String output;
    };

    using TableFormatter =
        std::function<TableFormatterResult(TableData const&)>;

}

#endif//RENDER_CSV_TABLE_FORMATTER_HPP_INCLUDED
