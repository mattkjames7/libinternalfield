#ifndef __COEFFS_H__
#define __COEFFS_H__
#include <vector>
#include <string>
#include <map>
#include "internal.h"
#include "coeffs.h"
#endif

/* models! */
extern Internal o6;
extern Internal sha;
extern Internal gsfc15evs;
extern Internal vip4;
extern Internal p11a;
extern Internal o4;
extern Internal gsfc15ev;
extern Internal gsfc13ev;
extern Internal isaac;
extern Internal jrm09;
extern Internal jpl15evs;
extern Internal jpl15ev;
extern Internal vit4;
extern Internal v117ev;
extern Internal jrm33;
extern Internal u17ev;
extern Internal vipal;

/* map the model names to their model object pointers */
map<string,Internal*> modelMap = {	{"o6",&o6},
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
}

/* this function will return the pointer to a model object given a string */
Internal* getModelObjPointer(string Model);
Internal* getModelObjPointer(const char *Model);

