coeffStruct& _model_coeff_uno2009() {
	static const int len = 44;
	static const int nmax = 8;
	static const int ndef = 8;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,6,6,6,
		6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5,0,1,2,
		3,4,5,6,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,8};
	static const double g[] = {-227.100000,11.000000,-20.700000,3.100000,
		5.100000,-10.300000,-1.500000,5.800000,1.900000,-4.700000,-0.600000,
		2.700000,1.200000,1.800000,-3.300000,-0.400000,0.800000,-0.200000,
		0.300000,0.700000,-1.000000,-0.300000,0.200000,-0.500000,-0.200000,
		-0.200000,0.300000,0.200000,0.100000,0.100000,-0.200000,-0.100000,
		-0.200000,-0.200000,0.100000,0.100000,0.300000,0.100000,-0.100000,
		0.000000,0.000000,0.100000,-0.100000,0.000000};
	static const double h[] = {0.000000,7.000000,0.000000,-3.300000,3.600000,
		0.000000,-4.300000,2.300000,-0.400000,0.000000,-1.700000,1.500000,
		2.000000,0.000000,0.000000,-1.200000,1.000000,1.400000,1.100000,
		0.300000,0.000000,-1.000000,0.100000,0.400000,0.500000,0.500000,
		0.100000,0.000000,-0.400000,-0.100000,0.000000,0.000000,0.200000,
		0.100000,0.100000,0.000000,-0.100000,0.100000,-0.100000,-0.100000,
		0.000000,0.100000,0.000000,0.100000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

