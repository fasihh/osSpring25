CC = gcc
TYPE = c
TARGET = main

INC_DIR = include
SRC_DIR = src
ASM_DIR = asm
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.$(TYPE)) $(TARGET).$(TYPE)
ASM_FILES := $(patsubst $(SRC_DIR)/%.$(TYPE), $(ASM_DIR)/%.s, $(SRC_FILES))
OBJ_FILES := $(patsubst $(ASM_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_FILES))

$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

$(ASM_DIR)/%.s: $(SRC_DIR)/%.$(TYPE)
	@mkdir -p $(ASM_DIR)
	$(CC) -I$(INC_DIR) -S $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(ASM_DIR)

.PRECIOUS: $(ASM_DIR)/%.s