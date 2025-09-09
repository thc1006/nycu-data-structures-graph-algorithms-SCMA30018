# Makefile for NYCU Data Structures & Graph Algorithms - HW1 Date Type
# Course: SCMA30018

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
SRCDIR = src
TESTDIR = tests
BENCHDIR = benchmarks
OBJDIR = build
BINDIR = bin

# Source files
SOURCES = $(SRCDIR)/date.c
MAIN_SRC = $(SRCDIR)/main.c
TEST_SOURCES = $(wildcard $(TESTDIR)/*.c)
BENCH_SOURCES = $(wildcard $(BENCHDIR)/*.c)

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJ = $(MAIN_SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.c=$(OBJDIR)/%.o)
BENCH_OBJECTS = $(BENCH_SOURCES:$(BENCHDIR)/%.c=$(OBJDIR)/%.o)

# Executables
MAIN_EXEC = $(BINDIR)/date_demo
TEST_EXEC = $(BINDIR)/test_date
BENCH_EXEC = $(BINDIR)/bench_date

# Default target
all: directories $(MAIN_EXEC)

# Create necessary directories
directories:
	@mkdir -p $(OBJDIR) $(BINDIR)

# Main executable
$(MAIN_EXEC): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Test executable
test: directories $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Benchmark executable
benchmark: directories $(BENCH_EXEC)
	./$(BENCH_EXEC)

$(BENCH_EXEC): $(OBJECTS) $(BENCH_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Object file compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(BENCHDIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

# Run the demo
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install (copy to system directories - optional)
install: $(MAIN_EXEC)
	@echo "Install target not implemented for educational project"

# Help
help:
	@echo "Available targets:"
	@echo "  all        - Build main executable"
	@echo "  test       - Build and run tests"
	@echo "  benchmark  - Build and run benchmarks"
	@echo "  run        - Build and run demo"
	@echo "  clean      - Remove build files"
	@echo "  help       - Show this help"

.PHONY: all test benchmark run clean install help directories