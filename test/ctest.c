#include <stdio.h>
#include <stdbool.h>
#include <internalfield.h>

int main() {

	printf("Testing C\n");
	
	/* try getting a model function */
	modelFieldPtr model = getModelFieldPtr("jrm33");
	double x = 10.0;
	double y = 10.0;
	double z = 0.0;
	double Bx, By, Bz;
	model(x,y,z,&Bx,&By,&Bz);

	printf("B = [%6.1f,%6.1f,%6.1f] nT at [%4.1f,%4.1f,%4.1f]\n",Bx,By,Bz,x,y,z);

	printf("C test done\n");


}

