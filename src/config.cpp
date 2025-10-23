/// @file  config.cpp
#include "config.hpp"
#include "string_operations_fwd.hpp"
#include <print>

namespace render_csv
{

    auto readCommandLineArguments(int argc, char* argv[])
        -> CommandLineArguments
    {
        CommandLineArguments result {};
        auto& data = result.configData;
        auto& log  = result.errorLog;
        
        ConfigData::FileGroup current {};

        for (int i = 1; i < argc; ++i) {
            StringView arg { argv[i] };
            std::println("TODO: parse argument {}\n", arg);
            // TODO
        }

        return result;
    }

}
