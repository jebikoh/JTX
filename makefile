# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall

# Directory structure
SRCDIR = src
BINDIR = bin
LIBDIR = lib
TESTDIR = test
OBJDIR = obj

# Executable name
EXEC = $(BINDIR)/yourprogram
TEST_EXEC = $(BINDIR)/test_yourprogram

# Source and object files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TEST_SOURCES = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/%.o, $(TEST_SOURCES))

# Default target
all: $(EXEC)

# Main executable
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test executable
test: $(TEST_EXEC)

$(TEST_EXEC): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -lcheck -lm
	./$(TEST_EXEC)

# Cleaning up
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*

# Phony targets
.PHONY: all test clean
