import numpy as np
import os
import platform

def MakeVariableObject(bdir,planet,name):

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
