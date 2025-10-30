// перед запуском прописать "chmod +x build.sh" в bash

#!/bin/bash

meson setup build
meson compile -C build
./build/rendercsv --help

meson test -C build -v

exit $?