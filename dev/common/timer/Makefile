#timer dev programme build makefile

CXX=g++
CFLAGS=-std=gnu++11
FRAMEWORKPATH=../../../framework
BASECOMMONPATH=../../../framework/base/common

OBJDIR=obj
objdir_tgt = $(OBJDIR)-$(wildcard $(OBJDIR))
objdir_present = $(OBJDIR)-$(OBJDIR)
objdir_absent = $(OBJDIR)-

_OBJ = stopwatch.o progtimer.o 

PROGNAME :=
ifeq ($(OS),Windows_NT)
	PROGNAME += progtimer.exe
else
	PROGNAME += progtimer
endif

all: | $(objdir_tgt) $(_OBJ) $(PROGNAME) 

$(objdir_present):
	@echo "Directory '$(OBJDIR)' exists, no need to create it again."

$(objdir_absent):
	@echo "Directory '$(OBJDIR)' does not exists."
	@echo "Creating directory '$(OBJDIR)'."
	@mkdir -p $(OBJDIR)

$(PROGNAME): $(patsubst %,$(OBJDIR)/%,$(_OBJ))
	@echo "Building programme:$(PROGNAME)"
	@$(CXX) -o $@ $^

stopwatch.o: $(BASECOMMONPATH)/timer/timer.cpp $(BASECOMMONPATH)/timer/timer.h
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -c $(BASECOMMONPATH)/timer/timer.cpp
	@mv timer.o $(OBJDIR)/stopwatch.o

progtimer.o: progtimer.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -c progtimer.cpp
	@mv progtimer.o $(OBJDIR)/progtimer.o

.PHONY: clean

# remove compiltion products
clean:
	@echo "Removing compilation products"
	@rm -rf $(OBJDIR)
	@rm $(PROGNAME)
