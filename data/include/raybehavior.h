/**********************************************************************************************
 * Ray Behavior is the only thing needed for patches.
 * LICENSE: ZLIB
 * Copyright (c) 2022 (SplatTab)
**********************************************************************************************/

class IRayBehaviour {
    public:

        virtual ~IRayBehaviour() = default;

        virtual void Init() {};
        virtual void Update() {};
        virtual void Draw() {};
        virtual void Close() {};
};