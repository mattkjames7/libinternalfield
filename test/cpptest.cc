#include <internalfield.h>
#include <filesystem>
#include <fstream>
#include <iostream>

void readTestData(double *Tx, double *Ty, double *Tz) {
   	std::filesystem::path fileName = std::filesystem::current_path();
    fileName /= "cpptest.bin";

	std::ifstream file(fileName,std::ios::binary);

	file.read(reinterpret_cast<char*>(Tx), sizeof(double));
	file.read(reinterpret_cast<char*>(Ty), sizeof(double));
	file.read(reinterpret_cast<char*>(Tz), sizeof(double));
	file.close();
}


int main() {

	std::cout << "C++ Test......................................";
	
	/* try getting a model object */
	InternalModel model;
	model.SetModel("jrm33");
	model.SetCartIn(true);
	model.SetCartOut(true);
	double x = 10.0;
	double y = 10.0;
	double z = 0.0;
	double Bx, By, Bz;
	model.Field(x,y,z,&Bx,&By,&Bz);

	/* read in the saved data */
	double Tx, Ty, Tz;
	readTestData(&Tx, &Ty, &Tz);

	/* compare results */
	bool pass = (Tx == Bx) && (Ty == By) && (Tz == Bz);
	if (pass) {
		std::cout << "PASS" << std::endl;
	} else {
		std::cout << "FAIL" << std::endl;
		std::cout << "Expected: ";
		std::cout << "[" << std::setw(10) << std::setprecision(3) << std::fixed << Tx;
		std::cout << ", " << std::setw(10) << std::setprecision(3) << std::fixed << Ty;
		std::cout << ", " << std::setw(10) << std::setprecision(3) << std::fixed << Tz;
		std::cout << "]" << std::endl;
		std::cout << "Output: ";
		std::cout << "[" << std::setw(10) << std::setprecision(3) << std::fixed << Bx;
		std::cout << ", " << std::setw(10) << std::setprecision(3) << std::fixed << By;
		std::cout << ", " << std::setw(10) << std::setprecision(3) << std::fixed << Bz;
		std::cout << "]" << std::endl;
	}

}

