import numpy as np
from .ListCoeffDatFiles import ListCoeffDatFiles
import os

	
def ListModelNames():
	'''
	List the names and lower case names of all models inside the coeffs
	directory.
	
	'''
	
	#start by listing all of the object files which have been created
	planets,_,files = ListCoeffDatFiles()
	
	#strip them of their extensions
	models = [os.path.splitext(f)[0] for f in files]
	modelsl = [os.path.splitext(f)[0].lower() for f in files]
	
	return planets,models,modelsl	
