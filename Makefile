CXX=g++
CXX_FLAGS=--std=c++11

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

INCLUDES=-I $(SRC_DIR)
LIB_PATHS=-L /usr/lib64 -L /usr/local/lib
LINKER_OPTIONS=-Wl,-rpath /usr/lib64 -Wl,-rpath /usr/local/lib
LIBS=-lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi

SOURCES=$(wildcard $(SRC_DIR)/*.cc)
OBJECTS=$(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES))

OUTPUT=$(BIN_DIR)/opengl_app

all: dirs main

main: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(LIB_PATHS) $(LINKER_OPTIONS) $^ -o $(OUTPUT) $(LIBS)

dirs: $(BIN_DIR) $(OBJ_DIR)

# Compiles each .o from a .cc
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXX_FLAGS) -c $^ -o $@


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

