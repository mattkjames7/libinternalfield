coeffStruct& _model_coeff_igrf1970() {
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
	static const double g[] = {-30220.000000,-2068.000000,-1781.000000,
		3000.000000,1611.000000,1287.000000,-2091.000000,1278.000000,
		838.000000,952.000000,800.000000,461.000000,-395.000000,234.000000,
		-216.000000,359.000000,262.000000,-42.000000,-160.000000,-56.000000,
		43.000000,64.000000,15.000000,-212.000000,2.000000,3.000000,
		-112.000000,72.000000,-57.000000,1.000000,14.000000,-22.000000,
		-2.000000,13.000000,-2.000000,14.000000,6.000000,-2.000000,
		-13.000000,-3.000000,5.000000,0.000000,11.000000,3.000000,8.000000,
		10.000000,2.000000,-12.000000,10.000000,-1.000000,0.000000,3.000000,
		1.000000,-1.000000,-3.000000,-3.000000,2.000000,-5.000000,-1.000000,
		6.000000,4.000000,1.000000,0.000000,3.000000,-1.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000};
	static const double h[] = {0.000000,5737.000000,0.000000,-2047.000000,
		25.000000,0.000000,-366.000000,251.000000,-196.000000,0.000000,
		167.000000,-266.000000,26.000000,-279.000000,0.000000,26.000000,
		139.000000,-139.000000,-91.000000,83.000000,0.000000,-12.000000,
		100.000000,72.000000,-37.000000,-6.000000,1.000000,0.000000,
		-70.000000,-27.000000,-4.000000,8.000000,23.000000,-23.000000,
		-11.000000,0.000000,7.000000,-15.000000,6.000000,-17.000000,
		6.000000,21.000000,-6.000000,-16.000000,0.000000,-21.000000,
		16.000000,6.000000,-4.000000,-5.000000,10.000000,11.000000,
		-2.000000,1.000000,0.000000,1.000000,1.000000,3.000000,4.000000,
		-4.000000,0.000000,-1.000000,3.000000,1.000000,-4.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

