/// @file  config.hpp
/// @brief Класс, отвечающий за настройки программы.
#ifndef RENDER_CSV_CONFIG_HPP_INCLUDED
#define RENDER_CSV_CONFIG_HPP_INCLUDED

#include "string_operations_fwd.hpp"
#include <memory>
#include <vector>

namespace render_csv
{

    struct ConfigData
    {
        bool    help        { false };
        bool    version     { false };

        struct FileGroup
        {
            using Inputs =
                std::vector<String>;

            bool    md          { false };
            bool    html        { false };
                    
            bool    overwrite   { false };
            bool    append      { false };
            bool    prepend     { false };
            
            String  htmlType    {};
            String  mdType      {};
            String  title       {};
            String  out         {};
            String  head        {};
            String  mid         {};
            String  foot        {};
            String  css         {};

            Inputs  in          {};
        };
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

    [[nodiscard]] auto readCommandLineArguments(int argc, char* argv[])
        -> CommandLineArguments;

}

#endif//RENDER_CSV_CONFIG_HPP_INCLUDED
