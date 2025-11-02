/// @file  html.hpp
/// @brief Класс записи HTML-файла.
#ifndef RENDER_CSV_HTML_HPP_INCLUDED
#define RENDER_CSV_HTML_HPP_INCLUDED

#include "table_formatter.hpp"

namespace render_csv
{

    namespace detail
    {
        //  Для упрощения тестирования.
        /// @brief Выполнить замену специальных символов (<, >, & и т.п.) на задающие их последовательности HTML.
        [[nodiscard]] auto htmlize(StringView)
            -> String;
    }

    enum class HtmlKind
    {
        Partial,
        Full,
        FullWithCss,
    };

    [[nodiscard]] auto makeHtmlFormatter(HtmlKind kind, StringView css = {})
        -> TableFormatter;

}

#endif//RENDER_CSV_HTML_HPP_INCLUDED
