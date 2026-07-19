#include <raybehavior.h>
#include <raylib.h>
#include <string>

class SquareGREEN : public IRayBehaviour {
    public:

        // Draw is called every frame during rendering.
        void Draw() override
        {
            DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 50, 100, 100, GREEN);
        }
};

RAYCLASS(SquareGREEN)