CC = g++
CFLAGS = -Wall -Wextra -std=c++11
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = obj
TARGET = main

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)
