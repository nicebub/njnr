bin_PROGRAMS = njnr
LEXERSOURCES = njnr.tab.cpp lex.yy.cc location.hh njnr.tab.hpp

njnrSOURCES = command.cpp compiler_core.cpp cpptypes.cpp debug.cpp
njnrSOURCES += getopt.cpp helper.cpp lex.cpp list.cpp
njnrSOURCES += main.cpp operator.cpp parser_functions.cpp
njnrSOURCES += CodeGenerator.cpp common/symbol_table.cpp common/symbol_table_stack.cpp
njnrSOURCES += common/symbol_table_stackX.cpp common/symbol_table_entry.cpp
njnrSOURCES += expressions/expressions.cpp
njnrSOURCES += functions/function_calls.cpp functions/functions.cpp
njnrSOURCES += statements/statements.cpp
njnrSOURCES += include/debug.hpp include/type.hpp include/list.hpp include/cpptypes.hpp
njnrSOURCES += include/constant.hpp include/common/symbol_table_stackX.hpp
njnrSOURCES += include/common/symbol_table_stack.hpp include/common/symbol_table.hpp
njnrSOURCES += include/compiler.hpp include/CodeGenerator.hpp include/common/symbol_table_entry.hpp
njnrSOURCES += include/lex.hpp include/data.hpp include/helper.hpp
njnrSOURCES += include/operator.hpp include/common/symbol_table_templates.h
njnrSOURCES += include/common/symbol_table_stack_templates.h

njnr_SOURCES = $(LEXERSOURCES) $(njnrSOURCES)
AUTOMAKE_OPTIONS = foreign

njnr_CPPFLAGS = -I$(srcdir)/include/ -I$(srcdir)/include/common/ --std=c++20 #-DDEBUGON
AM_CPPFLAGS = -I$(srcdir)/include/ -I$(srcdir)/include/common/ --std=c++20 #-DDEBUGON

AM_YFLAG = -d

CLEANFILES= lex.yy.cc njnr.tab.cpp njnr.tab.hpp njnr.output location.hh

EXTRA_DIST= njnr.l njnr.y $(srcdir)/../autogen.sh $(srcdir)/../test
CPPLINTFLAGS = --verbose=5 --filter=-whitespace/indent,-whitespace/braces,-whitespace/newline,-legal,-build/include_subdir,-readability/braces


#define MAIN

njnr.tab.cpp: $(srcdir)/njnr.y
	${BISON} -vt -Wcounterexamples -Wother -o $@ $<

lex.yy.cc: $(srcdir)/njnr.l njnr.tab.cpp
	${FLEX} -+ -o $@ $<

lint: $(njnrSOURCES)
	-$(CPPLINT) $(CPPLINTFLAGS) $^

check-local: lint

.PHONY: lint
