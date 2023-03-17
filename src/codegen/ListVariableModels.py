import numpy as np
import os
from .ListFiles import ListFiles

def ListVariableModels():
	'''
	list all variable model files
	'''
	fnames = ListFiles('variable/')
	n = fnames.size
	planet = []
	dat = []
	name = []
	for i in range(0,n):
		if fnames[i].endswith('.dat'):
			tmp,d = os.path.split(fnames[i])
			dat.append(d)
			planet.append(tmp[9:])
			name.append(os.path.splitext(d)[0])
	planet = np.array(planet)
	dat = np.array(dat)
	name = np.array(name)
	
	return planet,name,dat