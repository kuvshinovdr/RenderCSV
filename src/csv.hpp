/// @file  csv.hpp
/// @brief Класс чтения CSV-файла.
#ifndef RENDER_CSV_CSV_HPP_INCLUDED
#define RENDER_CSV_CSV_HPP_INCLUDED

#include "table_reader.hpp"

namespace render_csv
{

    class CsvReader
        : public TableReader
    {
    public:

        static auto test() noexcept
            -> int;
    };

}

#endif//RENDER_CSV_CSV_HPP_INCLUDED
