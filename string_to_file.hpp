/// @file  string_to_file.hpp
/// @brief Функция записи строки в файл.
#ifndef RENDER_CSV_STRING_TO_FILE_HPP_INCLUDED
#define RENDER_CSV_STRING_TO_FILE_HPP_INCLUDED

#include "file_operations_fwd.hpp"
#include "string_operations_fwd.hpp"

namespace render_csv
{

    using StringToFileResult =
        std::expected<void, ErrorCode>;

    enum class FileUpdateMode
    {
        Rewrite,
        Append,
    };

    /// @brief Записать данные StringView в заданный файл как двоичные данные.
    auto stringToFile(
        FilePath const& filename, 
        StringView      data, 
        FileUpdateMode  mode = FileUpdateMode::Rewrite
        ) noexcept -> StringToFileResult;

}

#endif//RENDER_CSV_STRING_TO_FILE_HPP_INCLUDED
