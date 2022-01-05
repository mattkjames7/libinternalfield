#ifndef __COEFFS_H__
#define __COEFFS_H__
#include <vector>
#include <string>
#include <map>
#endif

using std::string;
using std::vector;
using std::map;

/* list of model names */
extern vector<string> modelNames;
/* pointers to the memory where coefficients are stored */
extern unsigned char _binary_o6_bin_start;
extern unsigned char _binary_sha_bin_start;
extern unsigned char _binary_gsfc15evs_bin_start;
extern unsigned char _binary_vip4_bin_start;
extern unsigned char _binary_p11a_bin_start;
extern unsigned char _binary_o4_bin_start;
extern unsigned char _binary_gsfc15ev_bin_start;
extern unsigned char _binary_gsfc13ev_bin_start;
extern unsigned char _binary_isaac_bin_start;
extern unsigned char _binary_jrm09_bin_start;
extern unsigned char _binary_jpl15evs_bin_start;
extern unsigned char _binary_jpl15ev_bin_start;
extern unsigned char _binary_vit4_bin_start;
extern unsigned char _binary_v117ev_bin_start;
extern unsigned char _binary_jrm33_bin_start;
extern unsigned char _binary_u17ev_bin_start;
extern unsigned char _binary_vipal_bin_start;

/* map the model names to their pointers */
extern map<string,unsigned char*> modelMap;

/* this function will return the pointer to a model given a string */
unsigned char* getModelCoeffPointer(string Model);
unsigned char* getModelCoeffPointer(const char *Model);

