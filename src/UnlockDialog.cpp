#include "UnlockDialog.hpp"

using namespace geode::prelude;

// because robtop sometimes uses 2.2 cubes
// and the only way to reasonably check is
// by hardcoding this shit

// thanks rob
uint32_t checkIfIDIsFuture(UnlockType _type, uint32_t _id) {
    switch (_type) {
        case UnlockType::Cube: if (_id > 142) return 142;
        case UnlockType::Ship: if (_id > 51) return 51;
        case UnlockType::Ball: if (_id > 43) return 43;
        case UnlockType::Bird: if (_id > 35) return 35;
        case UnlockType::Dart: if (_id > 35) return 35;
        case UnlockType::Robot: if (_id > 26) return 26;
        case UnlockType::Spider: if (_id > 17) return 17;
        case UnlockType::Death: if (_id > 16) return 16;
        case UnlockType::Streak: if (_id > 7) return 7;
        case UnlockType::Col1: if (_id > 42) return 42;
        case UnlockType::Col2: if (_id > 42) return 42;
    }

    return _id;
}

void UnlockDialog::onUseAnyway(cocos2d::CCObject* pSender) {
    this->m_pKitWidget->onUse(nullptr);

    FLAlertLayer::onBtn1(pSender);
}

bool UnlockDialog::init(IconKitWidget* _par, float _w, float _h, UnlockList const& _list) {
    if (!FLAlertLayer::initWithColor({ 0x00, 0x00, 0x00, 0x3B }))
        return false;

    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    this->m_pLrSize = cocos2d::CCSize { _w, _h };
    this->m_pKitWidget = _par;

    this->m_mainLayer = cocos2d::CCLayer::create();
    this->addChild(this->m_mainLayer);

    auto bg = cocos2d::extension::CCScale9Sprite::create("square01_001.png", { 0.0f, 0.0f, 94.0f, 94.0f });
    bg->setContentSize(this->m_pLrSize);
    bg->setPosition(winSize.width / 2, winSize.height / 2);
    this->m_mainLayer->addChild(bg);

    auto title = cocos2d::CCLabelBMFont::create("Missing Icons", "goldFont.fnt");

    title->setPosition(winSize.width / 2, winSize.height / 2 + this->m_pLrSize.height / 2 - 25.0f);
    title->setScale(.8f);
    
    this->m_mainLayer->addChild(title);

    

    constexpr const unsigned int row_max = 4u;
    auto col_c = (_list.size() - _list.size() % row_max) / row_max + 1;

    auto iconMenu = cocos2d::CCMenu::create();
    std::vector<cocos2d::CCMenu*> rowMenus;
    for (auto i = 0u; i < col_c; i++)
        rowMenus.push_back(cocos2d::CCMenu::create());

    auto ix = 0u;
    auto cur_c = 0u;
    for (auto const& icon : _list) {
        auto plr = GJItemIcon::createBrowserIcon(
            icon.first, checkIfIDIsFuture(icon.first, icon.second)
        );
        
        if (++ix % 4 == 0) cur_c++;

        rowMenus.at(cur_c)->addChild(plr);
    }

    for (auto const& row : rowMenus) {
        row->alignItemsHorizontallyWithPadding(15.0f);
        row->setContentSize({ 0, getChild<GJItemIcon>(row, 0)->getScaledContentSize().height });
        iconMenu->addChild(row);
    }
    
    iconMenu->alignItemsVerticallyWithPadding(5.0f);
    iconMenu->setPosition(winSize / 2);
    this->m_mainLayer->addChild(iconMenu);

    this->m_buttonMenu = cocos2d::CCMenu::create();
    this->m_mainLayer->addChild(this->m_buttonMenu);

    this->m_button1 = ButtonSprite::create("Use Anyway", 0, 0, "goldFont.fnt", "GJ_button_01.png", 0.0f, .8f);
    this->m_button2 = ButtonSprite::create("Cancel", 0, 0, "goldFont.fnt", "GJ_button_01.png", 0.0f, .8f);

    this->m_button1->setScale(.8f);
    this->m_button2->setScale(.8f);

    auto btnUseAnyway = CCMenuItemSpriteExtra::create(
        this->m_button1,
        this,
        (cocos2d::SEL_MenuHandler)&UnlockDialog::onUseAnyway
    );
    this->m_buttonMenu->addChild(btnUseAnyway);

    // todo: dont fuck up when copying robtop's icons

    auto btnOK = CCMenuItemSpriteExtra::create(
        this->m_button2,
        this,
        (cocos2d::SEL_MenuHandler)&FLAlertLayer::onBtn2
    );
    this->m_buttonMenu->addChild(btnOK);

    this->m_buttonMenu->alignItemsHorizontallyWithPadding(5.0f);
    btnUseAnyway->setPositionY(- this->m_pLrSize.height / 2 + 30.0f);
    btnOK->setPositionY(- this->m_pLrSize.height / 2 + 30.0f);

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    return true;
}

UnlockDialog * UnlockDialog::create(IconKitWidget* _par, UnlockList const& _list) {
    auto pRet = new UnlockDialog();

    if (pRet && pRet->init(_par, 260.0f, 220.0f, _list)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return pRet;
}