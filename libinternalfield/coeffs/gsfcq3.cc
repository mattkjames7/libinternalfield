coeffStruct& _model_coeff_gsfcq3() {
	static const int len = 5;
	static const int nmax = 2;
	static const int ndef = 2;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2};
	static const int m[] = {0,1,0,1,2};
	static const double g[] = {11893.000000,11579.000000,-6030.000000,
		-12587.000000,196.000000};
	static const double h[] = {0.000000,-15684.000000,0.000000,6116.000000,
		4759.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

