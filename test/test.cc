#include "test.h"


int main() {

	/* some input coordinates to test a few models with */
	std::array<double,16> r = {3,3,3,3, 3,3,3,3, 3,3,3,3, 3,3,3,3};
	std::array<double,16> tdeg = {10,10,10,10,55,55,55,55,90,90,90,90,130,130,130,130};
	std::array<double,16> pdeg = {0,27,180,340, 0,27,180,340, 0,27,180,340, 0,27,180,340};
	std::array<double,16> t;
	std::array<double,16> p;


	/* convert to radians */
	int i;
	double deg2rad = M_PI/180.0;
	for (i=0;i<t.size();i++) {
		t[i] = deg2rad*tdeg[i];
		p[i] = deg2rad*pdeg[i];
	}
	
	/*output arrays */
	std::array<double,16> Br;
	std::array<double,16> Bt;
	std::array<double,16> Bp;
	

	
	
	/* output strings */
	const char s0[] = "  R  | Theta |  Phi  |         Br         |         Bt         |         Bp         \n";
	const char s1[] = "-----|-------|-------|--------------------|--------------------|--------------------\n"; 
	const char *fmt = " %3.1f | %5.1f | %5.1f | %18.11f | %18.11f | %18.11f\n";
	
	/* set model to VIP4 */
	InternalModel internalModel = getInternalModel();
	internalModel.SetModel("vip4");
	internalModel.SetCartIn(false);
	internalModel.SetCartOut(false);
	
	/* call model */
	internalModel.Field((int) r.size(),r.data(),t.data(),p.data(),Br.data(),Bt.data(),Bp.data());
	
	/* print output */
	printf("VIP4 output...\n");
	printf(s0);
	printf(s1);
	for (i=0;i<r.size();i++) {
		printf(fmt,r[i],tdeg[i],pdeg[i],Br[i],Bt[i],Bp[i]);
	}

	/* set model to JRM09 */
	internalModel.SetModel("jrm09");
	internalModel.SetCartIn(false);
	internalModel.SetCartOut(false);
	
	/* call model */
	internalModel.Field((int) r.size(),r.data(),t.data(),p.data(),Br.data(),Bt.data(),Bp.data());
	
	/* print output */
	printf("JRM09 output...\n");
	printf(s0);
	printf(s1);
	for (i=0;i<r.size();i++) {
		printf(fmt,r[i],tdeg[i],pdeg[i],Br[i],Bt[i],Bp[i]);
	}
	
	double bx,by,bz;
	jrm09Field(5.0,0.0,0.0,&bx,&by,&bz);
	printf("B: %f %f %f\n",bx,by,bz);
	
	printf("\nTesting Model CFG\n");
	char mstr[32];
	bool cartin,cartout;
	int deg;
	printf("Initial Config:\n");
	GetInternalCFG(mstr,&cartin,&cartout,&deg);
	printf("%s %d %d %d\n",mstr,cartin,cartout,deg);
	printf("Attempting to change config to\n jrm33 0 0 15\n");
	SetInternalCFG("jrm33",false,false,15);
	GetInternalCFG(mstr,&cartin,&cartout,&deg);
	printf("Result:\n");
	printf("%s %d %d %d\n",mstr,cartin,cartout,deg);
	
	
}
	
