cmake -DHELLOWORLD_WITH_EXECUTABLES="OFF" -DHELLOWORLD_WITH_TESTS="ON" -B build
cd build
cmake --build . --config Release
ctest -C Release