
if __name__ == "__main__":
	
	import sys
	bdir = sys.argv[1]

	import codegen

	codegen.GenerateCode(bdir)