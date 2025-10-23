/// @file  config.cpp
#include "config.hpp"
#include "string_operations_fwd.hpp"
#include <print>

namespace render_csv
{

    auto readCommandLineArguments(std::span<char const* const> args)
        -> CommandLineArguments
    {
        CommandLineArguments result {};
        auto& data { result.configData };
        auto& log  { result.errorLog   };
        
        ConfigData::FileGroup current {};
        auto  many { false };

        for (StringView arg: args) {
            std::println("TODO: parse argument {}\n", arg);
            // TODO
        }

        return result;
    }

}
