bin_PROGRAMS = njnr
njnr_SOURCES = njnr.tab.cpp lex.yy.cc command.cpp
njnr_SOURCES += compiler_core.cpp cpptypes.cpp debug.cpp
njnr_SOURCES += getopt.cpp helper.cpp lex.cpp list.cpp
njnr_SOURCES += main.cpp operator.cpp parser_functions.cpp
njnr_SOURCES += trans.cpp common/symbol_table.cpp common/symbol_table_stack.cpp
njnr_SOURCES += common/symbol_table_stackX.cpp common/symbol_table_entry.cpp
njnr_SOURCES += expressions/expressions.cpp
njnr_SOURCES += functions/function_calls.cpp functions/functions.cpp
njnr_SOURCES += statements/statements.cpp
njnr_SOURCES += include/debug.hpp include/type.hpp include/list.hpp include/cpptypes.hpp
njnr_SOURCES += include/constant.hpp include/common/symbol_table_stackX.hpp
njnr_SOURCES += include/common/symbol_table_stack.hpp include/common/symbol_table.hpp
njnr_SOURCES += include/compiler.hpp include/trans.hpp include/common/symbol_table_entry.hpp
njnr_SOURCES += njnr.tab.hpp location.hh include/lex.hpp include/data.hpp include/helper.hpp
njnr_SOURCES += include/operator.hpp include/common/symbol_table_templates.h
njnr_SOURCES += include/common/symbol_table_stack_templates.h

AUTOMAKE_OPTIONS = foreign

njnr_CPPFLAGS = -I$(srcdir)/include/ -I$(srcdir)/include/common/ --std=c++20
AM_CPPFLAGS = -I$(srcdir)/include/ -I$(srcdir)/include/common/ --std=c++20

AM_YFLAG = -d

CLEANFILES= lex.yy.cc njnr.tab.cpp njnr.tab.hpp njnr.output location.hh

EXTRA_DIST= njnr.l njnr.y ../autogen.sh

#define MAIN

njnr.tab.cpp: $(srcdir)/njnr.y
	${BISON} -vt -Wcounterexamples -Wother -o $@ $<

lex.yy.cc: $(srcdir)/njnr.l njnr.tab.cpp
	${FLEX} -+ -o $@ $<
