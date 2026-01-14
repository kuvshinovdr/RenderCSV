/// @file  md.cpp
#include "md.hpp"
#include "table_formatter_utils.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>

namespace render_csv
{

    // О формате GFM см.: https://github.github.com/gfm/
    [[nodiscard]] static auto formatMarkdownGfm(TableData const& data)
        -> TableFormatterResult
    {
        TableFormatterResult result;

        TableFormatterResult::Log validationLog = simpleValidate(data);
        result.warnings = validationLog;

        if (data.body.empty()) {
            return result;
        }

        std::ostringstream output;
        const std::size_t numBodyRows = data.body.size();
        
        // Вычисляем количество столбцов как максимум из:
        // 1) ширины заголовков
        // 2) максимальной ширины строк тела таблицы
        std::size_t numCols = data.headers.size();
        for (const auto& row : data.body) {
            numCols = std::max(numCols, row.size());
        }

        TableColumnWidths widths = computeColumnWidthsUtf8(data);
        std::vector<TableColumnWidths::ColumnWidth> maxWidths(numCols, 0);

        // Ширина заголовков 
        for (std::size_t col = 0; col < numCols && col < widths.headers.size(); ++col) {
            maxWidths[col] = std::max(maxWidths[col], widths.headers[col]);
        }

        // Ширина строк
        for (std::size_t bodyRow = 0; bodyRow < widths.body.size(); ++bodyRow) {
            for (std::size_t col = 0; col < numCols && col < widths.body[bodyRow].size(); ++col) {
                maxWidths[col] = std::max(maxWidths[col], widths.body[bodyRow][col]);
            }
        }

        // Заголовок таблицы 
        output << "|";
        for (std::size_t col = 0; col < numCols; ++col) {
            const auto& cell = (col < data.headers.size()) ? data.headers[col] : "";
            auto cellWidth = (col < widths.headers.size()) ? widths.headers[col] : 0;
            auto padding = maxWidths[col] - cellWidth;

            output << " " << cell;
            for (TableColumnWidths::ColumnWidth i = 0; i < padding; ++i) {
                output << " ";
            }
            output << " |";
        }
        output << "\n";

        // Разделительная строка
        output << "|";
        for (std::size_t col = 0; col < numCols; ++col) {
            output << " ";
            for (TableColumnWidths::ColumnWidth i = 0; i < maxWidths[col]; ++i) {
                output << "-";
            }
            output << " |";
        }
        output << "\n";

        // Тело таблицы
        for (std::size_t bodyRow = 0; bodyRow < numBodyRows; ++bodyRow) {
            output << "|";

            for (std::size_t col = 0; col < numCols; ++col) {
                const auto& cell = (col < data.body[bodyRow].size()) ? data.body[bodyRow][col] : "";
                auto cellWidth = 0;
                
                if (bodyRow < widths.body.size() && col < widths.body[bodyRow].size()) {
                    cellWidth = widths.body[bodyRow][col];
                }
                
                auto padding = maxWidths[col] - cellWidth;

                output << " " << cell;
                for (TableColumnWidths::ColumnWidth i = 0; i < padding; ++i) {
                    output << " ";
                }
                output << " |";
            }

            output << "\n";
        }

        // Подпись (caption), если есть
        if (!data.caption.empty()) {
            output << "\n: " << data.caption;
        }

        result.output = output.str();
        return result;
    }

    auto makeMarkdownFormatter(MarkdownKind kind)
        -> TableFormatter
    {
        switch (kind) {
        case MarkdownKind::GithubFlavored:
            return formatMarkdownGfm;
        }

        return {};
    }

} // namespace render_csv