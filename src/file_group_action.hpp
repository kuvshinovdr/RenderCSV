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

    namespace detail
    {

        using LoadFileGroupDataResult =
            Expected<LoadedFileGroupData>;

        /// @brief Загрузить данные всех файлов, упомянутых в файловой группе. 
        [[nodiscard]] auto loadFileGroupData(ConfigData::FileGroup const&) noexcept
            -> LoadFileGroupDataResult;

    }

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

        /// @brief Сформировать результат обработки файловой группы (вывод и ошибки). 
        [[nodiscard]] auto processFileGroupData(LoadedFileGroupData&&)
            -> FileGroupResult;

        /// @brief Сохранить результат обработки файловой группы в файл вывода.
        auto saveFileGroupOutput(ConfigData::FileGroup const& fg, StringView output)
            -> Expected<void>;

    }

    // В принципе, для внешнего API достаточно функции processFileGroup.
    // Предыдущие функции открыты для упрощения тестирования.

    /// @brief Суммарное действие: загрузка файловой группы + обработка её данных + сохранение результата.
    auto processFileGroup(ConfigData::FileGroup const&)
        -> FileGroupResult;

}

#endif//RENDER_CSV_FILE_GROUP_ACTION_HPP_INCLUDED
