#include "savetestdata.h"


void printVectorLine(
	double p0, double p1, double p2,
	double b0, double b1, double b2
	) {
	
	std::ostringstream out;
	out << "|";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p0 << " |";
	out << " " << std::setw(5) << std::setprecision(2) << std::fixed << p1 << " |";
	out << " " << std::setw(5) << std::setprecision(2) << std::fixed << p2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b2 << " |";


	std::cout << out.str() << std::endl;
}


void printVectors(
	std::vector<double> p0, std::vector<double> p1, std::vector<double> p2,
	std::vector<double> b0, std::vector<double> b1, std::vector<double> b2
) {

	std::cout << "|   r   |   t   |   p   | Br0      | Bt0      | Bp0      |" << std::endl;
	std::cout << "|:------|:------|:------|:---------|:---------|:---------|" << std::endl;

	int n = p0.size();
	int i;

	for (i=0;i<n;i++) {
		printVectorLine(p0[i],p1[i],p2[i],b0[i],b1[i],b2[i]);
	}
}



void printVectorLineCart(
	double p0, double p1, double p2,
	double b0, double b1, double b2
	) {
	
	std::ostringstream out;
	out << "|";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p0 << " |";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p1 << " |";
	out << " " << std::setw(5) << std::setprecision(1) << std::fixed << p2 << " |";

	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b0 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b1 << " |";
	out << " " << std::setw(8) << std::setprecision(1) << std::fixed << b2 << " |";


	std::cout << out.str() << std::endl;
}


void printVectorsCart(
	std::vector<double> p0, std::vector<double> p1, std::vector<double> p2,
	std::vector<double> b0, std::vector<double> b1, std::vector<double> b2
) {

	std::cout << "|   x   |   y   |   z   | Bx0      | By0      | Bz0      |" << std::endl;
	std::cout << "|:------|:------|:------|:---------|:---------|:---------|" << std::endl;

	int n = p0.size();
	int i;

	for (i=0;i<n;i++) {
		printVectorLineCart(p0[i],p1[i],p2[i],b0[i],b1[i],b2[i]);
	}
}

void saveVIP4Vectors() {
    std::filesystem::path vectorFile = std::filesystem::current_path();
    vectorFile /= "testvip4.bin";

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
	
	/*output arrays */
	std::vector<double> Br(16);
	std::vector<double> Bt(16);
	std::vector<double> Bp(16);        

	/* set model to VIP4 */
	InternalModel internalModel = getInternalModel();
	internalModel.SetModel("vip4");
	internalModel.SetCartIn(false);
	internalModel.SetCartOut(false);
	
	/* call model */
	internalModel.Field((int) r.size(),r.data(),t.data(),p.data(),Br.data(),Bt.data(),Bp.data());

    /* save the vectors */
	saveVectors(vectorFile,r,t,p,Br,Bt,Bp);                          

	std::cout << "VIP4" << std::endl;
	printVectors(r,t,p,Br,Bt,Bp);
}

void saveJRM09Vectors() {
    std::filesystem::path vectorFile = std::filesystem::current_path();
    vectorFile /= "testjrm09.bin";

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
	
	/*output arrays */
	std::vector<double> Br(16);
	std::vector<double> Bt(16);
	std::vector<double> Bp(16);        

	/* set model to VIP4 */
	InternalModel internalModel = getInternalModel();
	internalModel.SetModel("jrm09");
	internalModel.SetCartIn(false);
	internalModel.SetCartOut(false);
	
	/* call model */
	internalModel.Field((int) r.size(),r.data(),t.data(),p.data(),Br.data(),Bt.data(),Bp.data());

    /* save the vectors */
    saveVectors(vectorFile,r,t,p,Br,Bt,Bp);     

	std::cout << "JRM09" << std::endl;
	printVectors(r,t,p,Br,Bt,Bp);                     
}

void saveVIP4TestFunctionVectors() {
   std::filesystem::path vectorFile = std::filesystem::current_path();
    vectorFile /= "testvip4function.bin";

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

	/* convert to cartesian */
	int n = r.size();
	std::vector<double> x(n), y(n), z(n);
	for (i=0;i<n;i++) {
		x[i] = r[i]*cos(t[i])*cos(p[i]);
		y[i] = r[i]*cos(t[i])*sin(p[i]);
		z[i] = r[i]*sin(t[i]);
	}

	/*output arrays */
	std::vector<double> Bx(16);
	std::vector<double> By(16);
	std::vector<double> Bz(16);        

	for (i=0;i<x.size();i++) {
		vip4Field(x[i],y[i],z[i],&Bx[i],&By[i],&Bz[i]);
	}

    /* save the vectors */
	saveVectors(vectorFile,x,y,z,Bx,By,Bz);                          


	std::cout << "VIP4 (Cartesian)" << std::endl;
	printVectorsCart(x,y,z,Bx,By,Bz);

}

void saveVIP4ModelVariables() {

   	std::filesystem::path file = std::filesystem::current_path();
    file /= "testmodelvars.bin";

	Internal model("vip4");
	std::vector<struct schmidtcoeffs> schc = model.getSchmidtCoeffs();
	std::vector<std::vector<double>> Snm = model.getSnm();
	std::vector<std::vector<double>> g = model.getg();
	std::vector<std::vector<double>> h = model.geth();
	saveModelVariables(file,schc,Snm,g,h);

}

void saveCvector() {
	modelFieldPtr model = getModelFieldPtr("jrm33");
	double x = 10.0;
	double y = 10.0;
	double z = 0.0;
	double Bx, By, Bz;
	model(x,y,z,&Bx,&By,&Bz);

   	std::filesystem::path fileName = std::filesystem::current_path();
    fileName /= "ctest.bin";
	std::ofstream file(fileName,std::ios::binary);
	file.write(reinterpret_cast<const char*>(&Bx),sizeof(double));
	file.write(reinterpret_cast<const char*>(&By),sizeof(double));
	file.write(reinterpret_cast<const char*>(&Bz),sizeof(double));
	file.close();
}

void saveCppvector() {
	InternalModel model;
	model.SetModel("jrm33");
	model.SetCartIn(true);
	model.SetCartOut(true);
	double x = 10.0;
	double y = 10.0;
	double z = 0.0;
	double Bx, By, Bz;
	model.Field(x,y,z,&Bx,&By,&Bz);
   	std::filesystem::path fileName = std::filesystem::current_path();
    fileName /= "cpptest.bin";
	std::ofstream file(fileName,std::ios::binary);
	file.write(reinterpret_cast<const char*>(&Bx),sizeof(double));
	file.write(reinterpret_cast<const char*>(&By),sizeof(double));
	file.write(reinterpret_cast<const char*>(&Bz),sizeof(double));
	file.close();
}

int main() {
    saveVIP4Vectors();
    saveJRM09Vectors();
	saveVIP4TestFunctionVectors();
	saveVIP4ModelVariables();
	saveCvector();
	saveCppvector();
    return 0;
}