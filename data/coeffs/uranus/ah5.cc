coeffStruct& _model_coeff_ah5() {
	static const int len = 14;
	static const int nmax = 4;
	static const int ndef = 4;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4};
	static const double g[] = {11278.000000,10928.000000,-9648.000000,
		-12284.000000,1453.000000,-1265.000000,2778.000000,-4535.000000,
		-6297.000000,3388.000000,-29.000000,955.000000,5588.000000,
		8136.000000};
	static const double h[] = {0.000000,-16049.000000,0.000000,6405.000000,
		4220.000000,0.000000,-1548.000000,-2165.000000,-3036.000000,
		0.000000,-2036.000000,-3437.000000,-1154.000000,-2920.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

