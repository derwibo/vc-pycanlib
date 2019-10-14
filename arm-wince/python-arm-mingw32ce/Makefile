# Makefile

SUBDIRS= Python Parser Objects Modules PC PC/arm-mingw32ce Modules/_io Modules/cjkcodecs Modules/zlib

# Top of the package tree
TOP=	../../

# Directory for output files
OUT=	out/

# Path to search for .c files
vpath %.c $(TOP)
vpath %.rc $(TOP)

CC=arm-mingw32ce-gcc
CXX=arm-mingw32ce-g++
LD=arm-mingw32ce-gcc
AR=arm-mingw32ce-ar.exe
RANLIB=arm-mingw32ce-ranlib
RC=arm-mingw32ce-windres -O COFF -I../../Include -I. -D UNICODE

CFLAGS=-W -fexceptions -Wno-missing-field-initializers -O2 -I../../Include -I. -I../../Python -I../../modules/zlib -DPy_BUILD_CORE_MODULE -DNDEBUG -DMS_WIN32 -DWIN32 -DMS_WINDOWS -D_WINDOWS -DUNICODE -DUNDER_CE -DMS_WINCE -DWINCE_DEBUG -DUSE_DL_EXPORT
CXXFLAGS=$(CFLAGS)
LDFLAGS=-shared -marm-wince-pe -s -Wl,--add-stdcall-alias --no-undefined --enable-runtime-pseudo-reloc
LIBS+=-llargeint -lcoredll -lmingwex
ARFLAGS=-r
# -luser32 -ladvapi32 -lshell32

.PHONY: all
all: subdirs python27.dll libpython27.a

.PHONY: subdirs
subdirs:
	for file in $(SUBDIRS); do \
	  test -d $$file || mkdir $$file; \
	done

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.res: %.rc
	$(RC) $(CPPFLAGS) -o $@ -i $<

MODULES1_SRCS= \
	Modules/_bisectmodule.c \
	Modules/cjkcodecs/_codecs_cn.c \
	Modules/cjkcodecs/_codecs_hk.c \
	Modules/cjkcodecs/_codecs_iso2022.c \
	Modules/cjkcodecs/_codecs_jp.c \
	Modules/cjkcodecs/_codecs_kr.c \
	Modules/cjkcodecs/_codecs_tw.c \
	Modules/_codecsmodule.c \
	Modules/_collectionsmodule.c \
	Modules/_csv.c \
	Modules/_functoolsmodule.c \
	Modules/_heapqmodule.c \
	Modules/_io/_iomodule.c \
	Modules/_json.c \
	Modules/_localemodule.c \
	Modules/_math.c \
	Modules/_randommodule.c \
	Modules/_sre.c \
	Modules/_struct.c \
	Modules/_weakref.c \
	Modules/zlib/adler32.c \
	Modules/arraymodule.c \
	Modules/audioop.c \
	Modules/binascii.c \
	Modules/_io/bufferedio.c \
	Modules/_io/bytesio.c \
	Modules/cmathmodule.c \
	Modules/zlib/compress.c \
	Modules/cPickle.c \
	Modules/zlib/crc32.c \
	Modules/cStringIO.c \
	Modules/datetimemodule.c \
	Modules/zlib/deflate.c \
	Modules/errnomodule.c \
	Modules/future_builtins.c \
	Modules/gcmodule.c \
	Modules/getbuildinfo.c \
	Modules/zlib/gzclose.c \
	Modules/zlib/gzlib.c \
	Modules/zlib/gzread.c \
	Modules/zlib/gzwrite.c \
	Modules/_io/iobase.c \
	Modules/imageop.c \
	Modules/zlib/infback.c \
	Modules/zlib/inffast.c \
	Modules/zlib/inflate.c \
	Modules/zlib/inftrees.c \
	Modules/itertoolsmodule.c \
	Modules/mathmodule.c \
	Modules/md5.c \
	Modules/md5module.c \
	Modules/sha256module.c \
	Modules/sha512module.c \
	Modules/shamodule.c \
	Modules/signalmodule.c \
	Modules/xxsubtype.c \
	Modules/zipimport.c \
	Modules/zlibmodule.c \
	Modules/zlib/zutil.c \
	Modules/main.c \
	Modules/mmapmodule.c \
	Modules/cjkcodecs/multibytecodec.c \
	Modules/operator.c \
	Modules/parsermodule.c \
	Modules/posixmodule.c \
	Modules/rotatingtree.c \
	Modules/stropmodule.c \
	Modules/_io/stringio.c \
	Modules/symtablemodule.c \
	Modules/_io/textio.c \
	Modules/threadmodule.c \
	Modules/timemodule.c \
	Modules/zlib/trees.c \
	Modules/zlib/uncompr.c \

MODULES_SRCS= \
	Modules/_bisectmodule.c \
	Modules/_codecsmodule.c \
	Modules/_heapqmodule.c \
	Modules/_math.c \
	Modules/_randommodule.c \
	Modules/_struct.c \
	Modules/_weakref.c \
	Modules/arraymodule.c \
	Modules/cmathmodule.c \
	Modules/datetimemodule.c \
	Modules/gcmodule.c \
	Modules/getbuildinfo.c \
	Modules/mathmodule.c \
	Modules/operator.c \
	Modules/parsermodule.c \
	Modules/signalmodule.c \
	Modules/threadmodule.c \
	Modules/timemodule.c \

MODULES_OBJS= $(MODULES_SRCS:.c=.o)

OBJECTS_SRCS= \
	Objects/abstract.c \
	Objects/boolobject.c \
	Objects/bufferobject.c \
	Objects/bytearrayobject.c \
	Objects/bytes_methods.c \
	Objects/capsule.c \
	Objects/cellobject.c \
	Objects/classobject.c \
	Objects/cobject.c \
	Objects/codeobject.c \
	Objects/complexobject.c \
	Objects/descrobject.c \
	Objects/dictobject.c \
	Objects/enumobject.c \
	Objects/exceptions.c \
	Objects/fileobject.c \
	Objects/floatobject.c \
	Objects/frameobject.c \
	Objects/funcobject.c \
	Objects/genobject.c \
	Objects/intobject.c \
	Objects/iterobject.c \
	Objects/listobject.c \
	Objects/longobject.c \
	Objects/memoryobject.c \
	Objects/methodobject.c \
	Objects/moduleobject.c \
	Objects/object.c \
	Objects/obmalloc.c \
	Objects/rangeobject.c \
	Objects/setobject.c \
	Objects/sliceobject.c \
	Objects/stringobject.c \
	Objects/structseq.c \
	Objects/tupleobject.c \
	Objects/typeobject.c \
	Objects/unicodectype.c \
	Objects/unicodeobject.c \
	Objects/weakrefobject.c \

OBJECTS_OBJS= $(OBJECTS_SRCS:.c=.o)

PARSER_SRCS= \
	Parser/acceler.c \
	Parser/bitset.c \
	Parser/firstsets.c \
	Parser/grammar.c \
	Parser/grammar1.c \
	Parser/listnode.c \
	Parser/metagrammar.c \
	Parser/myreadline.c \
	Parser/node.c \
	Parser/parser.c \
	Parser/parsetok.c \
	Parser/tokenizer.c \

PARSER_OBJS= $(PARSER_SRCS:.c=.o)

PYTHON_SRCS= \
	Python/_warnings.c \
	Python/asdl.c \
	Python/ast.c \
	Python/bltinmodule.c \
	Python/ceval.c \
	Python/codecs.c \
	Python/compile.c \
	Python/dtoa.c \
	Python/dynload_win.c \
	Python/errors.c \
	Python/formatter_string.c \
	Python/formatter_unicode.c \
	Python/frozen.c \
	Python/future.c \
	Python/getargs.c \
	Python/getcompiler.c \
	Python/getcopyright.c \
	Python/getopt.c \
	Python/getplatform.c \
	Python/getversion.c \
	Python/graminit.c \
	Python/import.c \
	Python/importdl.c \
	Python/marshal.c \
	Python/mysnprintf.c \
	Python/mystrtoul.c \
	Python/modsupport.c \
	Python/peephole.c \
	Python/pyarena.c \
	Python/pyctype.c \
	Python/pyfpe.c \
	Python/pymath.c \
	Python/pystate.c \
	Python/pystrcmp.c \
	Python/pystrtod.c \
	Python/Python-ast.c \
	Python/pythonrun.c \
	Python/random.c \
	Python/structmember.c \
	Python/symtable.c \
	Python/sysmodule.c \
	Python/thread.c \
	Python/traceback.c \

PYTHON_OBJS= $(PYTHON_SRCS:.c=.o)

ARCH_SRCS= \
	PC/arm-mingw32ce/config.c \
	PC/dl_nt.c \
	PC/getpathp.c \
	PC/arm-mingw32ce/ce-compatibility.c \

#	PC/import_nt.c \
#	PC/_subprocess.c \
#	PC/msvcrtmodule.c \

ARCH_RCS= \
	PC/python_nt.rc \


ARCH_OBJS= $(ARCH_SRCS:.c=.o) $(ARCH_RCS:.rc=.res)


OBJS=$(OBJECTS_OBJS) $(PARSER_OBJS) $(PYTHON_OBJS) $(ARCH_OBJS) $(MODULES_OBJS)

libpython27.a: $(OBJS)
	-rm -f $@
	$(AR) $(ARFLAGS) $@ $(OBJECTS_OBJS)
	$(AR) $(ARFLAGS) $@ $(PARSER_OBJS)
	$(AR) $(ARFLAGS) $@ $(PYTHON_OBJS)
	$(AR) $(ARFLAGS) $@ $(ARCH_OBJS)
	$(AR) $(ARFLAGS) $@ $(MODULES_OBJS)
	$(RANLIB) $@


python27.dll: $(OBJS)
	$(LD) -static $(LDFLAGS) -o $@ $(OBJS) $(LIBS) -Wl,--output-def,python27.def,--out-implib,libpython27_dll.a

#python27_static.dll: $(OBJS)
#	$(LD) -static $(LDFLAGS) -o $@ $(OBJS) $(LIBS)


.PHONY: clean
clean:
	rm -f $(OBJS) pythoncore.dep
	rm -f python27.dll
	rm -f python27.dll.static
	rm -f libpython27.a

.PHONY: depends
depends:
	-$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $(filter %.c %.cc %.cpp %.cxx,$(SRCS)) > pythoncore.dep

-include pythoncore.dep

