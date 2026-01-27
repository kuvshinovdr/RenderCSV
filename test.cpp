#include <iostream>
#include "md.hpp"
using namespace std;

int main() {
    const string data[3][3] = {
        {"Name", "Age", "City"},
        {"Alice", "23", "New York"},
        {"Bob", "31", "Paris"}
    };

    string markdown = formatMarkdownGfm(data, 3, 3, "Example Table");

    cout << markdown;

    return 0;
}