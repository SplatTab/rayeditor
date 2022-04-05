# Ray Editor Lib Files
RELIBSRC = lib/imgui/*.cpp src/editor/*.cpp src/editor/utility/*.cpp src/editor/docks/*.cpp
RELIBLIB = -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32
RELIBINCLUDES = -Iinclude/imgui -Iinclude/raylib
RELIBOUTPUT = librayeditor.a


# Main Application Files
APPSRC = src/main.cpp src/rayeditor.res
APPLIBS = -lraypatcher
APPINCLUDES = -Iinclude/raypatcher
APPOUTPUT = rayeditor.exe

default:
	g++ $(APPSRC) $(RELIBSRC) -o $(APPOUTPUT) -O2 -Wall -Wno-missing-braces -Wunused-function -Iinclude $(RELIBINCLUDES) $(APPINCLUDES) -L lib $(RELIBLIB) $(APPLIBS)
	./$(OUTPUT)

rayeditorlib:
	g++ -c $(RELIBSRC) -O2 -Wall -Wno-missing-braces -Wunused-function -Iinclude $(RELIBINCLUDES) -L lib $(RELIBLIB)
