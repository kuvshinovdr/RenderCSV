/// @file  prepend_file.cpp
#include "prepend_file.hpp"
#include "file_to_string.hpp"
#include "string_to_file.hpp"

namespace render_csv
{

    auto prependFile(FilePath const& filename, StringView prefix) noexcept
        -> PrependFileResult
    {  auto per = fileToString(filename);
     if (!per.has_value())
         return { per.error() };
     try { *per = std::sting(prefix) + *per };
          catch (std::bad_alloc&) {
              return { std::errc::not_enough_memory };
          }
     auto result = stringToFile(filename, *per);
     if (!result.has_value())
         return { result.error() };
     return {};
    }     
        return {};
    }

}
