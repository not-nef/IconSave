#pragma once

using namespace geode::prelude;

class ISProfilePage : public FLAlertLayer {
    protected:
        GJUserScore* m_pScore;
    public:
        void onSaveIcons(cocos2d::CCObject*);
};