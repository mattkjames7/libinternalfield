coeffStruct& _model_coeff_kivelson2002a() {
	static const int len = 5;
	static const int nmax = 2;
	static const int ndef = 2;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1,2,2,2};
	static std::vector<int> m = {0,1,0,1,2};
	static std::vector<double> g = {-711.000000,46.800000,0.900000,27.000000,
		-0.400000};
	static std::vector<double> h = {0.000000,22.300000,0.000000,1.800000,
		-11.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

