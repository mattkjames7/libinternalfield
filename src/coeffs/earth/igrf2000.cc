coeffStruct& _model_coeff_igrf2000() {
	static const int len = 104;
	static const int nmax = 13;
	static const int ndef = 13;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,6,6,6,
		6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,
		10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,12,
		12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,
		13,13,13,13};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5,0,1,2,
		3,4,5,6,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,9,0,1,2,
		3,4,5,6,7,8,9,10,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,
		11,12,0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	static const double g[] = {-29619.400000,-1728.200000,-2267.700000,
		3068.400000,1670.900000,1339.600000,-2288.000000,1252.100000,
		714.500000,932.300000,786.800000,250.000000,-403.000000,111.300000,
		-218.800000,351.400000,222.300000,-130.400000,-168.600000,
		-12.900000,72.300000,68.200000,74.200000,-160.900000,-5.900000,
		16.900000,-90.400000,79.000000,-74.000000,0.000000,33.300000,
		9.100000,6.900000,7.300000,-1.200000,24.400000,6.600000,-9.200000,
		-7.900000,-16.600000,9.100000,7.000000,-7.900000,-7.000000,5.000000,
		9.400000,3.000000,-8.400000,6.300000,-8.900000,-1.500000,9.300000,
		-4.300000,-8.200000,-2.600000,-6.000000,1.700000,-3.100000,
		-0.500000,3.700000,1.000000,2.000000,4.200000,0.300000,-1.100000,
		2.700000,-1.700000,-1.900000,1.500000,-0.100000,0.100000,-0.700000,
		0.700000,1.700000,0.100000,1.200000,4.000000,-2.200000,-0.300000,
		0.200000,0.900000,-0.200000,0.900000,-0.500000,0.300000,-0.300000,
		-0.400000,-0.100000,-0.200000,-0.400000,-0.200000,-0.900000,
		0.300000,0.100000,-0.400000,1.300000,-0.400000,0.700000,-0.400000,
		0.300000,-0.100000,0.400000,0.000000,0.100000};
	static const double h[] = {0.000000,5186.100000,0.000000,-2481.600000,
		-458.000000,0.000000,-227.600000,293.400000,-491.100000,0.000000,
		272.600000,-231.900000,119.800000,-303.800000,0.000000,43.800000,
		171.900000,-133.100000,-39.300000,106.300000,0.000000,-17.400000,
		63.700000,65.100000,-61.200000,0.700000,43.800000,0.000000,
		-64.600000,-24.200000,6.200000,24.000000,14.800000,-25.400000,
		-5.800000,0.000000,11.900000,-21.500000,8.500000,-21.500000,
		15.500000,8.900000,-14.900000,-2.100000,0.000000,-19.700000,
		13.400000,12.500000,-6.200000,-8.400000,8.400000,3.800000,-8.200000,
		4.800000,0.000000,1.700000,0.000000,4.000000,4.900000,-5.900000,
		-1.200000,-2.900000,0.200000,-2.200000,-7.400000,0.000000,0.100000,
		1.300000,-0.900000,-2.600000,0.900000,-0.700000,-2.800000,-0.900000,
		-1.200000,-1.900000,-0.900000,0.000000,-0.400000,0.300000,2.500000,
		-2.600000,0.700000,0.300000,0.000000,0.000000,0.300000,-0.900000,
		-0.400000,0.800000,0.000000,-0.900000,0.200000,1.800000,-0.400000,
		-1.000000,-0.100000,0.700000,0.300000,0.600000,0.300000,-0.200000,
		-0.500000,-0.900000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}
