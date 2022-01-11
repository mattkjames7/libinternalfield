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
	
		/*these four functions will calculate the field in spherical
		 * polar RH system III coordinates.*/
		void Field(int,double*,double*,double*,double*,double*,double*);
		void Field(int,double*,double*,double*,int,double*,double*,double*);
		void Field(double,double,double,double*,double*,double*);
		void Field(double,double,double,int,double*,double*,double*);
		
		/* these will be Cartesian */
		void FieldCart(double,double,double,double*,double*,double*);
		void FieldCart(double,double,double,int,double*,double*,double*);

		
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
		
		
		void _Cart2Pol(double,double,double,double*,double*,double*);
		void _BPol2BCart(double,double,double,double,double,double*,double*,double*);
		
		bool copy;
	
};

#endif

