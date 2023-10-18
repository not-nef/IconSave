#pragma once

#include "IconKitWidget.hpp"

using namespace geode::prelude;

using UnlockList = std::vector<std::pair<UnlockType, uint32_t>>;

constexpr IconType getRelatedIconType(UnlockType _type) {
    switch (_type) {
        case UnlockType::Cube: return IconType::Cube;
        case UnlockType::Ship: return IconType::Ship;
        case UnlockType::Ball: return IconType::Ball;
        case UnlockType::Bird: return IconType::Ufo;
        case UnlockType::Dart: return IconType::Wave;
        case UnlockType::Robot: return IconType::Robot;
        case UnlockType::Spider: return IconType::Spider;
        case UnlockType::Death: return IconType::DeathEffect;
        case UnlockType::Streak: return IconType::Special;
    }

    return IconType::Cube;
}

class UnlockDialog : public FLAlertLayer {
    protected:
        cocos2d::CCSize m_pLrSize;
        IconKitWidget* m_pKitWidget;

        bool init(IconKitWidget*, float, float, UnlockList const&);
        void onUseAnyway(cocos2d::CCObject*);
    
    public:
        static UnlockDialog * create(IconKitWidget*, UnlockList const&);
};