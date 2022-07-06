coeffStruct& _model_coeff_gsfc15evs() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {420100.000000,-65700.000000,-21100.000000,
		-68600.000000,50900.000000,-18600.000000,-200.000000,15000.000000,
		-23500.000000};
	static const double h[] = {0.000000,25800.000000,0.000000,-46100.000000,
		11000.000000,0.000000,-57500.000000,51200.000000,30700.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

