#ifndef __READCOEFFS_H__
#define __READCOEFFS_H__
#include <stdio.h>
#include <stdlib.h>
#include "coeffs.h"
#include <vector>

void readCoeffs(unsigned char *data, 
				int *len, int *nmax, int *ndef, double *rscale,
				std::vector<int> n, std::vector<int> m,
				std::vector<double> g, std::vector<double> h);


#endif
