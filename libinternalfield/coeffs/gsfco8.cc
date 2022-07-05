coeffStruct& _model_coeff_gsfco8() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {9732.000000,3220.000000,7448.000000,664.000000,
		4499.000000,-6592.000000,4098.000000,-3581.000000,484.000000};
	static const double h[] = {0.000000,-9889.000000,0.000000,11230.000000,
		-70.000000,0.000000,-3669.000000,1791.000000,-770.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

