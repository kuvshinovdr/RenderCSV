/// @file  file_group_action.cpp
#include "file_group_action.hpp"
#include "file_to_string.hpp"
#include "string_to_file.hpp"
#include "error_fwd.hpp"
#include <format>


namespace render_csv
{

    constexpr auto FileLoadError { "File load error"sv };
    constexpr auto FileSaveError { "File save error"sv };
    constexpr auto FileGroupFail { "Failed to process the file group"sv };

    auto detail::loadFileGroupData(ConfigData::FileGroup const& fg) noexcept
        -> FileGroupResult
    {
        // TODO
        return {};
    }

    [[nodiscard]] static auto errorMessage(StringView intro, ErrorCode error)
        -> String
    {
        return std::format("{}: ({}) {}", intro, error.value(), error.message());
    }

    // Антипаттерн завистливая функция?
    bool detail::processFileGroupData(FileGroupResult& result)
    {
        // TODO
        return false;
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
        
        auto  saved  { stringToFile(fg.out, result.output )};
        if (!saved) {
            errors.push_back(errorMessage(FileSaveError, saved.error()));
        }
        
        return result;
    }

}