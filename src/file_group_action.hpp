/// @file  file_group_action.hpp
/// @brief Функционал обработки одной группы файлов (ввод/вывод).
#ifndef RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED
#define RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED

#include "config.hpp"

namespace render_csv
{

    /// @brief Загруженные в память входные файлы (здесь уже в виде строк).
    struct LoadedFileGroupData
    {
        using Inputs =
            std::vector<String>;

        String   head       {};
        String   mid        {};
        String   foot       {};
        String   css        {};

        Inputs   inputs     {};
    };

    /// @brief Результат обработки FileGroup: загруженные файлы, строка результата (output) и протокол ошибок.
    struct FileGroupResult
    {
        using ErrorLogEntry =
            String;

        using ErrorLog =
            std::vector<ErrorLogEntry>;

        LoadedFileGroupData loadedFileGroupData {};
        String              output              {};
        ErrorLog            errorLog            {};
    };

    /// @brief Суммарное действие: загрузка файловой группы + обработка её данных + сохранение результата.
    auto processFileGroup(ConfigData::FileGroup const&)
        -> FileGroupResult;

}

#endif//RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED
