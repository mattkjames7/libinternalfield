#include "timer.h"

double mean(int n, double *x) {
	double mu = 0.0;
	int i;
	for (i=0;i<n;i++) {
		mu += x[i];
	}
	mu = mu/n;
	return mu;
}

double stddev(int n, double *x) {
	
	double mu = mean(n,x);
	double sdx = 0.0;
	int i;
	
	for (i=0;i<n;i++) {
		sdx += pow(x[i] - mu,2.0);
	}
	sdx = sdx/(n-1);
	return sdx;
}


int main() {
	
	int narr[] = {1,10,100,1000,10000,100000};
	int n;
	
	double mu_vp[6],mu_vc[6],mu_sp[6],mu_sc[6];
	
	for (n=0;n<6;n++) {
		printf("Testing n = %d\n",narr[n]);
		test(narr[n],&mu_vp[n],&mu_sp[n],&mu_vc[n],&mu_sc[n]);
	}
	
	printf("Mean Vectorized, Polar: ");
	for (n=0;n<6;n++) {
		printf(" %12.10f",mu_vp[n]);
	}
	printf("\n");
	
	printf("Mean Single Vectors, Polar: ");
	for (n=0;n<6;n++) {
		printf(" %12.10f",mu_sp[n]);
	}
	printf("\n");
	
	printf("Mean Vectorized, Cartesian: ");
	for (n=0;n<6;n++) {
		printf(" %12.10f",mu_vc[n]);
	}
	printf("\n");
	
	printf("Mean Single Vector, Cartesian: ");
	for (n=0;n<6;n++) {
		printf(" %12.10f",mu_sc[n]);
	}
	printf("\n");



	
	
}
	
	
void test(int n, double *mu_vp, double *mu_sp, double *mu_vc, double *mu_sc) {	

	/* seed the random number generator */
	srand(time(NULL));	
	
	/* generate 10000 random vectors */
	double *x = new double[n];
	double *y = new double[n];
	double *z = new double[n];
	double *r = new double[n];
	double *t = new double[n];
	double *p = new double[n];
	
	int i, j;
	for (i=0;i<n;i++) {
		x[i] = 100*(rand()/RAND_MAX) - 50.0;
		y[i] = 100*(rand()/RAND_MAX) - 50.0;
		z[i] = 40*(rand()/RAND_MAX) - 20.0;
		
		r[i] = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
		t[i] = acos(z[i]/r[i]);
		p[i] = atan2(y[i],x[i]);
		
	}
	
	int ntest = 5;
	double *dt_vec_pol = new double[ntest];
	double *dt_vec_car = new double[ntest];
	double *dt_sgl_pol = new double[ntest];
	double *dt_sgl_car = new double[ntest];
	double t0, t1;
	double mu,sd;
	
	double *B0 = new double[n];
	double *B1 = new double[n];
	double *B2 = new double[n];
	
	/* get the model */
	InternalModel im;
	const char * Model = "jrm33";
	const int Degree = 18;
	im.SetModel(Model);
	im.SetDegree(Degree);
	
	printf("Testing model %s, degree %d\n",Model,Degree);
	
	/* time the function calling with a whole array (polar) */
	im.SetCartIn(false);
	im.SetCartOut(false);
	for (i=0;i<ntest;i++) {
		t0 = clock();
		im.Field(n,r,t,p,B0,B1,B2);
		t1 = clock();
		dt_vec_pol[i] = (t1 - t0)/CLOCKS_PER_SEC;		
	}
	mu_vp[0] = mean(ntest,dt_vec_pol);
	sd = stddev(ntest,dt_vec_pol);
	printf("%12.10f +/- %12.10f s - polar, vectorized (%d vectors, %d tests)\n",mu_vp[0],sd,n,ntest);
	
	
	/* time the function calling one element at a time (polar) */
	im.SetCartIn(false);
	im.SetCartOut(false);
	for (i=0;i<ntest;i++) {
		t0 = clock();
		for (j=0;j<n;j++) {
			im.Field(r[j],t[j],p[j],&B0[j],&B1[j],&B2[j]);
		}
		t1 = clock();
		dt_sgl_pol[i] = (t1 - t0)/CLOCKS_PER_SEC;		
	}
	mu_sp[0] = mean(ntest,dt_sgl_pol);
	sd = stddev(ntest,dt_sgl_pol);
	printf("%12.10f +/- %12.10f s - polar, single vectors (%d vectors, %d tests)\n",mu_sp[0],sd,n,ntest);
	
		
	/* time the function calling with a whole array (cartesian) */
	im.SetCartIn(true);
	im.SetCartOut(true);
	for (i=0;i<ntest;i++) {
		t0 = clock();
		im.Field(n,x,y,z,B0,B1,B2);
		t1 = clock();
		dt_vec_car[i] = (t1 - t0)/CLOCKS_PER_SEC;		
	}
	mu_vc[0] = mean(ntest,dt_vec_car);
	sd = stddev(ntest,dt_vec_car);
	printf("%12.10f +/- %12.10f s - Cartesian, vectorized (%d vectors, %d tests)\n",mu_vc[0],sd,n,ntest);
	
	
	/* time the function calling one element at a time (cartesian) */
	im.SetCartIn(true);
	im.SetCartOut(true);
	for (i=0;i<ntest;i++) {
		t0 = clock();
		for (j=0;j<n;j++) {
			im.Field(x[j],y[j],z[j],&B0[j],&B1[j],&B2[j]);
		}
		t1 = clock();
		dt_sgl_car[i] = (t1 - t0)/CLOCKS_PER_SEC;		
	}
	mu_sc[0] = mean(ntest,dt_sgl_car);
	sd = stddev(ntest,dt_sgl_car);
	printf("%12.10f +/- %12.10f s - Cartesian, single vectors (%d vectors, %d tests)\n",mu_sc[0],sd,n,ntest);
		
	
	
	delete[] x;
	delete[] y;
	delete[] z;
	delete[] r;
	delete[] t;
	delete[] p;
	delete[] dt_vec_pol;
	delete[] dt_vec_car;
	delete[] dt_sgl_pol;
	delete[] dt_sgl_car;
	delete[] B0;
	delete[] B1;
	delete[] B2;
	
}
