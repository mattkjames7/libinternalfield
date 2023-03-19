import numpy as np
from .ReadASCII import ReadASCII
from .WriteASCII import WriteASCII



def GenerateCoeffsCC(planets,names):
	'''
	Generate C++ file "coeffs.cc" using the models inside the 
	coeffs directory.
	
	'''

	models = names
	modelsl = np.array([m.lower() for m in models])


	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/template/coeffs.cc.0')
	code1 = ReadASCII('codegen/template/coeffs.cc.1')
	code2 = ReadASCII('codegen/template/coeffs.cc.2')
	code3 = ReadASCII('codegen/template/coeffs.cc.3')
	lines += code0

	#list of model names
	s = 'std::vector<std::string> getModelNames() {\n'
	mn = '{\t"' + '",\n\t\t\t\t\t\t\t\t"'.join(modelsl)+'"};\n\n'
	s += '\t static std::vector<std::string> modelNames = '+mn
	s += '\treturn modelNames;\n'
	s += '}\n'
	lines.append(s)
	
	#arrays of coefficients and struct definitions
	lines += code1
	for p,m in zip(planets,models):
		if p == '':
			cc = ReadASCII('coeffs/{:s}.cc'.format(m))
		else:
			cc = ReadASCII('coeffs/{:s}/{:s}.cc'.format(p,m))
		lines += cc
	
	#map of structures
	s = 'std::map<std::string,coeffStructFunc> getCoeffMap() {\n'
	s += '\tstatic std::map<std::string,coeffStructFunc> coeffMap = {\t\n'
	for i,(m,ml) in enumerate(zip(models,modelsl)):
		s += '\t\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",_model_coeff_{:s}'.format(m) + '}'
		if i < len(models) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '\t};\n'
	s += '\treturn coeffMap;\n'
	s += '}\n\n'
	lines.append(s)

	#map of pointers
	s = 'std::map<std::string,unsigned char*> getCoeffPtrMap() {\n'
	s += '\tstatic std::map<std::string,unsigned char*> coeffPtrMap = {\t\n'
	for i,(p,m) in enumerate(zip(planets,modelsl)):
		s += '\t\t\t'
		s += '{"' + m + '",&_binary_coeffs_{:s}_{:s}_bin_start'.format(p,m) + '}'
		if i < len(models) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '\t};\n'
	s += '\treturn coeffPtrMap;\n'
	s += '}\n\n'
	lines.append(s)


	#add more existing code
	lines += code3
	
	#write to file
	WriteASCII('coeffs.cc',lines)