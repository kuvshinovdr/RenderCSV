/// @file  md.cpp
#include "md.hpp"

namespace render_csv
{

    // https://github.github.com/gfm/
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