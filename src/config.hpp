/// @file  config.hpp
/// @brief Функционал, отвечающий за настройки программы.
#ifndef RENDER_CSV_CONFIG_HPP_INCLUDED
#define RENDER_CSV_CONFIG_HPP_INCLUDED

#include "string_operations_fwd.hpp"
#include <vector>
#include <span>

namespace render_csv
{

    /// @brief Данные конфигурации программы.
    struct ConfigData
    {
        bool    help        { false };
        bool    version     { false };

        /// @brief Описание файловой операции с получением одного результата.
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
            String  caption     {};
            String  out         {};
            String  head        {};
            String  mid         {};
            String  foot        {};
            String  css         {};

            using Inputs =
                std::vector<String>;

            Inputs  inputs      {};
        };

        using FileGroups =
            std::vector<FileGroup>;

        FileGroups fileGroups   {};
    };

    /// @brief Результат разбора параметров командной строки: конфигурация и протокол ошибок разбора.
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

    using CstringSpan =
        std::span<char const* const>;

    /// @brief Принять набор аргументов командной строки (нумерация с нуля, все аргументы проверяются).
    [[nodiscard]] auto parseCommandLineArguments(CstringSpan args)
        -> CommandLineArguments;

    /// @brief Принять набор аргументов командной строки в стандартной POSIX-форме. 
    [[nodiscard]] inline auto parseCommandLineArguments(int argc, char const* const* argv)
        -> CommandLineArguments
    {
        return parseCommandLineArguments(CstringSpan(argv + 1, argv + argc));
    }

}

#endif//RENDER_CSV_CONFIG_HPP_INCLUDED
