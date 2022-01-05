#include "models.h"

/* model definitions */
Internal o6(&_binary_o6_bin_start);
Internal sha(&_binary_sha_bin_start);
Internal gsfc15evs(&_binary_gsfc15evs_bin_start);
Internal vip4(&_binary_vip4_bin_start);
Internal p11a(&_binary_p11a_bin_start);
Internal o4(&_binary_o4_bin_start);
Internal gsfc15ev(&_binary_gsfc15ev_bin_start);
Internal gsfc13ev(&_binary_gsfc13ev_bin_start);
Internal isaac(&_binary_isaac_bin_start);
Internal jrm09(&_binary_jrm09_bin_start);
Internal jpl15evs(&_binary_jpl15evs_bin_start);
Internal jpl15ev(&_binary_jpl15ev_bin_start);
Internal vit4(&_binary_vit4_bin_start);
Internal v117ev(&_binary_v117ev_bin_start);
Internal jrm33(&_binary_jrm33_bin_start);
Internal u17ev(&_binary_u17ev_bin_start);
Internal vipal(&_binary_vipal_bin_start);

/* map the model names to their model object pointers */
map<string,Internal*> modelPtrMap = {	{"o6",&o6},
										{"sha",&sha},
										{"gsfc15evs",&gsfc15evs},
										{"vip4",&vip4},
										{"p11a",&p11a},
										{"o4",&o4},
										{"gsfc15ev",&gsfc15ev},
										{"gsfc13ev",&gsfc13ev},
										{"isaac",&isaac},
										{"jrm09",&jrm09},
										{"jpl15evs",&jpl15evs},
										{"jpl15ev",&jpl15ev},
										{"vit4",&vit4},
										{"v117ev",&v117ev},
										{"jrm33",&jrm33},
										{"u17ev",&u17ev},
										{"vipal",&vipal}
};

Internal* getModelObjPointer(string Model) {
	return modelPtrMap[Model];
}

Internal* getModelObjPointer(const char *Model) {
	return modelPtrMap[Model];
}

vector<string> listAvailableModels() {
	return listMapKeys(modelPtrMap);
}

