#include "InputNode.hpp"

using namespace geode::prelude;

const char* ISInputNode::getString() {
    return this->m_pInput->getTextField()->getString();
}

void ISInputNode::setString(const char* _str) {
    this->m_pInput->getTextField()->setString(_str);

    this->m_pInput->refreshLabel();
}

CCTextInputNode* ISInputNode::getInputNode() {
    return this->m_pInput;
}

bool ISInputNode::init(float _w, float _h, const char* _phtxt, const char* _fnt, const std::string & _awc, int _cc) {
    this->m_pBG = cocos2d::extension::CCScale9Sprite::create(
        "square02b_001.png", { 0.0f, 0.0f, 80.0f, 80.0f }
    );

    this->m_pBG->setScale(.5f);
    this->m_pBG->setColor({ 0, 0, 0 });
    this->m_pBG->setOpacity(75);
    this->m_pBG->setContentSize({ _w * 2, _h * 2 });

    this->addChild(this->m_pBG);

    this->m_pInput = CCTextInputNode::create(
        _w, _h, _phtxt, _fnt
    );

    this->m_pInput->setLabelPlaceholderColor({ 150, 150, 150 });
    this->m_pInput->setLabelPlaceholderScale(.75f);
    this->m_pInput->setMaxLabelScale(.8f);
    this->m_pInput->setMaxLabelWidth(_cc);
    if (_awc.length())
        this->m_pInput->setAllowedChars(_awc);

    this->addChild(this->m_pInput);

    return true;
}

bool ISInputNode::init(float _w, const char* _phtxt, const char* _fnt, const std::string & _awc, int _cc) {
    return init(_w, 30.0f, _phtxt, _fnt, _awc, _cc);
}

bool ISInputNode::initMulti(float _w, float _h, const char* _phtxt, const char* _fnt, const std::string & _awc, int _cc) {
    auto ret = init(_w, _h, _phtxt, _fnt, _awc, _cc);

    //this->m_pInput->setLineLength(_w);

    return ret;
}

ISInputNode* ISInputNode::create(float _w, const char* _phtxt, const char* _fnt, const std::string & _awc, int _cc) {
    auto pRet = new ISInputNode();

    if (pRet && pRet->init(_w, _phtxt, _fnt, _awc, _cc)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ISInputNode* ISInputNode::create(float _w, const char* _phtxt, const std::string & _awc) {
    return create(_w, _phtxt, "bigFont.fnt", _awc, 69);
}

ISInputNode* ISInputNode::create(float _w, const char* _phtxt, const std::string & _awc, int _cc) {
    return create(_w, _phtxt, "bigFont.fnt", _awc, _cc);
}

ISInputNode* ISInputNode::create(float _w, const char* _phtxt, const char* _fnt) {
    return create(_w, _phtxt, _fnt, "", 69);
}

ISInputNode* ISInputNode::create(float _w, const char* _phtxt) {
    return create(_w, _phtxt, "bigFont.fnt");
}

ISInputNode* ISInputNode::createMulti(float _w, float _h, const char* _phtxt, const char* _fnt, int _cc) {
    auto pRet = new ISInputNode();

    if (pRet && pRet->initMulti(_w, _h, _phtxt, _fnt, "", _cc)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ISInputNode* ISInputNode::createMulti(float _w, float _h, const char* _phtxt, const char* _fnt, const std::string & _awc, int _cc) {
    auto pRet = new ISInputNode();

    if (pRet && pRet->initMulti(_w, _h, _phtxt, _fnt, _awc, _cc)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}