coeffStruct& _model_coeff_thebault2018m2() {
	static const int len = 20;
	static const int nmax = 5;
	static const int ndef = 5;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5};
	static std::vector<int> m = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5};
	static std::vector<double> g = {-213.600000,0.900000,-57.700000,0.000000,
		0.000000,-35.800000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,2.100000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static std::vector<double> h = {0.000000,1.500000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

