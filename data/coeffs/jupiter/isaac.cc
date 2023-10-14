coeffStruct& _model_coeff_isaac() {
	static const int len = 65;
	static const int nmax = 10;
	static const int ndef = 10;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,6,6,6,
		6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,
		10,10,10,10,10,10,10,10,10};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5,0,1,2,
		3,4,5,6,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,9,0,1,2,
		3,4,5,6,7,8,9,10};
	static const double g[] = {406650.000000,-71420.000000,-12860.000000,
		-69810.000000,38520.000000,-4790.000000,-46420.000000,28670.000000,
		-9340.000000,-22300.000000,18930.000000,2760.000000,-13170.000000,
		1110.000000,-1650.000000,7550.000000,6230.000000,-1500.000000,
		-4000.000000,1420.000000,-6370.000000,3240.000000,8020.000000,
		270.000000,-4070.000000,2790.000000,-680.000000,640.000000,
		8920.000000,3660.000000,-6980.000000,-1140.000000,2390.000000,
		-1230.000000,310.000000,-5110.000000,7200.000000,4530.000000,
		-3710.000000,-200.000000,3120.000000,-2100.000000,710.000000,
		-133.000000,100.000000,330.000000,-960.000000,370.000000,
		3390.000000,-740.000000,-680.000000,400.000000,-92.000000,9.000000,
		280.000000,490.000000,-630.000000,910.000000,2850.000000,
		-380.000000,-620.000000,440.000000,-169.000000,31.000000,-0.800000};
	static const double h[] = {0.000000,23530.000000,0.000000,-31700.000000,
		7950.000000,0.000000,-7503.000000,40310.000000,-36860.000000,
		0.000000,20780.000000,32930.000000,-16950.000000,5960.000000,
		0.000000,30.000000,-3340.000000,2540.000000,3490.000000,-840.000000,
		0.000000,10510.000000,-9600.000000,5030.000000,1270.000000,
		-1060.000000,180.000000,0.000000,-270.000000,-2970.000000,
		7390.000000,1980.000000,-2120.000000,350.000000,19.000000,0.000000,
		7810.000000,-7380.000000,8520.000000,-870.000000,-1680.000000,
		720.000000,-8.000000,-46.000000,0.000000,-290.000000,1890.000000,
		1850.000000,690.000000,320.000000,-430.000000,270.000000,
		-120.000000,27.000000,0.000000,230.000000,1720.000000,1250.000000,
		-110.000000,-110.000000,-15.000000,360.000000,-250.000000,80.000000,
		-14.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}
