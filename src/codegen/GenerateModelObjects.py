import numpy as np
from .ListModelNames import ListModelNames
from .EncodeCoeffBinary import EncodeCoeffBinary
from .MakeCoeffObject import MakeCoeffObject

def GenerateModelObjects(bdir):

	planets,names,_ = ListModelNames()
	n = len(names)

	for i in range(0,n):
		print('Encodeing Model: {:s} for Body: {:s}'.format(names[i],planets[i]))
		EncodeCoeffBinary(planets[i],names[i])
		MakeCoeffObject(bdir,planets[i],names[i])