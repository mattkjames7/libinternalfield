import numpy as np
from .ListModelNames import ListModelNames
from .WriteCoeffCpp import WriteCoeffCpp

def ConvertDatCpp():
    
	    
	#list the dat files
	planets,names,_ = ListModelNames()
	nf = len(names)
	print('Found {:d} coefficient files...'.format(nf))
	
	#now attempt to convert them
	for i in range(0,nf):
		print('Converting coefficients in {:s} ({:d} of {:d})'.format(names[i],i+1,nf))
		
		try:
			#read it in, convert to binary
			WriteCoeffCpp(planets[i],names[i])
			
		except:
			#ignore if it fails
			print('Converting file {:s} failed, check the formatting'.format(names[i]))
			
