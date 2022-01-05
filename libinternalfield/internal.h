#ifndef __INTERNAL_H__
#define __INTERNAL_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


using namespace std;

/* This structure will store the Schmidt coefficients */
struct schmidtcoeffs {
	int n;
	int m;
	double g;
	double h;
};

class Internal {
	public:
		Internal(const char*);
		Internal(unsigned char *);
		Internal(const Internal&);
		~Internal();
	
		/*these two functions will calculate the field in Cartesian RH 
		 * system III coordinates.*/
		void Field(int,double*,double*,double*,double*,double*,double*);
		void Field(int,double*,double*,double*,int,double*,double*,double*);
		void Field(double,double,double,double*,double*,double*);
		void Field(double,double,double,int,double*,double*,double*);
		
		/* set model parameters*/
		void SetCartIn(bool);
		void SetCartOut(bool);
		bool GetCartIn();
		bool GetCartOut();
		
	private:
		/*Schmidt coefficients */
		struct schmidtcoeffs *schc_;
		int nschc_;
		double **Snm_;
		int nmax_;
		
		/* these ones will have Snm_ already multiplied */
		double **g_;
		double **h_;
		
		/* functions for initializing the object */
		void _LoadSchmidt(unsigned char*);
		void _Schmidt();
		void _CoeffGrids();

		/* This function will calculate the Legendre polynomials */
		void _Legendre(int,double*,double*,int,double***,double***);
		
		/* this function will calculate the magnetic field components in
		 * spherical polar coordinates */
		void _SphHarm(int,double*,double*,double*,int,double*,double*,double*);
		
		/* coordinate/field vector rotation */
		bool CartIn_;
		bool CartOut_;
		void _Cart2Pol(int,double*,double*,double*,double*,double*,double*);
		void _BPol2BCart(int,double*,double*,double*,double*,double*,double*,double*,double*);
		
		bool copy;
	
};

#endif

