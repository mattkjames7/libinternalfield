set "dataDir=%~1"

cd codegen
call compile.bat "!dataDir!"
cd ..

call compileobj.bat

mkdir ..\lib
g++ -lm -fPIC -std=c++17 -O3 ..\build\*.o  -shared -o ..\lib\libinternalfield.dll


