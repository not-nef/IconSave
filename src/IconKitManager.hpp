#pragma once

using namespace geode::prelude;

class IconKitManager : public GManager {
    cocos2d::CCArray* m_vKits;

    virtual bool init() override;

    virtual void encodeDataTo(DS_Dictionary* data);
    virtual void dataLoaded(DS_Dictionary* data);
    virtual void firstLoad();

    public:
        static IconKitManager* sharedState();

        void addKit(IconKitObject*);
        void removeKit(IconKitObject*);
        cocos2d::CCArray* getKits();
        void moveKitToTop(IconKitObject*);

        ~IconKitManager();
};