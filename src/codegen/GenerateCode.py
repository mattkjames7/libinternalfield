
import numpy as np
from .ConvertDatCpp import ConvertDatCpp
from .GenerateCoeffsH import GenerateCoeffsH
from .GenerateCoeffsCC import GenerateCoeffsCC
from .GenerateModelsH import GenerateModelsH
from .GenerateModelsCC import GenerateModelsCC
from .GenerateLibHeader import GenerateLibHeader
from .GenerateVarObjects import GenerateVarObjects
from .GenerateModelObjects import GenerateModelObjects
from .ListModelNames import ListModelNames


def GenerateCode(bdir):
    
	ConvertDatCpp()

	
	#list models
	planets,models,modelsl = ListModelNames()
			
	#generate files
	GenerateCoeffsH(models)
	GenerateCoeffsCC(planets,models)
	GenerateModelsH(models)
	GenerateModelsCC(models)
	GenerateLibHeader()

	#generate variable models
	GenerateVarObjects(bdir)
	GenerateModelObjects(bdir)