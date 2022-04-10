#include <raybehavior.h>
#include <raylib.h>

class ClassName : public IRayBehaviour {
    public:

        // Init is called when the program starts.
        void Init() override
        {
            // Init
        }

        // Update is called every frame before rendering.
        bool jump = false;
        void Update() override
        {
            if (IsKeyDown(KEY_SPACE))
            {
                bool jump = true;
            }
        }

        // Draw is called every frame during rendering.
        void Draw() override
        {
            if (jump)
            {
                DrawCircle(0, 0, 50, GREEN);
            }
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);
            DrawRectangle(30, 0, GetScreenWidth(), GetScreenHeight(), RED);
        }

        // Close is called then the program exits
        void Close() override
        {
            // Close
        }
};

// Important boilerplate code to register the behaviour
extern "C" __declspec(dllexport)IRayBehaviour* GetBehaviour(){ return new ClassName();}
extern "C" __declspec(dllexport)void KillBehaviour( IRayBehaviour* p ){ delete p;}