coeffStruct& _model_coeff_igrf1975() {
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
	static const double g[] = {-30100.000000,-2013.000000,-1902.000000,
		3010.000000,1632.000000,1276.000000,-2144.000000,1260.000000,
		830.000000,946.000000,791.000000,438.000000,-405.000000,216.000000,
		-218.000000,356.000000,264.000000,-59.000000,-159.000000,-49.000000,
		45.000000,66.000000,28.000000,-198.000000,1.000000,6.000000,
		-111.000000,71.000000,-56.000000,1.000000,16.000000,-14.000000,
		0.000000,12.000000,-5.000000,14.000000,6.000000,-1.000000,
		-12.000000,-8.000000,4.000000,0.000000,10.000000,1.000000,7.000000,
		10.000000,2.000000,-12.000000,10.000000,-1.000000,-1.000000,
		4.000000,1.000000,-2.000000,-3.000000,-3.000000,2.000000,-5.000000,
		-2.000000,5.000000,4.000000,1.000000,0.000000,3.000000,-1.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000};
	static const double h[] = {0.000000,5675.000000,0.000000,-2067.000000,
		-68.000000,0.000000,-333.000000,262.000000,-223.000000,0.000000,
		191.000000,-265.000000,39.000000,-288.000000,0.000000,31.000000,
		148.000000,-152.000000,-83.000000,88.000000,0.000000,-13.000000,
		99.000000,75.000000,-41.000000,-4.000000,11.000000,0.000000,
		-77.000000,-26.000000,-5.000000,10.000000,22.000000,-23.000000,
		-12.000000,0.000000,6.000000,-16.000000,4.000000,-19.000000,
		6.000000,18.000000,-10.000000,-17.000000,0.000000,-21.000000,
		16.000000,7.000000,-4.000000,-5.000000,10.000000,11.000000,
		-3.000000,1.000000,0.000000,1.000000,1.000000,3.000000,4.000000,
		-4.000000,-1.000000,-1.000000,3.000000,1.000000,-5.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}
