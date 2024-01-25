CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-L./lib -L/opt/homebrew/lib
LDLIBS=-ltgec -lm -lcheck
INCLUDES=-I./include -I/opt/homebrew/include

# Directory for object files
OBJDIR=./obj

# Your library path and name
LIBDIR=./lib
LIBNAME=libtgec.so

# Source and object files for your library
SRCS=$(wildcard ./src/*.c)
OBJS=$(patsubst ./src/%.c, $(OBJDIR)/%.o, $(SRCS))

# Test files
TEST_SRCS=$(wildcard test/*.c)
TEST_OBJS=$(patsubst test/%.c, $(OBJDIR)/%.o, $(TEST_SRCS))
TEST_BINS=$(patsubst test/%.c, bin/%, $(TEST_SRCS))

.PHONY: all clean test

all: $(LIBDIR)/$(LIBNAME) $(TEST_BINS)

$(LIBDIR)/$(LIBNAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS)

$(OBJDIR)/%.o: ./src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -c $< -o $@

bin/%: $(OBJDIR)/%.o
	$(CC) $(LDFLAGS) $(CFLAGS) $< -o $@ $(LDLIBS)

$(OBJDIR)/%.o: test/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_BINS)
	for test_bin in $(TEST_BINS); do ./$$test_bin; done

clean:
	rm -f $(LIBDIR)/$(LIBNAME) $(OBJS) $(TEST_OBJS) $(TEST_BINS)
