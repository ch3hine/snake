# Executable
TARGET = snake

# Folders
SRC_DIR = src
INC_DIR = include
LIBS_DIR = libs
OBJ_DIR = build
BIN_DIR = bin

# Extensions
CXX = g++
CXXFLAGS = -Wall -std=c++20 -I$(INC_DIR) -I$(LIBS_DIR)/SDL2/include
LDFLAGS = -L$(LIBS_DIR)/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -mwindows

# Source Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# To .o
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(BIN_DIR)/$(TARGET)

# Link executable
$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) assets/icon_res.o $(OBJS) -o $@ $(LDFLAGS)

# Compilation 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@/usr/bin/time -f "Compile time: %E" $(CXX)  $(CXXFLAGS) -c $< -o $@

# Dossiers
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET).exe