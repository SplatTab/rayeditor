#include <raybehavior.h>
#include <raylib.h>

#include <iostream>

class TemplateBehaviour : public IRayBehaviour {
    public:

        // Init is called when the game starts.
        void Init() override {
            std::cout << "Init" << std::endl;
        }

        // Update is called every frame.
        void Update() override {
            std::cout << "Update" << std::endl;
        }

        // Draw is called during the frames render phase.
        void Draw() override {
            DrawRectangle(50, 50, 3429032, 3429032, RAYWHITE);
            std::cout << "Draw" << std::endl;
        }

        // Close is called then the program exits
        void Close() override {
            std::cout << "Close" << std::endl;
        }
};

// Boilerplate code to register the behaviour
extern "C" __declspec(dllexport)IRayBehaviour* GetBehaviour(){ return new TemplateBehaviour();}
extern "C" __declspec(dllexport)void KillBehaviour( IRayBehaviour* p ){ delete p;}