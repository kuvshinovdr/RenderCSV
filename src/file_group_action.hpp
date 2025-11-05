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
