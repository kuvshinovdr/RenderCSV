#include "config.hpp"
#include <array>
#include <doctest.h>

TEST_SUITE("config")
{
    
    TEST_CASE("no args")
    {
        auto result { render_csv::parseCommandLineArguments({}) };

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

        auto result { render_csv::parseCommandLineArguments(args) };

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

        auto result { render_csv::parseCommandLineArguments(args) };

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == true);
        CHECK(data.fileGroups.empty());
    }

    TEST_CASE("--in")
    {
        auto args = std::array 
        {
            "--in",
            "test_filename"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        REQUIRE(data.fileGroups.size() == 1);
        REQUIRE(data.fileGroups[0].inputs.size() == 1);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename");
    }

    TEST_CASE("-i")
    {
        auto args = std::array 
        {
            "-i",
            "test_filename"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename");
    }

    TEST_CASE("--md")
    {
        auto args = std::array 
        {
            "--md",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        REQUIRE(data.fileGroups.size() == 1);
        REQUIRE(data.fileGroups[0].inputs.size() == 1);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Markdown);
        CHECK(data.fileGroups[0].mdType == "gfm");
    }

    TEST_CASE("--md=")
    {
        auto args = std::array 
        {
            "--md=",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Markdown);
        CHECK(data.fileGroups[0].mdType == "gfm");
    }

    TEST_CASE("--md=gfm")
    {
        auto args = std::array 
        {
            "--md=gfm",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Markdown);
        CHECK(data.fileGroups[0].mdType == "gfm");
    }

    TEST_CASE("--md=asd")
    {
        auto args = std::array 
        {
            "--md=asd",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Markdown);
        CHECK(data.fileGroups[0].mdType == "asd");
    }

    TEST_CASE("--html")
    {
        auto args = std::array 
        {
            "--html",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Html);
        CHECK(data.fileGroups[0].htmlType == "full");
    }

    TEST_CASE("--html=")
    {
        auto args = std::array 
        {
            "--html=",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Html);
        CHECK(data.fileGroups[0].htmlType == "full");
    }

    TEST_CASE("--html=part")
    {
        auto args = std::array 
        {
            "--html=part",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Html);
        CHECK(data.fileGroups[0].htmlType == "part");
    }

    TEST_CASE("--html=full")
    {
        auto args = std::array 
        {
            "--html=full",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Html);
        CHECK(data.fileGroups[0].htmlType == "full");
    }

    TEST_CASE("--html=full-styled")
    {
        auto args = std::array 
        {
            "--html=full-styled",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Html);
        CHECK(data.fileGroups[0].htmlType == "full-styled");
    }

    TEST_CASE("--caption")
    {
        auto args = std::array 
        {
            "--in",
            "test_filename",
            "--caption",
            "test_captionname"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename");
        CHECK(data.fileGroups[0].caption == "test_captionname");
    }

    TEST_CASE("-c")
    {
        auto args = std::array 
        {
            "--in",
            "test_filename",
            "-c",
            "test_captionname"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename");
        CHECK(data.fileGroups[0].caption == "test_captionname");
    }

    TEST_CASE("--many")
    {
        auto args = std::array 
        {
            "--many",
            "--in",
            "test_filename_1",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        REQUIRE(data.fileGroups.size() == 1);
        REQUIRE(data.fileGroups[0].inputs.size() == 2);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].inputs[1] == "test_filename_2");
    }

    TEST_CASE("--out")
    {
        auto args = std::array 
        {
            "--md",
            "--in",
            "test_filename_1",
            "--out",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Markdown);
        CHECK(data.fileGroups[0].mdType == "gfm");
    }

    TEST_CASE("-o")
    {
        auto args = std::array 
        {
            "--html",
            "--in",
            "test_filename_1",
            "-o",
            "test_filename_2"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].out == "test_filename_2");
        CHECK(data.fileGroups[0].outputFormat == render_csv::ConfigData::FileGroup::OutputFormat::Html);
        CHECK(data.fileGroups[0].htmlType == "full");
    }

    TEST_CASE("--head")
    {
        auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "--head",
            "test_headername"
            
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].head == "test_headername");
    }

    TEST_CASE("-h")
    {
        auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "-h",
            "test_headername"
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].head == "test_headername");
    }

    TEST_CASE("--mid")
    {
        auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "--mid",
            "test_middlename"
            
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].mid == "test_middlename");
    }

    TEST_CASE("-m")
    {
       auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "-m",
            "test_middlename"
            
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].mid == "test_middlename");
    }

    TEST_CASE("--foot")
    {
       auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "--foot",
            "test_footername"
            
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].foot == "test_footername");
    }

    TEST_CASE("-f")
    {
       auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "-f",
            "test_footername"
            
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].foot == "test_footername");
    }

    TEST_CASE("--css")
    {
       auto args = std::array 
        {
            "--in",
            "test_filename_1",
            "--css",
            "test_stylename"
            
        };

        auto result = render_csv::parseCommandLineArguments(args);

        CHECK(result.errorLog.empty());

        auto const& data { result.configData };
        CHECK(data.version == false);
        CHECK(data.help    == false);
        CHECK(data.fileGroups[0].inputs[0] == "test_filename_1");
        CHECK(data.fileGroups[0].css == "test_stylename");
    }
}
