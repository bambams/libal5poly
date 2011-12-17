BINDIR = bin
CXX = g++
CXXFLAGS = -fPIC -g3 -Iinclude -Wall `pkg-config --cflags allegro-5.0`
INCDIR = include
LIBDIR = lib
LIBS = `pkg-config --libs allegro-5.0`
MKDIR = mkdir -p
OBJDIR = obj
REMOVE = rm -fR
SONAME = al5poly
SRCDIR = src
SYMLINK = ln -fs
VERSION = 1

DIRS = ${BINDIR} ${LIBDIR} ${OBJDIR} ${OBJDIR}/example
LIBRARY = ${LIBDIR}/lib${SONAME}.${VERSION}.so
LIBOBJS = ${OBJDIR}/AnimationException.o \
		  ${OBJDIR}/Animation.o ${OBJDIR}/Camera.o \
		  ${OBJDIR}/Clock.o \
		  ${OBJDIR}/Exception.o \
		  ${OBJDIR}/Frame.o \
		  ${OBJDIR}/GameTime.o \
		  ${OBJDIR}/IAnimation.o \
		  ${OBJDIR}/ICamera.o \
		  ${OBJDIR}/IException.o \
		  ${OBJDIR}/IFrame.o \
		  ${OBJDIR}/IGameTime.o \
		  ${OBJDIR}/IRenderable.o \
		  ${OBJDIR}/IRenderer.o \
		  ${OBJDIR}/NullDestructor.o \
		  ${OBJDIR}/PlayerException.o \
		  ${OBJDIR}/Player.o \
		  ${OBJDIR}/Renderer.o
EXAMPLE = ${BINDIR}/al5poly_ex

.PHONY: all clean dirs example library run

all: library example

library: dirs ${LIBDIR} ${OBJDIR} ${LIBRARY}

example: library ${EXAMPLE} 

clean:
	${REMOVE} ${BINDIR} ${LIBDIR} ${OBJDIR}

dirs:
	${MKDIR} ${DIRS}

example: library ${EXAMPLE}

run: example all
	LD_LIBRARY_PATH=${LIBDIR} ${EXAMPLE}

${LIBRARY}: ${LIBOBJS}
	${CXX} -shared -Wl,-soname,lib${SONAME}.so -o $@ $? ${LIBS}
	${SYMLINK} lib${SONAME}.${VERSION}.so ${LIBDIR}/lib${SONAME}.so

${EXAMPLE}: ${OBJDIR}/example/main.o $(LIBRARY)
	${CXX} -o $@ $< ${LIBS} -L${LIBDIR} -lal5poly

${OBJDIR}/AnimationException.o: ${SRCDIR}/AnimationException.cpp ${INCDIR}/AnimationException.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Animation.o: ${SRCDIR}/Animation.cpp ${INCDIR}/Animation.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Camera.o: ${SRCDIR}/Camera.cpp ${INCDIR}/Camera.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Clock.o: ${SRCDIR}/Clock.cpp ${INCDIR}/Clock.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Exception.o: ${SRCDIR}/Exception.cpp ${INCDIR}/Exception.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Frame.o: ${SRCDIR}/Frame.cpp ${INCDIR}/Frame.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/GameTime.o: ${SRCDIR}/GameTime.cpp ${INCDIR}/GameTime.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/IAnimation.o: ${SRCDIR}/IAnimation.cpp ${INCDIR}/IAnimation.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/ICamera.o: ${SRCDIR}/ICamera.cpp ${INCDIR}/ICamera.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/IException.o: ${SRCDIR}/IException.cpp ${INCDIR}/IException.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/IFrame.o: ${SRCDIR}/IFrame.cpp ${INCDIR}/IFrame.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/IGameTime.o: ${SRCDIR}/IGameTime.cpp ${INCDIR}/IGameTime.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/IRenderable.o: ${SRCDIR}/IRenderable.cpp ${INCDIR}/IRenderable.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/IRenderer.o: ${SRCDIR}/IRenderer.cpp ${INCDIR}/IRenderer.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/example/main.o: ${SRCDIR}/example/main.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/NullDestructor.o: ${SRCDIR}/NullDestructor.cpp ${INCDIR}/NullDestructor.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/PlayerException.o: ${SRCDIR}/PlayerException.cpp ${INCDIR}/PlayerException.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Player.o: ${SRCDIR}/Player.cpp ${INCDIR}/Player.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/Renderer.o: ${SRCDIR}/Renderer.cpp ${INCDIR}/Renderer.hpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

