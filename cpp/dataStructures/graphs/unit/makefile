SHELL := /bin/bash
ARCH := -m$(shell getconf LONG_BIT)
IDIR := ../../../include
LDIR := ../../../lib
BIN := ~/bin
WARN := -Wall
CXXFLAGS := ${WARN} ${ARCH} -O2 -std=c++0x

LIBGA := ${LDIR}/lib-ga.a
LIBS := ${LDIR}/lib-ds.a ${LDIR}/lib-util.a

HFILES = ${IDIR}/stdinc.h \
	 ${IDIR}/Graph.h ${IDIR}/Graph_d.h ${IDIR}/Graph_f.h \
	 ${IDIR}/Graph_w.h ${IDIR}/Graph_wd.h ${IDIR}/Graph_wf.h
XFILES = copyGraph 
OFILES = copyGraph.o

${OFILES} : ${HFILES}

.cpp.o:
	${CXX} ${CXXFLAGS} -I ${IDIR} -c $<

all:	${XFILES}

copyGraph: copyGraph.o ${LIBS}
	${CXX} ${CXXFLAGS} $< ${LIBS} -o $@

clean:
	rm -f *.o ${XFILES}
