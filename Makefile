CC      = gcc
C_FLAGS = -Wall -Wextra -Werror
EXE     = hangman

BIN_DIR = bin
SRC_DIR = src
INC_DIR = includes


all: run

run: compile
	@$(BIN_DIR)/$(EXE)

compile:
	@$(CC) $(C_FLAGS) $(SRC_DIR)/*.c -I $(INC_DIR) -o $(BIN_DIR)/$(EXE)
