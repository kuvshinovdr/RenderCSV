/// @file  md.hpp
/// @brief Класс записи Markdown-файла.
#ifndef RENDER_CSV_MD_HPP_INCLUDED
#define RENDER_CSV_MD_HPP_INCLUDED

#include "table_writer.hpp"

namespace render_csv
{

    class MarkdownWriter
        : public TableWriter
    {
    public:

        static auto test() noexcept
            -> int;
    };

}

#endif//RENDER_CSV_MD_HPP_INCLUDED
