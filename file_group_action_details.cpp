/// @file  file_group_action_details.cpp

#include "file_group_action_details.hpp"
#include "file_to_string.hpp"
#include "csv.hpp"
#include "md.hpp"
#include "html.hpp"
#include "string_to_file.hpp"
#include "prepend_file.hpp"
#include <format>


namespace render_csv::detail
{

    auto errorMessage(StringView intro, ErrorCode error)
        -> String
    {
        return std::format("{}: ({}) {}", intro, error.value(), error.message());
    }

    auto loadFileGroupData(ConfigData::FileGroup const& fg) noexcept
        -> FileGroupResult
    {
        FileGroupResult result;

        for (const auto& filePath : fg.inputs) {
            std::ifstream file(filePath); 
            if (!file.is_open()) {
            result.errorLog.push_back(errorMessage("Failed to open file",fileGroupResult.error));
                continue;
            }

            std::stringstream buffer;
            buffer << file.rdbuf(); 
            result.data.push_back(buffer.str()); 
            file.close(); 
        }
        return result; 
    }


     bool processFileGroupData(ConfigData::FileGroup const& fg, FileGroupResult& result)
	{

	auto parser = makeCsvParser();;
	unique_ptr<Formatter> formatter;

	if (fg.outputFormat == "markdown") {
        formatter = makeMarkdownFormatter();
    } else if (fg.outputFormat == "html") {
        formatter = makeHtmlFormatter();      
    } else {
        result.errorLog.push_back(errorMessage("Unsupported output format", formatter.error));
        return false;
    }

    result.output.append(fg.head);

    for (const auto& input : fg.inputs) {
        auto parseResult = parser.parse(input);
        if (!parseResult.success) {
            result.errorLog.push_back(errorMessage("Error parsing input file", parseResult.error));
            continue;
        }

        auto formatResult = formatter->format(parseResult.data);
        if (!formatResult.success) {
            result.errorLog.push_back(errorMessage("Error formatting parsed data", formatResult.error));
            continue;
        }

       
        if (!result.output.empty()) {
            result.output.append(fg.mid); 
        }
        result.output.append(formatResult.data);
    }

   
    result.output.append(fg.foot);

    return true; 
}

    auto saveFileGroupOutput(FilePath const&                       filePath,
        StringView                            output,
        ConfigData::FileGroup::OutputFileMode mode
    ) noexcept
        -> Expected<void>
    {
        auto stringToFileMode { FileUpdateMode::Rewrite };

        switch (mode) {
            using enum ConfigData::FileGroup::OutputFileMode;
        case Unspecified:
            stringToFileMode = FileUpdateMode::OnlyNew;
            break;

        case Overwrite:
            stringToFileMode = FileUpdateMode::Rewrite;
            break;

        case Append:
            stringToFileMode = FileUpdateMode::Append;
            break;

        case Prepend:
            return prependFile(filePath, output);
        }

        return stringToFile(filePath, output, stringToFileMode);
    }

}
