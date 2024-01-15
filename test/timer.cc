#include "timer.h"

int nDots;

void addDot() {
	std::cout << ".";
	nDots += 1;
	if (nDots == 50) {
		nDots = 0;
		std::cout << std::endl;
	}
}


double mean(std::vector<double> &x) {
	double mu = 0.0;
	int i;
	for (i=0;i<x.size();i++) {
		mu += x[i];
	}
	mu = mu/x.size();
	return mu;	
}


double stddev(std::vector<double> &x) {
	
	double mu = mean(x);
	double sdx = 0.0;
	int i;
	
	for (i=0;i<x.size();i++) {
		sdx += pow(x[i] - mu,2.0);
	}
	sdx = sdx/(x.size()-1);
	return sdx;
}

vectorTuple getRandomVectors(int n) {


	/* seed the random number generator */
	srand(time(NULL));	
	
	/* generate 10000 random vectors */
	std::vector<double> x(n), y(n), z(n), r(n), t(n), p(n);

	int i;
	for (i=0;i<n;i++) {
		x[i] = 100*(rand()/RAND_MAX) - 50.0;
		y[i] = 100*(rand()/RAND_MAX) - 50.0;
		z[i] = 40*(rand()/RAND_MAX) - 20.0;
		
		r[i] = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
		t[i] = acos(z[i]/r[i]);
		p[i] = atan2(y[i],x[i]);
		
	}

	return {x,y,z,r,t,p};
}

std::vector<double> timeCartSingle(
	int ntest,
	std::vector<double> &x,
	std::vector<double> &y,
	std::vector<double> &z
) {
	InternalModel model;
	model.SetModel("jrm33");
	model.SetDegree(18);

	model.SetCartIn(true);
	model.SetCartOut(true);

	int n = x.size();
	std::vector<double> bx(n);
	std::vector<double> by(n);
	std::vector<double> bz(n);

	double t0, t1;
	int i, j;
	std::vector<double> times(ntest);

	for (i=0;i<ntest;i++) {
		t0 = clock();
		for (j=0;j<n;j++) {
			model.Field(x[j],y[j],z[j],&bx[j],&by[j],&bz[j]);
		}
		t1 = clock();
		times[i] = (t1 - t0)/CLOCKS_PER_SEC;
		addDot();
	}

	/* return mean and standard deviation */
	std::vector<double> out(2);
	out[0] = mean(times);
	out[1] = stddev(times);

	return out;
}

std::vector<double> timeCartArray(
	int ntest,
	std::vector<double> &x,
	std::vector<double> &y,
	std::vector<double> &z
) {
	InternalModel model;
	model.SetModel("jrm33");
	model.SetDegree(18);

	model.SetCartIn(true);
	model.SetCartOut(true);

	int n = x.size();
	std::vector<double> bx(n);
	std::vector<double> by(n);
	std::vector<double> bz(n);


	double t0, t1;
	int i;
	std::vector<double> times(ntest);

	for (i=0;i<ntest;i++) {
		t0 = clock();
		model.Field(x.size(),x.data(),y.data(),z.data(),bx.data(),by.data(),bz.data());
		t1 = clock();
		times[i] = (t1 - t0)/CLOCKS_PER_SEC;
		addDot();
	}

	/* return mean and standard deviation */
	std::vector<double> out(2);
	out[0] = mean(times);
	out[1] = stddev(times);

	return out;
}


std::vector<double> timePolarSingle(
	int ntest,
	std::vector<double> &r,
	std::vector<double> &t,
	std::vector<double> &p
) {
	InternalModel model;
	model.SetModel("jrm33");
	model.SetDegree(18);

	model.SetCartIn(false);
	model.SetCartOut(false);

	int n = r.size();
	std::vector<double> br(n);
	std::vector<double> bt(n);
	std::vector<double> bp(n);

	double t0, t1;
	int i, j;
	std::vector<double> times(ntest);

	for (i=0;i<ntest;i++) {
		t0 = clock();
		for (j=0;j<n;j++) {
			model.Field(r[j],t[j],p[j],&br[j],&bt[j],&bp[j]);
		}
		t1 = clock();
		times[i] = (t1 - t0)/CLOCKS_PER_SEC;
		addDot();
	}

	/* return mean and standard deviation */
	std::vector<double> out(2);
	out[0] = mean(times);
	out[1] = stddev(times);

	return out;
}

std::vector<double> timePolarArray(
	int ntest,
	std::vector<double> &r,
	std::vector<double> &t,
	std::vector<double> &p
) {
	InternalModel model;
	model.SetModel("jrm33");
	model.SetDegree(18);

	model.SetCartIn(false);
	model.SetCartOut(false);

	int n = r.size();
	std::vector<double> br(n);
	std::vector<double> bt(n);
	std::vector<double> bp(n);

	double t0, t1;
	int i;
	std::vector<double> times(ntest);

	for (i=0;i<ntest;i++) {
		t0 = clock();
		model.Field(r.size(),r.data(),t.data(),p.data(),br.data(),bt.data(),bp.data());
		t1 = clock();
		times[i] = (t1 - t0)/CLOCKS_PER_SEC;
		addDot();
	}

	/* return mean and standard deviation */
	std::vector<double> out(2);
	out[0] = mean(times);
	out[1] = stddev(times);

	return out;
}

timingResult timeModel(int n, int ntest) {

	vectorTuple pos = getRandomVectors(n);
	std::vector<double> x = std::get<0>(pos);
	std::vector<double> y = std::get<1>(pos);
	std::vector<double> z = std::get<2>(pos);
	std::vector<double> r = std::get<3>(pos);
	std::vector<double> t = std::get<4>(pos);
	std::vector<double> p = std::get<5>(pos);

	std::vector<double> ca = timeCartArray(ntest,x,y,z);
	std::vector<double> cs = timeCartSingle(ntest,x,y,z);
	std::vector<double> pa = timePolarArray(ntest,r,t,p);
	std::vector<double> ps = timePolarSingle(ntest,r,t,p);

	timingResult out = {
		ps[0],ps[1],
		pa[0],pa[1],
		cs[0],cs[1],
		ca[0],ca[1]
	};
	return out;
} 

std::vector<timingResult> getTimings(std::vector<int> n, int ntest) {
	std::vector<timingResult> out(n.size());
	
	for (int i=0;i<n.size();i++) {
		out[i] = timeModel(n[i],ntest);
	}

	return out;
}

std::ostream& scientificFormat(std::ostream& os) {
    os << std::setw(8) << std::setprecision(1) << std::scientific;
    return os;
}

void printTimingLine(int n, timingResult timing) {

	std::cout << "| " << std::setw(6) << n << " | ";
	std::cout << scientificFormat << timing.muCartSingle;
	std::cout << " ±" << scientificFormat << timing.sdCartSingle << " s |   "; 
	std::cout << scientificFormat << timing.muCartArray;
	std::cout << " ±" << scientificFormat << timing.sdCartArray << " s | ";
	std::cout << scientificFormat << timing.muPolarSingle;
	std::cout << " ±" << scientificFormat << timing.sdPolarSingle << " s | "; 
	std::cout << scientificFormat << timing.muPolarArray;
	std::cout << " ±" << scientificFormat << timing.sdPolarArray << " s |" << std::endl;


}

void printTimingResult(std::vector<int> n, std::vector<timingResult> timings) {

	std::cout << "| Count  | Cartesian (single)   | Cartesian (vectorized) | Polar (single)       | Polar (vectorized)   |" << std::endl;
	std::cout << "|:-------|:---------------------|:-----------------------|:---------------------|:---------------------|" << std::endl;

	for (int i=0;i<n.size();i++) {
		printTimingLine(n[i],timings[i]);
	}
}

int main() {

	std::cout << "Calculating average model timings" << std::endl;
	nDots = 0;

	std::vector<int> n = {1,10,100,1000,10000,100000};
	std::vector<timingResult> timings = getTimings(n,5);
	std::cout << std::endl;
	printTimingResult(n,timings);
}
