coeffStruct& _model_coeff_umoh() {
	static const int len = 152;
	static const int nmax = 16;
	static const int ndef = 16;
	static const double rscale =  1.0000000000000000000000000;
	static const int n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,6,6,6,
		6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,10,10,
		10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,12,
		12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,
		13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,
		16,16,16,16,16,16,16,16};
	static const int m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5,0,1,2,
		3,4,5,6,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,9,0,1,2,
		3,4,5,6,7,8,9,10,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,10,
		11,12,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,10,11,12,
		13,14,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,
		11,12,13,14,15,16};
	static const double g[] = {11854.690000,11507.230000,-5877.080000,
		-13084.900000,-604.660000,4182.820000,-1335.730000,-6776.280000,
		-4021.380000,398.370000,-431.860000,2168.910000,465.440000,
		-1758.430000,292.220000,-51.660000,14.560000,36.970000,241.050000,
		-263.430000,-100.690000,61.040000,-94.530000,59.670000,-60.990000,
		27.690000,31.420000,2.760000,-12.320000,8.860000,-17.050000,
		13.010000,-11.650000,0.830000,8.750000,2.510000,0.480000,1.500000,
		0.570000,-0.660000,0.950000,-0.430000,-0.520000,0.100000,-0.310000,
		0.190000,-0.240000,0.340000,-0.100000,0.160000,-0.080000,0.160000,
		-0.110000,-0.130000,-0.020000,-0.030000,-0.020000,-0.050000,
		0.020000,-0.030000,0.030000,-0.030000,0.030000,0.000000,-0.010000,
		0.010000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000};
	static const double h[] = {0.000000,-15811.900000,0.000000,5850.660000,
		4184.690000,0.000000,-5816.660000,-357.270000,-2265.150000,0.000000,
		-1013.870000,414.660000,-637.840000,65.550000,0.000000,520.220000,
		-383.170000,353.480000,22.320000,-331.660000,0.000000,12.060000,
		63.350000,-44.290000,37.320000,26.180000,-58.620000,0.000000,
		-21.490000,5.460000,-6.880000,3.040000,-4.860000,5.500000,1.570000,
		0.000000,1.820000,-2.790000,1.660000,-2.410000,1.750000,-1.810000,
		0.620000,1.120000,0.000000,0.320000,0.250000,-0.030000,0.230000,
		-0.230000,0.240000,-0.180000,-0.020000,0.050000,0.000000,-0.060000,
		0.020000,-0.010000,0.020000,0.010000,0.000000,0.010000,0.000000,
		-0.010000,-0.010000,0.000000,0.000000,-0.010000,0.000000,-0.010000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
		0.000000,0.000000,0.000000,0.000000,0.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

