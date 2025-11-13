#include "md.hpp"
#include "table_formatter_utils.hpp"
#include <string>
using namespace std;

string formatMarkdownGfm(const string data[][3], int rows, int cols, const string& caption) {
    // Проверка данных
    if (!simpleValidate(rows, cols)) {
        return ": invalid data";
    }

    // Считаем максимальную ширину каждого столбца
    int widths[10]; // максимум 10 столбцов
    for (int j = 0; j < cols; j++) {
        widths[j] = 0;
        for (int i = 0; i < rows; i++) {
            if ((int)data[i][j].size() > widths[j]) {
                widths[j] = data[i][j].size();
            }
        }
    }

    string result = "";

    // Формируем таблицу
    for (int i = 0; i < rows; i++) {
        result += "|";
        for (int j = 0; j < cols; j++) {
            string cell = data[i][j];
            while ((int)cell.size() < widths[j]) {
                cell += " ";
            }
            result += " " + cell + " |";
        }
        result += "\n";

        // Разделительная линия после заголовка
        if (i == 0) {
            result += "|";
            for (int j = 0; j < cols; j++) {
                string line = "";
                for (int k = 0; k < widths[j]; k++) {
                    line += "-";
                }
                result += " " + line + " |";
            }
            result += "\n";
        }
    }

    // Подпись таблицы
    if (!caption.empty()) {
        result += ": " + caption + "\n";
    }

    return result;
}