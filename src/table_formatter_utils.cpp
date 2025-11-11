/// @file  table_formatter_utils.cpp

// Используется библиотека https://github.com/nemtrif/utfcpp
#include <utf8.h>
#include "table_formatter_utils.hpp"

namespace render_csv
{

    // Виды предупреждений:
    // 1. Строки разной ширины в столбцах -- на каждой строке, количество столбцов в которой отличается от предыдущей.
    // 2. Количество строк и суммы ширин столбцов каждой строки в символах должны помещаться в int32_t.
    // 3. Строки не содержат корректную UTF-8.
    auto simpleValidate(TableData const& data)
        -> TableFormatterResult::Log
    {
        // TODO
        // utf8::is_valid для проверки корректности UTF-8 данных
        return {};
    }

    auto computeColumnWidthsUtf8(TableData const& data)
        -> TableColumnWidths
    {
        TableColumnWidths result;

        // --- Headers ---
        for (auto const& cell : data.headers)
        {
            auto width = static_cast<std::int32_t>(
                utf8::distance(cell.begin(), cell.end())
                );
            result.headers.push_back(width);
        }

        // --- Body ---
        for (auto const& row : data.body)
        {
            TableColumnWidths::OneRowColumnWidths rowWidths;
            rowWidths.reserve(row.size());

            for (auto const& cell : row)
            {
                auto width = static_cast<std::int32_t>(
                    utf8::distance(cell.begin(), cell.end())
                    );
                rowWidths.push_back(width);
            }

            result.body.push_back(std::move(rowWidths));
        }

        return result;
    }

}