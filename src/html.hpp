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

    /// @brief Вид генерации HTML.
    enum class HtmlKind
    {
        Partial,
        Full,
        FullWithCss,
    };

    /// @brief Создать генератор HTML нужного вида, сразу связав с CSS-файлом (загруженным в строку), если он есть.
    ///        Строка, на которую ссылается css, должна существовать во время вызова возвращённой функции.
    [[nodiscard]] auto makeHtmlFormatter(HtmlKind kind, StringView css = {})
        -> TableFormatter;

}

#endif//RENDER_CSV_HTML_HPP_INCLUDED
