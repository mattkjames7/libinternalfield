import numpy as np
from .ReadASCII import ReadASCII
from .WriteASCII import WriteASCII

def GenerateModelsCC(models):
	'''
	Generate C++ file "models.cc" using the models inside the 
	coeffs directory.
	
	'''

	modelsl = np.array([m.lower() for m in models])

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/template/models.cc.0')
	code1 = ReadASCII('codegen/template/models.cc.1')
	code2 = ReadASCII('codegen/template/models.cc.2')
	lines += code0

	#define models
	for m,ml in zip(models,modelsl):
		lines.append('Internal& {:s}()'.format(ml,m)+' {\n')
		lines.append('\tstatic Internal model("{:s}");\n'.format(m))
		lines.append('\treturn model;\n')
		lines.append('}\n\n')
	lines.append('\n')

	#add another map from model name to model pointer
	lines.append('/* map the model names to their model object pointers */\n')
	s = 'std::map<std::string,InternalFunc> getModelPtrMap() {\n'
	s += '\tstatic std::map<std::string,InternalFunc> modelPtrMap = {\n'
	for i,ml in enumerate(modelsl):
		s += '\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",{:s}'.format(ml) + '}'
		if i < len(modelsl) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '\t};\n'
	s += '\treturn modelPtrMap;\n'
	s += '}\n'
	lines.append(s)	
	
	#add some more of the existing code
	lines += code1
	
	#add another map from model name to model field function pointer
	s = 'std::map<std::string,modelFieldPtr> getModelFieldPtrMap() {\n'
	s += '\tstatic std::map<std::string,modelFieldPtr> modelFieldPtrMap = {\n'
	for i,ml in enumerate(modelsl):
		s += '\t\t\t\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",&{:s}Field'.format(ml) + '}'
		if i < len(modelsl) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '\t};\n'
	s += '\treturn modelFieldPtrMap;\n'
	s += '}\n'
	lines.append(s)		
	
	
	#add the rest of the existing code
	lines += code2
	
	#model wrapper functions for external code use
	for m in modelsl:
		s = 'void {:s}Field(double x, double y, double z,\n'.format(m)
		s+= '				double *Bx, double *By, double *Bz) {\n'
		s+= '	Internal model = {:s}();\n'.format(m)
		s+= '	model.FieldCart(x,y,z,Bx,By,Bz);\n'
		s+= '}\n\n'
		lines.append(s)
		

	#write to file
	WriteASCII('models.cc',lines)