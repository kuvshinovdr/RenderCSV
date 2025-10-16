/// @file  table_reader.hpp
/// @brief Интерфейс для классов, выполняющих чтение таблицы.
#ifndef RENDER_CSV_TABLE_READER_HPP_INCLUDED
#define RENDER_CSV_TABLE_READER_HPP_INCLUDED

#include "table_data.hpp"

namespace render_csv
{

    class TableReader
    {
    public:
        virtual ~TableReader() = default;

    };

}

#endif//RENDER_CSV_TABLE_READER_HPP_INCLUDED
