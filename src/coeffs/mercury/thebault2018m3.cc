coeffStruct& _model_coeff_thebault2018m3() {
	static const int len = 20;
	static const int nmax = 5;
	static const int ndef = 5;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5};
	static std::vector<int> m = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5};
	static std::vector<double> g = {-198.800000,0.900000,-77.600000,0.000000,
		0.000000,-20.600000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.600000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static std::vector<double> h = {0.000000,1.800000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

