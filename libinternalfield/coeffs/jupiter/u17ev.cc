coeffStruct& _model_coeff_u17ev() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0013165634891734168121502;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {410879.000000,-67885.000000,7086.000000,
		-64371.000000,46437.000000,-5104.000000,-15682.000000,25148.000000,
		-4253.000000};
	static const double h[] = {0.000000,22881.000000,0.000000,-30924.000000,
		13288.000000,0.000000,-15040.000000,45743.000000,-21705.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

