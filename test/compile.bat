copy ..\lib\libinternalfield.dll libinternalfield.dll
g++ -lm -fPIC -std=c++17 -g -I../include test.cc -Llibinternalfield.dll -o test.exe 
test.exe