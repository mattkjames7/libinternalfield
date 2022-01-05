#include <vector>
#include <string>
#include <stdio.h>

using std::vector;
using std::string;
using std::printf;

vector<string> s = {"abc","def","ghi"};

int main() {
	
	int n = s.size();
	int i;
	
	for (i=0;i<n;i++) {
		printf("%d %s\n",i,s[i].c_str());
	}
	
}
	
