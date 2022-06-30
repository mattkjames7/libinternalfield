coeffStruct& _model_coeff_gsfc13ev() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {435200.000000,-65600.000000,-19700.000000,
		-55700.000000,26700.000000,-13800.000000,-32400.000000,
		-17600.000000,12400.000000};
	static const double h[] = {0.000000,34100.000000,0.000000,-30600.000000,
		18700.000000,0.000000,-5300.000000,8300.000000,-31100.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

