coeffStruct& _model_coeff_gsfc15ev() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {418400.000000,-64700.000000,-21000.000000,
		-73700.000000,55400.000000,-22300.000000,1900.000000,22000.000000,
		-31200.000000};
	static const double h[] = {0.000000,23500.000000,0.000000,-49900.000000,
		9200.000000,0.000000,-66800.000000,61900.000000,-30700.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

