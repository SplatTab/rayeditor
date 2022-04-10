#pragma once
#include <imgui.h>

#define IMRAYBLACK IM_COL32(24, 24, 24, 255)
#define IMRAYWHITE IM_COL32(245, 245, 245, 255)

class PushStyle {
    public:

        static void TransparentTable(); // Transparent headers and buttons.
        static void RayWhiteInvertButtons(); // Ray White buttons that invert on hover to RayBlack.
        static void RayBlackInvertButtons(); // Ray Black buttons that invert on hover to RayWhite.
};

class PopStyle {
    public:

        static void TransparentTable();
        static void RayWhiteInvertButtons();
        static void RayBlackInvertButtons();
};