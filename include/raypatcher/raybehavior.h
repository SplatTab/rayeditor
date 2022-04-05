/**********************************************************************************************
 * Ray Behavior is used within the libaries itself.
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