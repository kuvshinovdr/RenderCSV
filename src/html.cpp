/// @file  html.cpp
#include "html.hpp"
#include "table_formatter_utils.hpp"

namespace render_csv
{

    auto detail::htmlize(StringView input)
        -> String
    {
        String result;
        for (char c : input) {
            switch (c) {
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '&': result += "&amp;"; break;
            case '\n': result += "<BR>"; break;
            default: result += c; break;
            }
        }
        return result;
    }

    [[nodiscard]] auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
        auto  result { TableFormatterResult{} };
        auto& output { result.output };
        
        // Начинаем таблицу
        output += "<table>\n";
        
        // Добавляем строки таблицы
        for (auto const& row : data.body) {
            output += "  <tr>\n";
            
            // Добавляем ячейки в строку
            for (auto const& cell : row) {
                output += "    <td>" + detail::htmlize(cell) + "</td>\n";
            }
            
            output += "  </tr>\n";
        }
        
        // Заканчиваем таблицу
        output += "</table>";
        
        return result;
    }

    [[nodiscard]] static auto formatHtmlFull(TableData const& data, StringView css = {})
        -> TableFormatterResult
    {
        // Если css.empty(), то не внедряем CSS, иначе внедряем.
        // TODO
        return {};
    }

    auto makeHtmlFormatter(HtmlKind kind, StringView css)
        -> TableFormatter
    {
        switch (kind) {
        case HtmlKind::Partial:
            return formatHtmlPartial;

        case HtmlKind::Full:
            return [](TableData const& data)
                {
                    return formatHtmlFull(data);
                };

        case HtmlKind::FullWithCss:
            return [css](TableData const& data)
                {
                    return formatHtmlFull(data, css);
                };
        }

        return {};
    }

}