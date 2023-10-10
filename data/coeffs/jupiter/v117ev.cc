coeffStruct& _model_coeff_v117ev() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0023695021241394442768069;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {420825.000000,-65980.000000,-3411.000000,
		-75856.000000,48321.000000,2153.000000,-3295.000000,26315.000000,
		-6905.000000};
	static const double h[] = {0.000000,26122.000000,0.000000,-29424.000000,
		10704.000000,0.000000,8883.000000,69538.000000,-24718.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

