﻿/// @file  table_formatter_utils.hpp
/// @brief Вспомогательный функционал для форматирования таблиц.
#ifndef RENDER_CSV_TABLE_FORMATTER_UTILS_HPP_INCLUDED
#define RENDER_CSV_TABLE_FORMATTER_UTILS_HPP_INCLUDED

#include "table_formatter.hpp"

namespace render_csv
{

    /// @brief Простая проверка качества данных (длины строк таблицы). 
    [[nodiscard]] auto simpleValidate(TableData const&)
        -> TableFormatterResult::Log;

    using ColumnWidth = std::int32_t;

    using RowColumnWidths =
        std::vector<ColumnWidth>;

    using TableColumnWidths =
        std::vector<RowColumnWidths>;

    /// @brief Вычислить ширины всех столбцов во всех строках в графических позициях UTF-8. 
    [[nodiscard]] auto computeColumnWidthsUtf8(TableData const&)
        -> TableColumnWidths;

}

#endif//RENDER_CSV_TABLE_FORMATTER_UTILS_HPP_INCLUDED
