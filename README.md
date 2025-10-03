# RenderCSV

Учебный проект на C++23.

## Цель

Консольное приложение, конвертирующее [.csv](https://ru.wikipedia.org/wiki/CSV)-файлы
в таблицы, оформленные в [Markdown](https://www.codecademy.com/resources/docs/markdown/tables) или [HTML](https://www.w3schools.com/html/html_tables.asp).

## Сборка

Поддерживаемые компиляторы:

- g++ 15.2 (Linux/Windows)
- MSVC 2022 (v.17.14 или новее)

Варианты сборки:

- Makefile (запускать make из-под bash) для g++ (соответствующая версия должна быть доступна в PATH)
- sln-файл для Visual Studio
- [CMake](https://cmake.org/) 4.1+/[Ninja](https://ninja-build.org/) — 
экспериментальная поддержка `import std` требует смены UUID для каждой [версии CMake](https://github.com/Kitware/CMake/blob/v4.1.2/Help/dev/experimental.rst) (требуется выбрать тег по версии и найти UUID для `CMAKE_EXPERIMENTAL_CXX_IMPORT_STD`) —
пока не рекомендуется использовать этот вариант

*Замечание.* При сборке Makefile на Windows требуется найти или установить терминал [bash](https://ru.wikipedia.org/wiki/Bash).
Если уже установлена git, то рядом с git.exe может найтись и bash.exe, например, в `C:\Program Files\Git\bin`.
Можно проверить, доступен ли он по PATH, введя в терминале (например, в cmd.exe) `bash --version`.
Требуется помнить, что bash не принимает пути с разделителем `\`, надо его заменять на `/`.


