bin/SimpleDES.exe: src/SimpleDES.obj src/Key.obj src/Init_Perm.obj src/DESAlgorithm.obj
	cl src/SimpleDES.obj src/Key.obj src/Init_Perm.obj src/DESAlgorithm.obj /Febin/SimpleDES.exe

src/SimpleDES.obj:
	cl /c /EHa src/SimpleDES.cpp /Fosrc/SimpleDES.obj

src/Key.obj:
	cl /c /EHa src/Key.cpp /Fosrc/Key.obj

src/Init_Perm.obj:
	cl /c /EHa src/Init_Perm.cpp /Fosrc/Init_Perm.obj

src/DESAlgorithm.obj:
	cl /c /EHa src/DESAlgorithm.cpp /Fosrc/DESAlgorithm.obj
