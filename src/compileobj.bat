::python3 CodeGen.py

mkdir ..\build
g++ -c -lm -fPIC -std=c++17 -O3 coeffs.cc -o ..\build\coeffs.o
g++ -c -lm -fPIC -std=c++17 -O3 models.cc -o ..\build\models.o
g++ -c -lm -fPIC -std=c++17 -O3 internal.cc -o ..\build\internal.o 
g++ -c -lm -fPIC -std=c++17 -O3 internalmodel.cc -o ..\build\internalmodel.o 
g++ -c -lm -fPIC -std=c++17 -O3 libinternal.cc -o ..\build\libinternal.o
