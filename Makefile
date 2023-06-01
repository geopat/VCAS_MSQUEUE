# Makefile for compiling C program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic

# Executable name
EXECUTABLE = program

# Source directory
SRC_DIR = src

# Include directory
INC_DIR = include

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=%.o)

# Default target
all: $(EXECUTABLE)

# Linking object files
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

# Compiling source files
%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

# Cleaning generated files
clean:
	rm -f $(OBJS) $(EXECUTABLE)
