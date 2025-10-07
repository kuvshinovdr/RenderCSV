module utils;

import std;

namespace render_csv::utils
{

    auto fileToString(FilePath const& filename) noexcept
        -> FileToStringResult
    {
        return {};
    }


    auto stringToFile(FilePath const& filename, 
                      StringView      data, 
                      FileUpdateMode  mode
                     ) noexcept -> StringToFileResult
    {
        return {};
    }

}