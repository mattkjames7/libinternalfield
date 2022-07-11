coeffStruct& _model_coeff_igrf1980() {
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
	static const double g[] = {-29992.000000,-1956.000000,-1997.000000,
		3027.000000,1663.000000,1281.000000,-2180.000000,1251.000000,
		833.000000,938.000000,782.000000,398.000000,-419.000000,199.000000,
		-218.000000,357.000000,261.000000,-74.000000,-162.000000,-48.000000,
		48.000000,66.000000,42.000000,-192.000000,4.000000,14.000000,
		-108.000000,72.000000,-59.000000,2.000000,21.000000,-12.000000,
		1.000000,11.000000,-2.000000,18.000000,6.000000,0.000000,-11.000000,
		-7.000000,4.000000,3.000000,6.000000,-1.000000,5.000000,10.000000,
		1.000000,-12.000000,9.000000,-3.000000,-1.000000,7.000000,2.000000,
		-5.000000,-4.000000,-4.000000,2.000000,-5.000000,-2.000000,5.000000,
		3.000000,1.000000,2.000000,3.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static const double h[] = {0.000000,5604.000000,0.000000,-2129.000000,
		-200.000000,0.000000,-336.000000,271.000000,-252.000000,0.000000,
		212.000000,-257.000000,53.000000,-297.000000,0.000000,46.000000,
		150.000000,-151.000000,-78.000000,92.000000,0.000000,-15.000000,
		93.000000,71.000000,-43.000000,-2.000000,17.000000,0.000000,
		-82.000000,-27.000000,-5.000000,16.000000,18.000000,-23.000000,
		-10.000000,0.000000,7.000000,-18.000000,4.000000,-22.000000,
		9.000000,16.000000,-13.000000,-15.000000,0.000000,-21.000000,
		16.000000,9.000000,-5.000000,-6.000000,9.000000,10.000000,-6.000000,
		2.000000,0.000000,1.000000,0.000000,3.000000,6.000000,-4.000000,
		0.000000,-1.000000,4.000000,0.000000,-6.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

