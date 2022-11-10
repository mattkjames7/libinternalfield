::python3 CodeGen.py
call compileobj.bat

mkdir ..\lib\libinternalfield
g++ -lm -fPIC -std=c++17 -O3 ..\build\*.o  -shared -o ..\lib\libinternalfield\libinternalfield.dll


