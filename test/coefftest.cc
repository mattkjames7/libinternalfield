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


int main() {

	std::cout << "Testing reading coefficients from memory..." << std::endl;

	testCoeff("jrm09");
	testCoeff("jrm33");
	testCoeff("vip4");

}

