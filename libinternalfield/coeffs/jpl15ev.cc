coeffStruct& _model_coeff_jpl15ev() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {406400.000000,-67500.000000,-9800.000000,
		-75700.000000,55000.000000,-306.000000,-33300.000000,24900.000000,
		-35000.000000};
	static const double h[] = {0.000000,26900.000000,0.000000,-55600.000000,
		11000.000000,0.000000,-61500.000000,46500.000000,-26400.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

