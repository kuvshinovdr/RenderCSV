/// @file  file_to_string.hpp
/// @brief Функция чтения файла в строку.
#ifndef RENDER_CSV_FILE_TO_STRING_HPP_INCLUDED
#define RENDER_CSV_FILE_TO_STRING_HPP_INCLUDED

#include "error_fwd.hpp"
#include "file_operations_fwd.hpp"
#include "string_operations_fwd.hpp"

namespace render_csv
{

    using FileToStringResult = Expected<String>;

    /// @brief Прочитать заданный файл в память целиком как двоичные данные и вернуть как объект String. 
    [[nodiscard]] auto fileToString(FilePath const& filename) noexcept
        -> FileToStringResult;

}

#endif//RENDER_CSV_FILE_TO_STRING_HPP_INCLUDED
