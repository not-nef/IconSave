#pragma once

using namespace geode::prelude;

class ISInputNode : public cocos2d::CCNode {
    protected:
        cocos2d::extension::CCScale9Sprite* m_pBG;
        CCTextInputNode* m_pInput;

        bool init(float, float, const char*, const char*, const std::string &, int);
        bool init(float, const char*, const char*, const std::string &, int);
        bool initMulti(float, float, const char*, const char*, const std::string &, int);

    public:
        static ISInputNode* create(float width, const char* placeholder, const char* fontFile, const std::string & filter, int limit);
        static ISInputNode* create(float width, const char* placeholder, const std::string & filter, int limit);
        static ISInputNode* create(float width, const char* placeholder, const std::string & filter);
        static ISInputNode* create(float width, const char* placeholder, const char* fontFile);
        static ISInputNode* create(float width, const char* placeholder);

        // don't remember if this even works lol
        // the second float is height, rest are
        // the same as normal
        static ISInputNode* createMulti(float, float, const char*, const char*, const std::string &, int);
        static ISInputNode* createMulti(float, float, const char*, const char*, int);

        CCTextInputNode* getInputNode();

        void setString(const char*);
        const char* getString();
};