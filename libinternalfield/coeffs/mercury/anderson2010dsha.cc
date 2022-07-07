coeffStruct& _model_coeff_anderson2010dsha() {
	static const int len = 2;
	static const int nmax = 1;
	static const int ndef = 1;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1};
	static const int m[] = {0,1};
	static const double g[] = {-249.000000,-12.000000};
	static const double h[] = {0.000000,16.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

