NAME := bitLudo
BIN_DIR := bin
BIN := $(BIN_DIR)/$(NAME)

SRC_DIR := src
SRC_FILES := ${wildcard $(SRC_DIR)/*.c}

DEBUG_FLAGS := -Wall -Wextra -fsanitize=address

build $(BIN): $(SRC_FILES)
	mkdir -p $(BIN_DIR)
	cc $(SRC_FILES) $(DEBUG_FLAGS) -o $(BIN)

run: $(BIN)
	$(BIN)
