#include "internalmodel.h" 

/***********************************************************************
 * NAME : InternalModel::InternalModel()
 * 
 * DESCRIPTION : Initialize the InternalModel object.
 * 
 * ********************************************************************/
InternalModel::InternalModel() {
	copy_ = false;
	init_ = new bool[1];
	init_[0]  = false;
	CheckInit();
}

InternalModel::InternalModel(const InternalModel &obj) {
	
	copy_ = true;
	init_ = obj.init_;
	CartIn_ = obj.CartIn_;
	CartOut_ = obj.CartOut_;
	Models_ = obj.Models_;
	ModelNames_ = obj.ModelNames_;
	//CurrentModel_ = obj.CurrentModel_;
	
	CurrentModelName_ = obj.CurrentModelName_;
	CurrentModel_ = Models_[CurrentModelName_[0]];
	

}

/***********************************************************************
 * NAME : void InternalModel::CheckInit()
 * 
 * DESCRIPTION : Check that the object has been initialized.
 * 
 * ********************************************************************/
void InternalModel::CheckInit() {
	
	if (!init_[0]) {
		Init();
		init_[0] = true;
	}
}

/***********************************************************************
 * NAME : void InternalModel::Init()
 * 
 * DESCRIPTION : Initialize the InternalModel object by reading the
 * 				available models and storing their object pointers.
 * 
 * ********************************************************************/
void InternalModel::Init() {	
	/* load all of the models into a map*/
	
	/* start by getting the models available */
	ModelNames_ = listAvailableModels();
	
	/* loop through each one and add to the map */
	int i;
	for (i=0;i<ModelNames_.size();i++) {
		Models_[ModelNames_[i]] = &getModelObjPointer(ModelNames_[i])();
	}
		
	/* set the current model */
	CurrentModel_ = Models_["jrm09"];
	CurrentModelName_ = new std::string[1];
	CurrentModelName_[0] = "jrm09";
	
	/* default parameters */
	CartIn_ = new bool[1];
	CartOut_ = new bool[1];
	CartIn_[0] = true;
	CartOut_[0] = true;

	
}


InternalModel::~InternalModel() {
	if (!copy_) {
		if (init_[0]) {
			delete[] CurrentModelName_;
			delete[] CartIn_;
			delete[] CartOut_;
		}
		delete[] init_;
	}
}	

/***********************************************************************
 * NAME : void InternalModel::SetCartIn(CartIn)
 * 
 * DESCRIPTION : Set input coordinate system either to Cartesian or 
 * 				spherical polar.
 * 
 * INPUTS :
 * 		bool	CartIn		If true: input coordinates are Cartesian,
 * 							if false: input coordinates are polar.
 * 
 * ********************************************************************/
void InternalModel::SetCartIn(bool CartIn) {
	CheckInit();
	CartIn_[0] = CartIn;
}

/***********************************************************************
 * NAME : bool InternalModel::GetCartIn(CartIn)
 * 
 * DESCRIPTION : Return whether input coordinates are Cartesian or not.
 * 
 * OUTPUTS :
 * 		bool	CartIn		If true: input coordinates are Cartesian,
 * 							if false: input coordinates are polar.
 * 
 * ********************************************************************/
bool InternalModel::GetCartIn() {
	CheckInit();
	return CartIn_[0];
}

/***********************************************************************
 * NAME : void InternalModel::SetCartOut(CartOut)
 * 
 * DESCRIPTION : Set output coordinate system either to Cartesian or 
 * 				spherical polar.
 * 
 * INPUTS :
 * 		bool	CartOut		If true: output coordinates are Cartesian,
 * 							if false: output coordinates are polar.
 * 
 * ********************************************************************/
void InternalModel::SetCartOut(bool CartOut) {
	CheckInit();
	CartOut_[0] = CartOut;
}

/***********************************************************************
 * NAME : bool InternalModel::GetCartOut(CartOut)
 * 
 * DESCRIPTION : Return whether output coordinates are Cartesian or not.
 * 
 * OUTPUTS :
 * 		bool	CartOut		If true: output coordinates are Cartesian,
 * 							if false: output coordinates are polar.
 * 
 * ********************************************************************/
bool InternalModel::GetCartOut() {
	CheckInit();
	return CartOut_[0];
}

/***********************************************************************
 * NAME : void InternalModel::SetModel(ModelName)
 * 
 * DESCRIPTION : Set the current model to use.
 * 
 * INPUTS :
 * 		const char *ModelName	The name of the model to use.
 * 
 * ********************************************************************/
void InternalModel::SetModel(const char *ModelName) {
	CheckInit();
	/* convert the input to a string because I am a n00b*/
	std::string ModelIn = ModelName;
	
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
		CurrentModelName_[0] = ModelIn;
	} else {
		/* ignore the new model, print a warning */
		printf("Invalid model name: %s, ignoring...\n",ModelIn.c_str());
	}
	
}

/***********************************************************************
 * NAME : void InternalModel::GetModel(ModelName)
 * 
 * DESCRIPTION : Get the current model in use.
 * 
 * INPUTS :
 * 		char *ModelName		The name of the model being used.
 * 
 * ********************************************************************/
void InternalModel::GetModel(char *ModelName) {
	CheckInit();
	strcpy(ModelName,CurrentModelName_[0].c_str());
}


/***********************************************************************
 * NAME : void InternalModel::SetDegree(n)
 * 
 * DESCRIPTION : Set the maximum degree of this model to use.
 * 
 * INPUTS : 
 * 		int		n			Model degree
 * 
 * ********************************************************************/
void InternalModel::SetDegree(int n) {
	CheckInit();
	CurrentModel_->SetDegree(n);
	
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
int InternalModel::GetDegree() {
	return CurrentModel_->GetDegree();
	
}


/***********************************************************************
 * NAME : void InternalModel::Field(n,p0,p1,p2,B0,B1,B2)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		int		n			Number of elements
 * 		double	*p0			Radial or x coordinate (planetary radii)
 * 		double 	*p1			Theta, colatitude (radians) or y (planetary radii)
 * 		double	*p2			Phi, azimuth (radians) or z (planetary radii)			
 * 
 * 
 * OUTPUTS :
 * 		double 	*B0			Radial or x field component (nT)
 * 		double 	*B1			Theta or y component (nT)
 * 		double 	*B2			Phi or z component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void InternalModel::Field(int n, double *p0, double *p1, double *p2,
							double *B0, double *B1, double *B2) {
	
	CheckInit();
	/* some IO pointers */
	int i;
	double *r, *t, *p, *Br, *Bt, *Bp;
	
	/* set the input pointers */
	if (!CartIn_[0]) {
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
	if (!CartOut_[0]) {
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
	if (CartOut_[0]) {
		_BPol2BCart(n,t,p,Br,Bt,Bp,B0,B1,B2);
		delete[] Br;
		delete[] Bt;
		delete[] Bp;
	}
	
	/* delete input arrays */
	if (CartIn_[0]) {
		delete[] r;
		delete[] t;
		delete[] p;
	}
}
								

/***********************************************************************
 * NAME : void InternalModel::Field(n,p0,p1,p2,MaxDeg,B0,B1,B2)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		int		n			Number of elements
 * 		double	*p0			Radial or x coordinate (planetary radii)
 * 		double 	*p1			Theta, colatitude (radians) or y (planetary radii)
 * 		double	*p2			Phi, azimuth (radians) or z (planetary radii)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	*B0			Radial or x field component (nT)
 * 		double 	*B1			Theta or y component (nT)
 * 		double 	*B2			Phi or z component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void InternalModel::Field(int n, double *p0, double *p1, double *p2,
							int MaxDeg, double *B0, double *B1, double *B2) {

	CheckInit();
	/* some IO pointers */
	int i;
	double *r, *t, *p, *Br, *Bt, *Bp;
	
	/* set the input pointers */
	if (!CartIn_[0]) {
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
	if (!CartOut_[0]) {
		Br = B0;
		Bt = B1;
		Bp = B2;
	} else { 
		Br = new double[n];
		Bt = new double[n];
		Bp = new double[n];		
	}
	
	/* store the existing model degree and set current*/
	int OldDeg = CurrentModel_->GetDegree();
	CurrentModel_->SetDegree(MaxDeg);
	
	/* call the model */
	CurrentModel_->Field(n,r,t,p,Br,Bt,Bp);
	
	/* return the original degree */
	CurrentModel_->SetDegree(OldDeg);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_[0]) {
		_BPol2BCart(n,t,p,Br,Bt,Bp,B0,B1,B2);
		delete[] Br;
		delete[] Bt;
		delete[] Bp;
	}
	
	/* delete input arrays */
	if (CartIn_[0]) {
		delete[] r;
		delete[] t;
		delete[] p;
	}
								
}

/***********************************************************************
 * NAME : void InternalModel::Field(p0,p1,p2,B0,B1,B2)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		double	p0			Radial or x coordinate (planetary radii)
 * 		double 	p1			Theta, colatitude (radians) or y (planetary radii)
 * 		double	p2			Phi, azimuth (radians) or z (planetary radii)			
 * 
 * 
 * OUTPUTS :
 * 		double 	*B0			Radial or x field component (nT)
 * 		double 	*B1			Theta or y component (nT)
 * 		double 	*B2			Phi or z component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void InternalModel::Field(	double p0, double p1, double p2,
							double *B0, double *B1, double *B2) {

	CheckInit();
	/* temporary variables*/
	double r, t, p, Br, Bt, Bp;
	
	/* convert input coords (or not) */
	if (!CartIn_[0]) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		_Cart2Pol(1,&p0,&p1,&p2,&r,&t,&p);
	}
	
	CurrentModel_->Field(r,t,p,&Br,&Bt,&Bp);

	/* rotate field vector if needed and delete output arrays */
	if (CartOut_[0]) {
		_BPol2BCart(1,&t,&p,&Br,&Bt,&Bp,B0,B1,B2);
	} else {
		B0[0] = Br;
		B1[0] = Bt;
		B2[0] = Bp;
	}								
}

/***********************************************************************
 * NAME : void InternalModel::Field(p0,p1,p2,MaxDeg,B0,B1,B2)
 * 
 * DESCRIPTION : Calculate the magnetic field.
 * 
 * INPUTS : 
 * 		double	p0			Radial or x coordinate (planetary radii)
 * 		double 	p1			Theta, colatitude (radians) or y (planetary radii)
 * 		double	p2			Phi, azimuth (radians) or z (planetary radii)			
 * 		int		MaxDeg		Maximum degree of the model to use.
 * 
 * 
 * OUTPUTS :
 * 		double 	*B0			Radial or x field component (nT)
 * 		double 	*B1			Theta or y component (nT)
 * 		double 	*B2			Phi or z component (nT)
 * 
 * 
 * 
 * ********************************************************************/
void InternalModel::Field(	double p0, double p1, double p2, int MaxDeg,
							double *B0, double *B1, double *B2) {
	
	CheckInit();
	/* temporary variables*/
	double r, t, p, Br, Bt, Bp;
	
	/* convert input coords (or not) */
	if (!CartIn_[0]) {
		r = p0;
		t = p1;
		p = p2;
	} else { 
		_Cart2Pol(1,&p0,&p1,&p2,&r,&t,&p);
	}
	

	/* store the existing model degree and set current*/
	int OldDeg = CurrentModel_->GetDegree();
	CurrentModel_->SetDegree(MaxDeg);
	
	/* call the model */
	CurrentModel_->Field(r,t,p,&Br,&Bt,&Bp);
	
	/* return the original degree */
	CurrentModel_->SetDegree(OldDeg);
	
	/* rotate field vector if needed and delete output arrays */
	if (CartOut_[0]) {
		_BPol2BCart(1,&t,&p,&Br,&Bt,&Bp,B0,B1,B2);
	} else {
		B0[0] = Br;
		B1[0] = Bt;
		B2[0] = Bp;
	}								
}


/***********************************************************************
 * NAME : void InternalModel::_Cart2Pol(l,x,y,z,r,t,p)
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

/***********************************************************************
 * NAME : void InternalModel::_BPol2Cart(l,t,p,Br,Bt,Bp,Bx,By,Bz)
 * 
 * DESCRIPTION : Convert polar field to Cartesian.
 * 
 * INPUTS : 
 * 		int		l			Number of elements
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
