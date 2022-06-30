coeffStruct& _model_coeff_o6() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0016813316146389034599906;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {424202.000000,-65929.000000,-2181.000000,
		-71106.000000,48714.000000,7565.000000,-15493.000000,19775.000000,
		-17958.000000};
	static const double h[] = {0.000000,24116.000000,0.000000,-40304.000000,
		7179.000000,0.000000,-38824.000000,34243.000000,-22439.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

