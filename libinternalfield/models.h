#ifndef __MODELS_H__
#define __MODELS_H__
#include <vector>
#include <string>
#include <map>
#include "internal.h"
#include "coeffs.h"
#include "listmapkeys.h"
#endif

/* models! */
extern Internal ness1975;
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
extern Internal langlais2019;
extern Internal v117ev;
extern Internal jrm33;
extern Internal u17ev;
extern Internal vipal;

/* map the model names to their model object pointers */
extern map<string,Internal*> modelPtrMap;

/* this function will return the pointer to a model object given a string */
Internal* getModelObjPointer(string Model);
Internal* getModelObjPointer(const char *Model);

/* a function to return a list of the models available */
vector<string> listAvailableModels();
