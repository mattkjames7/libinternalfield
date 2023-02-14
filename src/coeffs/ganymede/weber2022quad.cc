coeffStruct& _model_coeff_weber2022quad() {
	static const int len = 5;
	static const int nmax = 2;
	static const int ndef = 2;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2};
	static const int m[] = {0,1,0,1,2};
	static const double g[] = {-748.300000,41.100000,22.500000,23.300000,
		-26.800000};
	static const double h[] = {0.000000,20.800000,0.000000,16.500000,
		-10.600000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

