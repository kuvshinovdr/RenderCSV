#include "config.hpp"
#include <array>
#include <doctest.h>

TEST_SUITE("config")
{
    
    TEST_CASE("no args")
    {
        auto result = render_csv::readCommandLineArguments({});

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups.empty()); 
    }

    TEST_CASE("--version")
    {
        auto args = std::array 
        {
            "--version",
        };

        auto result = render_csv::readCommandLineArguments(args);

        CHECK(result.errorLog.empty());
        
        auto const& data { result.configData };
        CHECK(data.version == true);
        CHECK(data.help    == false);
        CHECK(data.fileGroups.empty());
    }

    TEST_CASE("--help")
    {
        auto args = std::array 
        {
            "--help",
        };

        auto result = render_csv::readCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == true);
        CHECK(data.fileGroups.empty());
    }
	
}
