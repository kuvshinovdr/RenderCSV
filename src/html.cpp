/// @file  html.cpp
#include "html.hpp"
#include "table_formatter_utils.hpp"

namespace render_csv
{

    [[nodiscard]] static auto htmlize(StringView input)
        -> String
    {
        String result;
        result.reserve(input.size());

        for (char c : input)
        {
            switch (c)
            {
            case '<':  result += "&lt;";   break;
            case '>':  result += "&gt;";   break;
            case '&':  result += "&amp;";  break;
            case '\n': result += "<BR>";   break;
            default:   result += c;        break;
            }
        }

    return result;
    }

    [[nodiscard]] static auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
        // TODO
        return {};
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