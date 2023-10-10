coeffStruct& _model_coeff_uno2009svd() {
	static const int len = 5;
	static const int nmax = 2;
	static const int ndef = 2;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2};
	static const int m[] = {0,1,0,1,2};
	static const double g[] = {-169.600000,6.700000,-56.000000,7.900000,
		13.700000};
	static const double h[] = {0.000000,17.500000,0.000000,-45.400000,
		-16.300000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

