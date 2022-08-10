EXEC = njnr
BISON=`which bison`
FLEX=`which flex`

all: $(EXEC)


$(EXEC): lex.yy.c njnr.tab.c njnr.tab.h
	$(CC) njnr.tab.c lex.yy.c main.c -o $@


njnr.tab.%: njnr.y
	$(BISON) -H njnr.y

lex.yy.c: njnr.tab.h njnr.l
	$(FLEX) njnr.l

clean:
	-rm lex.yy.c njnr.tab.h njnr.tab.c njnr 2>/dev/null

.PHONY: all clean
