#include "html.hpp"
#include <doctest.h>

namespace render_csv
{
    auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult;
}

using namespace std::literals;
using namespace render_csv;

TEST_SUITE("html")
{
    
    TEST_CASE("formatHtmlPartial")
    {
        auto const body
        {
            TableData::Body
            {
                { "alpha", "beta"  },
                { "gamma", "delta" },
            }
        };

        auto const expected
        {
            "<table>\n"
            "  <tr>\n"
            "    <td>alpha</td>\n"
            "    <td>beta</td>\n"
            "  </tr>\n"
            "  <tr>\n"
            "    <td>gamma</td>\n"
            "    <td>delta</td>\n"
            "  </tr>\n"
            "</table>"s
        };

        auto result { formatHtmlPartial(TableData{.body = body})};

        CHECK(result.output == expected);
    }
	
}
