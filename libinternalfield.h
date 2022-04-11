#ifndef __LIBINTERNALFIELD_H__
#define __LIBINTERNALFIELD_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>


#define INTERNALFIELD_VERSION_MAJOR 0
#define INTERNALFIELD_VERSION_MINOR 0
#define INTERNALFIELD_VERSION_PATCH 1

/* list of model names */
extern std::vector<std::string> modelNames;

/* pointers to the memory where coefficients are stored */
extern unsigned char _binary_jpl15ev_bin_start;
extern unsigned char _binary_sha_bin_start;
extern unsigned char _binary_isaac_bin_start;
extern unsigned char _binary_jpl15evs_bin_start;
extern unsigned char _binary_u17ev_bin_start;
extern unsigned char _binary_vit4_bin_start;
extern unsigned char _binary_vipal_bin_start;
extern unsigned char _binary_vip4_bin_start;
extern unsigned char _binary_langlais2019_bin_start;
extern unsigned char _binary_gsfc15ev_bin_start;
extern unsigned char _binary_o6_bin_start;
extern unsigned char _binary_p11a_bin_start;
extern unsigned char _binary_v117ev_bin_start;
extern unsigned char _binary_gsfc13ev_bin_start;
extern unsigned char _binary_ness1975_bin_start;
extern unsigned char _binary_jrm09_bin_start;
extern unsigned char _binary_o4_bin_start;
extern unsigned char _binary_gsfc15evs_bin_start;
extern unsigned char _binary_jrm33_bin_start;


/* map the model names to their pointers */
extern std::map<std::string,unsigned char*> modelMap;

/* fucntions to return the pointer to a model given a string/const char */

/***********************************************************************
 * NAME : getModelCoeffPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to the memory address
 *			where the model coefficients are stored.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		unsigned char *ptr	Pointer to model data.
 *
 **********************************************************************/
unsigned char* getModelCoeffPointer(std::string Model);

/***********************************************************************
 * NAME : getModelCoeffPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to the memory address
 *			where the model coefficients are stored.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		unsigned char *ptr	Pointer to model data.
 *
 **********************************************************************/
unsigned char* getModelCoeffPointer(const char *Model);



/* models! */
extern Internal jpl15ev;
extern Internal sha;
extern Internal isaac;
extern Internal jpl15evs;
extern Internal u17ev;
extern Internal vit4;
extern Internal vipal;
extern Internal vip4;
extern Internal langlais2019;
extern Internal gsfc15ev;
extern Internal o6;
extern Internal p11a;
extern Internal v117ev;
extern Internal gsfc13ev;
extern Internal ness1975;
extern Internal jrm09;
extern Internal o4;
extern Internal gsfc15evs;
extern Internal jrm33;


/* map the model names to their model object pointers */
extern std::map<std::string,Internal*> modelPtrMap;

/* functions to return the pointer to a model object given a string */

/***********************************************************************
 * NAME : getModelObjPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a model object.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		Internal *ptr		Pointer to model object.
 *
 **********************************************************************/
Internal* getModelObjPointer(std::string Model);

/***********************************************************************
 * NAME : getModelObjPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a model object.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		Internal *ptr		Pointer to model object.
 *
 **********************************************************************/
Internal* getModelObjPointer(const char *Model);

/* a function to return a list of the models available */
/***********************************************************************
 * NAME : listAvailableModels()
 *
 * DESCRIPTION : Function to return a list of model names available.
 *		
 * RETURNS :
 *		vector<string> Models	Model list.
 *
 **********************************************************************/
std::vector<std::string> listAvailableModels();

/* map of strings to direct field model function pointers */
typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);
extern std::map<std::string,modelFieldPtr> modelFieldPtrMap;

/* functions to return pointer to model field function */

/***********************************************************************
 * NAME : getModelFieldPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a wrapper function
 * 			which will provide a single field vector at a single 
 * 			position.
 *		
 * INPUTS : 
 *		std::string Model		Model name (use lower case!).
 *
 * RETURNS :
 *		modelFieldPtr *ptr		Pointer to model wrapper.
 *
 **********************************************************************/
modelFieldPtr getModelFieldPtr(std::string Model);

/***********************************************************************
 * NAME : getModelFieldPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a wrapper function
 * 			which will provide a single field vector at a single 
 * 			position.
 *		
 * INPUTS : 
 *		const char *Model		Model name (use lower case!).
 *
 * RETURNS :
 *		modelFieldPtr *ptr		Pointer to model wrapper.
 *
 **********************************************************************/
modelFieldPtr getModelFieldPtr(const char *Model);

/* functions to directly call each model for a single Cartesian vector (this will be used for tracing) */

/***********************************************************************
 * NAME : XXXXXField(x,y,z,Bx,By,Bz)
 *
 * DESCRIPTION : Model wrapper functions which can be passed to the 
 * 			tracing code. Replace XXXXXX with the name of the model...
 *		
 * INPUTS : 
 *		double	x			x coordinate in planetary radii.
 *		double	y			y coordinate in planetary radii.
 *		double	z			z coordinate in planetary radii.
 *
 * OUTPUTS :
 *		double	*Bx			x component of the field (nT).
 *		double	*By			y component of the field (nT).
 *		double	*Bz			z component of the field (nT).
 * 
 **********************************************************************/
void jpl15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void shaField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void isaacField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jpl15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void u17evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void vit4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void vipalField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void vip4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void gsfc15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void o6Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void p11aField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void v117evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void gsfc13evField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void ness1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jrm09Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void o4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void gsfc15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
void jrm33Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);


/* based upon https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/ */
/***********************************************************************
 * NAME : vector<> listMapKeys(inmap)
 * 
 * DESCRIPTION : List the keys used for a std::map.
 * 
 * INPUTS : 
 * 		map		inmap		std::map instance			
 * 
 * 
 * RETURNS :
 * 		vector	keys		vector object containing a list of the map 
 * 							keys
 * 
 * 
 * 
 * ********************************************************************/
template <typename Tkey, typename Tval> 
std::vector<Tkey> listMapKeys(std::map<Tkey,Tval> const &inmap) {
	std::vector<Tkey> keys;
	for (auto const& element: inmap) {
		keys.push_back(element.first);
	}
	return keys;
}	





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
		
		/* hack to scale r or x,y,z because some models use a different
		 * definition for the planetary radius - notably the different 
		 * Jupiter models - this should be rpgood/rpbad, where rpgood
		 * is the accepted planetary radius and rpbad is the erroneous
		 * one - this will be then multiplied by r: rnew = r*rscale_
		 * where rscale_ = rgood/rbad */
		double rscale_;
		
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
		std::string CurrentModelName_;


		/* coordinate/field vector rotation */
		bool init_;
		bool CartIn_;
		bool CartOut_;
		void _Cart2Pol(int,double*,double*,double*,double*,double*,double*);
		void _BPol2BCart(int,double*,double*,double*,double*,double*,double*,double*,double*);
};



/* we want to initialize the model objects witht heir parameters */
extern InternalModel internalModel;

extern "C" {
	/* these wrappers can be used to get the magnetic field vectors */

	/***********************************************************************
	 * NAME : InternalField(n,p0,p1,p2,B0,B1,B2)
	 *
	 * DESCRIPTION : Call the model field function. Coordinates depend 
	 * 		on the model  configuration
	 *		
	 * INPUTS : 
	 * 		int		n			Number of array elements
	 *		double	*p0			x or r coordinate in planetary radii.
	 *		double	*p1			y coordinate in planetary radii or theta 
	 * 							in radians.
	 *		double	*p2			z coordinate in planetary radii or phi
	 * 							in radians.
	 *
	 * OUTPUTS :
	 *		double	*B0			x or r component of the field (nT).
	 *		double	*B1			y or theta component of the field (nT).
	 *		double	*B2			z or phi component of the field (nT).
	 * 
	 **********************************************************************/
	void InternalField(int n, double *p0, double *p1, double *p2,
						double *B0, double *B1, double *B2);

	/***********************************************************************
	 * NAME : InternalFieldDeg(n,p0,p1,p2,MaxDeg,B0,B1,B2)
	 *
	 * DESCRIPTION : Call the model field function. Coordinates depend 
	 * 		on the model  configuration
	 *		
	 * INPUTS : 
	 * 		int		n			Number of array elements
	 *		double	*p0			x or r coordinate in planetary radii.
	 *		double	*p1			y coordinate in planetary radii or theta 
	 * 							in radians.
	 *		double	*p2			z coordinate in planetary radii or phi
	 * 							in radians.
	 * 		int 	MaxDeg		Maximum model degree to use.
	 *
	 * OUTPUTS :
	 *		double	*B0			x or r component of the field (nT).
	 *		double	*B1			y or theta component of the field (nT).
	 *		double	*B2			z or phi component of the field (nT).
	 * 
	 **********************************************************************/
	void InternalFieldDeg(int n, double *p0, double *p1, double *p2,
						int MaxDeg, double *B0, double *B1, double *B2);

	/***********************************************************************
	 * NAME : SetInternalCFG(Model,CartIn,CartOut,MaxDeg)
	 *
	 * DESCRIPTION : Configure the current model.
	 *		
	 * INPUTS : 
	 * 		const char *Model		Model name.
	 * 		bool CartIn				Set to True for Cartesian input
	 * 								coordinates or false for polar.
	 * 		bool CartOut			As above, but for the output.
	 * 		int  MaxDeg				Maximum degree used by model
	 * 
	 **********************************************************************/
	void SetInternalCFG(const char *Model, bool CartIn, bool CartOut, int MaxDeg);

	/***********************************************************************
	 * NAME : GetInternalCFG(Model,CartIn,CartOut,MaxDeg)
	 *
	 * DESCRIPTION : Return the current model configuration.
	 *		
	 * OUTPUTS : 
	 * 		char *Model				Model name.
	 * 		bool CartIn				True for Cartesian input
	 * 								coordinates or false for polar.
	 * 		bool CartOut			As above, but for the output.
	 * 		int  MaxDeg				Maximum degree used by model
	 * 
	 **********************************************************************/
	void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut, int *MaxDeg);

	
}
#endif