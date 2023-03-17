coeffStruct& _model_coeff_anderson2010qts04() {
	static const int len = 5;
	static const int nmax = 2;
	static const int ndef = 2;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1,2,2,2};
	static std::vector<int> m = {0,1,0,1,2};
	static std::vector<double> g = {-213.000000,-4.000000,-66.000000,9.000000,
		4.000000};
	static std::vector<double> h = {0.000000,7.000000,0.000000,5.000000,
		-4.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

