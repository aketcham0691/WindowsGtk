# change application name here (executable output name)

msys_version := $(if $(findstring Msys, $(shell uname -o)),$(word 1, $(subst ., ,$(shell uname -r))),0)
$(info The version of MSYS you are running is $(msys_version) (0 meaning not MSYS at all))
TARGET=template_app
PKGCONFIG = $(shell which pkg-config)

GLIB_COMPILE_RESOURCES = $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -Wl,--export-all-symbols
 
OBJS=src/main.o src/resources.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

# main.o: src/main.c gtktest.gresource gtktest src/resources.o
# 	$(CC) -c -o $(@F) $(CCFLAGS) $(GTKLIB) $<
    
%.o: %.c
	@echo "here"
	$(CC) -c -o $@ $(CCFLAGS) $(GTKLIB) $<

gtktest.gresource: resources/gtktest.gresource.xml
	$(GLIB_COMPILE_RESOURCES) resources/gtktest.gresource.xml --target=$@ --sourcedir=resources

src/resources.c: resources/gtktest.gresource.xml
	$(GLIB_COMPILE_RESOURCES) resources/gtktest.gresource.xml --target=$@ --sourcedir=resources --generate-source

clean:
	rm -f *.o $(TARGET)