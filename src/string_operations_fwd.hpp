/// @file  string_operations_fwd.hpp
/// @brief Общие объявления для операций со строками.
#ifndef RENDER_CSV_STRING_OPERATIONS_FWD_HPP_INCLUDED
#define RENDER_CSV_STRING_OPERATIONS_FWD_HPP_INCLUDED

#include <string>
#include <string_view>

namespace render_csv
{

    using String =
        std::string;

    using StringView = 
        std::string_view;

    using namespace std::string_literals;
    using namespace std::string_view_literals;

}

#endif//RENDER_CSV_STRING_OPERATIONS_FWD_HPP_INCLUDED
