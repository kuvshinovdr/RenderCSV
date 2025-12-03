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
    
    TEST_CASE("formatHtmlPartial/no caption/no headers")
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


    TEST_CASE("formatHtmlPartial/caption/headers")
    {
        auto const body
        {
            TableData::Body
            {
                { "alpha", "beta", "xxx", "yyy" },
                { "gamma", "delta", "zzz" },
                { "epsilon", "zeta" },
            }
        };

        auto const expected
        {
            "<table>\n"
            "  <caption>Test Table</caption>\n"
            "  <tr>\n"
            "    <th>Column 1</th>\n"
            "    <th>Column 2</th>\n"
            "  </tr>\n"
            "  <tr>\n"
            "    <td>alpha</td>\n"
            "    <td>beta</td>\n"
            "    <td>xxx</td>\n"
            "    <td>yyy</td>\n"
            "  </tr>\n"
            "  <tr>\n"
            "    <td>gamma</td>\n"
            "    <td>delta</td>\n"
            "    <td>zzz</td>\n"
            "  </tr>\n"
            "  <tr>\n"
            "    <td>epsilon</td>\n"
            "    <td>zeta</td>\n"
            "  </tr>\n"
            "</table>"s
        };

        auto result 
        { 
            formatHtmlPartial(TableData
                {
                    .caption = "Test Table",
                    .headers = { "Column 1", "Column 2" },
                    .body = body
                })
        };

        CHECK(result.output == expected);
    }
	
}
using render_csv::detail::htmlize;

TEST_SUITE("htmlize")
{
    TEST_CASE("htmlize/basic replacements")
    {
        CHECK(htmlize("<") == "&lt;");
        CHECK(htmlize(">") == "&gt;");
        CHECK(htmlize("&") == "&amp;");
    }

    TEST_CASE("htmlize/newline")
    {
        CHECK(htmlize("a\nb") == "a<br>\r\nb");
    }

    TEST_CASE("htmlize/no changes")
    {
        CHECK(htmlize("hello") == "hello");
        CHECK(htmlize("12345") == "12345");
    }

    TEST_CASE("htmlize/mixed string")
    {
        auto const input =
            "<tag>\n&hello <world>\r";

        auto const expected =
            "&lt;tag&gt;<br>\r\n"
            "&amp;hello &lt;world&gt;"s;

        CHECK(htmlize(input) == expected);
    }

    TEST_CASE("htmlize/empty string")
    {
        CHECK(htmlize("") == "");
    }
}

