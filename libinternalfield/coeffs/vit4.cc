coeffStruct& _model_coeff_vit4() {
	static const int len = 14;
	static const int nmax = 4;
	static const int ndef = 4;
	static const double rscale =  1.0023695021241394442768069;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4};
	static const double g[] = {428077.000000,-75306.000000,-4283.000000,
		-59426.000000,44386.000000,8906.000000,-21447.000000,21130.000000,
		-1190.000000,-22925.000000,18940.000000,-3851.000000,9926.000000,
		1271.000000};
	static const double h[] = {0.000000,24616.000000,0.000000,-50154.000000,
		38452.000000,0.000000,-17187.000000,40667.000000,-35263.000000,
		0.000000,16088.000000,11807.000000,6195.000000,12641.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

