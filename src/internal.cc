#include "internal.h"


/***********************************************************************
 * NAME : Internal::Internal(ptr)
 * 
 * DESCRIPTION : Initialize the Internal object.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	Pointer to the memory location to read.
 * 
 * ********************************************************************/
Internal::Internal(unsigned char *ptr) {

	useptr_ = true;
	init_ = new bool[1];
	init_[0] = false;
	modelptr_ = ptr;
	_Init();
}

/***********************************************************************
 * NAME : Internal::Internal(S)
 * 
 * DESCRIPTION : Initialize the Internal object.
 * 
 * INPUTS : 
 * 		coeffStruct		S	Struct containing the coefficients.
 * 
 * ********************************************************************/
Internal::Internal(const char *Model) {
	
	
	useptr_ = false;
	init_ = new bool[1];
	init_[0] = false;
	modelstr_ = &(getModelCoeffStruct(Model))();
	_Init();
}


Internal::Internal(const Internal &obj) {
	init_ = obj.init_;
	copy = true;
	useptr_ = obj.useptr_;
	init_ = obj.init_;
	nschc_ = obj.nschc_;
	schc_ = obj.schc_;
	Snm_ = obj.Snm_;
	nmax_ = obj.nmax_;
	ndef_ = obj.ndef_;
	ncur_ = obj.ncur_;
	rscale_ = obj.rscale_;
	g_ = obj.g_;
	h_ = obj.h_;
	Pnm_ = obj.Pnm_;
	dPnm_ = obj.dPnm_;
	cosmp_ = obj.cosmp_;
	sinmp_ = obj.sinmp_;
	
}

Internal::~Internal() {
	if (!copy) {
		delete[] init_;
		delete[] ncur_;
		
		/* delete the structure containing coefficients */
		delete[] schc_;
		
		/* delete other variables containing other coefficients */
		int n;
		for (n=0;n<=nmax_;n++) {
			delete[] Snm_[n];
			delete[] g_[n];
			delete[] h_[n];
		}
		delete[] Snm_;
		delete[] g_;
		delete[] h_;
		
		for (n=0;n<=nmax_;n++) {
			delete[] Pnm_[n];
			delete[] dPnm_[n];
			
		}		
		delete[] Pnm_;
		delete[] dPnm_;
		
		delete[] cosmp_;
		delete[] sinmp_;			
	}
}

void Internal::_CheckInit() {
	/* check if the object is initialized, if not then intialize it! */
	if (!init_[0]) {
		_Init();
	}
	
}


void Internal::_Init() {
	
	/* call the appropriate functions to intialize the object */
	/* read the coeffs into the object */
	if (useptr_) {
		_LoadSchmidt(modelptr_);	
	} else {
		_LoadSchmidt(*modelstr_);
	}

	/* calcualte Schmidt normalized coefficient grids */
	_Schmidt();
	_CoeffGrids();

	/* tell object that it is not a copy */
	copy = false;
	
	/* set the status of this object as being intialized */
	init_[0] = true;
	
	/* allocate Legendre polynomial arrays */
	int n, m;
	Pnm_ = new double*[nmax_+1];
	dPnm_ = new double*[nmax_+1];
	for (n=0;n<=nmax_;n++) {
		Pnm_[n] = new double[n+1];
		dPnm_[n] = new double[n+1];
	}		
	
	/* and cosmp sinmp */
	cosmp_ = new double[nmax_+1];
	sinmp_ = new double[nmax_+1];

}


/***********************************************************************
 * NAME : void Internal::_LoadSchmidt(ptr)
 * 
 * DESCRIPTION : Read the g/h coefficients from memory.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	Pointer to the memory location to read.
 * 
 * ********************************************************************/
void Internal::_LoadSchmidt(unsigned char *ptr){
	
	/* this is the length of each array */
	int l, i, j, p;
	
	/* read the length */
	l = ((int*) ptr)[0];
	ptr += sizeof(int);
	
	/* initialize the temporary arrays */
	int *n = new int[l];
	int *m = new int[l];
	int8_t *gh = new int8_t[l];
	double *coeffs = new double[l];
	
	/* load them in */
	for (i=0;i<l;i++) {
		gh[i] = ((int8_t*) ptr)[0];
		ptr += sizeof(int8_t);
	}
	for (i=0;i<l;i++) {
		n[i] = ((int*) ptr)[0];
		ptr += sizeof(int);
	}
	for (i=0;i<l;i++) {
		m[i] = ((int*) ptr)[0];
		ptr += sizeof(int);
	}
	for (i=0;i<l;i++) {
		coeffs[i] = ((double*) ptr)[0];
		ptr += sizeof(double);
	}
	ndef_ = ((int*) ptr)[0];
	ptr += sizeof(int);
	
	/* get n max */
	nmax_ = 0;
	for (i=0;i<l;i++) {
		if (n[i] > nmax_) {
			nmax_ = n[i];
		}
	}
	
	/* set current model degree to the default */
	ncur_[0] = ndef_;
	
	/* calculate the length of the coefficient structure */
	nschc_ = 0;
	for (i=0;i<nmax_;i++) {
		nschc_ += (2 + i);
	}
	
	/* get rscale */
	rscale_ = ((double*) ptr)[0];
	ptr += sizeof(double);
	
	/* create the structure array */
	schc_ = new struct schmidtcoeffs[nschc_];
	
	/*fill it up */
	p = 0;
	for (i=1;i<=nmax_;i++) {
		for (j=0;j<=i;j++) {
			schc_[p].n = i;
			schc_[p].m = j;
			schc_[p].g = 0.0;
			schc_[p].h = 0.0;
			p++;
		}
	}
	for (i=0;i<l;i++) {
		p = m[i]-1;
		for (j=0;j<n[i];j++) {
			p += (1 + j);
		}
		if (gh[i] == 0) {
			schc_[p].g = coeffs[i];
		} else {
			schc_[p].h = coeffs[i];
		}
	}
			
	/* free the original arrays */
	delete[] n;
	delete[] m;
	delete[] gh;
	delete[] coeffs;
	
}

/***********************************************************************
 * NAME : void Internal::_LoadSchmidt(S)
 * 
 * DESCRIPTION : Read the g/h coefficients from memory.
 * 
 * INPUTS : 
 * 		coeffStruct		S	Struct containing the coefficients.
 * 
 * ********************************************************************/
void Internal::_LoadSchmidt(coeffStruct S){
	
	/* this is the length of each array */
	int i, j, p;
	
	
	/* get n max and ndef*/
	nmax_ = S.nmax;
	ndef_ = S.ndef;
	
	/* set current model degree to the default */
	ncur_ = new int[1];
	ncur_[0] = ndef_;
	
	/* calculate the length of the coefficient structure */
	nschc_ = S.len;

	/* get rscale */
	rscale_ = S.rscale;
	
	/* create the structure array */
	schc_ = new struct schmidtcoeffs[nschc_];
	
	/*fill it up */
	p = 0;
	for (i=0;i<nschc_;i++) {
		schc_[i].n = S.n[i];
		schc_[i].m = S.m[i];
		schc_[i].g = S.g[i];
		schc_[i].h = S.h[i];
	}

	
}

/***********************************************************************
 * NAME : void Internal::_Schmidt()
 * 
 * DESCRIPTION : Calculate the Schmidt coefficients.
 * 
 * 
 * ********************************************************************/
void Internal::_Schmidt() {
	
	/* create nmax_+1*n+1 array full of coefficients */
	int n, m;
	Snm_ = new double*[nmax_+1];
	for (n=0;n<=nmax_;n++) {
		Snm_[n] = new double[n+1];
	}
	
	/* calculate a bunch of factorials */
	int nfact = 2*nmax_ + 1;
	double facts[nfact];
	facts[0] = 1.0;
	for (n=1;n<nfact;n++) {
		facts[n] = n*facts[n-1];
	}
	
	/* fill the arrays */
	double delta;
	for (n=0;n<=nmax_;n++) {
		for (m=0;m<=n;m++) {
			if (m == 0) {
				delta = 1.0;
			} else { 
				delta = 2.0;
			}
			Snm_[n][m] = sqrt(delta*((facts[n-m]/facts[n+m])));
		}
	}
}

/***********************************************************************
 * NAME : void Internal::_CoeffGrids()
 * 
 * DESCRIPTION : Initialize the g/h coefficient grids.
 * 
 * 
 * ********************************************************************/
void Internal::_CoeffGrids() {
	
	/* create the grids for g and h */
	int n, m;
	g_ = new double*[nmax_+1];
	h_ = new double*[nmax_+1];
	for (n=0;n<=nmax_;n++) {
		g_[n] = new double[n+1];
		h_[n] = new double[n+1];
		
		/* fill with zeros just in case */
		for (m=0;m<=n;m++) {
			g_[n][m] = 0.0;
			h_[n][m] = 0.0;
			
		}
	}	
	
	/* now we need to fill the arrays in, multiplying by Snm_ */
	for (n=0;n<nschc_;n++) {
		g_[schc_[n].n][schc_[n].m] = schc_[n].g*Snm_[schc_[n].n][schc_[n].m];
		h_[schc_[n].n][schc_[n].m] = schc_[n].h*Snm_[schc_[n].n][schc_[n].m];
	}		
	
		
	
}




/***********************************************************************
 * NAME : void Internal::SetDegree(n)
 * 
 * DESCRIPTION : Set the maximum degree of this model to use.
 * 
 * INPUTS : 
 * 		int		n			Model degree
 * 
 * ********************************************************************/
void Internal::SetDegree(int n) {
	/* check that the degree falls within a valid range */
	if (n > nmax_) {
		/* greater than the maximum, cap at nmax_ */
		printf("WARNING: Attempted to set model degree above maximum (%d)\n",nmax_);
		ncur_[0] = nmax_;
	} else if (n < 1) {
		/* too small - use default instead */
		//printf("WARNING: Attempted to use model degree < 1 - using default (%d)\n",ndef_);
		ncur_[0] = ndef_;
	} else {
		ncur_[0] = n;
	}
	
}

/***********************************************************************
 * NAME : int Internal::GetDegree()
 * 
 * DESCRIPTION : Get the current degree of this model in use.
 * 
 * OUTPUTS : 
 * 		int		n			Model degree
 * 
 * ********************************************************************/
int Internal::GetDegree() {
	_CheckInit();
	return ncur_[0];
	
}

/***********************************************************************
 * NAME : void Internal::_Legendre(l,costheta,sintheta,nmax,Pnm,dPnm)
 * 
 * DESCRIPTION : Calculate the Legendre polynomials.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	*costheta	Cosine of colatitude.
 * 		double	*sintheta	Sine of colatitude.
 * 		int		nmax		Maximum degree of the model
 * 
 * 
 * OUTPUTS :
 * 		double 	***Pnm			Polynomials
 * 		double 	***dPnm			Polynomial derivatives
 * 
 * ********************************************************************/
void Internal::_Legendre(int l, double *costheta, double *sintheta, 
						int nmax, double ***Pnm, double ***dPnm) {
	/* set up the intial few terms */
	int n, m, i;
	for (i=0;i<l;i++) {
		Pnm[0][0][i] = 1.0;
		Pnm[1][0][i] = costheta[i];
		Pnm[1][1][i] = sintheta[i];
		dPnm[0][0][i] = 0.0;
		dPnm[1][0][i] = -sintheta[i];
		dPnm[1][1][i] = costheta[i];
	}
	
	/* now recurse through the rest of them */
	double n21,onenm,nm1;
	for (n=2;n<=nmax;n++) {
		n21 = 2.0*n - 1.0;
		for (m=0;m<=n;m++) {
			if (m < n-1) {
				/* this case is the more complicated one, where we need
				 * two previous polynomials to calculate the next */
				onenm = 1.0/(n-m);
				nm1 = (n + m - 1.0);
				for (i=0;i<l;i++) {
					Pnm[n][m][i] = onenm*(n21*costheta[i]*Pnm[n-1][m][i] - nm1*Pnm[n-2][m][i]);
					dPnm[n][m][i] = onenm*(n21*(costheta[i]*dPnm[n-1][m][i] - sintheta[i]*Pnm[n-1][m][i]) - nm1*dPnm[n-2][m][i]);
				}				
			} else { 
				/* this case only requires one previous polynomial */
				for (i=0;i<l;i++) {
					Pnm[n][m][i] = n21*sintheta[i]*Pnm[n-1][m-1][i];
					dPnm[n][m][i] = n21*(costheta[i]*Pnm[n-1][m-1][i] + sintheta[i]*dPnm[n-1][m-1][i]);
				}
				
				
			}
		}
	}
			
	
}


/***********************************************************************
 * NAME : void Internal::_Legendre(l,costheta,sintheta,nmax,Pnm,dPnm)
 * 
 * DESCRIPTION : Calculate the Legendre polynomials.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	*costheta	Cosine of colatitude.
 * 		double	*sintheta	Sine of colatitude.
 * 		int		nmax		Maximum degree of the model
 * 
 * 
 * OUTPUTS :
 * 		double 	***Pnm			Polynomials
 * 		double 	***dPnm			Polynomial derivatives
 * 
 * ********************************************************************/
void Internal::_Legendre(double costheta, double sintheta, 
						int nmax, double **Pnm, double **dPnm) {
	/* set up the intial few terms */
	int n, m, i;
	Pnm[0][0] = 1.0;
	Pnm[1][0] = costheta;
	Pnm[1][1] = sintheta;
	dPnm[0][0] = 0.0;
	dPnm[1][0] = -sintheta;
	dPnm[1][1] = costheta;

	
	/* now recurse through the rest of them */
	double n21,onenm,nm1;
	for (n=2;n<=nmax;n++) {
		n21 = 2.0*n - 1.0;
		for (m=0;m<=n;m++) {
			if (m < n-1) {
				/* this case is the more complicated one, where we need
				 * two previous polynomials to calculate the next */
				onenm = 1.0/(n-m);
				nm1 = (n + m - 1.0);
				Pnm[n][m] = onenm*(n21*costheta*Pnm[n-1][m] - nm1*Pnm[n-2][m]);
				dPnm[n][m] = onenm*(n21*(costheta*dPnm[n-1][m] - sintheta*Pnm[n-1][m]) - nm1*dPnm[n-2][m]);
								
			} else { 
				/* this case only requires one previous polynomial */
				Pnm[n][m] = n21*sintheta*Pnm[n-1][m-1];
				dPnm[n][m] = n21*(costheta*Pnm[n-1][m-1] + sintheta*dPnm[n-1][m-1]);
				
				
				
			}
		}
	}
			
	
}

/***********************************************************************
 * NAME : void Internal::_SphHarm(l,r,t,p,MaxDeg,Br,Bt,Bp)
 * 
 * DESCRIPTION : Calculate the magnetic field using spherical harmonics.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	*r			Radial coordinate (planetary radii)
 * 		double 	*t			Theta, colatitude (radians)
 * 		double	*p			Phi, azimuth (radians)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	*Br			Radial field component (nT)
 * 		double 	*Bt			Theta component (nT)
 * 		double 	*Bp			Phi component (nT)
 * 
 * 
 * 
 * ********************************************************************/
/* try making a scalar version of this to remove new/delete allocation*/
void Internal::_SphHarm(	int l, double *r0, double *t, double *p,
							double *Br, double *Bt, double *Bp) {
	/* rescale r */
	int i;
	double *r = new double[l];
	for (i=0;i<l;i++) {
		r[i] = r0[i]*rscale_;
	}	
	
	/* set the maximum degree of the model to use */
	int nmax = ncur_[0];
	
	/* create arrays for the Legendre polynomials */
	int n, m;
	double ***Pnm = new double**[nmax+1];
	double ***dPnm = new double**[nmax+1];
	for (n=0;n<=nmax;n++) {
		Pnm[n] = new double*[n+1];
		dPnm[n] = new double*[n+1];
		
		for (m=0;m<=n;m++) {
			Pnm[n][m] = new double[l];
			dPnm[n][m] = new double[l];
		}
	}	
	
	/* create some arrays to be used in the field calculation */
	double *r1 = new double[l];
	double *C = new double[l];
	double *cost = new double[l];
	double *sint = new double[l];
	double *sint1 = new double[l];
	for (i=0;i<l;i++) {
		r1[i] = 1.0/r[i];
		C[i] = r1[i]*r1[i];
		cost[i] = cos(t[i]);
		sint[i] = sin(t[i]);
		if (sint[i] == 0.0) {
			sint1[i] = 0.0;
		} else {
			sint1[i] = 1.0/sint[i];
		}
	}
	double **cosmp = new double*[nmax+1];
	double **sinmp = new double*[nmax+1];
	for (m=0;m<=nmax;m++) {
		cosmp[m] = new double[l];
		sinmp[m] = new double[l];
		if (m == 0) {
			for (i=0;i<l;i++) {
				cosmp[0][i] = 1.0;
				sinmp[0][i] = 0.0;
			}
		} else {
			for (i=0;i<l;i++) {
				cosmp[m][i] = cos(((double) m)*p[i]);
				sinmp[m][i] = sin(((double) m)*p[i]);
			}
		}
	}
	double *sumr = new double[l];
	double *sumt = new double[l];
	double *sump = new double[l];
	
	
	/* calculate the Legendre polynomials */
	_Legendre(l,cost,sint,nmax,Pnm,dPnm);
	
	/* set B components to 0 */
	for (i=0;i<l;i++) {
		Br[i] = 0.0;
		Bt[i] = 0.0;
		Bp[i] = 0.0;
	}
	
	/* now start summing stuff up */
	for (n=1;n<=nmax;n++) {
		/* zero the sum arrays and update the C parameter */
		for (i=0;i<l;i++) {
			C[i] = C[i]*r1[i];
			sumr[i] = 0.0;
			sumt[i] = 0.0;
			sump[i] = 0.0;
		}
		
		/* start summing stuff */
		for (m=0;m<=n;m++) {
			for (i=0;i<l;i++) {
				sumr[i] += Pnm[n][m][i]*(g_[n][m]*cosmp[m][i] + h_[n][m]*sinmp[m][i]);
				sumt[i] += dPnm[n][m][i]*(g_[n][m]*cosmp[m][i] + h_[n][m]*sinmp[m][i]);
				sump[i] += ((double) m)*Pnm[n][m][i]*(h_[n][m]*cosmp[m][i] - g_[n][m]*sinmp[m][i]);
			}
		}
		
		/* now calculate B */
		for (i=0;i<l;i++) {
			Br[i] += C[i]*(n+1)*sumr[i];
			Bt[i] += -C[i]*sumt[i];
			Bp[i] += -C[i]*sump[i];
		}
		
	}
	
	/* finally multiply by 1/sintheta */
	for (i=0;i<l;i++) {
		Bp[i] = sint1[i]*Bp[i];
	}
	
	
	/* delete the arrays */
	for (n=0;n<=nmax;n++) {
		for (m=0;m<=n;m++) {
			delete[] Pnm[n][m];
			delete[] dPnm[n][m];
		}
		delete[] Pnm[n];
		delete[] dPnm[n];
		
		delete[] cosmp[n];
		delete[] sinmp[n];
	}		
	delete[] Pnm;
	delete[] dPnm;
	
	delete[] cosmp;
	delete[] sinmp;
	
	delete[] r;
	delete[] r1;
	delete[] C;
	delete[] cost;
	delete[] sint;
	delete[] sint1;
	
	delete[] sumr;
	delete[] sumt;
	delete[] sump;
					
}




/***********************************************************************
 * NAME : void Internal::_SphHarm(l,r,t,p,MaxDeg,Br,Bt,Bp)
 * 
 * DESCRIPTION : Calculate the magnetic field using spherical harmonics.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	*r			Radial coordinate (planetary radii)
 * 		double 	*t			Theta, colatitude (radians)
 * 		double	*p			Phi, azimuth (radians)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	*Br			Radial field component (nT)
 * 		double 	*Bt			Theta component (nT)
 * 		double 	*Bp			Phi component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::_SphHarm(double r0, double t, double p,
						double *Br, double *Bt, double *Bp) {
	/* rescale r */
	int i;
	double r;
	r = r0*rscale_;
	
	/* set the maximum degree of the model to use */
	int nmax = ncur_[0];
	
	/* create arrays for the Legendre polynomials */
	int n, m;
	
	/* create some arrays to be used in the field calculation */
	double r1;
	double C;
	double cost;
	double sint;
	double sint1;
	r1 = 1.0/r;
	C = r1*r1;
	cost = cos(t);
	sint = sin(t);
	if (sint == 0.0) {
		sint1 = 0.0;
	} else {
		sint1 = 1.0/sint;
	}


	for (m=0;m<=nmax_;m++) {
		if (m == 0) {
			cosmp_[0] = 1.0;
			sinmp_[0] = 0.0;
		} else {
			cosmp_[m] = cos(((double) m)*p);
			sinmp_[m] = sin(((double) m)*p);
		}
	}
	double sumr;
	double sumt;
	double sump;
	
	
	/* calculate the Legendre polynomials */
	_Legendre(cost,sint,nmax,Pnm_,dPnm_);
	
	/* set B components to 0 */
	Br[0] = 0.0;
	Bt[0] = 0.0;
	Bp[0] = 0.0;

	
	/* now start summing stuff up */
	for (n=1;n<=nmax;n++) {
		/* zero the sum arrays and update the C parameter */
		C = C*r1;
		sumr = 0.0;
		sumt = 0.0;
		sump = 0.0;
				
		/* start summing stuff */
		for (m=0;m<=n;m++) {
			sumr += Pnm_[n][m]*(g_[n][m]*cosmp_[m] + h_[n][m]*sinmp_[m]);
			sumt += dPnm_[n][m]*(g_[n][m]*cosmp_[m] + h_[n][m]*sinmp_[m]);
			sump += ((double) m)*Pnm_[n][m]*(h_[n][m]*cosmp_[m] - g_[n][m]*sinmp_[m]);

		}
		
		/* now calculate B */
		Br[0] += C*(n+1)*sumr;
		Bt[0] += -C*sumt;
		Bp[0] += -C*sump;
		
		
	}
	
	/* finally multiply by 1/sintheta */
	Bp[0] = sint1*Bp[0];
	
					
}



/***********************************************************************
 * NAME : void Internal::Field(l,r,t,p,Br,Bt,Bp)
 * 
 * DESCRIPTION : Calculate the magnetic field using current degree.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	*r			Radial coordinate (planetary radii)
 * 		double 	*t			Theta, colatitude (radians)
 * 		double	*p			Phi, azimuth (radians)			
 * 
 * 
 * OUTPUTS :
 * 		double 	*Br			Radial field component (nT)
 * 		double 	*Bt			Theta component (nT)
 * 		double 	*Bp			Phi component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::Field(int l, double *r, double *t, double *p,
						double *Br, double *Bt, double *Bp) {
	
	int i;
	/* call the model */
	for (i=0;i<l;i++) {
		_SphHarm(r[i],t[i],p[i],&Br[i],&Bt[i],&Bp[i]);
	}
	
}

/***********************************************************************
 * NAME : void Internal::Field(l,r,t,p,MaxDeg,Br,Bt,Bp)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	*r			Radial coordinate (planetary radii)
 * 		double 	*t			Theta, colatitude (radians)
 * 		double	*p			Phi, azimuth (radians)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	*Br			Radial field component (nT)
 * 		double 	*Bt			Theta component (nT)
 * 		double 	*Bp			Phi component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::Field(int l, double *r, double *t, double *p,
					int MaxDeg, double *Br, double *Bt, double *Bp) {
	
	/* set the model degree */
	SetDegree(MaxDeg);

	int i;
	/* call the model */
	for (i=0;i<l;i++) {
		_SphHarm(r[i],t[i],p[i],&Br[i],&Bt[i],&Bp[i]);
	}
	

}

/***********************************************************************
 * NAME : void Internal::Field(r,t,p,Br,Bt,Bp)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		double	r			Radial coordinate (planetary radii)
 * 		double 	t			Theta, colatitude (radians)
 * 		double	p			Phi, azimuth (radians)			
 * 
 * 
 * OUTPUTS :
 * 		double 	Br			Radial field component (nT)
 * 		double 	Bt			Theta component (nT)
 * 		double 	Bp			Phi component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::Field(	double r, double t, double p,
						double *Br, double *Bt, double *Bp) {
	
	/* call the model */
	_SphHarm(r,t,p,Br,Bt,Bp);
	

}


/***********************************************************************
 * NAME : void Internal::Field(r,t,p,MaxDeg,Br,Bt,Bp)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		double	r			Radial coordinate (planetary radii)
 * 		double 	t			Theta, colatitude (radians)
 * 		double	p			Phi, azimuth (radians)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	Br			Radial field component (nT)
 * 		double 	Bt			Theta component (nT)
 * 		double 	Bp			Phi component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::Field(	double r, double t, double p, int MaxDeg,
						double *Br, double *Bt, double *Bp) {
	
	/* set the model degree */
	SetDegree(MaxDeg);

	/* call the model */
	_SphHarm(r,t,p,Br,Bt,Bp);

}




/***********************************************************************
 * NAME : void Internal::FieldCart(x,y,z,Bx,By,Bz)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		double	x			x coordinate (planetary radii)
 * 		double 	y			y coordinate (planetary radii)
 * 		double	z			z coordinate (planetary radii)			
 * 
 * 
 * OUTPUTS :
 * 		double 	Bx			x field component (nT)
 * 		double 	By			y field component (nT)
 * 		double 	Bz			z field component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::FieldCart(	double x, double y, double z,
							double *Bx, double *By, double *Bz) {
	
	/* convert to polar */
	double r, t, p, Br, Bt, Bp;
	_Cart2Pol(x,y,z,&r,&t,&p);

	/* call the model */
	_SphHarm(r,t,p,&Br,&Bt,&Bp);

	/* convert B to Cartesian */
	_BPol2BCart(t,p,Br,Bt,Bp,Bx,By,Bz);
}



/***********************************************************************
 * NAME : void Internal::FieldCart(x,y,z,MaxDeg,Bx,By,Bz)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		double	x			x coordinate (planetary radii)
 * 		double 	y			y coordinate (planetary radii)
 * 		double	z			z coordinate (planetary radii)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	Bx			x field component (nT)
 * 		double 	By			y field component (nT)
 * 		double 	Bz			z field component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void Internal::FieldCart(	double x, double y, double z, int MaxDeg,
							double *Bx, double *By, double *Bz) {
	
	/* set the model degree */
	SetDegree(MaxDeg);
	
	/* convert to polar */
	double r, t, p, Br, Bt, Bp;
	_Cart2Pol(x,y,z,&r,&t,&p);

	/* call the model */
	_SphHarm(r,t,p,&Br,&Bt,&Bp);

	/* convert B to Cartesian */
	_BPol2BCart(t,p,Br,Bt,Bp,Bx,By,Bz);
}






/***********************************************************************
 * NAME : void Internal::_Cart2Pol(x,y,z,r,t,p)
 * 
 * DESCRIPTION : Convert Cartesian to polar.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
 * 		double	x			x 
 * 		double 	y			y 
 * 		double	z			z 			
 * 
 * 
 * OUTPUTS :
 * 		double 	*r			Radial component
 * 		double 	*t			Theta component
 * 		double 	*p			Phi component 
 * 
 * 
 * 
 * ********************************************************************/
void Internal::_Cart2Pol(	double x, double y, double z,
							double *r, double *t, double *p) {
	
	double pi2 = M_PI*2;
	r[0] = sqrt(x*x + y*y + z*z);
	t[0] = acos(z/r[0]);
	p[0] = fmod(atan2(y,x) + pi2,pi2);
	
}

/***********************************************************************
 * NAME : void Internal::_BPol2Cart(t,p,Br,Bt,Bp,Bx,By,Bz)
 * 
 * DESCRIPTION : Convert polar field to Cartesian.
 * 
 * INPUTS : 
 * 		double	t			t Theta position
 * 		double 	p			p Phi position
 * 		double	Br			Radial field 			
 * 		double	Bt			Theta field 			
 * 		double	Bp			Phi field 			
 * 
 * 
 * OUTPUTS :
 * 		double 	*Bx			x component
 * 		double 	*By			y component
 * 		double 	*Bz			z component 
 * 
 * 
 * 
 * ********************************************************************/
void Internal::_BPol2BCart(	double t, double p,
							double Br, double Bt, double Bp,
							double *Bx, double *By, double *Bz) {
	
	double cost, cosp, sint ,sinp;
	cost = cos(t);
	cosp = cos(p);
	sint = sin(t);
	sinp = sin(p);
	Bx[0] = Br*sint*cosp + Bt*cost*cosp - Bp*sinp;
	By[0] = Br*sint*sinp + Bt*cost*sinp + Bp*cosp;
	Bz[0] = Br*cost - Bt*sint;
	
								
}
