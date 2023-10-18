#include "ProfilePage.hpp"
#include "IconKitObject.hpp"
#include "IconKitManager.hpp"
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

void ISProfilePage::onSaveIcons(cocos2d::CCObject* pSender) {
    auto icon = new IconKitObject();
    icon->setCubeID(this->m_pScore->getPlayerCube());
    icon->setShipID(this->m_pScore->getPlayerShip());
    icon->setBallID(this->m_pScore->getPlayerBall());
    icon->setUfoID(this->m_pScore->getPlayerUfo());
    icon->setWaveID(this->m_pScore->getPlayerWave());
    icon->setRobotID(this->m_pScore->getPlayerRobot());
    icon->setSpiderID(this->m_pScore->getPlayerSpider());
    icon->setStreakID(this->m_pScore->getPlayerStreak());
    icon->setDeathID(this->m_pScore->getPlayerExplosion());
    icon->setPlayerFrame(this->m_pScore->getIconType());
    icon->setGlowEnabled(this->m_pScore->getGlowEnabled());
    icon->setColor1(this->m_pScore->getPlayerColor1());
    icon->setColor2(this->m_pScore->getPlayerColor2());
    icon->setName(this->m_pScore->m_userName.c_str());

    auto im = IconKitManager::sharedState();

    if (im) {
        im->addKit(icon);

        auto popup = TextAlertPopup::create("Icon Kit Saved!", .5f, .6f);
        this->addChild(popup, 100);
    }
}

class $modify(ProfilePage) {
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