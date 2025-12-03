// перед запуском прописать "chmod +x build.sh" в bash

#!/bin/bash

meson setup build
meson compile -C build
meson test -C build -v

./build/src/rendercsv --help

exit $?