/// @file  table_writer.hpp
/// @brief Интерфейс для классов, выполняющих запись таблицы.
#ifndef RENDER_CSV_TABLE_WRITER_HPP_INCLUDED
#define RENDER_CSV_TABLE_WRITER_HPP_INCLUDED

#include "table_data.hpp"

namespace render_csv
{

    class TableWriter
    {
    public:
        virtual ~TableWriter() = default;

    };

}

#endif//RENDER_CSV_TABLE_WRITER_HPP_INCLUDED
