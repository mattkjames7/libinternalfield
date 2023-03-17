import numpy as np



	
def ReadASCII(fname):
	'''
	Read an ASCII file in.
	
	'''
	with open(fname,'r') as f:
		lines = f.readlines()
		
	return lines