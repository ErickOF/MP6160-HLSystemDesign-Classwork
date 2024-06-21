SYSTEMC?=$(SYSTEMC_HOME)
TARGET?=test

# Compiler
CC=g++
CFLAGS=-Wall -I. -O3 -g -Wextra -Wunused-function

ifdef USE_CPP17
CFLAGS+=-std=c++17
endif

# Target
LD=g++
LFLAGS=-Wall -I. -lm -g
LIBS=-lsystemc -lm

# Source directories
SRCDIR=src
OBJDIR=obj
BINDIR=./
INCDIR=-I. -I./include -I$(SYSTEMC)/include -Ibasic_protocol -I$(SYSTEMC)/include/tlm_core/tlm_2
LIBDIR=-L. -L$(SYSTEMC)/lib-linux64

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): clean $(OBJECTS)
		@$(LD) $(OBJECTS) $(LFLAGS) $(LIBS) $(LIBDIR) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
		@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.PHONY: clean
clean:
		@rm -rf obj
		@rm -f $(TARGET)
		@mkdir -p obj

compile: $(BINDIR)/$(TARGET)

run:
		./$(TARGET)

all: compile run
