#include "internalmodel.h" 

InternalModel::InternalModel() {

	init_  = false;
}


void InternalModel::CheckInit() {
	
	if (!init_) {
		Init();
		init_ = true;
	}
}

void InternalModel::Init() {	
	/* load all of the models into a map*/
	
	/* start by getting the models available */
	ModelNames_ = listAvailableModels();
	
	/* loop through each one and add to the map */
	int i;
	for (i=0;i<ModelNames_.size();i++) {
		Models_[ModelNames_[i]] = getModelObjPointer(ModelNames_[i]);
	}
		
	/* set the current model */
	CurrentModel_ = Models_["jrm09"];
	CurrentModelName_ = "jrm09";
	
	/* default parameters */
	CartIn_ = true;
	CartOut_ = true;

	
}


InternalModel::~InternalModel() {

}	

void InternalModel::SetCartIn(bool CartIn) {
	CheckInit();
	CartIn_ = CartIn;
}

bool InternalModel::GetCartIn() {
	CheckInit();
	return CartIn_;
}

void InternalModel::SetCartOut(bool CartOut) {
	CheckInit();
	CartOut_ = CartOut;
}

bool InternalModel::GetCartOut() {
	CheckInit();
	return CartOut_;
}

void InternalModel::SetModel(const char *ModelName) {
	CheckInit();
	/* convert the input to a string because I am a n00b*/
	string ModelIn = ModelName;
	
	/* loop through list of models and check if it's in there*/
	bool validmodel = false;
	for (int i=0;i<ModelNames_.size();i++) {
		if (ModelIn.compare(ModelNames_[i]) == 0) {
			validmodel = true;
			break;
		}
	}
	
	
	if (validmodel) {
		/* set the new model if a valid string has been provided */
		CurrentModel_ = Models_[ModelIn];
		CurrentModelName_ = ModelIn;
	} else {
		/* ignore the new model, print a warning */
		printf("Invalid model name: %s, ignoring...\n",ModelIn.c_str());
	}
	
}

void InternalModel::GetModel(char *ModelName) {
	CheckInit();
	strcpy(ModelName,CurrentModelName_.c_str());
}

void InternalModel::Field(int n, double *p0, double *p1, double *p2,
							double *B0, double *B1, double *B2) {
	
	CheckInit();
	/* some IO pointers */
	int i;
	double *r, *t, *p, *Br, *Bt, *Bp;
	
	/* set the input pointers */
	if (!CartIn_) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		r = new double[n];
		t = new double[n];
		p = new double[n];
		_Cart2Pol(n,p0,p1,p2,r,t,p);
	}

	/* set up the output pointers */
	if (!CartOut_) {
		Br = B0;
		Bt = B1;
		Bp = B2;
	} else { 
		Br = new double[n];
		Bt = new double[n];
		Bp = new double[n];		
	}

	CurrentModel_->Field(n,r,t,p,Br,Bt,Bp);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_) {
		_BPol2BCart(n,t,p,Br,Bt,Bp,B0,B1,B2);
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
								


void InternalModel::Field(int n, double *p0, double *p1, double *p2,
							int MaxDeg, double *B0, double *B1, double *B2) {

	CheckInit();
	/* some IO pointers */
	int i;
	double *r, *t, *p, *Br, *Bt, *Bp;
	
	/* set the input pointers */
	if (!CartIn_) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		r = new double[n];
		t = new double[n];
		p = new double[n];
		_Cart2Pol(n,p0,p1,p2,r,t,p);
	}
	
	/* set up the output pointers */
	if (!CartOut_) {
		Br = B0;
		Bt = B1;
		Bp = B2;
	} else { 
		Br = new double[n];
		Bt = new double[n];
		Bp = new double[n];		
	}
	
	CurrentModel_->Field(n,r,t,p,MaxDeg,Br,Bt,Bp);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_) {
		_BPol2BCart(n,t,p,Br,Bt,Bp,B0,B1,B2);
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

	CheckInit();
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
	
	CheckInit();
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
	CheckInit();
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
	CheckInit();
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
