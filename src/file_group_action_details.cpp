/// @file  file_group_action_details.cpp

#include "file_group_action_details.hpp"
#include "file_to_string.hpp"
#include "string_to_file.hpp"
#include "prepend_file.hpp"
#include <format>

namespace render_csv::detail
{

    constexpr auto FailedToLoad = "Failed to load file "sv;

    auto errorMessage(StringView intro, ErrorCode error)
        -> String
    {
        return std::format("{}: ({}) {}", intro, error.value(), error.message());
    }

    [[nodiscard]] static auto loadFileGroupElement(
        String const&              filename,
        FileGroupResult::ErrorLog& errorLog
        ) -> String
    {
        if (filename.empty()) {
            return {};
        }

        auto data { fileToString(filename) };
        
        if (data) {
            return std::move(data).value();
        }

        auto message { std::format("{} {}", FailedToLoad, filename) };
        errorLog.push_back(errorMessage(message, data.error()));
        return {};
    }

    // Попробовать загрузить все файлы в строки.
    auto loadFileGroupData(ConfigData::FileGroup const& fg) noexcept
        -> FileGroupResult
    {
        auto result { FileGroupResult{} };

        result.loadedFileGroupData.head = loadFileGroupElement(fg.head, result.errorLog);
        // TODO: аналогично mid, foot, css и inputs (в цикле).
        // result.loadedFileGroupData.inputs.push_back

        return result;
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

    auto saveFileGroupOutput(
        FilePath const&                       filePath,
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
