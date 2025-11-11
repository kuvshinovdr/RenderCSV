/// @file  config.cpp
#include "config.hpp"
#include "string_operations_fwd.hpp"

namespace render_csv
{

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
        if (!sv.starts_with('-')) {
            return ArgumentKind::None;
        }

        sv.remove_prefix(1);
        if (!sv.starts_with('-')) {
            return ArgumentKind::Brief;
        }

        sv.remove_prefix(1);
        return ArgumentKind::Full;
    }

    namespace full
    {
        // В алфавитном порядке:
        constexpr auto Append       { "append"sv      };
        constexpr auto Caption      { "caption"sv     };
        constexpr auto Css          { "css"sv         };
        constexpr auto Footer       { "foot"sv        };
        constexpr auto Header       { "head"sv        };
        constexpr auto Help         { "help"sv        };
        constexpr auto Html         { "html"sv        };
        constexpr auto In           { "in"sv          };
        constexpr auto Many         { "many"sv        };
        constexpr auto Markdown     { "md"sv          };
        constexpr auto Middle       { "mid"sv         };
        constexpr auto Out          { "out"sv         };
        constexpr auto Overwrite    { "overwrite"sv   };
        constexpr auto Prepend      { "prepend"sv     };
        constexpr auto Version      { "version"sv     };
    }

    namespace brief
    {
        // В алфавитном порядке:
        constexpr auto Caption      { 'c' };
        constexpr auto Footer       { 'f' };
        constexpr auto Header       { 'h' };
        constexpr auto In           { 'i' };
        constexpr auto Middle       { 'm' };
        constexpr auto Out          { 'o' };
    }
    

    auto parseCommandLineArguments(CstringSpan args)
        -> CommandLineArguments
    {
        auto  result  { CommandLineArguments{} };

        auto& data    { result.configData };
        auto& log     { result.errorLog   };
        
        auto current_group { ConfigData::FileGroup{} };
        auto many    { false };

        for (auto i = 0zu; i < args.size(); ++i) {
            auto current { StringView{args[i]} };
            auto next    { StringView{}        };
            
            if (i + 1 < args.size()) {
                next = args[i + 1];
            }

            switch (argumentKind(current)) {
            case ArgumentKind::Full:
                if (current == full::Help){

                    data.help = true;

                }
                else if (current == full::Version)
                {
                    
                    data.version = true;

                }
                else if (current.starts_with(full::Markdown))
                {

                    current_group.outputFormat = ConfigData::FileGroup::OutputFormat::Markdown;
                    current_group.mdType = "gfm";

                    auto eqPos = current.find('=');
                    if (eqPos != ""sv.npos){
                        auto value = current.substr(eqPos + 1);
                        if (!value.empty()){
                            current_group.mdType = String(value);
                        }
                    }

                }
                else if (current.starts_with(full::Html))
                {
                    
                    current_group.outputFormat = ConfigData::FileGroup::OutputFormat::Html;
                    current_group.htmlType = "full";
                    
                    auto eqPos = current.find('=');
                    if (eqPos != ""sv.npos){
                        auto value = current.substr(eqPos + 1);
                        if (value == "part"sv) {
                            current_group.htmlType = "part";
                        } else if (value == "full"sv) {
                            current_group.htmlType = "full";
                        } else if (value == "full-styled"sv) {
                            current_group.htmlType = "full-styled";
                        } else {
                            current_group.htmlType = "full";
                        }
                    }

                } 
                else if (current == full::Overwrite) 
                {
                
                    current_group.outputFileMode = ConfigData::FileGroup::OutputFileMode::Overwrite;

                } 
                else if (current == full::Append) {

                    current_group.outputFileMode = ConfigData::FileGroup::OutputFileMode::Append;

                } 
                else if (current == full::Prepend) {
                    
                    current_group.outputFileMode = ConfigData::FileGroup::OutputFileMode::Prepend;

                } 
                else if (current == full::Many) {

                    many = true;

                }
                else if (current == full::Caption)
                {

                    if (!next.empty()){
                        current_group.caption = next;
                        ++i;
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --caption"sv});
                    }

                }
                else if (current == full::In)
                {

                    if (!next.empty()){
                        current_group.in.push_back(String(next));
                        ++i;
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --in"sv});
                    }

                }
                else if (current == full::Out)
                {

                    if (!next.empty())
                    {
                        if (current_group.outputFormat == ConfigData::FileGroup::OutputFormat::Unspecified){
                            log.push_back({current, "Missing output format for --out"sv});
                        }
                        current_group.out = next;
                        ++i;
                        if (many){
                            data.fileGroups.push_back(current_group);
                            current_group = ConfigData::FileGroup{};
                            many = false;
                        }
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --out"sv});
                    }
                }
                else if(current == full::Header)
                {
                    
                    if (!next.empty()){
                        current_group.head = next;
                        ++i;
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --head"sv});
                    }

                }
                else if(current == full::Middle)
                {
                    
                    if (!next.empty()){
                        current_group.mid = next;
                        ++i;
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --mid"sv});
                    }

                }
                else if(current == full::Footer)
                {
                    
                    if (!next.empty()){
                        current_group.foot = next;
                        ++i;
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --foot"sv});
                    }

                }
                else if(current == full::Css)
                {
                    
                    if (!next.empty()){
                        current_group.css = next;
                        ++i;
                    }
                    else
                    {
                        log.push_back({current, "Missing value for --css"sv});
                    }

                }
                else
                {
                    log.push_back({current, "Unknown argument"sv});
                }
                break;

            case ArgumentKind::Brief:
                for (auto j = 0zu; j < current.size(); ++j){
                    switch (current[j]){
                    case brief::Caption:
                        if (!next.empty()){
                            current_group.caption = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -c"sv});
                        }
                        break;
                        
                    case brief::In:
                        if (!next.empty()){
                            current_group.in.push_back(String(next));
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -i"sv});
                        }
                        break;
                        
                    case brief::Out:
                        if (!next.empty())
                        {
                            if (current_group.outputFormat == ConfigData::FileGroup::OutputFormat::Unspecified){
                                log.push_back({current, "Missing output format for -o"sv});
                            }
                            current_group.out = next;
                            ++i;
                            if (many){
                                data.fileGroups.push_back(current_group);
                                current_group = ConfigData::FileGroup{};
                                many = false;
                            }
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -o"sv});
                        }
                        break;

                    case brief::Header:
                        if (!next.empty()){
                            current_group.head = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -h"sv});
                        }
                        break;
                       
                    case brief::Middle:
                        if (!next.empty()){
                            current_group.mid = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -m"sv});
                        }
                        break;

                    case brief::Footer:
                        if (!next.empty()){
                            current_group.foot = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -f"sv});
                        }
                        break;
                    
                    default:
                        log.push_back({current, "Unknown brief argument"sv});
                    }
                }
                break;

            default:
                current_group.in.push_back(String(current));
                if (!many){
                    data.fileGroups.push_back(current_group);
                    current_group = ConfigData::FileGroup{};
                    if (!data.fileGroups.empty()) {
                        current_group.outputFormat = data.fileGroups.back().outputFormat;
                        current_group.outputFileMode = data.fileGroups.back().outputFileMode;
                    }
                }
            }
        }
        if (!current_group.in.empty()){
            data.fileGroups.push_back(current_group);
        }

        return result;
    }

}
