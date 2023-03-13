#ifndef __INTERNALVAR_H__
#define __INTERNALVAR_H__
#include "internal.h"


class InternalVar: public Internal {

	public:
		InternalVar();
		~InternalVar():

		SetTime(int,double);
		SetTime(double);

		GetTime(int*,double*);
		double GetTime();
}


#endif