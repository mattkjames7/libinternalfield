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

/* map of strings to direct field model function pointers */
typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);
extern map<string,modelFieldPtr> modelFieldPtrMap;

/* function to return pointer to model field function */
modelFieldPtr getModelFieldPtr(string Model);
modelFieldPtr getModelFieldPtr(const char *Model);

/* functions to directly call each model for a single Cartesian vector (this will be used for tracing) */
void ness1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void o6Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void shaField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void gsfc15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void vip4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void p11aField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void o4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void gsfc15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void gsfc13evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void isaacField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jrm09Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jpl15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jpl15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void vit4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void v117evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jrm33Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void u17evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void vipalField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
