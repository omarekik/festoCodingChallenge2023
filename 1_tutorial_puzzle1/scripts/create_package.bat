::!/bin/bash

:: Clean build folder
rmdir /q /s build

:: Build & Run unit tests & create conan package
conan profile detect --force

:: Install conan package
conan install . --output-folder=build --build=missing

:: Generate build system
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

:: Build
cmake --build . --config Release

:: Run test scripts
ctest .

:: Run App
call main\Release\Start.exe 

:: Return back from build folder to project folder
cd ..
