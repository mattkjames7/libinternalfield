#include <iostream>
#include <internalfield.h>
#include <string>
#include <stdio.h>

void testCoeff(std::string model) {

	/* get the memory address first */
	std::map<std::string,unsigned char*> cmap = getCoeffPtrMap();
	unsigned char *ptr = cmap[model];

	/* read the model coefficients*/
	coeffStruct mc;
	readCoeffs(ptr,&(mc.len),&(mc.nmax),&(mc.ndef),&(mc.rscale),
				mc.n,mc.m,mc.g,mc.h);

	/* print out the model */
	std::cout << model << ": ";
	std::cout << "Len: " << mc.len;
	std::cout << ", n_max: " << mc.nmax;
	std::cout << ", n_def: " << mc.ndef;
	std::cout << ", R_scale: "<< mc.rscale;
	std::cout << std::endl;

}

Internal getModel(std::string model) {

	/* get the memory address first */
	std::map<std::string,unsigned char*> cmap = getCoeffPtrMap();
	unsigned char *ptr = cmap[model];

	return Internal(ptr);

}

void testModel(std::string model) {

	std::cout << "Loading model: " << model << std::endl;
	Internal M = getModel(model);

	double x = 10.0, y = 0.0, z = 0.0;
	double Bx, By, Bz;

	M.Field(x,y,z,&Bx,&By,&Bz);
	std::cout << "B = [" << Bx << "," << By << "," << Bz << "] at ";
	std::cout << "[" << x << "," << y << "," << z << "]" << std::endl; 

}

int main() {

	std::cout << "Testing reading coefficients from memory..." << std::endl;

	testCoeff("jrm09");
	testCoeff("jrm33");
	testCoeff("vip4");

	testModel("jrm09");
	testModel("jrm33");
	testModel("vip4");

}

