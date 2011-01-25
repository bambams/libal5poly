BINDIR = bin
CXX = g++
CXXFLAGS = -fPIC -g3 -Iinclude -Wall
INCDIR = include
LIBDIR = lib
LIBS = `pkg-config --libs allegro-5.1` -L${LIBDIR} -lal5poly
MKDIR = mkdir -p
OBJDIR = obj
REMOVE = rm -fR
SONAME = libal5poly.so
SRCDIR = src
SYMLINK = ln -fs
VERSION = 1

LIBRARY = ${LIBDIR}/${SONAME}.${VERSION}
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
PROGRAM = ${BINDIR}/al5polytut

.PHONY: clean default

default: ${BINDIR} ${LIBDIR} ${OBJDIR} ${LIBRARY} ${PROGRAM} 

clean:
	${REMOVE} ${BINDIR} ${LIBDIR} ${OBJDIR}

${LIBRARY}: ${LIBOBJS}
	${CXX} -shared -Wl,-soname,${SONAME} -o $@ $?
	${SYMLINK} ${SONAME}.${VERSION} ${LIBDIR}/${SONAME}

${BINDIR}:
	${MKDIR} $@

${LIBDIR}:
	${MKDIR} $@

${OBJDIR}:
	${MKDIR} $@

${PROGRAM}: ${OBJDIR}/main.o $(LIBRARY)
	${CXX} -o $@ $< ${LIBS}

${OBJDIR}/AnimationException.o: ${SRCDIR}/AnimationException.cpp ${INCDIR}/AnimationException.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Animation.o: ${SRCDIR}/Animation.cpp ${INCDIR}/Animation.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Camera.o: ${SRCDIR}/Camera.cpp ${INCDIR}/Camera.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Clock.o: ${SRCDIR}/Clock.cpp ${INCDIR}/Clock.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Exception.o: ${SRCDIR}/Exception.cpp ${INCDIR}/Exception.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Frame.o: ${SRCDIR}/Frame.cpp ${INCDIR}/Frame.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/GameTime.o: ${SRCDIR}/GameTime.cpp ${INCDIR}/GameTime.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/IAnimation.o: ${SRCDIR}/IAnimation.cpp ${INCDIR}/IAnimation.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/ICamera.o: ${SRCDIR}/ICamera.cpp ${INCDIR}/ICamera.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/IException.o: ${SRCDIR}/IException.cpp ${INCDIR}/IException.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/IFrame.o: ${SRCDIR}/IFrame.cpp ${INCDIR}/IFrame.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/IGameTime.o: ${SRCDIR}/IGameTime.cpp ${INCDIR}/IGameTime.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/IRenderable.o: ${SRCDIR}/IRenderable.cpp ${INCDIR}/IRenderable.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/IRenderer.o: ${SRCDIR}/IRenderer.cpp ${INCDIR}/IRenderer.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/main.o: ${SRCDIR}/main.cpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/NullDestructor.o: ${SRCDIR}/NullDestructor.cpp ${INCDIR}/NullDestructor.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/PlayerException.o: ${SRCDIR}/PlayerException.cpp ${INCDIR}/PlayerException.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Player.o: ${SRCDIR}/Player.cpp ${INCDIR}/Player.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

${OBJDIR}/Renderer.o: ${SRCDIR}/Renderer.cpp ${INCDIR}/Renderer.hpp
	${CXX} ${CXXFLAGS} `pkg-config --cflags allegro-5.1` -c -o $@ $<

