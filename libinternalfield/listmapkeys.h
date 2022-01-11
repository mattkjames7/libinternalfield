#ifndef __LISTMAPKEYS_H__
#define __LISTMAPKEYS_H__
#include <vector>
#include <string>
#include <stdio.h>
#include <map>
#endif


/* based upon https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/ */
/***********************************************************************
 * NAME : vector<> listMapKeys(inmap)
 * 
 * DESCRIPTION : List the keys used for a std::map.
 * 
 * INPUTS : 
 * 		map		inmap		std::map instance			
 * 
 * 
 * RETURNS :
 * 		vector	keys		vector object containing a list of the map 
 * 							keys
 * 
 * 
 * 
 * ********************************************************************/
template <typename Tkey, typename Tval> 
std::vector<Tkey> listMapKeys(std::map<Tkey,Tval> const &inmap) {
	std::vector<Tkey> keys;
	for (auto const& element: inmap) {
		keys.push_back(element.first);
	}
	return keys;
}	


