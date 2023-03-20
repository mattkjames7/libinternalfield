#include "readcoeffs.h"

void readCoeffs(unsigned char *data, 
				int *len, int *nmax, int *ndef, double *rscale,
				std::vector<int> n, std::vector<int> m,
				std::vector<double> g, std::vector<double> h) {

	/* pointer to  read from*/
	unsigned char *ptr = data;


	/* this is the length of each array */
	int l, i, j, p;
	
	/* read the length */
	l = ((int*) ptr)[0];
	len[0] = l;
	ptr += sizeof(int);

	/* initialize the temporary arrays */
	int8_t *gh = new int8_t[l];
	double *coeffs = new double[l];
	
	/* load them in */
	for (i=0;i<l;i++) {
		gh[i] = ((int8_t*) ptr)[0];
		ptr += sizeof(int8_t);
	}
	for (i=0;i<l;i++) {
		n.push_back(((int*) ptr)[0]);
		ptr += sizeof(int);
	}
	for (i=0;i<l;i++) {
		m.push_back(((int*) ptr)[0]);
		ptr += sizeof(int);
	}
	for (i=0;i<l;i++) {
		coeffs[i] = ((double*) ptr)[0];
		ptr += sizeof(double);
	}
	ndef[0] = ((int*) ptr)[0];
	ptr += sizeof(int);
	
	/* get n max */
	nmax[0] = 0;
	for (i=0;i<l;i++) {
		if (n[i] > nmax[0]) {
			nmax[0] = n[i];
		}
	}

	/* calculate the length of the coefficient structure */
	int nschc = 0;
	for (i=0;i<nmax[0];i++) {
		nschc += (2 + i);
	}
	n.resize(nschc);
	m.resize(nschc);
	g.resize(nschc);
	h.resize(nschc);

	/* get rscale */
	rscale[0] = ((double*) ptr)[0];
	ptr += sizeof(double);


	p = 0;
	for (i=1;i<=nmax[0];i++) {
		for (j=0;j<=i;j++) {
			n[p] = i;
			m[p] = j;
			g[p] = 0.0;
			h[p] = 0.0;
			p++;
		}
	}

	for (i=0;i<l;i++) {
		p = m[i]-1;
		for (j=0;j<n[i];j++) {
			p += (1 + j);
		}
		if (gh[i] == 0) {
			g[p] = coeffs[i];
		} else {
			h[p] = coeffs[i];
		}
	}
			
	/* free the original arrays */
	delete[] gh;
	delete[] coeffs;

}
