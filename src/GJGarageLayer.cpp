#include "GJGarageLayer.hpp"
#include <Geode/modify/GJGarageLayer.hpp>
#include "IconSelectPopup.hpp"
#include "IconKitManager.hpp"

using namespace geode::prelude;

void ISGarageLayer::onSelectKit(cocos2d::CCObject* pSender) {
    IconSelectPopup::create(this)->show();
}

void ISGarageLayer::onSaveCurrent(cocos2d::CCObject* pSender) {
    auto gm = GameManager::sharedState();

    auto icon = new IconKitObject();
    icon->setCubeID(gm->getPlayerFrame());
    icon->setShipID(gm->getPlayerShip());
    icon->setBallID(gm->getPlayerBall());
    icon->setUfoID(gm->getPlayerBird());
    icon->setWaveID(gm->getPlayerDart());
    icon->setRobotID(gm->getPlayerRobot());
    icon->setSpiderID(gm->getPlayerSpider());
    icon->setStreakID(gm->getPlayerStreak());
    icon->setDeathID(gm->getPlayerDeathEffect());
    icon->setPlayerFrame(gm->getPlayerIconType());
    icon->setGlowEnabled(gm->getPlayerGlow());
    icon->setColor1(gm->getPlayerColor());
    icon->setColor2(gm->getPlayerColor2());
    icon->setName(GJAccountManager::sharedState()->m_username);

    auto im = IconKitManager::sharedState();

    if (im) {
        im->addKit(icon);

        auto popup = TextAlertPopup::create("Icon Kit Added!", .5f, .6f);
        this->addChild(popup, 100);
    }
}

class $modify(GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init()) {
            return false;
        }

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
        auto menu = cocos2d::CCMenu::create();

        auto spr_download = cocos2d::CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
        spr_download->setScale(.6f);

        auto downloadButton = CCMenuItemSpriteExtra::create(
            spr_download,
            this,
            menu_selector(ISGarageLayer::onSaveCurrent)
        );
        downloadButton->setPosition(65, 90);
        menu->addChild(downloadButton);

        auto spr_folder = cocos2d::CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png");
        spr_folder->setScale(1.15f);

        auto icon = SimplePlayer::create(1 + (std::rand() % 0xa0));    // 1 + (std::rand() % 0xa0)
        icon->setColor({
            (unsigned char)(1 + (std::rand() % 255)),
            (unsigned char)(1 + (std::rand() % 255)),
            (unsigned char)(1 + (std::rand() % 255))
        });   // { 200, 200, 200 }
        icon->setSecondColor({
            (unsigned char)(1 + (std::rand() % 255)),
            (unsigned char)(1 + (std::rand() % 255)),
            (unsigned char)(1 + (std::rand() % 255))
        });   // { 200, 200, 200 }
        icon->setScale(.45f);
        icon->setPosition(spr_folder->getContentSize() / 2);

        spr_folder->addChild(icon);

        auto folderButton = CCMenuItemSpriteExtra::create(
            spr_folder,
            this,
            menu_selector(ISGarageLayer::onSelectKit)
        );
        folderButton->setPosition(28, 90);
        menu->addChild(folderButton);

        menu->setPosition(0, 0);

        this->addChild(menu, 20);
        
        return true;
    }
};
