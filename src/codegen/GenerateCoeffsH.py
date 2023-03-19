import numpy as np
from .ReadASCII import ReadASCII
from .WriteASCII import WriteASCII

def GenerateCoeffsH(planets,models):
	'''
	Generate C++ header file "coeffs.h" using the models inside the 
	coeffs directory.
	
	'''

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/template/coeffs.h.0')
	code1 = ReadASCII('codegen/template/coeffs.h.1')
	lines += code0

	for p,m in zip(planets,models):
		lines.append('extern coeffStruct& _model_coeff_{:s}();\n'.format(m))
		lines.append('extern unsigned char _binary_coeffs_{:s}_{:s}_bin_start;\n'.format(p,m))
		
		
	#rest of the code
	lines += code1
	
	#write to file
	WriteASCII('coeffs.h',lines)
	
	