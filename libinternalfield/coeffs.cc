#include "coeffs.h"

/* list of model names */
vector<string> modelNames = {	"ness1975",
								"o6",
								"sha",
								"gsfc15evs",
								"vip4",
								"p11a",
								"o4",
								"gsfc15ev",
								"gsfc13ev",
								"isaac",
								"jrm09",
								"jpl15evs",
								"jpl15ev",
								"vit4",
								"langlais2019",
								"v117ev",
								"jrm33",
								"u17ev",
								"vipal"};


/* map the model names to their pointers */
map<string,unsigned char*> modelMap = {	{"ness1975",&_binary_ness1975_bin_start},
										{"o6",&_binary_o6_bin_start},
										{"sha",&_binary_sha_bin_start},
										{"gsfc15evs",&_binary_gsfc15evs_bin_start},
										{"vip4",&_binary_vip4_bin_start},
										{"p11a",&_binary_p11a_bin_start},
										{"o4",&_binary_o4_bin_start},
										{"gsfc15ev",&_binary_gsfc15ev_bin_start},
										{"gsfc13ev",&_binary_gsfc13ev_bin_start},
										{"isaac",&_binary_isaac_bin_start},
										{"jrm09",&_binary_jrm09_bin_start},
										{"jpl15evs",&_binary_jpl15evs_bin_start},
										{"jpl15ev",&_binary_jpl15ev_bin_start},
										{"vit4",&_binary_vit4_bin_start},
										{"langlais2019",&_binary_langlais2019_bin_start},
										{"v117ev",&_binary_v117ev_bin_start},
										{"jrm33",&_binary_jrm33_bin_start},
										{"u17ev",&_binary_u17ev_bin_start},
										{"vipal",&_binary_vipal_bin_start}
};


unsigned char* GetModelCoeffPointer(string Model) {
	return modelMap[Model];
}

unsigned char* GetModelCoeffPointer(const char *Model) {	
	return modelMap[Model];
}


