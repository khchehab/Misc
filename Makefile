# Commands
CC=/usr/local/Cellar/llvm/11.0.0_1/bin/clang
RM=rm -rf
MKDIR=mkdir -p

# Directories
SRC=src
BUILD=out

# Files
EXECUTABLE=main
SOURCE=$(SRC)/main.c $(SRC)/simple_map.c

# Flags
CC_FLAGS=-std=c11

all: clean main
	@$(EXEC_SANITIZE_FLAGS) ./$(BUILD)/$(EXECUTABLE)

debug: CC_FLAGS+=-DDEBUG -g -O0 -fsanitize=address -fno-omit-frame-pointer
debug: EXEC_SANITIZE_FLAGS=ASAN_OPTIONS=symbolize=1:detect_leaks=1 ASAN_SYMBOLIZER_PATH=/usr/local/Cellar/llvm/11.0.0_1/bin/llvm-symbolizer
debug: all

main: $(BUILD)
	@$(CC) $(SOURCE) -o $(BUILD)/$(EXECUTABLE) $(CC_FLAGS)

$(BUILD):
	@$(MKDIR) $(BUILD)

clean:
	@$(RM) $(BUILD)