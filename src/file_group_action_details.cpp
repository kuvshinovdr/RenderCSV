/// @file  file_group_action_details.cpp

#include "file_group_action_details.hpp"
#include "file_to_string.hpp"
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

    // Попробовать загрузить все файлы в строки.
    auto loadFileGroupData(ConfigData::FileGroup const& fg) noexcept
        -> FileGroupResult
    {
        // TODO
        return {};
    }

    // Антипаттерн завистливая функция?
    bool processFileGroupData(FileGroupResult& result)
    {
        // TODO
        return false;
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
