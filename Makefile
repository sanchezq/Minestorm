CC = gcc
EXE_NAME = exe

CFLAGS = -W -Wall -Wextra -Werror -pedantic
DEBUG_FLAGS = -ggdb3 -O0
RELEASE_FLAGS = -O3
IFLAGS = -Iinclude/
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lm


BUILD_DIR = build
SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) $^ -c -o $@

all: $(EXE_NAME)

$(EXE_NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXE_NAME)
	@echo "Done compiling $<"

clean:
	rm -f  $(BUILD_DIR)/*.o $(EXE_NAME)

