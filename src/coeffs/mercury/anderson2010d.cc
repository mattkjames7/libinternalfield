coeffStruct& _model_coeff_anderson2010d() {
	static const int len = 2;
	static const int nmax = 1;
	static const int ndef = 1;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1};
	static std::vector<int> m = {0,1};
	static std::vector<double> g = {-216.000000,-6.000000};
	static std::vector<double> h = {0.000000,14.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

