/// @file  csv.cpp
#include "csv.hpp"

namespace render_csv
{

    [[nodiscard]] static auto parseCsvNoHeaders(StringView input)
        -> TableParserResult
    {
        // TODO
        return {};
    }

    [[nodiscard]] static auto parseCsvWithHeaders(StringView input)
        -> TableParserResult
    {
        // TODO
        return {};
    }

    auto makeCsvParser(ExtractFirstRowAsHeaders extractFirstRowAsHeaders)
        -> TableParser
    {
        switch (extractFirstRowAsHeaders) {
        case ExtractFirstRowAsHeaders::No:
            return parseCsvNoHeaders;

        case ExtractFirstRowAsHeaders::Yes:
            return parseCsvWithHeaders;
        }

        return {};
    }

}