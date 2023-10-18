#pragma once

using namespace geode::prelude;

class ISGarageLayer : public GJGarageLayer {
    private:
        SimplePlayer* m_pPlayerPreview;
    
    public:
        inline SimplePlayer* getPlayerPreview() { return m_pPlayerPreview; }
        void onSaveCurrent(cocos2d::CCObject*);
        void onSelectKit(cocos2d::CCObject*);
};