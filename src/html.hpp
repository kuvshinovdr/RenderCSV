/// @file  html.hpp
/// @brief Класс записи HTML-файла.
#ifndef RENDER_CSV_HTML_HPP_INCLUDED
#define RENDER_CSV_HTML_HPP_INCLUDED

#include "table_writer.hpp"

namespace render_csv
{

    class HtmlWriter
        : public TableWriter
    {
    public:

        static auto test() noexcept
            -> int;
    };

}

#endif//RENDER_CSV_HTML_HPP_INCLUDED
