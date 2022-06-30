coeffStruct& _model_coeff_p11a() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {414400.000000,-69200.000000,3600.000000,
		-58100.000000,44200.000000,-4700.000000,-50200.000000,35200.000000,
		-13600.000000};
	static const double h[] = {0.000000,23500.000000,0.000000,-42700.000000,
		13400.000000,0.000000,-34200.000000,29600.000000,4100.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

