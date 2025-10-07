module utils;

import std;

namespace render_csv
{

    auto fileToString(FilePath const& filename) noexcept
        -> FileToStringResult
    {
        // TODO: свой класс категории ошибок
        auto        ec       { std::error_code{} };
        auto const  fileSize { std::filesystem::file_size(filename, ec) };
        
        if (ec) {
            return std::unexpected(ec);
        }

        if (fileSize > std::numeric_limits<std::size_t>::max()) {
            return std::unexpected(std::make_error_code(std::errc::file_too_large));
        }

        auto const  dataSize { static_cast<std::size_t>(fileSize) };
        auto        result   { String{} };
        try {
            result.resize(dataSize);
        }
        catch (...) {
            return std::unexpected(std::make_error_code(std::errc::not_enough_memory));
        }

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
        }

        file.read(result.data(), dataSize);
        if (file.gcount() != dataSize) {
            return std::unexpected(std::make_error_code(std::errc::interrupted));
        }

        return result;
    }

    [[nodiscard]] auto toIosMode(FileUpdateMode mode) noexcept
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

        file.write(data.data(), data.size());
        if (file.bad()) {
            return std::unexpected(std::make_error_code(std::errc::interrupted));
        }

        return {};
    }

}