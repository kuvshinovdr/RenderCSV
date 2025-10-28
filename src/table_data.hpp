/// @file  table_data.hpp
/// @brief Определение класса, инкапсулирующего данные таблицы.
#ifndef RENDER_CSV_TABLE_DATA_HPP_INCLUDED
#define RENDER_CSV_TABLE_DATA_HPP_INCLUDED

#include "string_operations_fwd.hpp"
#include <vector>

namespace render_csv
{

    struct TableData
    {                
        using Row       = std::vector<String>;
        using Headers   = Row;
        using Body      = std::vector<Row>;

        String  title;
        Headers headers;
        Body    body;
    };

}

#endif//RENDER_CSV_TABLE_DATA_HPP_INCLUDED
