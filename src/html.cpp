/// @file  html.cpp
#include "html.hpp"
#include "table_formatter_utils.hpp"

namespace render_csv
{

    auto detail::htmlize(StringView input)
        -> String
    {
        // Выполнить замену специальных символов:
        // <  -->  &lt;
        // >  -->  &gt;
        // &  -->  &amp;
        // \n -->  <BR>
        return String{input};
    }

    [[nodiscard]] static auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
        // TODO
        return {};
    }

    [[nodiscard]] static auto formatHtmlFull(TableData const& data, StringView css = {})
        -> TableFormatterResult
    {
        TableFormatterResult result;

        // Получение html таблицы
        auto partialResult = formatHtmlPartial(data);

        // Строка со структурой документа
        String fullHtml;
        fullHtml += "<!DOCTYPE html>";
        fullHtml += "<meta charset=\"UTF-8\">";
        
         fullHtml += "<html>";
        fullHtml += "<head>";

        if (!data.caption.empty()) {
        fullHtml += "<title>" + detail::htmlize(data.caption) + "</title>"; 
        }

        if (!css.empty()) {
        fullHtml += "<style>";
        fullHtml += String(css);
        fullHtml += "</style>";
        }

        fullHtml += "</head>";
        fullHtml += "<body>";
        
        fullHtml += partialResult.output;
        
        fullHtml += "</body>";
        fullHtml += "</html>";
        
        result.output = std::move(fullHtml);
        return result;
    }

    auto makeHtmlFormatter(HtmlKind kind, StringView css)
        -> TableFormatter
    {
        switch (kind) {
        case HtmlKind::Partial:
            return formatHtmlPartial;

        case HtmlKind::Full:
            return [](TableData const& data)
                {
                    return formatHtmlFull(data);
                };

        case HtmlKind::FullWithCss:
            return [css](TableData const& data)
                {
                    return formatHtmlFull(data, css);
                };
        }

        return {};
    }

}
