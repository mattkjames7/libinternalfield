#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <internalfield.h>


void readTestData(double *Tx, double *Ty, double *Tz) {
	const char *fileName = "data/ctest.bin";

    FILE *file = fopen(fileName, "rb");

    size_t readSize = sizeof(double);
	fread(Tx, readSize, 1, file);
	fread(Ty, readSize, 1, file);
    fread(Tz, readSize, 1, file);

    fclose(file);
}

int main() {

	printf("C Test........................................");
	
	/* try getting a model function */
	modelFieldPtr model = getModelFieldPtr("jrm33");
	double x = 10.0;
	double y = 10.0;
	double z = 0.0;
	double Bx, By, Bz;
	model(x,y,z,&Bx,&By,&Bz);

	/* read in the saved data */
	double Tx, Ty, Tz;
	readTestData(&Tx, &Ty, &Tz);

	/* compare results */
	const double absTol = 1e-3;
	const double relTol = 1e-12;
	bool pass = true;
	double diff, scale, tol;

	diff = fabs(Tx - Bx);
	scale = fmax(fabs(Tx), fabs(Bx));
	tol = fmax(absTol, relTol * scale);
	if (diff > tol) {
		pass = false;
	}

	diff = fabs(Ty - By);
	scale = fmax(fabs(Ty), fabs(By));
	tol = fmax(absTol, relTol * scale);
	if (diff > tol) {
		pass = false;
	}

	diff = fabs(Tz - Bz);
	scale = fmax(fabs(Tz), fabs(Bz));
	tol = fmax(absTol, relTol * scale);
	if (diff > tol) {
		pass = false;
	}

	if (pass) {
		printf("PASS\n");
	} else {
		printf("FAIL\n");
		printf("Expected: [%10.3f, %10.3f, %10.3f]\n",Tx,Ty,Tz);
		printf("Output: [%10.3f, %10.3f, %10.3f]\n",Bx,By,Bz);
	}	


}

