/// @file  html.cpp
#include "html.hpp"
#include "table_formatter_utils.hpp"

namespace render_csv
{

    auto detail::htmlize(StringView input)
        -> String
    {
        auto result { String{} };
        result.reserve(input.size());

        for (auto c : input)
        {
            switch (c)
            {
            case '<':  result += "&lt;";   break;
            case '>':  result += "&gt;";   break;
            case '&':  result += "&amp;";  break;
            case '\n': result += "<br>\n"; break;
            default:   result += c;        break;
            }
        }

        return result;
    }

    [[nodiscard]] auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
        auto  result { TableFormatterResult{} };
        auto& output { result.output };
        
        output += "<table>\n";
        
        if (!data.caption.empty()) {
            output += "  <caption>" + detail::htmlize(data.caption) + "</caption>\n";
        }
        
        if (!data.headers.empty()) {
            output += "  <tr>\n";
            for (auto const& header : data.headers) {
                output += "    <th>" + detail::htmlize(header) + "</th>\n";
            }
            
            output += "  </tr>\n";
        }

        for (auto const& row : data.body) {
            output += "  <tr>\n";
            
            for (auto const& cell : row) {
                output += "    <td>" + detail::htmlize(cell) + "</td>\n";
            }
            
            output += "  </tr>\n";
        }
        
        output += "</table>";
        
        return result;
    }

    [[nodiscard]] static auto formatHtmlFull(TableData const& data, StringView css = {})
        -> TableFormatterResult
    {
        auto result { TableFormatterResult{} };

        // Получение html таблицы
        auto partialResult { formatHtmlPartial(data) };
        result.warnings = partialResult.warnings;
        
        // Строка со структурой документа
        auto& fullHtml { result.output };

        fullHtml += "<!DOCTYPE html>";
        fullHtml += "<meta charset=\"UTF-8\">";
        
        fullHtml += "<html>";
        fullHtml += "<head>";
        // Заголовок
        if (!data.caption.empty()) {
        fullHtml += "<title>" + detail::htmlize(data.caption) + "</title>"; 
        }
        //Подключения css
        if (!css.empty()) {
        fullHtml += "<style>";
        fullHtml += String(css);
        fullHtml += "</style>";
        }

        fullHtml += "</head>";
        fullHtml += "<body>";

        // Вставка результата formatHtmlPartial
        fullHtml += partialResult.output;
        
        // Завершение документа
        fullHtml += "</body>";
        fullHtml += "</html>";

        return result;
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
