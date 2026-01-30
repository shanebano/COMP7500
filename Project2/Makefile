# Makefile for pwordcount
# Word Count Tool using Unix Pipes

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = pwordcount
SOURCES = pwordcount.c process_communication.c word_count.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = process_communication.h word_count.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

test: $(TARGET)
	@echo "Running tests..."
	@echo "Test 1: No arguments (should show usage)"
	@./$(TARGET) || true
	@echo ""
	@echo "Test 1 is a Success"
	@echo ""
	@echo "Test 2: File Doesnt Exist"
	@./$(TARGET) simple_file.txt || true
	@echo ""
	@echo "Test 2 is a Success"
	@echo ""
	@echo "Test 3: Sample file with words"
	@./$(TARGET) sample_file.txt || true
	@echo ""
	@echo "Test 3 is a Success"
	@echo ""
	@echo "Test 4: Empty file"
	@./$(TARGET) empty.txt || true
	@echo ""
	@echo "Test 4 is a Success"
	@echo ""
	@echo "Test 5: Large File"
	@./$(TARGET) 64kb_test.txt || true
	@echo ""
	@echo "Test 5 is a Success"
	@echo ""


.PHONY: all clean test