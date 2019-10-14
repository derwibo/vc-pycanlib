# Makefile
#

PYTHONVERSION = 27
PYLIBDIR      = C:/Programme/Python/27/libs
PYINCDIR      = I:/Python-2.7.9/Include

CANLIBOBJFILES := candll.o can.o

.PHONY : all
all : canlib.pyd

.PHONY : clean
clean :
	rm -f canlib.pyd
	rm -f *.o

canlib.pyd : $(CANLIBOBJFILES)
	arm-mingw32ce-g++ -shared -Wl,--add-stdcall-alias $(CANLIBOBJFILES) -marm-wince-pe -lcoredll -L./ -lpython27_dll -Wl,--out-implib,libcanlib_dll.a -o canlib.pyd

%.o : ../src/%.cxx
	arm-mingw32ce-g++ -c -Wno-deprecated -Wno-invalid-offsetof -Wno-write-strings -D UNICODE -D UNDER_CE -I$(PYINCDIR) -I./python-arm-mingw32ce $< -o $@
