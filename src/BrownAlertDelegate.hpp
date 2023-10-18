#pragma once

using namespace geode::prelude;

class BrownAlertDelegate : public FLAlertLayer {
    protected:
        // layer size is stored here
        CCSize m_pLrSize;

        virtual bool init(
            float width,
            float height,
            const char* bg = "GJ_square01.png",
            const char* title = ""
        );
        virtual void setup() = 0;

        virtual void onClose(CCObject*);
};