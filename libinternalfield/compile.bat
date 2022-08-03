python3 CodeGen.py


g++ -c -lm -fPIC -std=c++17 coeffs.cc -o coeffs.o
g++ -c -lm -fPIC -std=c++17 models.cc -o models.o
g++ -c -lm -fPIC -std=c++17 internal.cc -o internal.o 
g++ -c -lm -fPIC -std=c++17 internalmodel.cc -o internalmodel.o 
g++ -c -lm -fPIC -std=c++17 libinternal.cc -o libinternal.o


g++ -lm -fPIC -std=c++17 -g coeffs.o internal.o models.o internalmodel.o libinternal.o  -shared -o libinternalfield.dll


