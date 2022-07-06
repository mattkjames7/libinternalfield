coeffStruct& _model_coeff_gsfcq3full() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {11893.000000,11579.000000,-6030.000000,
		-12587.000000,196.000000,2705.000000,1188.000000,-4808.000000,
		-2412.000000};
	static const double h[] = {0.000000,-15684.000000,0.000000,6116.000000,
		4759.000000,0.000000,-7095.000000,-1616.000000,-2608.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

