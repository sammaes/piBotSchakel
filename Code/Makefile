#
# MakeFile for the project....
#

CROSS_CC_PREFIX=arm-linux-gnueabihf-
 
ifdef CROSS_COMPILE
  
endif
 
CC 	:= $(CROSS_CC_PREFIX)g++ # This is the main compiler

SRCDIR 	:= src
BUILDDIR:= build
TARGET 	:= bin/udptest
 
SRCEXT 	:= cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS 	:= -g -Wall
LIB 	:= 
INC 	:= -I include

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
testavg:
	g++ test/testAverage.cpp src/Average.cpp src/Positie.cpp $(INC) -o test/testavg
	
# Spikes
#ticket:
#  $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
