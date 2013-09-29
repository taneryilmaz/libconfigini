#
# libconfig Makefile
#


LIB = config

LIBARCH = $(patsubst %,lib%.a,${LIB})

HDRS = src/config.h src/queue.h
SRCS = src/config.c

INSTALLHDRS = src/config.h

OBJS := ${SRCS:.c=.o}

# library installation directory
INSTALLDIR = /usr/local


CFLAGS = -g -ggdb -Wall

CC = gcc

###################################################################################################

ifdef installdir
	INSTALLDIR = $(installdir)
endif


.PHONY: all install test clean doxygen help

all: $(LIBARCH)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBARCH): $(OBJS) 
	ar rcs $(LIBARCH) $(OBJS)

install: all
	@mkdir -p $(INSTALLDIR)/include && cp $(INSTALLHDRS) $(INSTALLDIR)/include
	@mkdir -p $(INSTALLDIR)/lib     && cp $(LIBARCH) $(INSTALLDIR)/lib

test:
	$(MAKE) -C tests/

clean:
	rm -f ~core~ $(OBJS) $(LIBARCH)
	rm -rf html/
	$(MAKE) -C tests/ clean

doxygen: docs/html.dox
	@mkdir -p html
	@doxygen docs/html.dox
	
	
help:
	@echo "Installdir: $(INSTALLDIR)"
	@echo "targets:"
	@echo "   all                     Build all"
	@echo "   installdir=<path>       Install library to path"
	@echo "   install                 Install library to $INSTALLDIR/lib and its header to $INSTALLDIR/include"
	@echo "   test                    Run unittests"
	@echo "   clean                   Clean library generated files"
	@echo "   doxygen                 Generate documentation"
	
