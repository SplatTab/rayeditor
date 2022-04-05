#include "rayeditor.hpp"

using namespace RayEditor;

void CachedIcons::LoadIcons() {
    folder = LoadTexture("data/resources/icons/folder.png");
    folder.width = 74;
    folder.height = 84;

    defaultFile = LoadTexture("data/resources/icons/defaultfile.png");
    defaultFile.width = 72;
    defaultFile.height = 84;
}

void CachedIcons::UnloadIcons() {
    UnloadTexture(folder);
    UnloadTexture(defaultFile);
}