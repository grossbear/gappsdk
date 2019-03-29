#MathLib static library build makefile

CXX=g++
ARCH=ar
CFLAGS=-std=gnu++11 -Wall
OBJDIR=obj
FRAMEWORKPATH = ../../framework
MATHPATH = ../../framework/base/math

CALCPRECFLAGS = 
ifdef FLTSQRTPRECFLAG
CALCPRECFLAGS += -D$(FLTSQRTPRECFLAG)
endif
ifdef FLTTRIPRECFLAG
CALCPRECFLAGS += -D$(FLTTRIPRECFLAG)
endif

LIBRARY_DEFS = $(CALCPRECFLAGS)
ifeq ($(SIMDEXTFLAG), 1)
LIBRARY_DEFS += -DMATH_SIMD_EXT
endif
ifeq ($(INTFLOATNOFPU), 1)
LIBRARY_DEFS += -DMATH_INTFLOAT_SW
endif

COMMA := ,
VAR_DATATYPE_A := $(subst $(COMMA), ,$(CLASSDATATYPES))
VAR_DATATYPE_1 := $(word 1,$(VAR_DATATYPE_A))
VAR_DATATYPE_2 := $(word 2,$(VAR_DATATYPE_A))
VAR_DATATYPE_3 := $(word 3,$(VAR_DATATYPE_A))
VAR_DATATYPE_4 := $(word 4,$(VAR_DATATYPE_A))

ifneq ($(VAR_DATATYPE_1), )
LIBRARY_DEFS += -D$(VAR_DATATYPE_1)
endif
ifneq ($(VAR_DATATYPE_2), )
LIBRARY_DEFS += -D$(VAR_DATATYPE_2)
endif
ifneq ($(VAR_DATATYPE_3), )
LIBRARY_DEFS += -D$(VAR_DATATYPE_3)
endif
ifneq ($(VAR_DATATYPE_4), )
LIBRARY_DEFS += -D$(VAR_DATATYPE_4)
endif


_OBJ = thalf.o elemfunc.o sqrt.o trigonometry.o interp.o prng.o perlin.o\
vector.o plane.o matrix.o quaternion.o 3dmath.o

all: buildinfo $(_OBJ) mathlib.a
	
# link
mathlib.a: $(patsubst %, %, $(_OBJ))
	@echo "Building static library: $@"
	@$(ARCH) rcs $@ $^

# info
info:
	@echo "FLTSQRTPRECFLAG - float square root precision flag"
	@echo "values: {MATH_HIGH_PREC_FLOAT_SQRT; MATH_FLOAT_TABLE_SQRT; MATH_FAST_FLOAT_SQRT}"
	@echo "FLTTRIPRECFLAG - float trigonometry precision flag"
	@echo "values: {MATH_HIGH_PREC_FLOAT_TRIGONOMETRY; MATH_FLOAT_TABLE_TRIGONOMETRY}"
	@echo ""
	@echo "SIMDEXTFLAG - SIMD extension flag"
	@echo "INTFLOATNOFPU - software float-integer convertion"
	@echo "CLASSDATATYPES - Build classes instantiation list using following data types:"
	@echo "MATH_DOUBLE_INST,MATH_LONG_DOUBLE_INST,MATH_FIXED_INST,MATH_HALF_INST"
	@echo "note: MATH_LONG_DOUBLE_INST, MATH_FIXED_INST, MATH_HALF_INST - unsopported yet"


buildinfo:
ifeq ($(FLTSQRTPRECFLAG), MATH_HIGH_PREC_FLOAT_SQRT)
	@echo "High precision float square root calculation in algebra classes"
else ifeq ($(FLTSQRTPRECFLAG), MATH_FLOAT_TABLE_SQRT)
	@echo "Table float square root calculation in algebra classes"
else ifeq ($(FLTSQRTPRECFLAG), MATH_FAST_FLOAT_SQRT)
	@echo "Approximation float square root calculation in algebra classes"
else
	@echo "Default float square root calculation in algebra classes"
endif

ifeq ($(SQRTPRECFLAG), MATH_HIGH_PREC_FLOAT_TRIGONOMETRY)
	@echo "High precision float trigonometry calculation in algebra classes"
else ifeq ($(SQRTPRECFLAG), MATH_FLOAT_TABLE_TRIGONOMETRY)
	@echo "Table float trigonometry calculation in algebra classes"
else
	@echo "Default float trigonometry calculation in algebra classes"
endif

ifneq ($(VAR_DATATYPE_1), )
	@echo "Compiling with "$(VAR_DATATYPE_1)" flag"
endif
ifneq ($(VAR_DATATYPE_2), )
	@echo "Compiling with "$(VAR_DATATYPE_2)" flag"
endif
ifneq ($(VAR_DATATYPE_3), )
	@echo "Compiling with "$(VAR_DATATYPE_3)" flag"
endif
ifneq ($(VAR_DATATYPE_4), )
	@echo "Compiling with "$(VAR_DATATYPE_4)" flag"
endif
	
	
# compile source file
thalf.o: $(MATHPATH)/types/thalf.cpp
	@echo "Compiling file: $<" 
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/types/thalf.cpp
	
elemfunc.o: $(MATHPATH)/elementary/elemfunc.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/elementary/elemfunc.cpp
	
sqrt.o: $(MATHPATH)/elementary/sqrt.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/elementary/sqrt.cpp
	
trigonometry.o: $(MATHPATH)/elementary/trigonometry.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/elementary/trigonometry.cpp
	
interp.o: $(MATHPATH)/elementary/interpolation.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/elementary/interpolation.cpp
	@mv interpolation.o $@

prng.o: $(MATHPATH)/pseudorandom/prng.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/pseudorandom/prng.cpp
	
perlin.o: $(MATHPATH)/pseudorandom/perlin.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/pseudorandom/perlin.cpp
	
vector.o: $(MATHPATH)/algebra/vectorinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(LIBRARY_DEFS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/vectorinst.cpp
	@mv vectorinst.o $@
	
plane.o: $(MATHPATH)/algebra/planeinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(LIBRARY_DEFS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/planeinst.cpp
	@mv planeinst.o plane.o
	
matrix.o: $(MATHPATH)/algebra/mtxinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(LIBRARY_DEFS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/mtxinst.cpp
	@mv mtxinst.o matrix.o
	
quaternion.o: $(MATHPATH)/algebra/quatinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(LIBRARY_DEFS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/quatinst.cpp
	@mv quatinst.o quaternion.o
	
3dmath.o: $(MATHPATH)/space/3dmathinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(LIBRARY_DEFS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/space/3dmathinst.cpp
	@mv 3dmathinst.o 3dmath.o
	
.PHONY: clean

# remove compilation products
clean:
	@rm *.o
	@rm mathlib.a
	@echo "Removing static library mathlib.a and compiled object files."
