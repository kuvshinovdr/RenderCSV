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
            case '\n': result += "<br>\n"; break;
            default: result += c; break;
            }
        }
        return result;
    }

    [[nodiscard]] static auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
        TableFormatterResult result;
        
        result += "<table>\n";
        
        if (!data.caption.empty()) {
            result += "  <caption>" + detail::htmlize(data.caption) + "</caption>\n";
        }
        
        if (!data.headers.empty()) {
            result += "  <tr>\n";
            for (auto const& header : data.headers) {
                result += "    <th>" + detail::htmlize(header) + "</th>\n";
            }
            result += "  </tr>\n";
        }

        for (auto const& row : data.body) {
            result += "  <tr>\n";
            
            for (auto const& cell : row) {
                result += "    <td>" + detail::htmlize(cell) + "</td>\n";
            }
            
            result += "  </tr>\n";
        }
        
        result += "</table>";
        
        return result;
    }

    [[nodiscard]] static auto formatHtmlFull(TableData const& data, StringView css = {})
        -> TableFormatterResult
    {
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