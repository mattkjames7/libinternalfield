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

def ListCppFiles():
	'''
	List the .cc files within the "coeffs" directory
	
	'''
	
	files = os.listdir('coeffs')
	bnf = []
	for f in files:
		if f.endswith('.cc'):
			bnf.append(f)
	
	bnf = np.array(bnf)
	print('Found {:d} C++ parameter files'.format(bnf.size))
	return bnf

	
def ListModelNames():
	'''
	List the names and lower case names of all models inside the coeffs
	directory.
	
	'''
	
	#start by listing all of the object files which have been created
	files = ListDatFiles()
	
	#strip them of their extensions
	models = [os.path.splitext(f)[0] for f in files]
	modelsl = [os.path.splitext(f)[0].lower() for f in files]
	
	return models,modelsl	
	
def WriteCppFile(fname):
	'''
	This will convert the ASCII files of internal magnetic field model
	coefficients to C++ code.
	
	Inputs
	======
	fnamein : str
		Name of the ASCII file containing the coefficients.
	fnameout : str
		Name of the output C++ file.
	
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
	Rscale = np.float64(stuff.get('Rscale',1.0))

	#count the number of coeffs (including ones missing from the file)
	nschc = 0
	nmax = n.max()
	for i in range(0,nmax):
		nschc += (2 + i)
	dtype = [('n','int32'),('m','int32'),('g','float64'),('h','float64')]
	schc = np.recarray(nschc,dtype=dtype)
		
	p = 0;
	for i in range(1,nmax+1):
		for j in range(0,i+1):
			schc[p].n = i
			schc[p].m = j
			schc[p].g = 0.0
			schc[p].h = 0.0
			p += 1;

	for i in range(0,nl):
		p = m[i]-1
		for j in range(0,n[i]):
			p += (1 + j)
		
		if (gh[i] == 0):
			schc[p].g = coeff[i];
		else:
			schc[p].h = coeff[i];
		
		
	
	#output file names
	name,ext = os.path.splitext(fname)
	fnameout = name + '.cc'

	#cpp contents
	clines = []
	clines.append('coeffStruct& _model_coeff_{:s}()'.format(name)+' {\n')
	clines.append('\tstatic const int len = {:d};\n'.format(nschc))
	clines.append('\tstatic const int nmax = {:d};\n'.format(nmax))
	clines.append('\tstatic const int ndef = {:d};\n'.format(DefDeg))
	clines.append('\tstatic const double rscale = {:f};\n'.format(Rscale))
	cn = '\tstatic const int n[] = ' + '{'
	cm = '\tstatic const int m[] = ' + '{'
	cg = '\tstatic const double g[] = ' + '{'
	ch = '\tstatic const double h[] = ' + '{'
	lstr0 = len(cn)
	lstrn = lstr0
	lstrm = lstr0
	lstrg = lstr0
	lstrh = lstr0
	for i in range(0,nschc):
		cns = '{:d},'.format(schc[i].n)
		cms = '{:d},'.format(schc[i].m)
		cgs = '{:f},'.format(schc[i].g)
		chs = '{:f},'.format(schc[i].h)
		
		if lstrn + len(cns) > 72:
			cn += '\n\t\t'
			lstrn = 4 + len(cns)
		else:
			lstrn += len(cns)
		if lstrm + len(cms) > 72:
			cm += '\n\t\t'
			lstrm = 4 + len(cms)
		else:
			lstrm += len(cms)
		if lstrg + len(cgs) > 72:
			cg += '\n\t\t'
			lstrg = 4 + len(cgs)
		else:
			lstrg += len(cgs)
		if lstrh + len(chs) > 72:
			ch += '\n\t\t'
			lstrh = 4 + len(chs)
		else:
			lstrh += len(chs)
			
		cn += cns
		cm += cms
		cg += cgs
		ch += chs
		
	clines.append(cn[:-1] + '};\n')
	clines.append(cm[:-1] + '};\n')
	clines.append(cg[:-1] + '};\n')
	clines.append(ch[:-1] + '};\n')
	

	clines.append('\tstatic coeffStruct out = {len,nmax,ndef,rscale,n,m,g,h};\n')
	clines.append('\treturn out;\n')
	clines.append('}\n\n')

	
	#C++ file
	print('Saving {:s}'.format(fnameout))
	fc = open('coeffs/'+fnameout,'w')
	fc.writelines(clines)
	fc.close()
	
	
	
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

	for m in models:
		lines.append('extern coeffStruct& _model_coeff_{:s}();\n'.format(m))
		
		
	#rest of the code
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
	code3 = ReadASCII('codegen/coeffs.cc.3')
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
	for m in models:
		cc = ReadASCII('coeffs/{:s}.cc'.format(m))
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
			
	#add more existing code
	lines += code3
	
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
		lines.append('extern Internal& {:s}();\n'.format(m))
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
			WriteCppFile(f)
			
		except:
			#ignore if it fails
			print('Converting file {:s} failed, check the formatting'.format(f))
			

	
	#list models
	models,modelsl = ListModelNames()
			
	#generate files
	GenerateCoeffsH(models,modelsl)
	GenerateCoeffsCC(models,modelsl)
	GenerateModelsH(models,modelsl)
	GenerateModelsCC(models,modelsl)
	GenerateLibHeader()
