/// @file  html.hpp
/// @brief Класс записи HTML-файла.
#ifndef RENDER_CSV_HTML_HPP_INCLUDED
#define RENDER_CSV_HTML_HPP_INCLUDED

#include "table_formatter.hpp"

namespace render_csv
{

    //  Для упрощения тестирования.
    namespace detail
    {
        /// @brief Вычислить длину результата htmlize.
        [[nodiscard]] auto htmlizeLength(StringView) noexcept
            -> std::size_t;

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
