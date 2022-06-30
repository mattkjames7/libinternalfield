coeffStruct& _model_coeff_vip4() {
	static const int len = 14;
	static const int nmax = 4;
	static const int ndef = 4;
	static const double rscale =  1.0023695021241394442768069;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4};
	static const double g[] = {420543.000000,-65920.000000,-5118.000000,
		-61904.000000,49690.000000,-1576.000000,-52036.000000,24386.000000,
		-17597.000000,-16758.000000,22210.000000,-6074.000000,-20243.000000,
		6643.000000};
	static const double h[] = {0.000000,24992.000000,0.000000,-36052.000000,
		5250.000000,0.000000,-8804.000000,40829.000000,-31586.000000,
		0.000000,7557.000000,40411.000000,-16597.000000,3866.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

