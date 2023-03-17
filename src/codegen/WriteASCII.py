import numpy as np

def WriteASCII(fname,lines):
	'''
	Write ASCII to a file
	'''
	with open(fname,'w') as f:
		f.writelines(lines)
		print('Saved {:s}'.format(fname))
	