/// @file  config.hpp
/// @brief Класс, отвечающий за настройки программы.
#ifndef RENDER_CSV_CONFIG_HPP_INCLUDED
#define RENDER_CSV_CONFIG_HPP_INCLUDED

#include "string_operations_fwd.hpp"
#include <memory>
#include <vector>
#include <span>

namespace render_csv
{

    struct ConfigData
    {
        bool    help        { false };
        bool    version     { false };

        struct FileGroup
        {
            enum class OutputFormat
            {
                Unspecified,
                Markdown,
                Html,
            };

            OutputFormat    outputFormat    { OutputFormat::Unspecified };
            
            enum class OutputFileMode
            {
                Unspecified,
                Overwrite,
                Append,
                Prepend,
            };
            
            OutputFileMode  outputFileMode  { OutputFileMode::Unspecified };
            
            String  htmlType    {};
            String  mdType      {};
            String  title       {};
            String  out         {};
            String  head        {};
            String  mid         {};
            String  foot        {};
            String  css         {};

            using Inputs =
                std::vector<String>;

            Inputs  in          {};
        };

        using FileGroups =
            std::vector<FileGroup>;

        FileGroups fileGroups   {};
    };

    struct CommandLineArguments
    {
        ConfigData  configData  {};

        struct ErrorLogEntry
        {
            StringView argument {};
            StringView error    {};
            String     details  {};
        };

        using ErrorLog =
            std::vector<ErrorLogEntry>;

        ErrorLog    errorLog    {};
    };

    /// @brief Принять набор аргументов командной строки (нумерация с нуля, все аргументы проверяются).
    [[nodiscard]] auto readCommandLineArguments(std::span<char const* const> args)
        -> CommandLineArguments;

    /// @brief Принять набор аргументов командной строки в стандартной POSIX-форме. 
    [[nodiscard]] inline auto readCommandLineArguments(int argc, char* argv[])
        -> CommandLineArguments
    {
        auto arg { static_cast<char const* const*>(argv) };
        return readCommandLineArguments(std::span(arg + 1, arg + argc));
    }

}

#endif//RENDER_CSV_CONFIG_HPP_INCLUDED
