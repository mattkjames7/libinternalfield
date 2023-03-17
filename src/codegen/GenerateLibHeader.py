import numpy as np
from .ReadASCII import ReadASCII
from .WriteASCII import WriteASCII


def _ExtractCoeffsH():
	'''
	Extract the bits of coeffs.h that we want
	'''
	lines = ReadASCII('coeffs.h')
	return _RemoveDirectives(lines)

def _ExtractModelsH():
	'''
	Extract the bits we need from models.h

	'''
	lines = ReadASCII('models.h')

	c,cc = _SplitHeaderDefs(lines)

	c = _RemoveDirectives(c)
	cc = _RemoveDirectives(cc)

	keep = np.ones(cc.size,dtype='bool')
	for i in range(0,cc.size):
		if 'typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);' in cc[i]:
			keep[i] = False
	use = np.where(keep)[0]
	cc = cc[use]

	return c,cc

def _ExtractInternalH():

	lines = ReadASCII('internal.h')

	return _RemoveDirectives(lines)

def _ExtractInternalModelH():

	lines = ReadASCII('internalmodel.h')
	return _RemoveDirectives(lines)

def _ExtractLibinternalH():

	lines = ReadASCII('libinternal.h')

	c,cc = _SplitHeaderDefs(lines)

	c = _RemoveDirectives(c)
	cc = _RemoveDirectives(cc)

	return c,cc

def _ExtractListmapkeysH():

	lines = ReadASCII('listmapkeys.h')
	return _RemoveDirectives(lines)

def _ExtractReadCoeffsH():

	lines = ReadASCII('readcoeffs.h')
	return _RemoveDirectives(lines)


def _RemoveDirectives(lines):
	'''
	Remove compiler directives and includes
	'''
	lines = np.array(lines)
	nl = lines.size

	use = np.ones(nl,dtype='bool')
	for i in range(0,nl):
		if lines[i].strip().startswith('#'):
			use[i] = False

	use = np.where(use)

	return lines[use]

def _SplitHeaderDefs(lines):
	'''
	split code into C and C++ code

	'''
	lines = np.array(lines)
	ltype = np.zeros(lines.size,dtype='bool')
	isC = False
	for i in range(0,lines.size):

		if isC and lines[i].strip() == '}':
			isC = False
		ltype[i] = isC
		if 'extern "C"' in lines[i].strip():
			isC = True

	usec = np.where(ltype)[0]
	usecc = np.where(ltype == False)[0]

	c = lines[usec]
	cc = lines[usecc]

	return c,cc


def GenerateLibHeader():
	'''
	Generate a library header to be included when linking to 
	libinternalfield.so
	
	'''
	
	#read in the template code
	code = ReadASCII('codegen/template/libinternalfield.h.0')
	
	#read in the other headers
	ccode = []
	cccode = []

	cc = _ExtractCoeffsH()
	cccode = cccode + cc.tolist()

	cc = _ExtractReadCoeffsH()
	cccode = cccode + cc.tolist()

	cc = _ExtractInternalH()
	cccode = cccode + cc.tolist()

	c,cc = _ExtractModelsH()
	ccode = ccode + c.tolist()
	cccode = cccode + cc.tolist()

	cc = _ExtractListmapkeysH()
	cccode = cccode + cc.tolist()



	cc = _ExtractInternalModelH()
	cccode = cccode + cc.tolist()

	c,cc = _ExtractLibinternalH()
	ccode = ccode + c.tolist()
	cccode = cccode + cc.tolist()	

	#add C code
	code = code + ccode

	#add C++ code
	code.append('#ifdef __cplusplus\n')
	code.append('}\n')

	code = code + cccode
	code.append('#endif\n')
	code.append('#endif\n')			
	
	#save it
	WriteASCII('../include/internalfield.h',code)
	