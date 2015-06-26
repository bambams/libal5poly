BINDIR = bin
CXX = g++
INCDIR = include
INSTALL = install
LIBDIR = lib
MKDIR = mkdir -p
OBJDIR = obj
PREFIX = /usr
REMOVE = rm -fR
SONAME = al5poly
SRCDIR = src
SYMLINK = ln -fs
VERSION = 1

CXXFLAGS = -fPIC -g3 -I${INCDIR} -Wall `pkg-config --cflags allegro-5.0`
LIBS = `pkg-config --libs allegro-5.0`

DIRS = ${BINDIR} ${LIBDIR} ${OBJDIR} ${OBJDIR}/example
EXAMPLE = ${BINDIR}/al5poly_ex
LIBRARY = ${LIBDIR}/lib${SONAME}.${VERSION}.so

HEADERS = $(shell find $(INCDIR) -name \*.hpp)
SOURCES = $(shell find ${SRCDIR} -name \*.cpp)
OBJECTS = $(shell find ${SRCDIR} -name \*.cpp | \
		sed -e 's/cpp$$/o/' -e "s/${SRCDIR}/${OBJDIR}/")

${OBJDIR}/%.o: ${SRCDIR}/%.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} -c -o $@ $<

.PHONY: all clean dirs example install library run

all: library example

clean:
	${REMOVE} ${BINDIR} ${LIBDIR} ${OBJDIR}

dirs:
	${MKDIR} ${DIRS}

example: library ${EXAMPLE}

install: library
	${INSTALL} -d ${PREFIX}/${INCDIR}/al5poly ${PREFIX}/$(LIBDIR)
	${INSTALL} -t ${PREFIX}/${INCDIR}/al5poly ${HEADERS}
	${INSTALL} -t ${PREFIX}/${LIBDIR} ${LIBRARY}

library: dirs ${LIBDIR} ${OBJDIR} ${LIBRARY}

run: example all
	LD_LIBRARY_PATH=${LIBDIR} ${EXAMPLE}

${LIBRARY}: ${OBJECTS}
	${CXX} -shared -Wl,-soname,lib${SONAME}.so -o $@ $? ${LIBS}
	${SYMLINK} lib${SONAME}.${VERSION}.so ${LIBDIR}/lib${SONAME}.so

${EXAMPLE}: ${OBJDIR}/example/main.o $(LIBRARY)
	${CXX} -o $@ $< ${LIBS} -L${LIBDIR} -lal5poly
