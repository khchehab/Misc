# Commands
CC=clang
RM=rm -rf
MKDIR=mkdir -p

# Directories
SRC=src
BUILD=out

# Files
EXECUTABLE=main
SOURCE=$(SRC)/main.c $(SRC)/hashtable.c

# Flags
CC_FLAGS=-std=c11 -fsanitize=address


all: clean main
	@./$(BUILD)/$(EXECUTABLE)

debug: CC_FLAGS+=-DDEBUG
debug: all

main: $(BUILD)
	@$(CC) $(SOURCE) -o $(BUILD)/$(EXECUTABLE) $(CC_FLAGS)

$(BUILD):
	@$(MKDIR) $(BUILD)

clean:
	@$(RM) $(BUILD)