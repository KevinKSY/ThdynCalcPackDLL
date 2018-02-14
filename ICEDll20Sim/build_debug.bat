@ECHO OFF
mkdir build
cd build
cmake -G "Visual Studio 14" ..
cmake --build . --config Debug
