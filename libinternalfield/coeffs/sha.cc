const int _model_coeff_sha_len = 15;
const int _model_coeff_sha_nmax = 3;
const int _model_coeff_sha_ndef = 3;
const double _model_coeff_sha_rscale = 1.000000;
const int _model_coeff_sha_n[] = {1,1,2,2,2,3,3,3,3};
const int _model_coeff_sha_m[] = {0,1,0,1,2,0,1,2,3};
const double _model_coeff_sha_g[] = {409200.000000,-70500.000000,
	-3300.000000,-69900.000000,53700.000000,-11300.000000,-58500.000000,
	28300.000000,6700.000000};
const double _model_coeff_sha_h[] = {0.000000,23100.000000,0.000000,
	-53100.000000,7400.000000,0.000000,-42300.000000,12000.000000,
	-17100.000000};
coeffStruct _model_coeff_sha ={_model_coeff_sha_len,
								_model_coeff_sha_nmax,
								_model_coeff_sha_ndef,
								_model_coeff_sha_rscale,
								_model_coeff_sha_n,
								_model_coeff_sha_m,
								_model_coeff_sha_g,
								_model_coeff_sha_h};

