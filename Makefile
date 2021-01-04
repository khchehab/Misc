# Commands
CC=clang
RM=rm -f

# Directories
SRC=src
BUILD=out

# Files
EXECUTABLE=main
SOURCE=*.c

# Flags
CC_FLAGS=-std=c11

all: clean main
	@./$(BUILD)/$(EXECUTABLE)

main:
	@$(CC) $(SRC)/$(SOURCE) -o $(BUILD)/$(EXECUTABLE) $(CC_FLAGS)

clean:
	@$(RM) $(BUILD)/*