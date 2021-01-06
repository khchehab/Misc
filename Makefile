# Commands
CC=clang
RM=rm -f

# Directories
SRC=src
BUILD=out

# Files
EXECUTABLE=main
SOURCE=$(SRC)/main.c $(SRC)/hashtable.c

# Flags
CC_FLAGS=-std=c11


all: clean main
	@./$(BUILD)/$(EXECUTABLE)

debug: CC_FLAGS+=-DDEBUG
debug: all

main:
	@$(CC) $(SOURCE) -o $(BUILD)/$(EXECUTABLE) $(CC_FLAGS)

clean:
	@$(RM) $(BUILD)/*