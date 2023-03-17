coeffStruct& _model_coeff_igrf2010() {
	static const int len = 104;
	static const int nmax = 13;
	static const int ndef = 13;
	static const double rscale =  1.0000000000000000000000000;
	static std::vector<int> n = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,6,
		6,6,6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,
		10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,
		11,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,
		13,13,13,13,13,13};
	static std::vector<int> m = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,4,5,0,
		1,2,3,4,5,6,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,9,0,
		1,2,3,4,5,6,7,8,9,10,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,7,8,9,
		10,11,12,0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	static std::vector<double> g = {-29496.570000,-1586.420000,-2396.060000,
		3026.340000,1668.170000,1339.850000,-2326.540000,1232.100000,
		633.730000,912.660000,808.970000,166.580000,-356.830000,89.400000,
		-230.870000,357.290000,200.260000,-141.050000,-163.170000,-8.030000,
		72.780000,68.690000,75.920000,-141.400000,-22.830000,13.100000,
		-78.090000,80.440000,-75.000000,-4.550000,45.240000,14.000000,
		10.460000,1.640000,4.920000,24.410000,8.210000,-14.500000,-5.590000,
		-19.340000,11.610000,10.850000,-14.050000,-3.540000,5.500000,
		9.450000,3.450000,-5.270000,3.130000,-12.380000,-0.760000,8.430000,
		-8.420000,-10.080000,-1.940000,-6.240000,0.890000,-1.070000,
		-0.160000,2.450000,-0.330000,2.130000,3.090000,-1.030000,-2.800000,
		3.050000,-1.480000,-2.030000,1.650000,-0.510000,0.540000,-0.790000,
		0.370000,1.790000,0.120000,0.750000,3.750000,-2.120000,-0.210000,
		0.300000,1.040000,-0.630000,0.950000,-0.110000,0.520000,-0.390000,
		-0.370000,0.210000,-0.770000,0.040000,-0.090000,-0.890000,0.310000,
		0.420000,-0.450000,1.080000,-0.310000,0.780000,-0.180000,0.380000,
		0.020000,0.420000,-0.260000,-0.260000};
	static std::vector<double> h = {0.000000,4944.260000,0.000000,
		-2708.540000,-575.730000,0.000000,-160.400000,251.750000,
		-537.030000,0.000000,286.480000,-211.030000,164.460000,-309.720000,
		0.000000,44.580000,189.010000,-118.060000,-0.010000,101.040000,
		0.000000,-20.900000,44.180000,61.540000,-66.260000,3.020000,
		55.400000,0.000000,-57.800000,-21.200000,6.540000,24.960000,
		7.030000,-27.610000,-3.280000,0.000000,10.840000,-20.030000,
		11.830000,-17.410000,16.710000,6.960000,-10.740000,1.640000,
		0.000000,-20.540000,11.510000,12.750000,-7.140000,-7.420000,
		7.970000,2.140000,-6.080000,7.010000,0.000000,2.730000,-0.100000,
		4.710000,4.440000,-7.220000,-0.960000,-3.950000,-1.990000,-1.970000,
		-8.310000,0.000000,0.130000,1.670000,-0.660000,-1.760000,0.850000,
		-0.390000,-2.510000,-1.270000,-2.110000,-1.940000,-1.860000,
		0.000000,-0.870000,0.270000,2.130000,-2.490000,0.490000,0.590000,
		0.000000,0.130000,0.270000,-0.860000,-0.230000,0.870000,0.000000,
		-0.870000,0.300000,1.660000,-0.590000,-1.140000,-0.070000,0.540000,
		0.100000,0.490000,0.440000,-0.250000,-0.530000,-0.790000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

