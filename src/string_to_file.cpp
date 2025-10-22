/// @file  string_to_file.cpp
#include "string_to_file.hpp"
#include <fstream>

namespace render_csv
{

    [[nodiscard]] static auto toIosMode(FileUpdateMode mode) noexcept
        -> std::ios_base::openmode
    {
        switch (mode) {
        case FileUpdateMode::Rewrite:
            return std::ios::out | std::ios::binary;
        case FileUpdateMode::Append:
            return std::ios::out | std::ios::binary | std::ios::app;
        }

        std::unreachable();
    }

    auto stringToFile(FilePath const& filename, 
        StringView      data, 
        FileUpdateMode  mode
    ) noexcept -> StringToFileResult
    {
        // TODO: свой класс категории ошибок
        std::ofstream file(filename, toIosMode(mode));
        if (!file.is_open()) {
            return std::unexpected(std::make_error_code(std::errc::read_only_file_system));
        }

        if (std::cmp_greater(data.size(), std::numeric_limits<std::streamsize>::max())) {
            return std::unexpected(std::make_error_code(std::errc::value_too_large));
            // Эту ситуацию можно решить без ошибки, но её возникновение в реальности невероятно.
        }

        file.write(data.data(), static_cast<std::streamsize>(data.size()));
        if (file.bad()) {
            return std::unexpected(std::make_error_code(std::errc::interrupted));
        }

        return {};
    }

}
