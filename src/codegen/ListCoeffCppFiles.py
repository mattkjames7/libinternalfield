import numpy as np
import os


def ListCoeffCppFiles():
	'''
	List the .cc files within the "coeffs" directory
	
	'''
	
	files = os.listdir('coeffs')
	bnf = []
	for f in files:
		if f.endswith('.cc'):
			bnf.append(f)
	
	bnf = np.array(bnf)
	print('Found {:d} C++ parameter files'.format(bnf.size))
	return bnf
