#include "rayeditor.hpp"

using namespace RayEditor;

///<summary>
/// Caches default icons for use in the editor. NOTE: This should only be called by the editor and not in scripts.
///</summary>
void CachedIcons::LoadIcons()
{
    folder = LoadTexture("data/resources/icons/folder.png");
    folder.width = 74;
    folder.height = 84;

    defaultFile = LoadTexture("data/resources/icons/defaultfile.png");
    defaultFile.width = 72;
    defaultFile.height = 84;

    sourceFile = LoadTexture("data/resources/icons/sourcefile.png");
    sourceFile.width = 72;
    sourceFile.height = 84;

    cameracenter = LoadTexture("data/resources/icons/cameracenter.png");
}

///<summary>
/// Frees default icons from VRAM. NOTE: This should only be called by the editor and not in scripts.
///</summary>
void CachedIcons::UnloadIcons()
{
    UnloadTexture(folder);
    UnloadTexture(defaultFile);
    UnloadTexture(sourceFile);
    UnloadTexture(cameracenter);
}