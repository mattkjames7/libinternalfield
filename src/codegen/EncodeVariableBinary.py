import numpy as np
from .ReadVariableDat import ReadVariableDat

def EncodeVariableBinary(planet,name):
    
	datname = 'variable/'+planet+'/'+name+'.dat'
	binname = 'variable/'+planet+'/'+name+'.bin'

	names,dates,times = ReadVariableDat(datname)

	f = open(binname,'wb')
	n = len(names)
	np.int32(n).tofile(f)
	for nm in names:
		l = np.int32(len(nm))
		l.tofile(f)
		f.write(nm.encode('utf8'))
	dates.tofile(f)
	times.tofile(f)
	f.close()
	print('Saved '+binname)