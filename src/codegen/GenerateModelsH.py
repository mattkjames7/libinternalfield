import numpy as np
from .ReadASCII import ReadASCII
from .WriteASCII import WriteASCII


def GenerateModelsH(models):
	'''
	Generate C++ header file "models.h" using the models inside the 
	coeffs directory.
	
	'''

	modelsl = np.array([m.lower() for m in models])

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/template/models.h.0')
	code1 = ReadASCII('codegen/template/models.h.1')
	lines += code0

	#add externs
	for m in modelsl:
		lines.append('extern Internal& {:s}();\n'.format(m))
	lines.append('\n')
	
	#add the rest of the existing code
	lines += code1

	#define model field functions
	
	for m in modelsl:
		s = '	void {:s}Field(double x, double y, double z,\n'.format(m)
		s+= '				double *Bx, double *By, double *Bz);\n'
		lines.append(s)		
	lines.append('}\n')

	#write to file
	WriteASCII('models.h',lines)