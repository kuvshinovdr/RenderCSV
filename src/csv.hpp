/// @file  csv.hpp
/// @brief Класс чтения CSV-файла.
#ifndef RENDER_CSV_CSV_HPP_INCLUDED
#define RENDER_CSV_CSV_HPP_INCLUDED

#include "table_parser.hpp"
#include <type_traits>

namespace render_csv
{

    /// @brief Указать, следует ли извлекать первую строчку CSV в качестве заголовков колонок таблицы.
    enum class ExtractFirstRowAsHeaders
    {
        No,
        Yes,
    };

    /// @brief Парсер CSV по стандарту RFC 4180 https://datatracker.ietf.org/doc/html/rfc4180
    [[nodiscard]] auto makeCsvParser(ExtractFirstRowAsHeaders)
        -> TableParser;

}

#endif//RENDER_CSV_CSV_HPP_INCLUDED
