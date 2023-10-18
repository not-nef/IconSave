#pragma once

#include "BrownAlertDelegate.hpp"
#include "InputNode.hpp"

using namespace geode::prelude;

using RenameCallback = std::function<void(const char*)>;

class RenameDialog : public BrownAlertDelegate {
    protected:
        RenameCallback m_cbCallback = nullptr;
        ISInputNode* m_pInput;
        const char* m_sBtnText;
        const char* m_sPlaceholder;

        bool initWithText(float, float, const char*, const char* = "Rename Kit", const char* = "Apply");

        void setup() override;

        void onRename(cocos2d::CCObject*);
    
    public:
        static RenameDialog * create();
        static RenameDialog * create(const char*, const char* = "Apply");

        void setCallback(RenameCallback);
};