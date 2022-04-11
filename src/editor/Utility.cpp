#include <rayeditor.hpp>
#include <repatcher.h>

using namespace RayEditor;

Vector2 Utility::RayVec2Add(Vector2 a, Vector2 b)
{
    return Vector2{a.x + b.x, a.y + b.y};
}

Vector2 Utility::RayVec2Subtract(Vector2 a, Vector2 b)
{
    return Vector2{a.x - b.x, a.y - b.y};
}

Vector2 Utility::RayVec2Divide(Vector2 a, Vector2 b)
{
    return Vector2{a.x / b.x, a.y / b.y};
}

Vector2 Utility::RayVec2Multiply(Vector2 a, Vector2 b)
{
    return Vector2{a.x * b.x, a.y * b.y};
}

ImVec4 Utility::RayColorToImguiColor(Color color)
{
    return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}

std::string Utility::PatchErrorToString(int error)
{
    switch (error)
    {
        case PATCH_ERROR_NO_ERROR: return "PATCH_ERROR_DYNAMIC_LIB_NOT_LOADED"; break;
        case PATCH_ERROR_INVALID_PATH: return "PATCH_ERROR_INVALID_PATH"; break;
        case PATCH_ERROR_NOT_DIRECTORY: return "PATCH_ERROR_NOT_DIRECTORY"; break;
        case PATCH_ERROR_NOT_FILE: return "PATCH_ERROR_NOT_FILE"; break;
        case PATCH_ERROR_NOT_SOURCE_FILE: return "PATCH_ERROR_NOT_SOURCE_FILE"; break;
        case PATCH_ERROR_FAILED_EXTRACTION: return "PATCH_ERROR_FAILED_EXTRACTION"; break;
        case PATCH_ERROR_DYNAMIC_LIB_NOT_LOADED: return "PATCH_ERROR_DYNAMIC_LIB_NOT_LOADED"; break;
        default: return "PATCH_ERROR_UNKOWN"; break;
    }
}

// Copyright (c) 2021 Jeffery Myers
// Thanks for str filter Jeff
char* Utility::stristr(const char* str1, const char* str2)
{
    const char* p1 = str1;
    const char* p2 = str2;
    const char* r = *p2 == 0 ? str1 : 0;

    while (*p1 != 0 && *p2 != 0)
    {

        if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
        {
            if (r == 0)
            {
                r = p1;
            }
            p2++;
        }
        else
        {
            p2 = str2;
            if (r != 0)
            {
                p1 = r + 1;
            }

            if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
            {
                r = p1;
                p2++;
            }
            else
            {
                r = 0;
            }
        }

        p1++;
    }

    return *p2 == 0 ? (char*)r : 0;
}