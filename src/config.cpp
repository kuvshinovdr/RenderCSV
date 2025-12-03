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
        
        auto currentGroup { ConfigData::FileGroup{} };
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

                    currentGroup.outputFormat = ConfigData::FileGroup::OutputFormat::Markdown;
                    currentGroup.mdType = "gfm";

                    auto eqPos = current.find('=');
                    if (eqPos != ""sv.npos){
                        auto value = current.substr(eqPos + 1);
                        if (!value.empty()){
                            currentGroup.mdType = String(value);
                        }
                    }

                }
                else if (current.starts_with(full::Html))
                {
                    
                    currentGroup.outputFormat = ConfigData::FileGroup::OutputFormat::Html;
                    currentGroup.htmlType = "full";
                    
                    auto eqPos = current.find('=');
                    if (eqPos != current.npos){
                        auto value = current.substr(eqPos + 1);
                        if (value == "part"sv) {
                            currentGroup.htmlType = "part";
                        } else if (value == "full"sv) {
                            currentGroup.htmlType = "full";
                        } else if (value == "full-styled"sv) {
                            currentGroup.htmlType = "full-styled";
                        } else {
                            currentGroup.htmlType = "full";
                        }
                    }

                } 
                else if (current == full::Overwrite) 
                {
                
                    currentGroup.outputFileMode = ConfigData::FileGroup::OutputFileMode::Overwrite;

                } 
                else if (current == full::Append) {

                    currentGroup.outputFileMode = ConfigData::FileGroup::OutputFileMode::Append;

                } 
                else if (current == full::Prepend) {
                    
                    currentGroup.outputFileMode = ConfigData::FileGroup::OutputFileMode::Prepend;

                } 
                else if (current == full::Many) {

                    many = true;

                }
                else if (current == full::Caption)
                {

                    if (!next.empty()){
                        currentGroup.caption = next;
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
                        currentGroup.inputs.push_back(String(next));
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
                        if (currentGroup.outputFormat == ConfigData::FileGroup::OutputFormat::Unspecified){
                            log.push_back({current, "Missing output format for --out"sv});
                        }
                        currentGroup.out = next;
                        ++i;
                        if (many){
                            data.fileGroups.push_back(currentGroup);
                            currentGroup = ConfigData::FileGroup{};
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
                        currentGroup.head = next;
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
                        currentGroup.mid = next;
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
                        currentGroup.foot = next;
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
                        currentGroup.css = next;
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
                            currentGroup.caption = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -c"sv});
                        }
                        break;
                        
                    case brief::In:
                        if (!next.empty()){
                            currentGroup.inputs.push_back(String(next));
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
                            if (currentGroup.outputFormat == ConfigData::FileGroup::OutputFormat::Unspecified){
                                log.push_back({current, "Missing output format for -o"sv});
                            }
                            currentGroup.out = next;
                            ++i;
                            if (many){
                                data.fileGroups.push_back(currentGroup);
                                currentGroup = ConfigData::FileGroup{};
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
                            currentGroup.head = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -h"sv});
                        }
                        break;
                       
                    case brief::Middle:
                        if (!next.empty()){
                            currentGroup.mid = next;
                            ++i;
                        }
                        else
                        {
                            log.push_back({current, "Missing value for -m"sv});
                        }
                        break;

                    case brief::Footer:
                        if (!next.empty()){
                            currentGroup.foot = next;
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
                currentGroup.inputs.push_back(String(current));
                if (!many){
                    data.fileGroups.push_back(currentGroup);
                    currentGroup = ConfigData::FileGroup{};
                    if (!data.fileGroups.empty()) {
                        currentGroup.outputFormat = data.fileGroups.back().outputFormat;
                        currentGroup.outputFileMode = data.fileGroups.back().outputFileMode;
                    }
                }
            }
        }
        if (!currentGroup.inputs.empty()){
            data.fileGroups.push_back(currentGroup);
        }

        return result;
    }

}
