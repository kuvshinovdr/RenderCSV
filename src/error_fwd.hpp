/// @file  error_fwd.hpp
/// @brief Объявление ErrorCode.
#ifndef RENDER_CSV_ERROR_FWD_HPP_INCLUDED
#define RENDER_CSV_ERROR_FWD_HPP_INCLUDED

#include <expected>
#include <system_error>

namespace render_csv
{

    using ErrorCode =
        std::error_code;

    template <typename T>
    using Expected =
        std::expected<T, ErrorCode>;

}

#endif//RENDER_CSV_ERROR_FWD_HPP_INCLUDED
