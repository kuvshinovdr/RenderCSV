/// @file  table_formatter_utils.cpp

// Используется библиотека https://github.com/nemtrif/utfcpp
#include <utf8.h>
#include "table_formatter_utils.hpp"

namespace render_csv
{

    // Виды предупреждений:
    // 1. Строки разной ширины в столбцах -- на каждой строке, количество столбцов в которой отличается от предыдущей.
    // 2. Количество строк и суммы ширин столбцов каждой строки в символах должны помещаться в int32_t.
    // 3. Строки не содержат корректную UTF-8.
    auto simpleValidate(TableData const& data)
        -> TableFormatterResult::Log
    {
        // TODO
        // utf8::is_valid для проверки корректности UTF-8 данных
        return {};
    }

    auto computeColumnWidthsUtf8(TableData const& data)
        -> TableColumnWidths
    {
        // TODO
        // utf8::distance для вычисления количества кодовых позиций
        return {};
    }

}
