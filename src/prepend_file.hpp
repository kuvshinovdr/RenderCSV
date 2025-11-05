/// @file  prepend_file.hpp
/// @brief Функция записи строки в начало файла.
#ifndef RENDER_CSV_PREPEND_FILE_HPP_INCLUDED
#define RENDER_CSV_PREPEND_FILE_HPP_INCLUDED

#include "error_fwd.hpp"
#include "file_operations_fwd.hpp"
#include "string_operations_fwd.hpp"

namespace render_csv
{

    using PrependFileResult = Expected<void>;

    /// @brief Прочитать файл, добавить строку в его начало, записать результат в заданный файл.
    auto prependFile(FilePath const& filename, StringView prefix) noexcept
        -> PrependFileResult;

}

#endif//RENDER_CSV_PREPEND_FILE_HPP_INCLUDED
