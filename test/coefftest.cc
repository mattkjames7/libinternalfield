#include <iostream>
#include <internalfield.h>
#include <string>
#include <stdio.h>

void testCoeff(std::string model) {

	/* get the memory address first */
	std::map<std::string,unsigned char*> cmap = getCoeffPtrMap();
	unsigned char *ptr = cmap[model];
	std::cout << model << std::endl;
	std::cout << cmap.size() << std::endl;
	printf("ptr: %d\n",ptr);
	/* read the model coefficients*/
	coeffStruct mc;
	readCoeffs(ptr,&(mc.len),&(mc.nmax),&(mc.ndef),&(mc.rscale),
				mc.n,mc.m,mc.g,mc.h);

	/* print out the model */
	std::cout << model;
	std::cout << mc.len;
	std::cout << mc.nmax;
	std::cout << mc.ndef;
	std::cout << mc.rscale;
	std::cout << std::endl;

}


int main() {

	std::cout << "Testing reading coefficients from memory..." << std::endl;

	testCoeff("jrm09");
	testCoeff("jrm33");
	testCoeff("vip4");

}

