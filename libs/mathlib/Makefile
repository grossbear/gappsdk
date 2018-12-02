#MathLib static library build makefile

CXX=g++
ARCH=ar
CFLAGS=-std=gnu++11 -Wall
OBJDIR=obj
FRAMEWORKPATH = ../../framework
MATHPATH = ../../framework/base/math

ifndef VECFLAGS
	VECFLAGS = MATH_HIGH_PREC_FLOAT_VEC
	VECFLAGSSTR = "High precision float square root calculation in vectors classes"
endif

_OBJ = thalf.o elemfunc.o sqrt.o trigonometry.o prng.o perlin.o\
vector.o plane.o matrix.o quaternion.o 3dmath.o

all: $(_OBJ) mathlib.a
	
# link
mathlib.a: $(patsubst %, %, $(_OBJ))
	@echo "Building static library: $@"
	@$(ARCH) rcs $@ $^
	
	
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
	
prng.o: $(MATHPATH)/pseudorandom/prng.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/pseudorandom/prng.cpp
	
perlin.o: $(MATHPATH)/pseudorandom/perlin.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/pseudorandom/perlin.cpp
	
vector.o: $(MATHPATH)/algebra/vectorinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -D$(VECFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/vectorinst.cpp
	@mv vectorinst.o $@
	
plane.o: $(MATHPATH)/algebra/planeinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/planeinst.cpp
	@mv planeinst.o plane.o
	
matrix.o: $(MATHPATH)/algebra/mtxinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/mtxinst.cpp
	@mv mtxinst.o matrix.o
	
quaternion.o: $(MATHPATH)/algebra/quatinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/algebra/quatinst.cpp
	@mv quatinst.o quaternion.o
	
3dmath.o: $(MATHPATH)/space/3dmathinst.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -I$(MATHPATH) -c $(MATHPATH)/space/3dmathinst.cpp
	@mv 3dmathinst.o 3dmath.o
	
.PHONY: clean

# remove compilation products
clean:
	rm *.o mathlib.a