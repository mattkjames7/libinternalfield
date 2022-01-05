#include "internalmodel.h"

InternalModel::InternalModel() {
	
	/* load all of the models into a map*/
	
	

		
	/* set the current model */
	CurrentModel_ = jrm09_;
	strcpy(CurrentModelName_,"JRM09");
	
	/* default parameters */
	CartIn_ = true;
	CartOut_ = true;
	CurrentModel_->SetCartIn(CartIn_);
	CurrentModel_->SetCartOut(CartOut_);
	
}


InternalModel::~InternalModel() {

}	

void Internal::SetCartIn(bool CartIn) {
	CartIn_ = CartIn;
}

bool Internal::GetCartIn() {
	return CartIn_;
}

void Internal::SetCartOut(bool CartOut) {
	CartOut_ = CartOut;
}

bool Internal::GetCartOut() {
	return CartOut_;
}

void InternalModel::SetModel(char *ModelName) {

	/* Find the correct model and set it */
	bool validmodel = true;
	if (strcmp(ModelName,"JRM09") == 0) {
		CurrentModel_ = jrm09_;
	} else if (strcmp(ModelName,"JRM33") == 0) {
		CurrentModel_ = jrm33_;
	} else if (strcmp(ModelName,"VIP4") == 0) {
		CurrentModel_ = vip4_;
	} else if (strcmp(ModelName,"GSFC13EV") == 0) {
		CurrentModel_ = gsfc13ev_;
	} else if (strcmp(ModelName,"GSFC15EV") == 0) {
		CurrentModel_ = gsfc15ev_;
	} else if (strcmp(ModelName,"GSFC15EVS") == 0) {
		CurrentModel_ = gsfc15evs_;
	} else if (strcmp(ModelName,"ISAAC") == 0) {
		CurrentModel_ = isaac_;
	} else if (strcmp(ModelName,"JPL15EV") == 0) {
		CurrentModel_ = jpl15ev_;
	} else if (strcmp(ModelName,"JPL15EVS") == 0) {
		CurrentModel_ = jpl15evs_;
	} else if (strcmp(ModelName,"O4") == 0) {
		CurrentModel_ = o4_;
	} else if (strcmp(ModelName,"O6") == 0) {
		CurrentModel_ = o6_;
	} else if (strcmp(ModelName,"P11A") == 0) {
		CurrentModel_ = p11a_;
	} else if (strcmp(ModelName,"SHA") == 0) {
		CurrentModel_ = sha_;
	} else if (strcmp(ModelName,"U17EV") == 0) {
		CurrentModel_ = u17ev_;
	} else if (strcmp(ModelName,"V117EV") == 0) {
		CurrentModel_ = v117ev_;
	} else if (strcmp(ModelName,"VIPAL") == 0) {
		CurrentModel_ = vipal_;
	} else if (strcmp(ModelName,"VIT4") == 0) {
		CurrentModel_ = vit4_;
	} else {
		printf("Invalid model name: %s, ignoring...\n",ModelName);
		validmodel = false;
	}
	
	/* change the stored model name and set model parameters */
	if (validmodel) {
		strcpy(CurrentModelName_,ModelName);
		CurrentModel_->SetCartIn(CartIn_);
		CurrentModel_->SetCartOut(CartOut_);
	}
}

void InternalModel::GetModel(char *ModelName) {
	
	strcpy(ModelName,CurrentModelName_);
}

void InternalModel::Field(int n, double *p0, double *p1, double *p2,
							double *B0, double *B1, double *B2) {
	
	/* some IO pointers */
	int i;
	double *r, *t, *p, *Br, *Bt, *Bp;
	
	/* set the input pointers */
	if (!CartIn_) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		r = new double[l];
		t = new double[l];
		p = new double[l];
		_Cart2Pol(l,p0,p1,p2,r,t,p);
	}

	/* set up the output pointers */
	if (!CartOut_) {
		Br = B0;
		Bt = B1;
		Bp = B2;
	} else { 
		Br = new double[l];
		Bt = new double[l];
		Bp = new double[l];		
	}

	CurrentModel_->Field(n,r,t,p,Br,Bt,Bp);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_) {
		_BPol2BCart(l,t,p,Br,Bt,Bp,B0,B1,B2);
		delete[] Br;
		delete[] Bt;
		delete[] Bp;
	}
	
	/* delete input arrays */
	if (CartIn_) {
		delete[] r;
		delete[] t;
		delete[] p;
	}
}
								
}

void InternalModel::Field(int n, double *p0, double *p1, double *p2,
							int MaxDeg, double *B0, double *B1, double *B2) {

	
	/* some IO pointers */
	int i;
	double *r, *t, *p, *Br, *Bt, *Bp;
	
	/* set the input pointers */
	if (!CartIn_) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		r = new double[l];
		t = new double[l];
		p = new double[l];
		_Cart2Pol(l,p0,p1,p2,r,t,p);
	}
	
	/* set up the output pointers */
	if (!CartOut_) {
		Br = B0;
		Bt = B1;
		Bp = B2;
	} else { 
		Br = new double[l];
		Bt = new double[l];
		Bp = new double[l];		
	}
	
	CurrentModel_->Field(n,r,t,p,MaxDeg,Br,Bt,Bp);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_) {
		_BPol2BCart(l,t,p,Br,Bt,Bp,B0,B1,B2);
		delete[] Br;
		delete[] Bt;
		delete[] Bp;
	}
	
	/* delete input arrays */
	if (CartIn_) {
		delete[] r;
		delete[] t;
		delete[] p;
	}
								
}

void InternalModel::Field(	double p0, double p1, double p2,
							double *B0, double *B1, double *B2) {


	/* temporary variables*/
	double r, t, p, Br, Bt, Bp;
	
	/* convert input coords (or not) */
	if (!CartIn_) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		_Cart2Pol(1,&p0,&p1,&p2,&r,&t,&p);
	}
	
	CurrentModel_->Field(r,t,p,&Br,&Bt,&Bp);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_) {
		_BPol2BCart(1,&t,&p,&Br,&Bt,&Bp,B0,B1,B2);
	} else {
		B0[0] = Br;
		B1[0] = Bt;
		B2[0] = Bp;
	}								
}

void InternalModel::Field(	double p0, double p1, double p2, int MaxDeg,
							double *B0, double *B1, double *B2) {

	/* temporary variables*/
	double r, t, p, Br, Bt, Bp;
	
	/* convert input coords (or not) */
	if (!CartIn_) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		_Cart2Pol(1,&p0,&p1,&p2,&r,&t,&p);
	}
	
	
	CurrentModel_->Field(r,t,p,MaxDeg,&Br,&Bt,&Bp);
	
	/* rotate field vector if needed and delete output arrays */
	if (CartOut_) {
		_BPol2BCart(1,&t,&p,&Br,&Bt,&Bp,B0,B1,B2);
	} else {
		B0[0] = Br;
		B1[0] = Bt;
		B2[0] = Bp;
	}								
}



void InternalModel::_Cart2Pol(int l, double *x, double *y, double *z,
						double *r, double *t, double *p) {
	
	int i;
	double pi2 = M_PI*2;
	for (i=0;i<l;i++) {
		r[i] = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
		t[i] = acos(z[i]/r[i]);
		p[i] = fmod(atan2(y[i],x[i]) + pi2,pi2);
	}
}

void InternalModel::_BPol2BCart(int l, double *t, double *p,
							double *Br, double *Bt, double *Bp,
							double *Bx, double *By, double *Bz) {
	
	int i;
	double cost, cosp, sint ,sinp;
	for (i=0;i<l;i++) {
		cost = cos(t[i]);
		cosp = cos(p[i]);
		sint = sin(t[i]);
		sinp = sin(p[i]);
		Bx[i] = Br[i]*sint*cosp + Bt[i]*cost*cosp - Bp[i]*sinp;
		By[i] = Br[i]*sint*sinp + Bt[i]*cost*sinp + Bp[i]*cosp;
		Bz[i] = Br[i]*cost - Bt[i]*sint;
	}
								
}
