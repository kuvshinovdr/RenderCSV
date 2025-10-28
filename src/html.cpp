/// @file  html.cpp
#include "html.hpp"

namespace render_csv
{

    static auto formatHtmlFull(TableData const& data, StringView css = {})
        -> TableFormatterResult
    {
        // TODO
        return {};
    }

    static auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
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