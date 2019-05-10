#MathLib build makefile and build dev program

CXX=g++
CFLAGS=-std=gnu++11
OBJDIR=obj
FRAMEWORKPATH = ../../../framework
MATHPATH = ../../../framework/base/math
MATHLIBPATH = ../../../libs/mathlib

_OBJ = mathssedev.o mathlib.a

PROGNAME := 
ifeq ($(OS),Windows_NT)
	PROGNAME += mathssedev.exe
else
	PROGNAME += mathssedev
endif

all: MakeDir $(_OBJ) $(PROGNAME)

MakeDir:
	mkdir -p $(OBJDIR)

$(PROGNAME): $(patsubst %,$(OBJDIR)/%,$(_OBJ))
	$(CXX) -o $@ $^

mathlib.a:
	make -C $(MATHLIBPATH) CLASSDATATYPES=MATH_DOUBLE_INST
	cp $(MATHLIBPATH)/mathlib.a $(OBJDIR)/mathlib.a
	
mathssedev.o: mathssedev.cpp
	$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -c mathssedev.cpp
	mv mathssedev.o $(OBJDIR)/mathssedev.o

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(PROGNAME)
