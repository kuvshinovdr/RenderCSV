/// @file  file_group_action.hpp
/// @brief Функционал обработки одной группы файлов (ввод/вывод).
#ifndef RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED
#define RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED

#include "config.hpp"
#include "error_fwd.hpp"

namespace render_csv
{

    struct LoadedFileGroupData
    {
        using Inputs =
            std::vector<String>;

        String   head       {};
        String   mid        {};
        String   foot       {};

        Inputs   inputs     {};
    };

    struct FileGroupResult
    {
        using ErrorLog =
            std::vector<String>;

        LoadedFileGroupData loadedFileGroupData {};
        String              output              {};
        ErrorLog            errorLog            {};
    };

    namespace detail
    {
        // В принципе, для внешнего API достаточно функции processFileGroup.
        // Данные функции доступны для упрощения тестирования.

        /// @brief Загрузить данные всех файлов, упомянутых в файловой группе. 
        [[nodiscard]] auto loadFileGroupData(ConfigData::FileGroup const&) noexcept
            -> FileGroupResult;

        /// @brief Сформировать результат обработки файловой группы на месте (вывод и ошибки).
        /// @return истина, если ошибок не было; ложь, если были
        bool processFileGroupData(FileGroupResult&);

    }

    /// @brief Суммарное действие: загрузка файловой группы + обработка её данных + сохранение результата.
    auto processFileGroup(ConfigData::FileGroup const&)
        -> FileGroupResult;

}

#endif//RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED
