# Makefile
#
#

PYTHONVERSION = 27
PYLIBDIR      = C:/Programme/Python/27/libs
PYINCDIR      = C:/Programme/Python/27/include

CANLIBOBJFILES := candll.o can.o

.PHONY : all
all : canlib.pyd

.PHONY : clean
clean :
	rm -f canlib.pyd
	rm -f *.o

canlib.pyd : $(CANLIBOBJFILES)
	g++ -shared -Wl,--add-stdcall-alias $(CANLIBOBJFILES) -L$(PYLIBDIR) -luser32 -luuid -lwinmm -lpython$(PYTHONVERSION) -L. -lpcanbasic -Wl,--out-implib,canlib_dll.a -o canlib.pyd

%.o : ../src/%.cxx
	g++ -c -g -Wno-deprecated -Wno-invalid-offsetof -Wno-write-strings -D UNICODE -I$(PYINCDIR) $< -o $@
