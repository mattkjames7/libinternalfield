coeffStruct& _model_coeff_o4() {
	static const int len = 9;
	static const int nmax = 3;
	static const int ndef = 3;
	static const double rscale =  1.0016813316146389034599906;
	static const int n[] = {1,1,2,2,2,3,3,3,3};
	static const int m[] = {0,1,0,1,2,0,1,2,3};
	static const double g[] = {421800.000000,-66400.000000,-20300.000000,
		-73500.000000,51300.000000,-23300.000000,-7600.000000,16800.000000,
		-23100.000000};
	static const double h[] = {0.000000,26400.000000,0.000000,-46900.000000,
		8800.000000,0.000000,-58000.000000,48700.000000,-29400.000000};
	static coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};
	return out;
}

