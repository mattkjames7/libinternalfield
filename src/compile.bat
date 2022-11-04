::python3 CodeGen.py


g++ -c -lm -fPIC -std=c++17 coeffs.cc -o ../build/coeffs.o
g++ -c -lm -fPIC -std=c++17 models.cc -o ../build/models.o
g++ -c -lm -fPIC -std=c++17 internal.cc -o ../build/internal.o 
g++ -c -lm -fPIC -std=c++17 internalmodel.cc -o ../build/internalmodel.o 
g++ -c -lm -fPIC -std=c++17 libinternal.cc -o ../build/libinternal.o


g++ -lm -fPIC -std=c++17 -g ../build/*.o  -shared -o libinternalfield.dll

