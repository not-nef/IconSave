#pragma once

#include "IconKitObject.hpp"
#include "IconSelectPopup.hpp"

using namespace geode::prelude;

using UnlockList = std::vector<std::pair<UnlockType, uint32_t>>;

class IconKitWidget : public CCLayer, public FLAlertLayerProtocol {
    public:
        static constexpr const float s_defWidth = 360.0f;
        static constexpr const float s_defHeight = 70.0f;

    protected:
        float m_fWidth = s_defWidth;
        float m_fHeight = s_defHeight;
        IconKitObject* m_pKitObject;
        CCLabelBMFont* m_pNameLabel;

        CC_SYNTHESIZE(IconSelectPopup*, m_pParentPopup, ParentPopup);
        CC_SYNTHESIZE(GJGarageLayer*, m_pGarage, Garage);

        cocos2d::extension::CCScale9Sprite* m_pBGSprite;

        bool init(IconKitObject*, float);

        void onRemove(cocos2d::CCObject*);
        void onUse(cocos2d::CCObject*);
        void onShare(cocos2d::CCObject*);
        void onRename(cocos2d::CCObject*);
        void onSettings(cocos2d::CCObject*);
        void onMoveToTop(cocos2d::CCObject*);
        void onEditKit(cocos2d::CCObject*);

        UnlockList checkRequiredIcons();

        void FLAlert_Clicked(FLAlertLayer*, bool) override;

    public:
        static IconKitWidget * create(IconKitObject*);
        static IconKitWidget * create(IconKitObject*, float);
};