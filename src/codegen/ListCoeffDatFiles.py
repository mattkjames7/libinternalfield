import numpy as np
from .ListFiles import ListFiles
import os


def ListCoeffDatFiles():
	'''
	List the dat files within the "coeffs" directory
	
	'''
	
	fnames = ListFiles('coeffs/')
	n = fnames.size
	planet = []
	dat = []
	name = []
	for i in range(0,n):
		if fnames[i].endswith('.dat'):
			tmp,d = os.path.split(fnames[i])
			dat.append(d)
			planet.append(tmp[7:])
			name.append(os.path.splitext(d)[0])
	planet = np.array(planet)
	dat = np.array(dat)
	name = np.array(name)
	
	return planet,name,dat