/// @file  file_group_action.cpp
#include "file_group_action.hpp"
#include <format>

namespace render_csv
{

    using namespace std::literals;

    constexpr auto FileLoadError { "File load error"sv };
    constexpr auto FileSaveError { "File save error"sv };

    auto detail::loadFileGroupData(ConfigData::FileGroup const& fg) noexcept
        -> LoadFileGroupDataResult
    {
        // TODO
        return {};
    }

    [[nodiscard]] static auto errorMessage(StringView intro, ErrorCode error)
        -> String
    {
        return std::format("{}: ({}) {}", intro, error.value(), error.message());
    }

    auto detail::processFileGroupData(LoadedFileGroupData&& data)
        -> FileGroupResult
    {
        // TODO
        return {};
    }

    auto detail::saveFileGroupOutput(ConfigData::FileGroup const& fg, StringView output)
        -> Expected<void>
    {
        // TODO
        return {};
    }

    auto processFileGroup(ConfigData::FileGroup const& fg)
        -> FileGroupResult
    {
        using namespace detail;
        auto loaded { loadFileGroupData(fg) };
        
        if (!loaded) {
            auto  result { FileGroupResult{} };
            auto& errors { result.errorLog   };
            errors.push_back(errorMessage(FileLoadError, loaded.error()));
            return result;
        }

        auto  result { processFileGroupData(std::move(loaded.value())) };
        auto  saved  { saveFileGroupOutput(fg, result.output)          };

        if (!saved) {
            auto& errors { result.errorLog };
            errors.push_back(errorMessage(FileSaveError, saved.error()));
        }
        
        return result;
    }

}