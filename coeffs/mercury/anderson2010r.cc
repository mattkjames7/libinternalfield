coeffStruct& _model_coeff_anderson2010r() {
	static const int len = 5;
	static const int nmax = 2;
	static const int ndef = 2;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2};
	static const int m[] = {0,1,0,1,2};
	static const double g[] = {-222.000000,12.000000,-24.000000,9.000000,
		9.000000};
	static const double h[] = {0.000000,2.000000,0.000000,-6.000000,8.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

