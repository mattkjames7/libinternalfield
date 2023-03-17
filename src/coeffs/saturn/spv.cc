coeffStruct& _model_coeff_spv() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1,2,2,2,3,3,3,3};
	static std::vector<int> m = {0,1,0,1,2,0,1,2,3};
	static std::vector<double> g = {21160.000000,0.000000,1560.000000,
		0.000000,0.000000,2320.000000,0.000000,0.000000,0.000000};
	static std::vector<double> h = {0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

