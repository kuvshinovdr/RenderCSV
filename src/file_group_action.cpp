/// @file  file_group_action.cpp
#include "file_group_action.hpp"
#include "file_group_action_details.hpp"

namespace render_csv
{

    constexpr auto FileSaveError { "File save error"sv };
    constexpr auto FileGroupFail { "Failed to process the file group"sv };

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