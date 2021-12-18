CC       = nvcc
LOCALDIR = $(HOME)/.local
FLAGS    = -std=c++11 -rdc=true -DGRID_SIZE=16 -DBLOCK_SIZE=16
LDFLAGS  = 
EXE      = main

BIN_DIR = ./bin
SRC_DIR = ./src
BLD_DIR = ./build

EXT=.cu

SRC_FIL = $(wildcard $(SRC_DIR)/*$(EXT))
OBJ_FIL = $(patsubst $(SRC_DIR)/%$(EXT),$(BLD_DIR)/%.o,$(SRC_FIL))

all: dirs $(BIN_DIR)/$(EXE)

dirs: $(BIN_DIR) $(BLD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(BIN_DIR)/$(EXE): $(OBJ_FIL)
	$(CC) $(FLAGS) $^ -o $(BIN_DIR)/$(EXE) $(LDFLAGS) 

$(OBJ_FIL) : $(BLD_DIR)/%.o : $(SRC_DIR)/%$(EXT)
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -f build/*
	rm -f bin/$(EXE)

