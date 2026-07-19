# Compiler
# Should use MSYS 2 G++ on windows
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wno-missing-braces -Wunused-function

# Includes
INCLUDES := \
    -Iinclude \
    -Iinclude/imgui \
    -Iinclude/raylib\

# Source files
SRC := \
    $(wildcard lib/imgui/*.cpp) \
	$(wildcard lib/repatcher/*.cpp) \
    $(wildcard src/editor/*.cpp) \
    $(wildcard src/editor/docks/*.cpp) \
    src/main.cpp

OBJ := $(SRC:.cpp=.o)

TARGET := rayeditor

# Platform detection
ifeq ($(OS),Windows_NT)
    TARGET := rayeditor.exe
    LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32
    RES := src/rayeditor.res
else
    LIBS := -lraylib -lGL -lpthread -ldl -lm
    RES :=
endif

LDFLAGS := -Llib -L.

all: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(CXX) $(OBJ) $(RES) -o $@ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean