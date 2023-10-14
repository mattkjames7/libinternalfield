coeffStruct& _model_coeff_igrf1985() {
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
	static const double g[] = {-29873.000000,-1905.000000,-2072.000000,
		3044.000000,1687.000000,1296.000000,-2208.000000,1247.000000,
		829.000000,936.000000,780.000000,361.000000,-424.000000,170.000000,
		-214.000000,355.000000,253.000000,-93.000000,-164.000000,-46.000000,
		53.000000,65.000000,51.000000,-185.000000,4.000000,16.000000,
		-102.000000,74.000000,-62.000000,3.000000,24.000000,-6.000000,
		4.000000,10.000000,0.000000,21.000000,6.000000,0.000000,-11.000000,
		-9.000000,4.000000,4.000000,4.000000,-4.000000,5.000000,10.000000,
		1.000000,-12.000000,9.000000,-3.000000,-1.000000,7.000000,1.000000,
		-5.000000,-4.000000,-4.000000,3.000000,-5.000000,-2.000000,5.000000,
		3.000000,1.000000,2.000000,3.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000};
	static const double h[] = {0.000000,5500.000000,0.000000,-2197.000000,
		-306.000000,0.000000,-310.000000,284.000000,-297.000000,0.000000,
		232.000000,-249.000000,69.000000,-297.000000,0.000000,47.000000,
		150.000000,-154.000000,-75.000000,95.000000,0.000000,-16.000000,
		88.000000,69.000000,-48.000000,-1.000000,21.000000,0.000000,
		-83.000000,-27.000000,-2.000000,20.000000,17.000000,-23.000000,
		-7.000000,0.000000,8.000000,-19.000000,5.000000,-23.000000,
		11.000000,14.000000,-15.000000,-11.000000,0.000000,-21.000000,
		15.000000,9.000000,-6.000000,-6.000000,9.000000,9.000000,-7.000000,
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
