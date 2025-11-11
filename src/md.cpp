/// @file  md.cpp
#include "md.hpp"
#include "table_formatter_utils.hpp"

namespace render_csv
{

    // О формате GFM см.: https://github.github.com/gfm/
    [[nodiscard]] static auto formatMarkdownGfm(TableData const&)
        -> TableFormatterResult
    {
        // TODO
        return {};
    }

    auto makeMarkdownFormatter(MarkdownKind kind)
        -> TableFormatter
    {
        switch (kind) {
        case MarkdownKind::GithubFlavored:
            return formatMarkdownGfm;
        }

        return {};
    }

}