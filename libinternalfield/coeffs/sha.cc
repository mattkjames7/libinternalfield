coeffStruct& _model_coeff_sha() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0013165634891734168121502;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {409200.000000,-70500.000000,-3300.000000,
		-69900.000000,53700.000000,-11300.000000,-58500.000000,28300.000000,
		6700.000000};
	static const double h[] = {0.000000,23100.000000,0.000000,-53100.000000,
		7400.000000,0.000000,-42300.000000,12000.000000,-17100.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

