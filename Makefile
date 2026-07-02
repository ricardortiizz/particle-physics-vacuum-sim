# Compiler and compilation options
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -I./include
LDFLAGS = -L./lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Project structure directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Object files needed for the graphical simulator
OBJS = $(OBJ_DIR)/main_raylib.o $(OBJ_DIR)/Particle.o $(OBJ_DIR)/ParticleSet.o $(OBJ_DIR)/useful.o $(OBJ_DIR)/Vector2D.o

# Final executable target
TARGET = $(BIN_DIR)/particle_sim

# Main target (executed by default with a simple 'make')
all: $(TARGET)

# Linking rule to create the final binary in bin/
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Generic pattern rule to compile any .cpp from src/ into .o in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Project clean-up rule
clean:
	@echo "Cleaning compilation files..."
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

# Prevent conflicts with files named 'all' or 'clean'
.PHONY: all clean