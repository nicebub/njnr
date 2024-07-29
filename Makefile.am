SUBDIRS = src
dist_doc_DATA = README.md
CLEANFILES= ./bin/njnr
.PHONY: mvbin

all-local: mvbin

mvbin: src/njnr
	mkdir -p ./bin/
	cp -aRp src/njnr ./bin/
