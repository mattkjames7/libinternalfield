mkdir build
mkdir lib/libinternalfield
cd src
call compile.bat 
cd ..

rm build/*.o
rmdir build