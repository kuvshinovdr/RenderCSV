/// @file  file_operations_fwd.hpp
/// @brief Общие объявления для операций с файлами.
#ifndef RENDER_CSV_FILE_OPERATIONS_FWD_HPP_INCLUDED
#define RENDER_CSV_FILE_OPERATIONS_FWD_HPP_INCLUDED

#include <filesystem>
#include <expected>

namespace render_csv
{

    using FilePath =
        std::filesystem::path;

    using ErrorCode =
        std::error_code;

}

#endif//RENDER_CSV_FILE_OPERATIONS_FWD_HPP_INCLUDED
