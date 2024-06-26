#  From https://hiltmon.com/blog/2015/09/28/the-simple-c-plus-plus-makefile-executable-edition/
#  Makefile
#  modernCppPractice
#
#  Created by Hilton Lipschitz on 2015-09-01.
#  Copyright (c) 2015 Maritime Capital LP. All rights reserved.
#

# HIL: No spaces or comments after otherwise it captures them!
# Determine the platform
UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
	CC := clang++ -arch x86_64
else
	CC := g++
endif

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

# Targets
EXECUTABLE := modernCppPractice
TARGET := $(TARGETDIR)/$(EXECUTABLE)

# Final Paths
INSTALLBINDIR := /usr/local/bin

# Code Lists
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Folder Lists
# Note: Intentionally excludes the root of the include folder 
# so the lists are clean
INCDIRS := $(shell find include/**/* -name '*.h' -exec dirname {} \; | sort | uniq)
INCLIST := $(patsubst include/%,-I include/%,$(INCDIRS))
BUILDLIST := $(patsubst include/%,$(BUILDDIR)/%,$(INCDIRS))

# Shared Compiler Flags
CFLAGS := -c -g -Wall
INC := -I include $(INCLIST) -I /usr/local/include
LIB := -L /usr/local/lib
#LIB := -L /usr/local/lib -lsantacruzengine -lsantacruzlib -larcadia \
  -lcorinth -lyaml-cpp -lzmq -lhiredis -lbondoas

# Platform Specific Compiler Flags
ifeq ($(UNAME_S),Linux)
	CFLAGS += -std=gnu++17 -O2 # -fPIC
	
	# PostgreSQL Special
	#PG_VER := 9.3
	#INC += -I /usr/pgsql-$(PG_VER)/include
	#LIB += -L /usr/pgsql-$(PG_VER)/lib 
else
	CFLAGS += -std=c++17 -stdlib=libc++ -O2
endif

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "  Linking $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDLIST)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning $(TARGET)..."; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	@echo "Installing $(EXECUTABLE)..."; cp $(TARGET) $(INSTALLBINDIR)
	
distclean:
	@echo "Removing $(EXECUTABLE)"; rm $(INSTALLBINDIR)/$(EXECUTABLE)

.PHONY: clean