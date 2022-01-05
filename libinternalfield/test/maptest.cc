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


/* based upon https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/ */
template <typename Tkey, typename Tval> 
vector<Tkey> listMapKeys(map<Tkey,Tval> const &inmap) {
	vector<Tkey> keys;
	for (auto const& element: inmap) {
		keys.push_back(element.first);
	}
	return keys;
}	

int main() {
	
	int n = m.size();
	string s = "b";
	printf("a: %d\n",m["a"]);
	printf("b: %d\n",m["b"]);
	printf("c: %d\n",m["c"]);
	printf("b (using string): %d\n",m[s]);

	int i;
	printf("size: %ld\n",m.size());
	
	vector<string> keys = listMapKeys(m);
	for (i=0;i<n;i++) {
		printf("%s : %d\n",keys[i].c_str(),m[keys[i]]);
	}

}

	
