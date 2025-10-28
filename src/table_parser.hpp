/// @file  table_parser.hpp
/// @brief Интерфейс функций, выполняющих разбор таблицы.
#ifndef RENDER_CSV_TABLE_PARSER_HPP_INCLUDED
#define RENDER_CSV_TABLE_PARSER_HPP_INCLUDED

#include <cstdint>
#include <vector>
#include <functional>
#include "table_data.hpp"

namespace render_csv
{

    struct TableParserResult
    {
        struct LogEntry
        {
            struct Position
            {
                using Coordinate = std::int32_t;

                Coordinate row {-1};
                Coordinate col {-1};
            };

            Position position;
            String   description;
        };

        using Log =
            std::vector<LogEntry>;

        Log         errors;
        Log         warnings;
        TableData   tableData;
    };

    using TableParser =
        std::function<TableParserResult(StringView)>;

}

#endif//RENDER_CSV_TABLE_PARSER_HPP_INCLUDED
