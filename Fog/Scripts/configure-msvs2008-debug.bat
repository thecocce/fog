mkdir ..\Build
cd ..\Build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DFOG_DEBUG=1 -DFOG_DEBUG_MEMORY=1 -DFOG_BUILD_EXAMPLES=True -G"Visual Studio 9 2008"
cd ..\Scripts
pause
