#include "IconKitObject.hpp"
#include "IconKitManager.hpp"
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(ISProfilePage, ProfilePage) {
    void onSaveIcons(cocos2d::CCObject* pSender) {
        auto icon = new IconKitObject();
        icon->setCubeID(this->m_score->getPlayerCube());
        icon->setShipID(this->m_score->getPlayerShip());
        icon->setBallID(this->m_score->getPlayerBall());
        icon->setUfoID(this->m_score->getPlayerUfo());
        icon->setWaveID(this->m_score->getPlayerWave());
        icon->setRobotID(this->m_score->getPlayerRobot());
        icon->setSpiderID(this->m_score->getPlayerSpider());
        icon->setStreakID(this->m_score->getPlayerStreak());
        icon->setDeathID(this->m_score->getPlayerExplosion());
        icon->setPlayerFrame(this->m_score->getIconType());
        icon->setGlowEnabled(this->m_score->getGlowEnabled());
        icon->setColor1(this->m_score->getPlayerColor1());
        icon->setColor2(this->m_score->getPlayerColor2());
        icon->setName(this->m_score->m_userName.c_str());

        auto im = IconKitManager::sharedState();

        if (im) {
            im->addKit(icon);

            auto popup = TextAlertPopup::create("Icon Kit Saved!", .5f, .6f);
            this->addChild(popup, 100);
        }
    }

    bool init(int accountID, bool idk) {
        if (!ProfilePage::init(accountID, idk)) {
            return false;
        }

        auto spr_download = cocos2d::CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
        spr_download->setScale(.8f);

        auto downloadButton = CCMenuItemSpriteExtra::create(
            spr_download, this, (cocos2d::SEL_MenuHandler)&ISProfilePage::onSaveIcons
        );

        downloadButton->setPosition(
            15.0f,
            -95.0f
        );

        this->m_buttonMenu->addChild(downloadButton);
        
        return true;
    }
};