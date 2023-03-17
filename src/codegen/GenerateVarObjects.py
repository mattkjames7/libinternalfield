import numpy as np
from .MakeVariableObject import MakeVariableObject
from .EncodeVariableBinary import EncodeVariableBinary
from .ListVariableModels import ListVariableModels


def GenerateVarObjects(bdir):

	planets,names,dats = ListVariableModels()
	n = names.size

	for i in range(0,n):
		EncodeVariableBinary(planets[i],names[i])
		MakeVariableObject(bdir,planets[i],names[i])
