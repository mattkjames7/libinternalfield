coeffStruct& _model_coeff_anderson2012() {
	static const int len = 14;
	static const int nmax = 4;
	static const int ndef = 4;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4};
	static const double g[] = {-190.000000,0.000000,-74.600000,0.000000,
		0.000000,-22.000000,0.000000,0.000000,0.000000,-5.700000,0.000000,
		0.000000,0.000000,0.000000};
	static const double h[] = {0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

