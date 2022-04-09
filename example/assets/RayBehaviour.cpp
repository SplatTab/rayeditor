#include <raybehavior.h>
#include <raylib.h>

#include <iostream>

class TemplateBehaviour : public IRayBehaviour {
    public:

        // Init is called when the program starts.
        void Init() override
        {
            std::cout << "Init" << std::endl;
        }

        // Update is called every frame before rendering.
        void Update() override
        {
            std::cout << "Update" << std::endl;
        }

        // Draw is called every frame during rendering.
        void Draw() override
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
        }

        // Close is called then the program exits
        void Close() override
        {
            std::cout << "Close" << std::endl;
        }
};

// Important boilerplate code to register the behaviour
extern "C" __declspec(dllexport)IRayBehaviour* GetBehaviour(){ return new TemplateBehaviour();}
extern "C" __declspec(dllexport)void KillBehaviour( IRayBehaviour* p ){ delete p;}