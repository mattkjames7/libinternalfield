#ifndef __INTERNAL_H__
#define __INTERNAL_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



/* This structure will store the Schmidt coefficients */
struct schmidtcoeffs {
	int n;
	int m;
	double g;
	double h;
};


/***********************************************************************
 * NAME : class Internal
 * 
 * DESCRIPTION : 
 * 		Class which will store the g and h spherical harmonic 
 * 		coefficients for a given model. To obtain the magnetic field,
 * 		use the Field() and FieldCart() member functions.
 * 
 * ********************************************************************/
class Internal {
	public:
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

		/* set current degree */
		void SetDegree(int n);
		int GetDegree();

		
	private:
		/*Schmidt coefficients */
		struct schmidtcoeffs *schc_;
		int nschc_;
		double **Snm_;
		
		/* maximum, default and current degree */
		int nmax_;
		int ndef_;
		int ncur_;
		
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
		void _SphHarm(int,double*,double*,double*,double*,double*,double*);
		/* could do with writing a scalar version of this for extra speed */
		
		void _Cart2Pol(double,double,double,double*,double*,double*);
		void _BPol2BCart(double,double,double,double,double,double*,double*,double*);
		
		bool copy;
	
};

#endif

