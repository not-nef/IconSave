#pragma once

#include "BrownAlertDelegate.hpp"
#include "IconKitObject.hpp"

using namespace geode::prelude;

class IconSelectPopup : public BrownAlertDelegate {
    public:
        static constexpr const unsigned int s_nMaxOnPage = 10;

    protected:
        GJGarageLayer* m_pGarage;
        cocos2d::CCLabelBMFont* m_pPageLabel;
        
        unsigned int m_nCurrentPage = 0;
        cocos2d::CCSize m_sScrLayerSize;

        CCMenuItemSpriteExtra* m_pBtnLeft;
        CCMenuItemSpriteExtra* m_pBtnRight;

        void setup() override;
        void onClose(cocos2d::CCObject*);

        void showPage(unsigned int, const char* = "");
        void onNextPage(cocos2d::CCObject*);
        void onPrevPage(cocos2d::CCObject*);
        void onSearch(cocos2d::CCObject*);
        void onCancelSearch(cocos2d::CCObject*);
        void onImport(cocos2d::CCObject*);

        void scrollWheel(float, float) override;

    public:
        void showKitRemovedMessage(float);
        void refreshList();
        void editKit(IconKitObject*);

        static IconSelectPopup * create(GJGarageLayer* = nullptr);
};