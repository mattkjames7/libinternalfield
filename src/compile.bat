::python3 CodeGen.py
call compileobj.bat

mkdir ../lib/libinternalfield
g++ -lm -fPIC -std=c++17 -g ../build/*.o  -shared -o ../libinternalfield/libinternalfield.dll


