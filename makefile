CC=/opt/homebrew/opt/llvm/bin/clang
CFLAGS=-Wall -g
LDFLAGS=-L./lib -L/opt/homebrew/lib -L/opt/homebrew/opt/openblas/lib -L/opt/homebrew/opt/llvm/lib
LDLIBS=-lm -lcheck -lopenblas
INCLUDES=-I./include -I/opt/homebrew/include -I/opt/homebrew/opt/openblas/include -I/opt/homebrew/opt/llvm/include

# Directory for object files
OBJDIR=./obj

# Your library path and name
LIBDIR=./lib
LIBNAME=libjtx.so

# Source and object files for your library
SRCS=$(wildcard ./src/*.c)
OBJS=$(patsubst ./src/%.c, $(OBJDIR)/%.o, $(SRCS))

# Test files
TEST_SRCS=$(wildcard test/*.c)
TEST_OBJS=$(patsubst test/%.c, $(OBJDIR)/%.o, $(TEST_SRCS))
TEST_BINS=$(patsubst test/%.c, bin/%, $(TEST_SRCS))

.PHONY: all clean test

all: directories $(LIBDIR)/$(LIBNAME) $(TEST_BINS)

directories:
	mkdir -p $(OBJDIR) $(BINDIR) $(LIBDIR) bin

$(LIBDIR)/$(LIBNAME): $(OBJS)
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJS) $(LDLIBS)

$(OBJDIR)/%.o: ./src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -c $< -o $@

bin/%: $(OBJDIR)/%.o
	$(CC) $(LDFLAGS) $(CFLAGS) $< -o $@ $(LDLIBS) -ljtx

$(OBJDIR)/%.o: test/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_BINS)
	for test_bin in $(TEST_BINS); do ./$$test_bin; done

clean:
	rm -f $(LIBDIR)/$(LIBNAME) $(OBJS) $(TEST_OBJS) $(TEST_BINS)
