/// @file  file_group_action_details.hpp
/// @brief Вспомогательные функции для реализации processFileGroup вынесены в заголовок для облегчения тестирования.
#ifndef RENDER_CSV_FILE_GROUP_ACTION_DETAILS_HPP_INCLUDED
#define RENDER_CSV_FILE_GROUP_ACTION_DETAILS_HPP_INCLUDED

#include "file_group_action.hpp"
#include "file_operations_fwd.hpp"

namespace render_csv::detail
{

    /// @brief Загрузить данные всех файлов, упомянутых в файловой группе. 
    [[nodiscard]] auto loadFileGroupData(ConfigData::FileGroup const&) noexcept
        -> FileGroupResult;

    /// @brief Сформировать результат обработки файловой группы на месте (вывод и ошибки).
    /// @return истина, если ошибок не было; ложь, если были
    bool processFileGroupData(FileGroupResult&);

    /// @brief Сохранить файл в заданном режиме (по сути, реализует prepend, поскольку остальные режимы поддерживаются функцией stringToFile).
    auto saveFileGroupOutput(FilePath const&                       filePath,
                             StringView                            output,
                             ConfigData::FileGroup::OutputFileMode mode
                            ) noexcept
        -> Expected<void>;

}

#endif//RENDER_CSV_FILE_GROUP_ACTION_DETAILS_HPP_INCLUDED
