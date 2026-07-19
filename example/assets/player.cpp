#include <raybehavior.h>
#include <raylib.h>

class Player : public IRayBehaviour {
    private:
        Vector2 position;
        float speed;
        Texture2D tex;

    public:

        // Init is called when object is initialized
        void Init() override
        {
            tex = LoadTexture("example/assets/icon.png");
            speed = 200.0f;
            position = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        }

        // Update is called every frame before rendering.
        void Update() override
        {
            float delta = GetFrameTime();

            if (IsKeyDown(KEY_D))
                position.x += speed * delta;

            if (IsKeyDown(KEY_A))
                position.x -= speed * delta;

            if (IsKeyDown(KEY_S))
                position.y += speed * delta;

            if (IsKeyDown(KEY_W))
                position.y -= speed * delta;
        }

        // Draw is called every frame during rendering.
        void Draw() override
        {
            DrawTexture(tex, (int)position.x, (int)position.y, WHITE);
        }

        // Close is called then object is freed
        void Close() override
        {
            UnloadTexture(tex);
        }
};

RAYCLASS(Player)