
g++ -lm -fPIC -std=c++17 -g test.cc -o test.exe -Wl,-rpath='$$ORIGIN/..' -L.. -linternalfield
	
exit
