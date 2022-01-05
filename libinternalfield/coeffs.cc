#include "coeffs.h"


unsigned char* GetModelCoeffPointer(string Model) {
	return modelMap[Model];
}


unsigned char* GetModelCoeffPointer(const char *Model) {
	return modelMap[Model];
}

