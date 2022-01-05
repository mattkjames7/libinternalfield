#ifndef __LISTMAPKEYS_H__
#define __LISTMAPKEYS_H__
#include <vector>
#include <string>
#include <stdio.h>
#include <map>
#endif

using std::vector;
using std::map;




/* based upon https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/ */
template <typename Tkey, typename Tval> 
vector<Tkey> listMapKeys(map<Tkey,Tval> const &inmap) {
	vector<Tkey> keys;
	for (auto const& element: inmap) {
		keys.push_back(element.first);
	}
	return keys;
}	


