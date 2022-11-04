coeffStruct& _model_coeff_jpl15evs() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {406800.000000,-66800.000000,-9300.000000,
		-67200.000000,50200.000000,-111.000000,-31600.000000,22000.000000,
		-25000.000000};
	static const double h[] = {0.000000,24300.000000,0.000000,-49800.000000,
		11900.000000,0.000000,-47600.000000,38000.000000,-22800.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

