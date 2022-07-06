#ifndef __INTERNALMODEL_H__
#define __INTERNALMODEL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include "models.h"
#include "internal.h"

/***********************************************************************
 * NAME : class InternalModel
 * 
 * DESCRIPTION : 
 * 		Class which can access all instances of Internal objects.
 * 
 * ********************************************************************/
class InternalModel {
	
	public:
		/* constructor */
		InternalModel();
		
		/* copy constructor */
		InternalModel(const InternalModel&);
		
		/* destructor */
		~InternalModel();
		
		/* Init this function - I would like to remove this if at all possible*/
		void CheckInit();
		void Init();
		
		/* set model parameters */
		void SetCartIn(bool);
		void SetCartOut(bool);
		bool GetCartIn();
		bool GetCartOut();
		void SetModel(const char *);
		void GetModel(char *);
		void SetDegree(int n);
		int GetDegree();

		/* Field functions */
		void Field(int,double*,double*,double*,int,double*,double*,double*);
		void Field(int,double*,double*,double*,double*,double*,double*);
		void Field(double,double,double,int,double*,double*,double*);
		void Field(double,double,double,double*,double*,double*);
				
		/* these objects are the models to use */
		std::map<std::string,Internal*> Models_;
		std::vector<std::string> ModelNames_;

	private:
		Internal *CurrentModel_;
		std::string *CurrentModelName_;


		/* coordinate/field vector rotation */
		bool copy_;
		bool *init_;
		bool *CartIn_;
		bool *CartOut_;
		void _Cart2Pol(int,double*,double*,double*,double*,double*,double*);
		void _Cart2Pol(double,double,double,double*,double*,double*);
		void _BPol2BCart(int,double*,double*,double*,double*,double*,double*,double*,double*);
		void _BPol2BCart(double,double,double,double,double,double*,double*,double*);
};


#endif
