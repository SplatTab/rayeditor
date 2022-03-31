EXTRAFILES = lib/imgui/*.cpp src/rayeditor.res
SRCFILES = src/docks/*.cpp src/utility/*.cpp src/editor/*.cpp src/main.cpp
OUTPUT = rayeditor.exe

default:
	g++ $(SRCFILES) $(EXTRAFILES) -o $(OUTPUT) -O2 -Wall -Wno-missing-braces -Wunused-function -Iinclude -Iinclude/imgui -Iinclude/libeditor -Iinclude/raylib -L lib -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32
	./$(OUTPUT)