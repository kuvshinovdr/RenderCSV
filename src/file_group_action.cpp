/// @file  file_group_action.cpp
#include "file_group_action.hpp"
#include "file_group_action_details.hpp"
#include "file_to_string.hpp"
#include "string_to_file.hpp"
#include "prepend_file.hpp"
#include "error_fwd.hpp"
#include <format>


namespace render_csv
{

    constexpr auto FileLoadError { "File load error"sv };
    constexpr auto FileSaveError { "File save error"sv };
    constexpr auto FileGroupFail { "Failed to process the file group"sv };

    [[nodiscard]] static auto errorMessage(StringView intro, ErrorCode error)
        -> String
    {
        return std::format("{}: ({}) {}", intro, error.value(), error.message());
    }

    namespace detail
    {

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

    auto processFileGroup(ConfigData::FileGroup const& fg)
        -> FileGroupResult
    {
        using namespace detail;
        
        auto  result { loadFileGroupData(fg) };
        auto& errors { result.errorLog   };
        
        if (!processFileGroupData(result)) {
            errors.emplace_back(FileGroupFail);
            return result;
        }
        
        auto saved  { saveFileGroupOutput(fg.out, result.output, fg.outputFileMode) };
        
        if (!saved) {
            errors.push_back(errorMessage(FileSaveError, saved.error()));
        }
        
        return result;
    }

}