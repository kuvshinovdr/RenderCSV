/// @file  table_reader.hpp
/// @brief Интерфейс для классов, выполняющих чтение таблицы.
#ifndef RENDER_CSV_TABLE_READER_HPP_INCLUDED
#define RENDER_CSV_TABLE_READER_HPP_INCLUDED

#include <cstdint>
#include <span>
#include "table_data.hpp"
#include "error_fwd.hpp"

namespace render_csv
{

    using TableReaderResult = Expected<TableData>;

    class TableReader
    {
    public:
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
            std::span<LogEntry const>;

        virtual ~TableReader() = default;
        
        [[nodiscard]] virtual auto parse(StringView input) noexcept
            -> TableReaderResult = 0;
        [[nodiscard]] virtual auto errors() const noexcept
            -> Log = 0;
        [[nodiscard]] virtual auto warnings() const noexcept
            -> Log = 0;
    };

}

#endif//RENDER_CSV_TABLE_READER_HPP_INCLUDED
