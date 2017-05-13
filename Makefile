CXX=g++
CXX_FLAGS=--std=c++11
LIB_PATHS=-L /usr/lib64 -L /usr/local/lib
LINKER_OPTIONS=-Wl,-rpath /usr/lib64 -Wl,-rpath /usr/local/lib
LIBS=-lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi

BIN_DIR=bin
OUTPUT=$(BIN_DIR)/opengl_app

all: $(BIN_DIR)
	$(CXX) $(CXX_FLAGS) $(LIB_PATHS) $(LINKER_OPTIONS) main.cc -o $(OUTPUT) $(LIBS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

