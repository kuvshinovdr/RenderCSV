/// @file  file_group_action_details.cpp

#include "file_group_action_details.hpp"
#include "file_to_string.hpp"
#include "string_to_file.hpp"
#include "prepend_file.hpp"
#include <format>

namespace render_csv::detail
{

    auto errorMessage(StringView intro, ErrorCode error)
        -> String
    {
        return std::format("{}: ({}) {}", intro, error.value(), error.message());
    }

    // Попробовать загрузить все файлы в строки.
    auto loadFileGroupData(ConfigData::FileGroup const& fg) noexcept
        -> FileGroupResult
    {
        // TODO
        return {};
    }

    // "Ядро" программы: готовы входы (в виде строк), сформировать выход.
    bool processFileGroupData(ConfigData::FileGroup const& fg, FileGroupResult& result)
    {
        // TODO:
        // 1. Создать нужный парсер.
        // 2. Создать нужный форматтер.
        // 3. Записать в result.output содержимое head.
        // 4. Для каждого input из inputs выполнить парсер и для его результата -- форматтер,
        //    добавить результат в output (перед ним -- mid, если это не первый input).
        // 5. Добавить в output содержимое foot.
        // 
        // Если в процессе возникают ошибки: записываем их в result.errorLog с помощью errorMessage. 
        return false;
    }

    auto saveFileGroupOutput(FilePath const&                       filePath,
        StringView                            output,
        ConfigData::FileGroup::OutputFileMode mode
    ) noexcept
        -> Expected<void>
    {
        auto stringToFileMode { FileUpdateMode::Rewrite };

        switch (mode) {
            using enum ConfigData::FileGroup::OutputFileMode;
        case Unspecified:
            stringToFileMode = FileUpdateMode::OnlyNew;
            break;

        case Overwrite:
            stringToFileMode = FileUpdateMode::Rewrite;
            break;

        case Append:
            stringToFileMode = FileUpdateMode::Append;
            break;

        case Prepend:
            return prependFile(filePath, output);
        }

        return stringToFile(filePath, output, stringToFileMode);
    }

}
