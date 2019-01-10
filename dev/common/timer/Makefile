#timer dev programme build makefile

CXX=g++
CFLAGS=-std=gnu++11 -Wall -pedantic
FRAMEWORKPATH=../../../framework
BASECOMMONPATH=../../../framework/base/common

OBJDIR=obj
objdir_tgt = $(OBJDIR)-$(wildcard $(OBJDIR))
objdir_present = $(OBJDIR)-$(OBJDIR)
objdir_absent = $(OBJDIR)-

_OBJ = stopwatch.o main.o 

PROGNAME :=
ifeq ($(OS),Windows_NT)
	PROGNAME += timerprog.exe
else
	PROGNAME += timerprog
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

stopwatch.o: $(BASECOMMONPATH)/timer/stopwatch.cpp $(BASECOMMONPATH)/timer/stopwatch.h
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -c $<
	@mv stopwatch.o $(OBJDIR)/stopwatch.o

main.o: timerdev.cpp
	@echo "Compiling file: $<"
	@$(CXX) $(CFLAGS) -I$(FRAMEWORKPATH) -c $<
	@mv timerdev.o $(OBJDIR)/main.o

.PHONY: clean

# remove compiltion products
clean:
	@echo "Removing compilation products"
	@rm -rf $(OBJDIR)
	@rm $(PROGNAME)
