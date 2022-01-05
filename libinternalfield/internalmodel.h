#ifndef __INTERNALMODEL_H__
#define __INTERNALMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include "internal.h"
#include <string.h>
#include <vector>
#include <string>
#include <map>
#include "models.h"

class InternalModel {
	
	public:
		/* constructor */
		InternalModel();
		
		/* destructor */
		~InternalModel();
		
		/* set model parameters */
		void SetCartIn(bool);
		void SetCartOut(bool);
		bool GetCartIn();
		bool GetCartOut();
		void SetModel(char *);
		void GetModel(char *);

		/* Field functions */
		void Field(int,double*,double*,double*,int,double*,double*,double*);
		void Field(int,double*,double*,double*,double*,double*,double*);
		void Field(double,double,double,int,double*,double*,double*);
		void Field(double,double,double,double*,double*,double*);
				
		/* these objects are the models to use */
		map<string,Internal*> Models_;

	private:
		Internal *CurrentModel_;
		char CurrentModelName_[32];


		/* coordinate/field vector rotation */
		bool CartIn_;
		bool CartOut_;
		void _Cart2Pol(int,double*,double*,double*,double*,double*,double*);
		void _BPol2BCart(int,double*,double*,double*,double*,double*,double*,double*,double*);
};


#endif
