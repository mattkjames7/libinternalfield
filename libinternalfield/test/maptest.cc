#include <vector>
#include <string>
#include <stdio.h>
#include <map>

using std::vector;
using std::string;
using std::printf;
using std::map;


map<string,int> m = {
	{"a",100},
	{"b",200},
	{"c",300},
};


int main() {
	
	int n = m.size();
	string s = "b";
	printf("a: %d\n",m["a"]);
	printf("b: %d\n",m["b"]);
	printf("c: %d\n",m["c"]);
	printf("b (using string): %d\n",m[s]);


}
	
