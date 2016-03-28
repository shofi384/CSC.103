SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
HEADERS := $(wildcard *.h *.hpp)
# TARGETS := main check
TARGETS := main

COMMON   := -O2 -Wall -DNDEBUG
CFLAGS   := $(CFLAGS) $(COMMON)
CC       := g++
LD       := $(CC)

ifdef skel
CFLAGS   += -DSKEL
endif

all : $(TARGETS)
.PHONY : all

# {{{ for debugging
debug : CFLAGS += -g -DDEBUG=1 -U NDEBUG
debug : $(TARGETS)
.PHONY : debug
# }}}

$(OBJECTS) : %.o : %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGETS) : % : %.o
	$(LD) -o $@ $^

.PHONY : clean
clean :
	rm -f $(OBJECTS) $(TARGETS) output
