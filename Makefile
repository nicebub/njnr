ifeq ($(OSTYPE),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	CLEANDIR = rmdir
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
#	GENERATE_RUNNER= tools/genrunners.sh
endif

.PHONY: all clean test run lint #regen

vpath %.cpp src
vpath %.s src
vpath %.hpp include
vpath %.so lib
vpath %.la lib


CXX=`which g++`
COMPILER = $(CXX)
BISON = `which bison`
BISOP = -vt -Wcounterexamples -Wother

FLEX  = `which flex++`
FLOP = -+

ifeq ($(shell uname -s),Darwin)
 FCFLAGS = -I/usr/local/opt/flex/include
else
 FCFLAGS = -I/usr/include
endif


PATHS = src/
PATHSC = $(PATHS)/common/
PATHI = include/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/
PATHC = $(PATHI)/common/
EXAMPLES = example/
EXEC = $(PATHB)njnr

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

BASE_SRCT = $(wildcard $(PATHT)*base*.cpp)

SRC_FILES := $(subst $(PATHS),,$(wildcard $(PATHS)*.cpp))
SRC_FILES += $(subst $(PATHSC),,$(wildcard $(PATHSC)*.cpp))
SRC_FILES += $(subst $(PATHS)/functions/,,$(wildcard $(PATHS)/functions/*.cpp))
SRC_FILES += $(subst $(PATHS)/statements/,,$(wildcard $(PATHS)/statements/*.cpp))
SRC_FILES += $(subst $(PATHS)/expressions/,,$(wildcard $(PATHS)/expressions/*.cpp))

ASSEM_FILES := $(subst $(PATHS),,$(wildcard $(PATHS)*.s))

HEAD_FILES:= $(subst $(PATHI),,$(wildcard $(PATHI)*.hpp))
SOURCES := $(patsubst %,$(PATHS)%,$(SRC_FILES))
OBJECTS := $(patsubst %.cpp,$(PATHO)%.o,$(SRC_FILES))
ASSEMBLYS := $(patsubst %.s,$(PATHO)%.o,$(ASSEM_FILES))
DEPS := $(patsubst %.cpp, $(PATHD)%.d,$(SRC_FILES))

COMPILE=$(COMPILER) -c
LINK=$(COMPILER)
DEPEND=$(COMPILER) -MM -MG -MF
CPPFLAGS = -Wall -std=c++17 #-DDEBUGON
CPPFLAGS += -Wall -Wpedantic -pedantic-errors -Wno-comment -I. -I$(PATHI) -I$(PATHC)
CPPFLAGS += -g
CPPFLAGS += -Os -pipe -time
#CPPFLAGS += -ll -lm
ifeq ($(OSTYPE),Darwin)
CPPFLAGS += -Wno-deprecated-register 
endif
CPPFLAGS += ${LDFLAGS} -Wmissing-include-dirs -Winvalid-pch -Wno-overloaded-virtual
TFLAGS = $(CPPFLAGS) $(FCFLAGS) #-DTEST 
ifdef DEBUG
TFLAGS += -DDEBUG=$(DEBUG)
endif
all: $(BUILD_PATHS) $(EXEC)

clean: test_clean
	$(CLEANUP) njnr.tab.cpp njnr.tab.hpp
	$(CLEANUP) $(PATHI)njnr.tab.hpp $(PATHS)njnr.tab.cpp $(PATHI)location.hh
	$(CLEANUP) $(PATHS)lex.yy.cc
	$(CLEANUP) $(PATHS)njnr.output
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHD)*.d
	$(CLEANUP) $(PATHB)njnr
	$(CLEANUP) -rf $(PATHB)njnr.dSYM
	$(CLEANUP) examples/*.asm
	$(CLEANDIR) $(PATHD)
	$(CLEANDIR) $(PATHO)
	$(CLEANDIR) $(PATHR)
	$(CLEANDIR) $(PATHB)
	$(CLEANUP) test.asm
test_clean:

.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

$(PATHS)njnr.tab.cpp : $(PATHS)njnr.y
	$(BISON) $(BISOP) -o $@ $^
	mv $(PATHS)njnr.tab.hpp $(PATHI)
	mv $(PATHS)location.hh $(PATHI)


$(PATHS)lex.yy.cc : $(PATHS)njnr.l $(PATHS)njnr.tab.cpp
	$(FLEX) $(FLOP) -o $@ $<

$(PATHD)%.d:: %.cpp %.hpp $(BUILD_PATHS)
	$(COMPILER) $(CPPFLAGS) $(FCFLAGS) -MM -MG $< -o $@

$(PATHO)%.o:: %.s
	$(COMPILER) -E -dM $(CPPFLAGS) $<
	$(COMPILER) $(CPPFLAGS) -c $< -o $@

ifeq ($(shell ls ${PATHO}njnr.tab.o),)
UCC=$(PATHO)njnr.tab.o
else
UCC=
endif
$(EXEC):: $(BUILD_PATHS) $(ASSEMBLYS) $(PATHO)njnr.tab.o $(PATHO)lex.yy.o $(OBJECTS) $(OUTFILE)   #$(DEPS)
	$(COMPILER) $(CPPFLAGS) $(FCFLAGS) $(ASSEMBLYS) $(UCC) $(PATHO)lex.yy.o $(OBJECTS)  -o $@

run: $(EXEC)
	./$(EXEC) $(EXAMPLES)expr.l

test: $(BUILD_PATHS) $(BASE_RESULTS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"


$(PATHR)%.txt: $(PATHB)%$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Testbase%_Runner$(TARGET_EXTENSION): $(PATHO)Testbase%_Runner.o $(PATHO)Testbase%.o $(PATHO)base%.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHB)Test%set_Runner$(TARGET_EXTENSION): $(PATHO)Test%set_Runner.o $(PATHO)baseset.o $(PATHO)Test%set.o $(PATHO)%set.o  $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHB)Test%vector_Runner$(TARGET_EXTENSION): $(PATHO)Test%vector_Runner.o $(PATHO)Test%vector.o $(PATHO)baseset.o $(PATHO)basevector.o $(PATHO)%set.o $(PATHO)%vector.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^


$(PATHO)njnr.tab.o: $(PATHS)njnr.tab.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)lex.yy.o: $(PATHS)lex.yy.cc
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@
	
$(PATHO)%.o:: $(PATHS)%.cpp $(PATHI)%.hpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHSC)%.cpp $(PATHC)%.hpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHT)%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHS)/functions/%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHS)/statements/%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHS)/expressions/%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHS)%.cpp
	$(COMPILER) $(TFLAGS) $(FCFLAGS) -c $< -o $@

$(PATHO)%.o:: $(PATHU)%.cpp $(PATHU)%.hpp
	$(COMPILER) $(FCFLAGS) $(TFLAGS) -c $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

LINT = `cpplint`
LINTFLAGS = --verbose=2
ASTYLE = `which astyle`
AFLAGS = 

lint:
	 ${LINT} ${LINTFLAGS} src/*.cpp include/*.hpp

style:
	$(ASTYLE) $(AFLAGS) $(PATHS)*.cpp $(PATHI)*.hpp
	$(CLEANUP) $(PATHS)*.orig $(PATHI)*.orig