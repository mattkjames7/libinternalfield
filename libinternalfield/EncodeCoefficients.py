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
	f.close()
	
def MakeObjectFile(fname):
	'''
	Convert the binary file coefficients to object files which have an 
	address that can be used in C++
	
	'''
	
	#get the output file name
	name,ext = os.path.splitext(fname)
	fnameout = name + '.o'
	
	#call ld
	cmd = 'ld -r -b binary -o coeffs/{:s} coeffs/{:s}'.format(fnameout,fname)
	os.system(cmd)

def CreateHeaderFiles(files):
	'''
	Here we will write a header file "coeffs.h" which will store the 
	following:
	
	- The pointers to each embedded set of coefficients
	- A list of model names
	- a std::map which maps model names to their pointers
	
	Another header will be written which will contain instances of each 
	model (models.h).
	
	'''
	print('Generating coeffs.h')
	#extract the model names from the files
	models = [os.path.splitext(f)[0] for f in files]
	modelsl = [os.path.splitext(f)[0].lower() for f in files]
	
	
	#this is the output list of strings to be written to file
	lines = []
	
	#add the includes
	lines.append('#ifndef __COEFFS_H__\n')
	lines.append('#define __COEFFS_H__\n')
	lines.append('#include <vector>\n')
	lines.append('#include <string>\n')
	lines.append('#include <map>\n')
	#lines.append('#include "internal.h"\n')
	lines.append('#endif\n\n')
	
	#using 
	lines.append('using std::string;\n')
	lines.append('using std::vector;\n')
	lines.append('using std::map;\n\n')
	
	#list of model names
	lines.append('/* list of model names */\n');
	s = '{\t"' + '",\n\t\t\t\t\t\t\t\t"'.join(modelsl)+'"};\n\n'
	lines.append('vector<string> modelNames = '+s)

	#define all of the memory pointers
	lines.append('/* pointers to the memory where coefficients are stored */\n')
	for m in models:
		s = 'extern unsigned char _binary_{:s}_bin_start;\n'.format(m)
		lines.append(s)
	lines.append('\n')


	#define the map
	lines.append('/* map the model names to their pointers */\n')
	s = 'map<string,unsigned char*> modelMap = {\t'
	for i,(m,ml) in enumerate(zip(models,modelsl)):
		if i > 0:
			s += '\t\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",&_binary_{:s}_bin_start'.format(m) + '}'
		if i < len(models) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '}\n\n'
	lines.append(s)
		
	#header for getModelCoeffPointer
	lines.append('/* this function will return the pointer to a model given a string */\n')
	lines.append('unsigned char* getModelCoeffPointer(string Model);\n')
	lines.append('unsigned char* getModelCoeffPointer(const char *Model);\n\n')
	
	
	#write to file
	f = open('coeffs.h','w')
	f.writelines(lines)
	f.close()


	print('Generating models.h')
	#this is the output list of strings to be written to file
	lines = []
	
	#add the includes
	s = [ 	'#ifndef __COEFFS_H__\n',
			'#define __COEFFS_H__\n',
			'#include <vector>\n',
			'#include <string>\n',
			'#include <map>\n',
			'#include "internal.h"\n',
			'#include "coeffs.h"\n',
			'#include "listmapkeys.h"\n',
			'#endif\n\n']
	lines += s
	
	#add externs
	lines.append('/* models! */\n')
	for m in modelsl:
		lines.append('extern Internal {:s};\n'.format(m))
	lines.append('\n')

	#add another map from model name to model pointer
	lines.append('/* map the model names to their model object pointers */\n')
	s = 'map<string,Internal*> modelMap = {\t'
	for i,ml in enumerate(modelsl):
		if i > 0:
			s += '\t\t\t\t\t\t\t\t\t'
		s += '{"' + ml + '",&{:s}'.format(ml) + '}'
		if i < len(modelsl) - 1:
			s += ',\n'
		else:
			s += '\n'
	s += '}\n\n'
	lines.append(s)	

	#header for getModelCoeffPointer
	lines.append('/* this function will return the pointer to a model object given a string */\n')
	lines.append('Internal* getModelObjPointer(string Model);\n')
	lines.append('Internal* getModelObjPointer(const char *Model);\n\n')
	
	#prototype for the function which lists all of the models
	lines.append('/* a function to return a list of the models available */\n')
	lines.append('vector<string> listAvailableModels();\n')
	
		
	#write to file
	f = open('models.h','w')
	f.writelines(lines)
	f.close()	
	
	print('Generating models.cc')
	#this is the output list of strings to be written to file
	lines = []
	
	#include
	lines.append('#include "models.h"\n\n')
	
	#define models
	lines.append('/* model definitions */\n')
	for m,ml in zip(models,modelsl):
		lines.append('Internal {:s}(&_binary_{:s}_bin_start);\n'.format(ml,m))
	lines.append('\n')
	
	#add function to return model pointer here
	s = [	'Internal* getModelObjPointer(string Model) {\n',
			'	return modelMap[Model];\n',
			'}\n\n',
			'Internal* getModelObjPointer(const char *Model) {\n',
			'	return modelMap[Model];\n',
			'}\n']
	lines += s	
	lines.append('\n')
	
	#add the function which will return the list of available models
	s = [	'vector<string> listAvailableModels() {\n',
			'	return listMapKeys(modelMap);\n',
			'}\n' ]
	lines += s
	lines.append('\n')
	
	#write to file
	f = open('models.cc','w')
	f.writelines(lines)
	f.close()		
	
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
	
	#list object files
	files = ListObjFiles()
			
	#create header file
	CreateHeaderFiles(files)
