/// @file  config.cpp
#include "config.hpp"
#include "string_operations_fwd.hpp"
#include <print>

namespace render_csv
{

    using namespace std::literals;

    enum class ArgumentKind
    {
        None,   // не начинается на -
        Brief,  // на -
        Full,   // на --
    };

    // Функция проверяет префиксы -- и - у параметра sv, классифицируя вид аргумента, и удаляет эти префиксы. 
    [[nodiscard]] inline auto argumentKind(StringView& sv)
        -> ArgumentKind
    {
        if (sv.starts_with('-')) {
            sv.remove_prefix(1);
            if (sv.starts_with('-')) {
                sv.remove_prefix(1);
                return ArgumentKind::Full;
            }

            return ArgumentKind::Brief;
        }

        return ArgumentKind::None;
    }

    namespace full
    {
        constexpr auto Version      { "version"sv     };
        constexpr auto Help         { "help"sv        };
        constexpr auto Overwrite    { "overwrite"sv   };
        constexpr auto Append       { "append"sv      };
        constexpr auto Prepend      { "prepend"sv     };
        constexpr auto Markdown     { "md"sv          };
        constexpr auto Html         { "html"sv        };
        constexpr auto Many         { "many"sv        };
        constexpr auto In           { "in"sv          };
        constexpr auto Out          { "out"sv         };
        constexpr auto Title        { "title"sv       };
        constexpr auto Header       { "head"sv        };
        constexpr auto Footer       { "foot"sv        };
        constexpr auto Middle       { "mid"sv         };
        constexpr auto Css          { "css"sv         };
    }

    namespace brief
    {
        constexpr auto In           { 'i' };
        constexpr auto Out          { 'o' };
        constexpr auto Title        { 't' };
        constexpr auto Header       { 'h' };
        constexpr auto Footer       { 'f' };
        constexpr auto Middle       { 'm' };
    }
    

    auto readCommandLineArguments(CstringSpan args)
        -> CommandLineArguments
    {
        CommandLineArguments result {};

        auto& data { result.configData };
        auto& log  { result.errorLog   };
        
        ConfigData::FileGroup current {};
        auto  many { false };

        for (StringView arg: args) {
            switch (argumentKind(arg)) {
            case ArgumentKind::Full:
                std::println("TODO: parse full argument {}\n", arg);
                // TODO
                break;

            case ArgumentKind::Brief:
                std::println("TODO: parse brief argument {}\n", arg);
                // TODO
                break;

            default:
                std::println("TODO: deal with unknown argument {}\n", arg);
                // TODO
            }
        }

        return result;
    }

}
