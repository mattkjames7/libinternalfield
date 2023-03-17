import numpy as np
import os

def ProcessIGRF():
	'''
	Read the IGRF coefficient file and split it into one for each 5
	year period
	
	data are from:
	https://www.ngdc.noaa.gov/IAGA/vmod/coeffs/igrf13coeffs.txt
	
	'''
	print('Reading IGRF coefficients')
	f = open('igrf/igrf13coeffs.txt','r')
	lines = f.readlines()
	f.close()
	
	#get the years
	yl = lines[3]
	yr = np.int32(np.float64(yl.split()[3:-1]))
	yr = np.append(yr,yr[-1] + 5)
	
	#remove the header
	lines = lines[4:]
	
	#get the number of coefficient columns
	nc = np.size(lines[0].split()) - 3
	
	#number of rows
	nr = np.size(lines)
	
	#the output arrays
	gh = np.zeros(nr,dtype='U')
	n = np.zeros(nr,dtype='int32')
	m = np.zeros(nr,dtype='int32')
	c = np.zeros((nr,nc),dtype='object')
	
	#fill them
	for i in range(0,nr):
		s = lines[i].split()
		gh[i] = s[0]
		n[i] = np.int32(s[1])
		m[i] = np.int32(s[2])
		c[i,:] = np.array(s[3:])
		
	#correct the final column
	for i in range(0,nr):
		a = np.float64(c[i,-2])
		b = np.float64(c[i,-1])
		c[i,-1] = '{:8.1f}'.format(a + b)
	
	#write to files
	path = 'coeffs/earth/'
	if not os.path.isdir(path):
		os.system('mkdir -pv '+path)
	for i in range(0,nc):
		fname = path + 'igrf{:04d}.dat'.format(yr[i])
		print('Saving '+fname)
		f = open(fname,'w')
		for j in range(0,nr):
			l = '{:s}	{:d}	{:d}	{:s}\n'.format(gh[j],n[j],m[j],c[j,i])
			f.write(l)

		f.close()

	#add the list of models to the file in the "variable" folder
	path = 'variable/earth/'
	if not os.path.isdir(path):
		os.system('mkdir -pv '+path)
	fname = path + 'igrf.dat'
	f = open(fname,'w')
	for i in range(0,nc):
		l = 'igrf{:04d}	{:04d}0101 0.0\n'.format(yr[i],yr[i])
		f.write(l)
	f.close() 