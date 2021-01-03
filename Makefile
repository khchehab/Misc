# Commands
CC=clang
RM=rm -f

# Files
EXECUTABLE=main
SOURCE=main.c map.c

# Flags
CC_FLAGS=-std=c11

all: clean main
	@./main

main:
	@$(CC) $(SOURCE) -o $(EXECUTABLE) $(CC_FLAGS)

clean:
	@$(RM) $(EXECUTABLE)