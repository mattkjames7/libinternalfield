import numpy as np
import os
import platform

def ProcessIGRF():
	'''
	Read the IGRF coefficient file and split it into one for each 5
	year period
	
	data are from:
	https://www.ngdc.noaa.gov/IAGA/vmod/coeffs/igrf13coeffs.txt
	
	'''
	print('Reading IGRF coefficients')
	f = open('igrf/igrf13coeffs.txt','r')
	lines = f.readlines()
	f.close()
	
	#get the years
	yl = lines[3]
	yr = np.int32(np.float64(yl.split()[3:-1]))
	yr = np.append(yr,yr[-1] + 5)
	
	#remove the header
	lines = lines[4:]
	
	#get the number of coefficient columns
	nc = np.size(lines[0].split()) - 3
	
	#number of rows
	nr = np.size(lines)
	
	#the output arrays
	gh = np.zeros(nr,dtype='U')
	n = np.zeros(nr,dtype='int32')
	m = np.zeros(nr,dtype='int32')
	c = np.zeros((nr,nc),dtype='object')
	
	#fill them
	for i in range(0,nr):
		s = lines[i].split()
		gh[i] = s[0]
		n[i] = np.int32(s[1])
		m[i] = np.int32(s[2])
		c[i,:] = np.array(s[3:])
		
	#correct the final column
	for i in range(0,nr):
		a = np.float64(c[i,-2])
		b = np.float64(c[i,-1])
		c[i,-1] = '{:8.1f}'.format(a + b)
	
	#write to files
	path = 'coeffs/earth/'
	if not os.path.isdir(path):
		os.system('mkdir -pv '+path)
	for i in range(0,nc):
		fname = path + 'igrf{:04d}.dat'.format(yr[i])
		print('Saving '+fname)
		f = open(fname,'w')
		for j in range(0,nr):
			l = '{:s}	{:d}	{:d}	{:s}\n'.format(gh[j],n[j],m[j],c[j,i])
			f.write(l)

		f.close()

	#add the list of models to the file in the "variable" folder
	path = 'variable/earth/'
	if not os.path.isdir(path):
		os.system('mkdir -pv '+path)
	fname = path + 'igrf.dat'
	f = open(fname,'w')
	for i in range(0,nc):
		l = 'igrf{:04d}	{:04d}0101 0.0\n'.format(yr[i],yr[i])
		f.write(l)
	f.close() 

def ListFiles(start,ReturnNames=False):
	'''
	Should list the files that exist within a folder.
	'''
	
	FileOut = []
	NameOut = []
	for root,dirs,files in os.walk(start,topdown=False,followlinks=True):
		for name in files:
			FileOut.append(root+'/'+name)
			NameOut.append(name)
	
	FileOut = np.array(FileOut)
	NameOut = np.array(NameOut)
	
	if ReturnNames:
		return FileOut,NameOut
	else:
		return FileOut



def ListDatFiles():
	'''
	List the dat files within the "coeffs" directory
	
	'''
	
	fnames = ListFiles('coeffs/')
	n = fnames.size
	planet = []
	dat = []
	name = []
	for i in range(0,n):
		if fnames[i].endswith('.dat'):
			tmp,d = os.path.split(fnames[i])
			dat.append(d)
			planet.append(tmp[7:])
			name.append(os.path.splitext(d)[0])
	planet = np.array(planet)
	dat = np.array(dat)
	name = np.array(name)
	
	return planet,name,dat

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
	planets,_,files = ListDatFiles()
	
	#strip them of their extensions
	models = [os.path.splitext(f)[0] for f in files]
	modelsl = [os.path.splitext(f)[0].lower() for f in files]
	
	return planets,models,modelsl	


def EncodeFile(planet,name):
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
	
	fname = planet+'/'+name+'.dat'
	print('Reading file '+fname)
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
	Rscale.tofile(f)
	f.close()

def MakeObjectFile(bdir,planet,name):
	'''
	Convert the binary file coefficients to object files which have an 
	address that can be used in C++
	
	'''
	
	binname = 'coeffs/'+planet+'/'+name+'.bin'

	outname = 'coeffs/'+planet+'/'+name+'_bin.bin'

	#get the object name name
	oname = os.path.splitext(outname)[0] + '.o'
	cname = os.path.splitext(outname)[0] + '.cc'
	
	#get the OS
	OS = platform.system()

	if OS in ['Windows']:
		#use ld
		cmd = 'ld -r -b binary '+binname+' -o '+oname
		os.system(cmd)
	else:
		#use xxd
		cmd = 'xxd -i '+binname+' > '+cname
		os.system(cmd)
		cmd = 'gcc -c '+cname+' -o '+oname
		os.system(cmd)
		cmd = 'rm -v '+cname
		os.system(cmd)
	
	#move it to the build directory
	vdir = bdir + '/coef'
	if not os.path.isdir(vdir):
		os.makedirs(vdir)
	bfname = vdir + '/' + os.path.basename(oname)

	cmd = 'mv -v '+oname+' '+bfname
	os.system(cmd)

def ListVariableModels():
	'''
	list all variable model files
	'''
	fnames = ListFiles('variable/')
	n = fnames.size
	planet = []
	dat = []
	name = []
	for i in range(0,n):
		if fnames[i].endswith('.dat'):
			tmp,d = os.path.split(fnames[i])
			dat.append(d)
			planet.append(tmp[9:])
			name.append(os.path.splitext(d)[0])
	planet = np.array(planet)
	dat = np.array(dat)
	name = np.array(name)
	
	return planet,name,dat


def ReadVariableDat(fname):

	f = open(fname,'r')
	lines = np.array(f.readlines())
	f.close()

	n = lines.size
	names = np.zeros(n,dtype='object')
	dates = np.zeros(n,dtype='int32')
	times = np.zeros(n,dtype='float64')

	for i in range(0,n):
		s = lines[i].split()
		names[i] = s[0]
		dates[i] = np.int32(s[1])
		times[i] = np.float64(s[2])
	return names,dates,times

def EncodeVariableModelBin(planet,name):

	datname = 'variable/'+planet+'/'+name+'.dat'
	binname = 'variable/'+planet+'/'+name+'.bin'

	names,dates,times = ReadVariableDat(datname)

	f = open(binname,'wb')
	n = len(names)
	np.int32(n).tofile(f)
	for nm in names:
		l = np.int32(len(nm))
		l.tofile(f)
		f.write(nm.encode('utf8'))
	dates.tofile(f)
	times.tofile(f)
	f.close()
	print('Saved '+binname)

def MakeVariableObjectFile(bdir,planet,name):

	binname = 'variable/'+planet+'/'+name+'.bin'

	#get the object name name
	oname = os.path.splitext(binname)[0] + '.o'
	cname = os.path.splitext(binname)[0] + '.cc'
	
	#get the OS
	OS = platform.system()

	if OS in ['Windows','Linux']:
		#use ld
		cmd = 'ld -r -b binary '+binname+' -o '+oname
		os.system(cmd)
	else:
		#use xxd
		cmd = 'xxd -i '+binname+' > '+cname
		os.system(cmd)
		cmd = 'gcc -c '+cname+' -o '+oname
		os.system(cmd)
		cmd = 'rm -v '+cname
		os.system(cmd)
	
	#move it to the build directory
	vdir = bdir + '/var'
	if not os.path.isdir(vdir):
		os.makedirs(vdir)
	bfname = vdir + '/' + os.path.basename(oname)

	cmd = 'mv -v '+oname+' '+bfname
	os.system(cmd)

def GenerateVarObjects(bdir):

	planets,names,dats = ListVariableModels()
	n = names.size

	for i in range(0,n):
		EncodeVariableModelBin(planets[i],names[i])
		MakeVariableObjectFile(bdir,planets[i],names[i])


def GenerateModelObjects(bdir):

	planets,names,dats = ListDatFiles()
	n = names.size

	for i in range(0,n):
		EncodeFile(planets[i],names[i])
		MakeObjectFile(bdir,planets[i],names[i])
	
def WriteCppFile(planet,fname):
	'''
	This will convert the ASCII files of internal magnetic field model
	coefficients to C++ code.
	
	Inputs
	======
	planet : str
		Name of the planet.
	fname : str
		Name of the ASCII file containing the coefficients.
	
	'''
	#open the ASCII file
	if planet == '':
		#planet = 'unknown'	
		f = open('coeffs/'+fname,'r')
	else:
		f = open('coeffs/'+planet+'/'+fname,'r')
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
	good = np.zeros(nl,dtype='bool')
	for i in range(0,nl):
		try:
			s = lines[i].split()

			if s[0] == 'h':
				gh[i] = 1
			else:
				gh[i] = 0
			n[i] = np.int32(s[1])
			m[i] = np.int32(s[2])
			coeff[i] = np.float64(s[3])
			good[i] = True
		except:
			good[i] = False
	
	#remove any bad bits
	use = np.where(good)[0]
	gh = gh[use]
	n = n[use]
	m = m[use]
	coeff = coeff[use]
	nl = use.size
	
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
	fnameout = planet + '/' + name + '.cc'

	#cpp contents
	clines = []
	clines.append('coeffStruct& _model_coeff_{:s}()'.format(name)+' {\n')
	clines.append('\tstatic const int len = {:d};\n'.format(nschc))
	clines.append('\tstatic const int nmax = {:d};\n'.format(nmax))
	clines.append('\tstatic const int ndef = {:d};\n'.format(DefDeg))
	clines.append('\tstatic const double rscale = {:28.25f};\n'.format(Rscale))
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
	#print('Saving {:s}'.format(fnameout))
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
	

def GenerateCoeffsH(models):
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
	
	

def GenerateCoeffsCC(planets,models,modelsl):
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
			
	#add more existing code
	lines += code3
	
	#write to file
	WriteASCII('coeffs.cc',lines)
	

def GenerateModelsH(modelsl):
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
		s = '	void {:s}Field(double x, double y, double z,\n'.format(m)
		s+= '				double *Bx, double *By, double *Bz);\n'
		lines.append(s)		
	lines.append('}\n')

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
	code = ReadASCII('codegen/libinternalfield.h.0')
	
	#read in the other headers
	ccode = []
	cccode = []

	cc = _ExtractCoeffsH()
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
	
	

if __name__ == "__main__":
	
	import sys
	bdir = sys.argv[1]

	#list the dat files
	planets,_,files = ListDatFiles()
	nf = files.size
	print('Found {:d} coefficient files...'.format(nf))
	
	#now attempt to convert them
	for i in range(0,nf):
		print('Converting coefficients in {:s} ({:d} of {:d})'.format(files[i],i+1,nf))
		
		try:
			#read it in, convert to binary
			WriteCppFile(planets[i],files[i])
			
		except:
			#ignore if it fails
			print('Converting file {:s} failed, check the formatting'.format(files[i]))
			

	
	#list models
	planets,models,modelsl = ListModelNames()
			
	#generate files
	GenerateCoeffsH(models)
	GenerateCoeffsCC(planets,models,modelsl)
	GenerateModelsH(modelsl)
	GenerateModelsCC(models,modelsl)
	GenerateLibHeader()

	#generate variable models
	GenerateVarObjects(bdir)
	GenerateModelObjects(bdir)