#include <raybehavior.h>
#include <raylib.h>
#include <string>

class ClassName : public IRayBehaviour {
    public:

        // Draw is called every frame during rendering.
        void Draw() override
        {
            DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 50, 100, 100, PURPLE);
        }
};

// Important boilerplate code to register the behaviour
extern "C" __declspec(dllexport)IRayBehaviour* GetBehaviour(){ return new ClassName();}
extern "C" __declspec(dllexport)void KillBehaviour( IRayBehaviour* p ){ delete p;}