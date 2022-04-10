#include <raybehavior.h>
#include <raylib.h>
#include <string>

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
            DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 50, 100, 100, RED);
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