NAME := bitLudo
BIN_DIR := bin
BIN := $(BIN_DIR)/$(NAME)
REL_BIN := $(BIN_DIR)/release/$(NAME)

SRC_DIR := src
SRC_FILES := ${wildcard $(SRC_DIR)/*.c}

DEBUG_FLAGS := -Wall -Wextra -g -fsanitize=address
RELEASE_FLAGS := -O3

build $(BIN): $(SRC_FILES)
	mkdir -p $(BIN_DIR)
	cc $(SRC_FILES) $(DEBUG_FLAGS) -o $(BIN)

release $(REL_BIN): $(SRC_FILES)
	mkdir -p $(BIN_DIR)/release
	cc $(SRC_FILES) $(RELEASE_FLAGS) -o $(REL_BIN)


run: $(BIN)
	$(BIN)
