import numpy as np
import os


def ListCoeffBinFiles():
	'''
	List the binary files within the "coeffs" directory
	
	'''
	
	files = os.listdir('coeffs')
	bnf = []
	for f in files:
		if f.endswith('.bin'):
			bnf.append(f)
	
	bnf = np.array(bnf)
	print('Found {:d} binary files'.format(bnf.size))
	return bnf