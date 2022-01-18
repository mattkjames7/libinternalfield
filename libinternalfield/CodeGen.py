import numpy as np
import os

def ListDatFiles():
	'''
	List the dat files within the "coeffs" directory
	
	'''
	
	files = os.listdir('coeffs')
	dat = []
	for f in files:
		if f.endswith('.dat'):
			dat.append(f)
	
	dat = np.array(dat)
	print('Found {:d} coefficient files'.format(dat.size))
	return dat

def ListBinFiles():
	'''
	List the binary files within the "coeffs" directory
	
	'''
	
	files = os.listdir('coeffs')
	bnf = []
	for f in files:
		if f.endswith('.bin'):
			bnf.append(f)
	
	bnf = np.array(bnf)
	print('Found {:d} binary files'.format(bnf.size))
	return bnf

def ListObjFiles():
	'''
	List the object files within the "coeffs" directory
	
	'''
	
	files = os.listdir('coeffs')
	obj = []
	for f in files:
		if f.endswith('.o'):
			obj.append(f)
	
	obj = np.array(obj)
	print('Found {:d} coefficient files'.format(obj.size))
	return obj
	
def ListModelNames():
	'''
	List the names and lower case names of all models inside the coeffs
	directory.
	
	'''
	
	#start by listing all of the object files which have been created
	files = ListObjFiles()
	
	#strip them of their extensions
	models = [os.path.splitext(f)[0] for f in files]
	modelsl = [os.path.splitext(f)[0].lower() for f in files]
	
	return models,modelsl	
	
def EncodeFile(fname):
	'''
	This will encode the ASCII files of internal magnetic field model
	coefficients as pure binary.
	
	Inputs
	======
	fnamein : str
		Name of the ASCII file containing the coefficients.
	fnameout : str
		Name of the output binary file.
	
	'''
	
	#open the ASCII file
	f = open('coeffs/'+fname,'r')
	lines = f.readlines()
	f.close()
	lines = np.array(lines)
	
	#get the number of lines in the file
	nl = lines.size
	
	#get any extra info out starting with '#'
	remove = np.zeros(nl,dtype='bool')
	stuff = {}
	for i in range(0,nl):
		l = lines[i]
		if l[0] == '#':
			#add this to the stuff dictionary
			s = l[1:].split()
			stuff[s[0]] = s[1]
			remove[i] = True
	good = np.where(remove == False)[0]
	lines = lines[good]
	nl = lines.size
	

	
	#create the arrays for the coefficients
	gh = np.zeros(nl,dtype='int8')
	n = np.zeros(nl,dtype='int32')
	m = np.zeros(nl,dtype='int32')
	coeff = np.zeros(nl,dtype='float64')
	
	#fill them
	for i in range(0,nl):
		s = lines[i].split()

		if s[0] == 'h':
			gh[i] = 1
		else:
			gh[i] = 0
			
		n[i] = np.int32(s[1])
		m[i] = np.int32(s[2])
		coeff[i] = np.float64(s[3])

	#get any extra info - more things might be added here e.g. "planet"
	if 'DefaultDegree' in stuff:
		DefDeg = np.int32(stuff['DefaultDegree'])
	else:
		DefDeg = np.int32(n.max())
		

	
	#output file name
	name,ext = os.path.splitext(fname)
	fnameout = name + '.bin'
	
	#we could add extra stuff here, e.g. default order, citation etc.
	#open the output file
	print('Saving {:s}'.format(fnameout))
	f = open('coeffs/'+fnameout,'wb')
	np.int32(nl).tofile(f)
	gh.tofile(f)
	n.tofile(f)
	m.tofile(f)
	coeff.tofile(f)
	DefDeg.tofile(f)
	f.close()

def MakeObjectFile(fname):
	'''
	Convert the binary file coefficients to object files which have an 
	address that can be used in C++
	
	'''
	
	#get the output file name
	name,ext = os.path.splitext(fname)
	fnameout = name + '.o'
	
	#change working directory
	pwd = os.getcwd()
	os.chdir('coeffs/')
	
	#call ld
	cmd = 'ld -r -b binary -o {:s} {:s}'.format(fnameout,fname)
	os.system(cmd)
	
	#return to original directory
	os.chdir(pwd)

	
def ReadASCII(fname):
	'''
	Read an ASCII file in.
	
	'''
	with open(fname,'r') as f:
		lines = f.readlines()
		
	return lines
	

def WriteASCII(fname,lines):
	'''
	Write ASCII to a file
	'''
	with open(fname,'w') as f:
		f.writelines(lines)
		print('Saved {:s}'.format(fname))
	

def GenerateCoeffsH(models,modelsl):
	'''
	Generate C++ header file "coeffs.h" using the models inside the 
	coeffs directory.
	
	'''

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/coeffs.h.0')
	code1 = ReadASCII('codegen/coeffs.h.1')
	lines += code0

	#add the memory pointers
	for m in models:
		s = 'extern unsigned char _binary_{:s}_bin_start;\n'.format(m)
		lines.append(s)
	lines.append('\n')
	
	#add the rest of the existing code
	lines += code1
	
	#write to file
	WriteASCII('coeffs.h',lines)
	
	

def GenerateCoeffsCC(models,modelsl):
	'''
	Generate C++ file "coeffs.cc" using the models inside the 
	coeffs directory.
	
	'''

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/coeffs.cc.0')
	code1 = ReadASCII('codegen/coeffs.cc.1')
	code2 = ReadASCII('codegen/coeffs.cc.2')
	lines += code0

	#list of model names
	s = '{\t"' + '",\n\t\t\t\t\t\t\t\t"'.join(modelsl)+'"};\n\n'
	lines.append('std::vector<std::string> modelNames = '+s)
		
	#add some existing code
	lines += code1

	#define the map
	s = 'std::map<std::string,unsigned char*> modelMap = {\t'
	for i,(m,ml) in enumerate(zip(models,modelsl)):
		if i > 0:
			s += '\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",&_binary_{:s}_bin_start'.format(m) + '}'
		if i < len(models) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '};\n\n'
	lines.append(s)

	#add more existing code
	lines += code2
	
	#write to file
	WriteASCII('coeffs.cc',lines)
	

def GenerateModelsH(models,modelsl):
	'''
	Generate C++ header file "models.h" using the models inside the 
	coeffs directory.
	
	'''

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/models.h.0')
	code1 = ReadASCII('codegen/models.h.1')
	lines += code0

	#add externs
	for m in modelsl:
		lines.append('extern Internal {:s};\n'.format(m))
	lines.append('\n')
	
	#add the rest of the existing code
	lines += code1

	#define model field functions
	for m in modelsl:
		s = 'void {:s}Field(double x, double y, double z,\n'.format(m)
		s+= '				double *Bx, double *By, double *Bz);\n'
		lines.append(s)		
			
	#write to file
	WriteASCII('models.h',lines)

def GenerateModelsCC(models,modelsl):
	'''
	Generate C++ file "models.cc" using the models inside the 
	coeffs directory.
	
	'''

	#output list
	lines = []
	
	#read in the existing bits of code from the codegen folder
	code0 = ReadASCII('codegen/models.cc.0')
	code1 = ReadASCII('codegen/models.cc.1')
	code2 = ReadASCII('codegen/models.cc.2')
	lines += code0

	#define models
	for m,ml in zip(models,modelsl):
		lines.append('Internal {:s}(&_binary_{:s}_bin_start);\n'.format(ml,m))
	lines.append('\n')

	#add another map from model name to model pointer
	lines.append('/* map the model names to their model object pointers */\n')
	s = 'std::map<std::string,Internal*> modelPtrMap = {\t'
	for i,ml in enumerate(modelsl):
		if i > 0:
			s += '\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",&{:s}'.format(ml) + '}'
		if i < len(modelsl) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '};\n\n'
	lines.append(s)	
	
	#add some more of the existing code
	lines += code1
	
	#add another map from model name to model field function pointer
	s = 'std::map<std::string,modelFieldPtr> modelFieldPtrMap = {\t'
	for i,ml in enumerate(modelsl):
		if i > 0:
			s += '\t\t\t\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",&{:s}Field'.format(ml) + '}'
		if i < len(modelsl) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '};\n\n'
	lines.append(s)		
	
	
	#add the rest of the existing code
	lines += code2
	
	#model wrapper functions for external code use
	for m in modelsl:
		s = 'void {:s}Field(double x, double y, double z,\n'.format(m)
		s+= '				double *Bx, double *By, double *Bz) {\n'
		s+= '	{:s}.FieldCart(x,y,z,Bx,By,Bz);\n'.format(m)
		s+= '}\n\n'
		lines.append(s)
		

	#write to file
	WriteASCII('models.cc',lines)
	
def GenerateLibHeader():
	'''
	Generate a library header to be included when linking to 
	libinternalfield.so
	
	'''
	
	#read in the template code
	code = ReadASCII('codegen/libinternalfield.h.0')
	
	#read in the other headers
	headers = ['coeffs.h','models.h','listmapkeys.h','internal.h',
				'internalmodel.h','libinternal.h']
	for h in headers:
		lines = ReadASCII(h)
		for l in lines:
			if not l[0] == '#':
				code.append(l)
	code.append('#endif')			
	
	#save it
	WriteASCII('../libinternalfield.h',code)
	
	

if __name__ == "__main__":
	
	#list the dat files
	files = ListDatFiles()
	
	#now attempt to convert them
	for i,f in enumerate(files):
		print('Converting coefficients in {:s} ({:d} of {:d})'.format(f,i+1,files.size))
		try:
			#read it in, convert to binary
			EncodeFile(f)
		except:
			#ignore if it fails
			print('Converting file {:s} failed, check the formatting'.format(f))
			
	#list all of the binary files
	files = ListBinFiles()
	
	#use ld to convert them to object files
	for i,f in enumerate(files):
		print('Converting binary {:s} ({:d} of {:d})'.format(f,i+1,files.size))
		try:
			MakeObjectFile(f)
		except:
			print('Something went wrong while converting {:s}'.format(f))
	
	#list models
	models,modelsl = ListModelNames()
			
	#generate files
	GenerateCoeffsH(models,modelsl)
	GenerateCoeffsCC(models,modelsl)
	GenerateModelsH(models,modelsl)
	GenerateModelsCC(models,modelsl)
	GenerateLibHeader()