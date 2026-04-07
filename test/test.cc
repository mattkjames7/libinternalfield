#include "test.h"

#include <algorithm>
#include <cstring>

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
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p0 << " |";
	out << " " << std::setw(5) << std::setprecision(2) << std::fixed << p1 << " |";
	out << " " << std::setw(5) << std::setprecision(2) << std::fixed << p2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t2 << " |\n";

	return out.str();
}

std::string formatVectorsCart(
	double p0, double p1, double p2,
	double b0, double b1, double b2,
	double t0, double t1, double t2
	) {
	
	std::ostringstream out;
	out << "|";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p0 << " |";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p1 << " |";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << t2 << " |\n";

	return out.str();
}

void printVectors(FieldVectors pos, FieldVectors orig, FieldVectors test) {

	std::cout << "|   r   |   t   |   p   | Br0      | Bt0      | Bp0      | Br1      | Bt1      | Bp1      |" << std::endl;
	std::cout << "|:------|:------|:------|:---------|:---------|:---------|:---------|:---------|:---------|" << std::endl;

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


void printVectorsCart(FieldVectors pos, FieldVectors orig, FieldVectors test) {

	std::cout << "|   x   |   y   |   z   | Bx0      | By0      | Bz0      | Bx1      | By1      | Bz1      |" << std::endl;
	std::cout << "|:------|:------|:------|:---------|:---------|:---------|:---------|:---------|:---------|" << std::endl;

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
		line = formatVectorsCart(p0[i],p1[i],p2[i],b0[i],b1[i],b2[i],t0[i],t1[i],t2[i]);
		std::cout << line;
	}
}

FieldVectors vip4TestVectors() {
	std::vector<double> tr, tt, tp, tbr, tbt, tbp;
	std::filesystem::path file = "data/testvip4.bin";
	readVectors(file,tr,tt,tp,tbr,tbt,tbp);
	return {tbr,tbt,tbp};	
}

FieldVectors jrm09TestVectors() {
	std::vector<double> tr, tt, tp, tbr, tbt, tbp;
	std::filesystem::path file = "data/testjrm09.bin";
	readVectors(file,tr,tt,tp,tbr,tbt,tbp);
	return {tbr,tbt,tbp};	
}

FieldVectors vip4TestFunctionVectors() {
	std::vector<double> tr, tt, tp, tbr, tbt, tbp;
	std::filesystem::path file = "data/testvip4function.bin";
	readVectors(file,tr,tt,tp,tbr,tbt,tbp);
	return {tbr,tbt,tbp};	
}

bool compareSavedVectors(FieldVectors origField, FieldVectors bField) {


	return compareVectors(
		std::get<0>(bField),std::get<1>(bField),std::get<2>(bField),
		std::get<0>(origField),std::get<1>(origField),std::get<2>(origField)
	);
}

void testVip4Internal() {

	FieldVectors pos = getPositions();
	FieldVectors bVip4 = vip4Vectors(pos);
	FieldVectors origVip4 = vip4TestVectors();

	bool goodVip4 = compareSavedVectors(origVip4,bVip4);
	std::cout << "VIP4 vector test..............................";
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
	std::cout << "JRM09 vector test.............................";
	if (goodJrm09) {
		std::cout << "PASS" << std::endl;
	} else { 
		std::cout << "FAIL" << std::endl;
		printVectors(pos,origJrm09,bJrm09);
	}
	
}


void testVip4Function() {

	FieldVectors pos = getPositionsCart();
	FieldVectors bVip4 = vip4FunctionVectors(pos);
	FieldVectors origVip4 = vip4TestFunctionVectors();

	bool goodVip4 = compareSavedVectors(origVip4,bVip4);
	std::cout << "VIP4 function test............................";
	if (goodVip4) {
		std::cout << "PASS" << std::endl;
	} else { 
		std::cout << "FAIL" << std::endl;
		printVectorsCart(pos,origVip4,bVip4);
	}

}


void printSchmidt(std::vector<internalfield::schmidtcoeffs> schc) {
	int i;
	std::cout << "n: ";
	for (i=0;i<schc.size();i++) {
		std::cout << std::setw(4) << schc[i].n << " ";
	}
	std::cout << "m: ";
	for (i=0;i<schc.size();i++) {
		std::cout << std::setw(4) << schc[i].m << " ";
	}
	std::cout << "g: ";
	for (i=0;i<schc.size();i++) {
		std::cout << std::setw(10) << std::setprecision(3) << schc[i].g << " ";
	}
	std::cout << "h: ";
	for (i=0;i<schc.size();i++) {
		std::cout << std::setw(10) << std::setprecision(3) << schc[i].h << " ";
	}
}

void compareSchmidtCoeffs(
	std::vector<internalfield::schmidtcoeffs> &schc0,
	std::vector<internalfield::schmidtcoeffs> &schc1
){
	int n = schc0.size();
	std::cout << "Schmidt Coefficients..........................";
	bool passed = true;
	int i;

	if (schc1.size() != n) {
		passed = false;
	} else {
		for (i=0;i<n;i++) {
			if ((schc0[i].n != schc1[i].n) ||
				(schc0[i].m != schc1[i].m) ||
				(schc0[i].g != schc1[i].g) ||
				(schc0[i].h != schc1[i].h)) {
				passed = false;
				break;
			}
		}
	}

	if (passed) {
		std::cout << "PASS" << std::endl;
	} else {
		std::cout << "FAIL" << std::endl;
		std::cout << "Schmidt Coefficient mismatch" << std::endl;
		std::cout << "Expected:" << std::endl;
		printSchmidt(schc0);
		std::cout << "Found:" << std::endl;
		printSchmidt(schc1);
	}
}

void printVectorVector(std::vector<std::vector<double>> x) {
	int i, j;
	std::cout << "[" << std::endl;
	for (i=0;i<x.size();i++) {
		std::cout << "\t[";
		for (j=0;j<x[i].size();j++) {
			if (j % 6 == 0) {
				std::cout << std::endl << "\t\t";
			}
			std::cout << std::setw(10) << std::setprecision(3) << x[i][j] << " ";
		}
		std::cout << std::endl << "\t]" << std::endl;

	}
	std::cout << "]" << std::endl;
}

void printVectorVector(std::vector<std::vector<int>> x) {
	int i, j;
	std::cout << "[" << std::endl;
	for (i=0;i<x.size();i++) {
		std::cout << "\t[";
		for (j=0;j<x[i].size();j++) {
			if (j % 10 == 0) {
				std::cout << std::endl << "\t\t";
			}
			std::cout << std::setw(4) << x[i][j] << " ";
		}
		std::cout << std::endl << "\t]" << std::endl;

	}
	std::cout << "]" << std::endl;
}


void compareVectorVector(
	std::string name,
	std::vector<std::vector<double>> x0, 
	std::vector<std::vector<double>> x1
) {

	int i, j, n = x0.size(), s = 46 - name.size();
	std::cout << name;
	for (i=0;i<s;i++) {
		std::cout << ".";
	}
	bool passed = true;

	if (x1.size() != n) {
		passed = false;
	} else {
		for (i=0;i<n;i++) {
			for (j=0;j<x0[i].size();j++) {
				if (x0[i][j] != x1[i][j]) {
					passed = false;
					break;
				}
			}
		}
	}

	if (passed) {
		std::cout << "PASS" << std::endl;
	} else {
		std::cout << "FAIL" << std::endl;
		std::cout << "Mismatch (" << name << ")" << std::endl;
		std::cout << "Expected:" << std::endl;
		printVectorVector(x0);
		std::cout << "Found:" << std::endl;
		printVectorVector(x1);
	}
}


void compareVectorVector(
	std::string name,
	std::vector<std::vector<int>> x0, 
	std::vector<std::vector<int>> x1
) {

	int i, j, n = x0.size(), s = 46 - name.size();
	std::cout << name << s;
	for (i=0;i<s;i++) {
		std::cout << ".";
	}
	bool passed = true;

	if (x1.size() != n) {
		passed = false;
	} else {
		for (i=0;i<n;i++) {
			for (j=0;j<x0[i].size();j++) {
				if (x0[i][j] != x1[i][j]) {
					passed = false;
					break;
				}
			}
		}
	}

	if (passed) {
		std::cout << "PASS" << std::endl;
	} else {
		std::cout << "FAIL" << std::endl;
		std::cout << "Mismatch (" << name << ")" << std::endl;
		std::cout << "Expected:" << std::endl;
		printVectorVector(x0);
		std::cout << "Found:" << std::endl;
		printVectorVector(x1);
	}
}



void testModelVars() {
	std::vector<std::vector<double>> Snm0, Snm1, g0, g1, h0, h1;
	std::vector<internalfield::schmidtcoeffs> schc0, schc1;

	Internal model("vip4");
	schc1 = model.getSchmidtCoeffs();
	Snm1 = model.getSnm();
	g1 = model.getg();
	h1 = model.geth();

   	std::filesystem::path file = std::filesystem::current_path();
	file /= "data/testmodelvars.bin";
	readModelVariables(file,schc0,Snm0,g0,h0);

	compareSchmidtCoeffs(schc0,schc1);
	compareVectorVector("Snm",Snm0,Snm1);
	compareVectorVector("g",g0,g1);
	compareVectorVector("h",h0,h1);
}

void testVip4MacroFunction() {
	std::cout << "VIP4 macro wrapper validity test...............";

	const double x = 9.5;
	const double y = -2.25;
	const double z = 1.75;

	double bxWrap = 0.0;
	double byWrap = 0.0;
	double bzWrap = 0.0;
	vip4Field(x, y, z, &bxWrap, &byWrap, &bzWrap);

	InternalModel model;
	model.SetModel("vip4");
	model.SetCartIn(true);
	model.SetCartOut(true);

	double bxModel = 0.0;
	double byModel = 0.0;
	double bzModel = 0.0;
	model.Field(x, y, z, &bxModel, &byModel, &bzModel);

	const bool finite = std::isfinite(bxWrap) && std::isfinite(byWrap) && std::isfinite(bzWrap);
	const double absTol = 1e-6;
	const double dx = std::fabs(bxWrap - bxModel);
	const double dy = std::fabs(byWrap - byModel);
	const double dz = std::fabs(bzWrap - bzModel);
	const bool matchesModel = (dx <= absTol) && (dy <= absTol) && (dz <= absTol);

	if (finite && matchesModel) {
		std::cout << "PASS" << std::endl;
	} else {
		std::cout << "FAIL" << std::endl;
		if (!finite) {
			std::cout << "vip4Field returned non-finite values" << std::endl;
		}
		if (!matchesModel) {
			std::cout << "vip4Field output differs from InternalModel(vip4)" << std::endl;
			std::cout << "Wrapper: [" << bxWrap << ", " << byWrap << ", " << bzWrap << "]" << std::endl;
			std::cout << "Model:   [" << bxModel << ", " << byModel << ", " << bzModel << "]" << std::endl;
		}
	}
}

void testSingletonConfigRoundTrip() {
	std::cout << "Singleton config get/set + field change........";

	double x = 8.0;
	double y = 1.25;
	double z = -0.5;

	char modelName[64];
	bool cartIn = false;
	bool cartOut = false;
	int maxDeg = 0;

	SetInternalCFG("vip4", true, true, 1);
	GetInternalCFG(modelName, &cartIn, &cartOut, &maxDeg);

	const bool cfgAOk = (std::strcmp(modelName, "vip4") == 0) && cartIn && cartOut && (maxDeg == 1);

	double bxA = 0.0;
	double byA = 0.0;
	double bzA = 0.0;
	InternalField(1, &x, &y, &z, &bxA, &byA, &bzA);

	SetInternalCFG("vip4", true, true, 4);
	GetInternalCFG(modelName, &cartIn, &cartOut, &maxDeg);

	const bool cfgBOk = (std::strcmp(modelName, "vip4") == 0) && cartIn && cartOut && (maxDeg == 4);

	double bxB = 0.0;
	double byB = 0.0;
	double bzB = 0.0;
	InternalField(1, &x, &y, &z, &bxB, &byB, &bzB);

	const bool finite = std::isfinite(bxA) && std::isfinite(byA) && std::isfinite(bzA) &&
					 std::isfinite(bxB) && std::isfinite(byB) && std::isfinite(bzB);
	const double delta = std::fabs(bxA - bxB) + std::fabs(byA - byB) + std::fabs(bzA - bzB);
	const bool fieldChanged = delta > 1e-6;

	if (cfgAOk && cfgBOk && finite && fieldChanged) {
		std::cout << "PASS" << std::endl;
	} else {
		std::cout << "FAIL" << std::endl;
		if (!cfgAOk || !cfgBOk) {
			std::cout << "Config round-trip mismatch from GetInternalCFG" << std::endl;
			std::cout << "Model=" << modelName << " CartIn=" << cartIn << " CartOut=" << cartOut << " MaxDeg=" << maxDeg << std::endl;
		}
		if (!finite) {
			std::cout << "InternalField returned non-finite values" << std::endl;
		}
		if (!fieldChanged) {
			std::cout << "InternalField output did not change after config update" << std::endl;
		}
	}
}


int main() {

	testVip4Internal();
	testJrm09Internal();
	testVip4Function();
	testModelVars();
	testVip4MacroFunction();
	testSingletonConfigRoundTrip();
}
	
