#include "IconKitObject.hpp"
#include "IconKitManager.hpp"
#include "UnlockDialog.hpp"
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(ISProfilePage, ProfilePage) {
    static void onModify(auto& self) {
        self.setHookPriority("ProfilePage::loadPageFromUserInfo", -132456789);
    }

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

        this->m_buttonMenu->getChildByID("is-download-button")->removeFromParentAndCleanup(true);

        auto spr_use = cocos2d::CCSprite::createWithSpriteFrameName("GJ_selectSongBtn_001.png");
        spr_use->setScale(.8f);

        auto downloadButton = CCMenuItemSpriteExtra::create(spr_use, this, menu_selector(ISProfilePage::useKit));
        downloadButton->setPosition(15.0f, -95.0f);

        downloadButton->setID("is-download-button");

        this->m_buttonMenu->addChild(downloadButton);
    }

    void useKit(cocos2d::CCObject* pSender) {
        auto gm = GameManager::sharedState();

        gm->setPlayerFrame(this->m_score->getPlayerCube());
        gm->setPlayerShip(this->m_score->getPlayerShip());
        gm->setPlayerBall(this->m_score->getPlayerBall());
        gm->setPlayerBird(this->m_score->getPlayerUfo());
        gm->setPlayerDart(this->m_score->getPlayerWave());
        gm->setPlayerRobot(this->m_score->getPlayerRobot());
        gm->setPlayerSpider(this->m_score->getPlayerSpider());
        gm->setPlayerStreak(std::max(static_cast<uint32_t>(this->m_score->getPlayerStreak()), 1u));
        gm->setPlayerDeathEffect(this->m_score->getPlayerExplosion());
        gm->setPlayerGlow(this->m_score->getGlowEnabled());
        gm->setPlayerColor(this->m_score->getPlayerColor1());
        gm->setPlayerColor2(this->m_score->getPlayerColor2());

        auto alert = TextAlertPopup::create("Kit Enabled!", .5f, .6f);
        this->addChild(alert, 9999);
    }

    bool checkIfKitIsSaved() {
        auto kits = IconKitManager::sharedState()->getKits();

        for (auto i = 0; i < kits->count(); i++) {
            auto kit = dynamic_cast<IconKitObject*>(kits->objectAtIndex(i));

            if (
                kit->getCubeID() == this->m_score->getPlayerCube() 
                && kit->getShipID() == this->m_score->getPlayerShip() 
                && kit->getBallID() == this->m_score->getPlayerBall() 
                && kit->getUfoID() == this->m_score->getPlayerUfo() 
                && kit->getWaveID() == this->m_score->getPlayerWave() 
                && kit->getRobotID() == this->m_score->getPlayerRobot() 
                && kit->getSpiderID() == this->m_score->getPlayerSpider() 
                && kit->getStreakID() == this->m_score->getPlayerStreak() 
                && kit->getDeathID() == this->m_score->getPlayerExplosion() 
                && kit->getColor1() == this->m_score->getPlayerColor1() 
                && kit->getColor2() == this->m_score->getPlayerColor2()
            ) {return true;}
        }

        return false;
    }

    void loadPageFromUserInfo(GJUserScore* score) {
        ProfilePage::loadPageFromUserInfo(score);

        auto spr_download = cocos2d::CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
        auto spr_use = cocos2d::CCSprite::createWithSpriteFrameName("GJ_selectSongBtn_001.png");

        spr_download->setScale(.8f);
        spr_use->setScale(.8f);

        CCMenuItemSpriteExtra* downloadButton;

        if (ISProfilePage::checkIfKitIsSaved()) {
            downloadButton = CCMenuItemSpriteExtra::create(spr_use, this, menu_selector(ISProfilePage::useKit));
            downloadButton->setPosition(15.0f, -95.0f);
        }
        else {
            downloadButton = CCMenuItemSpriteExtra::create(spr_download, this, menu_selector(ISProfilePage::onSaveIcons));
            downloadButton->setPosition(15.0f, -95.0f);
        }

        downloadButton->setID("is-download-button");

        this->m_buttonMenu->addChild(downloadButton);

        // Remove MegaHack Button
        for (const auto& child : CCArrayExt<CCNode*>(m_buttonMenu->getChildren())) {
            if (child->getPosition() == CCPoint(16.f, -95.f)) {
                child->setVisible(false);
            }
        }
    }
};