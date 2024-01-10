#include "test.h"

FieldVectors getPositions() {
	std::vector<double> r = {3,3,3,3, 3,3,3,3, 3,3,3,3, 3,3,3,3};
	std::vector<double> tdeg = {10,10,10,10,55,55,55,55,
                                90,90,90,90,130,130,130,130};
	std::vector<double> pdeg = {0,27,180,340, 0,27,180,340,
                                0, 27,180,340, 0,27,180,340};  
	std::vector<double> t(16);
	std::vector<double> p(16);

	/* convert to radians */
	int i;
	double deg2rad = M_PI/180.0;
	for (i=0;i<t.size();i++) {
		t[i] = deg2rad*tdeg[i];
		p[i] = deg2rad*pdeg[i];
	}

	return {r,t,p};	
}

FieldVectors getPositionsCart() {

	FieldVectors pos = getPositions();

	std::vector<double> r = std::get<0>(pos);
	std::vector<double> t = std::get<1>(pos);
	std::vector<double> p = std::get<2>(pos);

	/* convert to cartesian */
	int n = r.size();
	std::vector<double> x(n), y(n), z(n);
	int i;
	for (i=0;i<n;i++) {
		x[i] = r[i]*cos(t[i])*cos(p[i]);
		y[i] = r[i]*cos(t[i])*sin(p[i]);
		z[i] = r[i]*sin(t[i]);
	}
	return {x,y,z};	
}


FieldVectors vip4Vectors(FieldVectors pos) {

	std::vector<double> r = std::get<0>(pos);
	std::vector<double> t = std::get<1>(pos);
	std::vector<double> p = std::get<2>(pos);

	std::vector<double> Br(r.size());
	std::vector<double> Bt(t.size());
	std::vector<double> Bp(p.size());

	/* set model to VIP4 */
	InternalModel internalModel = getInternalModel();
	internalModel.SetModel("vip4");
	internalModel.SetCartIn(false);
	internalModel.SetCartOut(false);
	
	/* call model */
	internalModel.Field((int) r.size(),r.data(),t.data(),p.data(),Br.data(),Bt.data(),Bp.data());

	return {Br,Bt,Bp};

}


FieldVectors jrm09Vectors(FieldVectors pos) {

	std::vector<double> r = std::get<0>(pos);
	std::vector<double> t = std::get<1>(pos);
	std::vector<double> p = std::get<2>(pos);

	std::vector<double> Br(r.size());
	std::vector<double> Bt(t.size());
	std::vector<double> Bp(p.size());

	/* set model to JRM09 */
	InternalModel internalModel = getInternalModel();
	internalModel.SetModel("jrm09");
	internalModel.SetCartIn(false);
	internalModel.SetCartOut(false);
	
	/* call model */
	internalModel.Field((int) r.size(),r.data(),t.data(),p.data(),Br.data(),Bt.data(),Bp.data());

	return {Br,Bt,Bp};

}


FieldVectors vip4FunctionVectors(FieldVectors pos) {

	std::vector<double> x = std::get<0>(pos);
	std::vector<double> y = std::get<1>(pos);
	std::vector<double> z = std::get<2>(pos);

	std::vector<double> Bx(x.size());
	std::vector<double> By(x.size());
	std::vector<double> Bz(x.size());

	int i;
	for (i=0;i<x.size();i++) {
		vip4Field(x[i],y[i],z[i],&Bx[i],&By[i],&Bz[i]);
	}
	return {Bx,By,Bz};

}


std::string formatVectors(
	double p0, double p1, double p2,
	double b0, double b1, double b2,
	double t0, double t1, double t2
	) {
	
	std::ostringstream out;
	out << "|";
	out << " " << std::setw(3) << std::setprecision(0) << std::fixed << p0 << " |";
	out << " " << std::setw(3) << std::setprecision(0) << std::fixed << p1 << " |";
	out << " " << std::setw(3) << std::setprecision(0) << std::fixed << p2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t2 << " |\n";

	return out.str();
}

void printVectors(FieldVectors pos, FieldVectors orig, FieldVectors test) {

	std::cout << "|  r  |  t  |  p  | Br0      | Bt0      | Bp0      | Br1      | Bt1      | Bp1      |" << std::endl;
	std::cout << "|:----|:----|:----|:---------|:---------|:---------|:---------|:---------|:---------|" << std::endl;

	std::vector<double> p0,p1,p2,b0,b1,b2,t0,t1,t2;
	p0 = std::get<0>(pos);
	p1 = std::get<1>(pos);
	p2 = std::get<2>(pos);

	b0 = std::get<0>(orig);
	b1 = std::get<1>(orig);
	b2 = std::get<2>(orig);

	t0 = std::get<0>(test);
	t1 = std::get<1>(test);
	t2 = std::get<2>(test);

	int n = p0.size();
	int i;
	std::string line;
	for (i=0;i<n;i++) {
		line = formatVectors(p0[i],p1[i],p2[i],b0[i],b1[i],b2[i],t0[i],t1[i],t2[i]);
		std::cout << line;
	}
}

FieldVectors vip4TestVectors() {
	std::vector<double> tr, tt, tp, tbr, tbt, tbp;
	std::filesystem::path file = "testvip4.bin";
	readVectors(file,tr,tt,tp,tbr,tbt,tbp);
	return {tbr,tbt,tbp};	
}

FieldVectors jrm09TestVectors() {
	std::vector<double> tr, tt, tp, tbr, tbt, tbp;
	std::filesystem::path file = "testjrm09.bin";
	readVectors(file,tr,tt,tp,tbr,tbt,tbp);
	return {tbr,tbt,tbp};	
}

FieldVectors vip4TestFunctionVectors() {
	std::vector<double> tr, tt, tp, tbr, tbt, tbp;
	std::filesystem::path file = "testvip4function.bin";
	readVectors(file,tr,tt,tp,tbr,tbt,tbp);
	return {tbr,tbt,tbp};	
}

bool compareSavedVectors(FieldVectors origField, FieldVectors bField) {


	return compareVectors(
		std::get<0>(bField),std::get<0>(bField),std::get<0>(bField),
		std::get<0>(origField),std::get<0>(origField),std::get<0>(origField)
	);
}

void testVip4Internal() {

	FieldVectors pos = getPositions();
	FieldVectors bVip4 = vip4Vectors(pos);
	FieldVectors origVip4 = vip4TestVectors();

	bool goodVip4 = compareSavedVectors(origVip4,bVip4);
	std::cout << "VIP4 vector test................................";
	if (goodVip4) {
		std::cout << "PASS" << std::endl;
	} else { 
		std::cout << "FAIL" << std::endl;
		printVectors(pos,origVip4,bVip4);
	}

}

void testJrm09Internal() {

	FieldVectors pos = getPositions();
	FieldVectors bJrm09 = jrm09Vectors(pos);
	FieldVectors origJrm09 = jrm09TestVectors();


	bool goodJrm09 = compareSavedVectors(origJrm09,bJrm09);
	std::cout << "JRM09 vector test...............................";
	if (goodJrm09) {
		std::cout << "PASS" << std::endl;
	} else { 
		std::cout << "FAIL" << std::endl;
		printVectors(pos,origJrm09,bJrm09);
	}
	
}


void testVip4Function() {

	FieldVectors pos = getPositions();
	FieldVectors bVip4 = vip4FunctionVectors(pos);
	FieldVectors origVip4 = vip4TestFunctionVectors();

	bool goodVip4 = compareSavedVectors(origVip4,bVip4);
	std::cout << "VIP4 function test...............................";
	if (goodVip4) {
		std::cout << "PASS" << std::endl;
	} else { 
		std::cout << "FAIL" << std::endl;
		printVectors(pos,origVip4,bVip4);
	}

}


int main() {

	testVip4Internal();
	testJrm09Internal();
	testVip4Function();
	
}
	
