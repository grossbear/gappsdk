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
ifeq ($(SIMDEXTFLAG), 1)
CALCPRECFLAGS += -DMATH_SIMD_EXT
endif
ifeq ($(INTFLOATNOFPU), 1)
CALCPRECFLAGS += -DMATH_INTFLOAT_SW
endif

 #prng.o perlin.o\

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

prng.o: $(MATHPATH)/pseudorandom/prng.cpp $(MATHPATH)/elementary/interpolation.h $(MATHPATH)/elementary/interpolation.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/pseudorandom/prng.cpp
	
perlin.o: $(MATHPATH)/pseudorandom/perlin.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/pseudorandom/perlin.cpp
	
vector.o: $(MATHPATH)/algebra/vectorinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(CALCPRECFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/vectorinst.cpp
	@mv vectorinst.o $@
	
plane.o: $(MATHPATH)/algebra/planeinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(CALCPRECFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/planeinst.cpp
	@mv planeinst.o plane.o
	
matrix.o: $(MATHPATH)/algebra/mtxinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(CALCPRECFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/mtxinst.cpp
	@mv mtxinst.o matrix.o
	
quaternion.o: $(MATHPATH)/algebra/quatinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(CALCPRECFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/quatinst.cpp
	@mv quatinst.o quaternion.o
	
3dmath.o: $(MATHPATH)/space/3dmathinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) $(CALCPRECFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/space/3dmathinst.cpp
	@mv 3dmathinst.o 3dmath.o
	
.PHONY: clean

# remove compilation products
clean:
	@rm *.o
	@rm mathlib.a
	@echo "Removing static library mathlib.a and compiled object files."
