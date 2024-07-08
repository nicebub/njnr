bin_PROGRAMS = njnr
njnr_SOURCES = njnr.tab.cpp lex.yy.cc *.cpp
AM_CPPFLAGS = -Iinclude/ -Iinclude/common/
AM_YFLAG = -d
#define MAIN
njnr.tab.cpp: njnr.y
	${BISON} -vt -Wcounterexamples -Wother -o $@ $<
lex.yy.cc: njnr.l njnr.tab.cpp
	${FLEX} -+ -o $@ $<
