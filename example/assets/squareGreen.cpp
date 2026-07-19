#include <raybehavior.h>
#include <raylib.h>
#include <string>

class SquareRED : public IRayBehaviour {
    public:

        // Draw is called every frame during rendering.
        void Draw() override
        {
            DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2, 100, 100, RED);
        }
};

RAYCLASS(SquareRED)