/// @file  md.hpp
/// @brief Класс записи Markdown-файла.
#ifndef RENDER_CSV_MD_HPP_INCLUDED
#define RENDER_CSV_MD_HPP_INCLUDED

#include "table_formatter.hpp"

namespace render_csv
{

    /// @brief Вид генерации Markdown.
    enum class MarkdownKind
    {
        GithubFlavored,
    };

    /// @brief Создать генератор Markdown нужного вида. 
    [[nodiscard]] auto makeMarkdownFormatter(MarkdownKind kind)
        -> TableFormatter;

}

#endif//RENDER_CSV_MD_HPP_INCLUDED
