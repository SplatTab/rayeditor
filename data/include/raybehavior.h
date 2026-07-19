class IRayBehaviour {
    public:

        virtual ~IRayBehaviour() = default;

        virtual void Init() {};
        virtual void Update() {};
        virtual void Draw() {};
        virtual void Close() {};
};

#define RAYCLASS(className) \
extern "C" __declspec(dllexport) IRayBehaviour* GetBehaviour() \
{ \
    return new className(); \
} \
extern "C" __declspec(dllexport) void KillBehaviour(IRayBehaviour* p) \
{ \
    delete p; \
}