set "dataDir=%~1"
echo "%dataDir%"
call compileobj.bat

g++ -lm -fPIC -std=c++17 -O3 listfiles.o splitstring.o trimstring.o ^
savecoeffs.o igrf.o savemodels.o savevariable.o savelibheader.o main.cc ^
-o savecoeffs

call savecoeffs.exe "%dataDir%"
