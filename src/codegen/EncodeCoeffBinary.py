import numpy as np
import os
from .ReadASCII import ReadASCII

def EncodeCoeffBinary(planet,name):
	'''
	This will encode the ASCII files of internal magnetic field model
	coefficients as pure binary.
	
	Inputs
	======
	fnamein : str
		Name of the ASCII file containing the coefficients.
	fnameout : str
		Name of the output binary file.
	
	'''
	
	fname = planet+'/'+name+'.dat'
	print('Reading file '+fname)
	#open the ASCII file
	f = open('coeffs/'+fname,'r')
	lines = f.readlines()
	f.close()
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
	for i in range(0,nl):
		s = lines[i].split()

		if s[0] == 'h':
			gh[i] = 1
		else:
			gh[i] = 0
			
		n[i] = np.int32(s[1])
		m[i] = np.int32(s[2])
		coeff[i] = np.float64(s[3])

	#get any extra info - more things might be added here e.g. "planet"
	if 'DefaultDegree' in stuff:
		DefDeg = np.int32(stuff['DefaultDegree'])
	else:
		DefDeg = np.int32(n.max())
	Rscale = np.float64(stuff.get('Rscale',1.0))

	
	#output file name
	name,ext = os.path.splitext(fname)
	fnameout = name + '.bin'
	
	#we could add extra stuff here, e.g. default order, citation etc.
	#open the output file
	print('Saving {:s}'.format(fnameout))
	f = open('coeffs/'+fnameout,'wb')
	np.int32(nl).tofile(f)
	gh.tofile(f)
	n.tofile(f)
	m.tofile(f)
	coeff.tofile(f)
	DefDeg.tofile(f)
	Rscale.tofile(f)
	f.close()