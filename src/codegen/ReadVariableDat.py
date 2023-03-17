import numpy as np
from  .ReadASCII import ReadASCII

def ReadVariableDat(fname):

	lines = np.array(ReadASCII(fname))

	n = lines.size
	names = np.zeros(n,dtype='object')
	dates = np.zeros(n,dtype='int32')
	times = np.zeros(n,dtype='float64')

	for i in range(0,n):
		s = lines[i].split()
		names[i] = s[0]
		dates[i] = np.int32(s[1])
		times[i] = np.float64(s[2])
	return names,dates,times