SRC = lib/imgui/*.cpp src/editor/*.cpp src/editor/utility/*.cpp src/editor/docks/*.cpp

APPSRC = src/main.cpp src/rayeditor.res
APPOUTPUT = rayeditor.exe

INCLUDES = -Iinclude -Iinclude/imgui -Iinclude/raylib
LIBPATHS = -Llib -L.
LIBS = -lraypatcher -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

default:
	g++ -std=c++17 $(SRC) $(APPSRC) -o $(APPOUTPUT) -O2 -Wall -Wno-missing-braces -Wunused-function $(INCLUDES) $(LIBPATHS) $(LIBS)