/// @file  html.cpp
#include "html.hpp"
#include "table_formatter_utils.hpp"
#include <algorithm>
#include <ranges>

namespace render_csv
{

    namespace html
    {

        constexpr auto Lt   { "&lt;"sv     };
        constexpr auto Gt   { "&gt;"sv     };
        constexpr auto Amp  { "&amp;"sv    };
        constexpr auto Br   { "<br>\r\n"sv };

    }


    auto detail::htmlizeLength(StringView input) noexcept
        -> std::size_t
    {
        auto result { 0zu };

        for (auto c : input) {
            switch (c) {
            using namespace html;
            case '<':  result += Lt.size();  break;
            case '>':  result += Gt.size();  break;
            case '&':  result += Amp.size(); break;
            case '\r': break; // HTML использует CRLF
            case '\n': result += Br.size();  break;
            default:   ++result;
            }
        }

        return result;
    }

    auto detail::htmlize(StringView input)
        -> String
    {
        auto result { String{} };
        
        result.resize(htmlizeLength(input));
        auto writePos { result.data() };

        for (auto c : input) {
            switch (c) {
            using namespace html;
            case '<':  
                writePos = std::copy_n(Lt.data(), Lt.size(), writePos);
                break;
            case '>':
                writePos = std::copy_n(Gt.data(), Gt.size(), writePos);
                break;
            case '&':
                writePos = std::copy_n(Amp.data(), Amp.size(), writePos);
                break;
            case '\r':
                // HTML использует CRLF
                break;
            case '\n':
                writePos = std::copy_n(Br.data(), Br.size(), writePos);
                break;
            default:
                *writePos++ = c;
            }
        }

        return result;
    }

    [[nodiscard]] auto formatHtmlPartial(TableData const& data)
        -> TableFormatterResult
    {
        auto  result { TableFormatterResult{} };
        auto& output { result.output };
        
        output += "<table>\n"sv;
        
        if (!data.caption.empty()) {
            output += "  <caption>"sv;
            output += detail::htmlize(data.caption);
            output += "</caption>\n"sv;
        }
        
        if (!data.headers.empty()) {
            output += "  <tr>\n"sv;
            
            for (auto const& header : data.headers) {
                output += "    <th>"sv;
                output += detail::htmlize(header);
                output += "</th>\n"sv;
            }
            
            output += "  </tr>\n"sv;
        }

        for (auto const& row : data.body) {
            output += "  <tr>\n"sv;
            
            for (auto const& cell : row) {
                output += "    <td>"sv;
                output += detail::htmlize(cell);
                output += "</td>\n"sv;
            }
            
            output += "  </tr>\n"sv;
        }
        
        output += "</table>"sv;
        
        return result;
    }

    [[nodiscard]] auto formatHtmlFull(TableData const& data, StringView css = {})
        -> TableFormatterResult
    {
        auto result { TableFormatterResult{} };

        // Получение HTML таблицы.
        auto partialResult { formatHtmlPartial(data) };
        result.warnings = std::move(partialResult.warnings);
        
        // Строка со структурой документа.
        auto& fullHtml { result.output };

        fullHtml += "<!DOCTYPE html>"sv;
        fullHtml += "<meta charset=\"UTF-8\">"sv;
        
        fullHtml += "<html>"sv;
        fullHtml += "<head>"sv;
        
        // Заголовок.
        if (!data.caption.empty()) {
            fullHtml += "<title>"sv;
            fullHtml += detail::htmlize(data.caption);
            fullHtml += "</title>"sv; 
        }
        
        // Подключение CSS.
        if (!css.empty()) {
            fullHtml += "<style>"sv;
            fullHtml += String(css);
            fullHtml += "</style>"sv;
        }

        fullHtml += "</head><body>"sv;

        // Вставка результата formatHtmlPartial.
        fullHtml += partialResult.output;
        
        // Завершение документа.
        fullHtml += "</body></html>"sv;

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
