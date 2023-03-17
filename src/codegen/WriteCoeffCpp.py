import numpy as np
from .ReadASCII import ReadASCII
from .WriteASCII import WriteASCII
import os
	
def WriteCoeffCpp(planet,name):
	'''
	This will convert the ASCII files of internal magnetic field model
	coefficients to C++ code.
	
	Inputs
	======
	planet : str
		Name of the planet.
	fname : str
		Name of the ASCII file containing the coefficients.
	
	'''
	#open the ASCII file
	if planet == '':
		#planet = 'unknown'	
		coeffdat = 'coeffs/'+name+'.dat'
	else:
		coeffdat = 'coeffs/'+planet+'/'+name+'.dat'
	lines = ReadASCII(coeffdat)
	lines = np.array(lines)
	
	#get the number of lines in the file
	nl = lines.size
	
	#get any extra info out starting with '#'
	remove = np.zeros(nl,dtype='bool')
	stuff = {}
	for i in range(0,nl):
		l = lines[i]
		if l[0] == '#':
			#add this to the stuff dictionary
			s = l[1:].split()
			stuff[s[0]] = s[1]
			remove[i] = True
	good = np.where(remove == False)[0]
	lines = lines[good]
	nl = lines.size
	

	
	#create the arrays for the coefficients
	gh = np.zeros(nl,dtype='int8')
	n = np.zeros(nl,dtype='int32')
	m = np.zeros(nl,dtype='int32')
	coeff = np.zeros(nl,dtype='float64')
	
	#fill them
	good = np.zeros(nl,dtype='bool')
	for i in range(0,nl):
		try:
			s = lines[i].split()

			if s[0] == 'h':
				gh[i] = 1
			else:
				gh[i] = 0
			n[i] = np.int32(s[1])
			m[i] = np.int32(s[2])
			coeff[i] = np.float64(s[3])
			good[i] = True
		except:
			good[i] = False
	
	#remove any bad bits
	use = np.where(good)[0]
	gh = gh[use]
	n = n[use]
	m = m[use]
	coeff = coeff[use]
	nl = use.size
	
	#get any extra info - more things might be added here e.g. "planet"
	if 'DefaultDegree' in stuff:
		DefDeg = np.int32(stuff['DefaultDegree'])
	else:
		DefDeg = np.int32(n.max())
	Rscale = np.float64(stuff.get('Rscale',1.0))

	#count the number of coeffs (including ones missing from the file)
	nschc = 0
	nmax = n.max()
	for i in range(0,nmax):
		nschc += (2 + i)
	dtype = [('n','int32'),('m','int32'),('g','float64'),('h','float64')]
	schc = np.recarray(nschc,dtype=dtype)
		
	p = 0;
	for i in range(1,nmax+1):
		for j in range(0,i+1):
			schc[p].n = i
			schc[p].m = j
			schc[p].g = 0.0
			schc[p].h = 0.0
			p += 1;

	for i in range(0,nl):
		p = m[i]-1
		for j in range(0,n[i]):
			p += (1 + j)
		
		if (gh[i] == 0):
			schc[p].g = coeff[i];
		else:
			schc[p].h = coeff[i];
		
		
	
	#output file names
	fnameout = planet + '/' + name + '.cc'

	#cpp contents
	clines = []
	clines.append('coeffStruct& _model_coeff_{:s}()'.format(name)+' {\n')
	clines.append('\tstatic const int len = {:d};\n'.format(nschc))
	clines.append('\tstatic const int nmax = {:d};\n'.format(nmax))
	clines.append('\tstatic const int ndef = {:d};\n'.format(DefDeg))
	clines.append('\tstatic const double rscale = {:28.25f};\n'.format(Rscale))
	cn = '\tstatic std::vector<int> n = ' + '{'
	cm = '\tstatic std::vector<int> m = ' + '{'
	cg = '\tstatic std::vector<double> g = ' + '{'
	ch = '\tstatic std::vector<double> h = ' + '{'
	lstr0 = len(cn)
	lstrn = lstr0
	lstrm = lstr0
	lstrg = lstr0
	lstrh = lstr0
	for i in range(0,nschc):
		cns = '{:d},'.format(schc[i].n)
		cms = '{:d},'.format(schc[i].m)
		cgs = '{:f},'.format(schc[i].g)
		chs = '{:f},'.format(schc[i].h)
		
		if lstrn + len(cns) > 72:
			cn += '\n\t\t'
			lstrn = 4 + len(cns)
		else:
			lstrn += len(cns)
		if lstrm + len(cms) > 72:
			cm += '\n\t\t'
			lstrm = 4 + len(cms)
		else:
			lstrm += len(cms)
		if lstrg + len(cgs) > 72:
			cg += '\n\t\t'
			lstrg = 4 + len(cgs)
		else:
			lstrg += len(cgs)
		if lstrh + len(chs) > 72:
			ch += '\n\t\t'
			lstrh = 4 + len(chs)
		else:
			lstrh += len(chs)
			
		cn += cns
		cm += cms
		cg += cgs
		ch += chs
		
	clines.append(cn[:-1] + '};\n')
	clines.append(cm[:-1] + '};\n')
	clines.append(cg[:-1] + '};\n')
	clines.append(ch[:-1] + '};\n')
	

	clines.append('\tstatic coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};\n')
	clines.append('\treturn out;\n')
	clines.append('}\n\n')

	
	#C++ file
	#print('Saving {:s}'.format(fnameout))
	fout = 'coeffs/'+fnameout
	WriteASCII(fout,clines)
