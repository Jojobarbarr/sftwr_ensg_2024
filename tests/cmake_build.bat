if exist build rmdir build /s /q
cmake -B build
cmake --build build --config Release