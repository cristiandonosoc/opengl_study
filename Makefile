CXX=g++
CXX_FLAGS=--std=c++11 -Wall -Wextra -Werror -g -Og

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
INCLUDE_DIR=include
EXTERNAL_DIR=external

INCLUDES=-I ./$(SRC_DIR) -I ./$(EXTERNAL_DIR) -I $(INCLUDE_DIR) -isystem /usr/local/include
LIB_PATHS=-L /usr/lib64 -L /usr/local/lib -L /usr/local/lib64
# LINKER_OPTIONS=-Wl,-rpath /usr/lib32 -Wl,-rpath /usr/local/lib
LIBS= -lglfw3 -lGL  -lpthread -lX11 -lXrandr -lXinerama -lXxf86vm -lXcursor -ldl

SOURCES=$(wildcard $(SRC_DIR)/*.cc)
OBJECTS=$(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES))

OUTPUT=$(BIN_DIR)/opengl_app

all: dirs main

main: $(OBJECTS) $(SRC_DIR)/glad.o
	$(CXX) $(CXX_FLAGS) $(LIB_PATHS) $(LINKER_OPTIONS) $^ -o $(OUTPUT) $(LIBS)

$(SRC_DIR)/glad.o: $(SRC_DIR)/glad.c
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $^ -o $@

dirs: $(BIN_DIR) $(OBJ_DIR)

# Compiles each .o from a .cc
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $^ -o $@


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

