// there needs to be a better way to do this but im lazy

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/LevelAreaLayer.hpp>
#include <Geode/modify/SecretLayer5.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include <Geode/modify/RewardsPage.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/MessagesProfilePage.hpp>
#include <Geode/modify/FriendsProfilePage.hpp>
#include <Geode/modify/FRequestProfilePage.hpp>
#include <Geode/modify/FriendRequestPopup.hpp>
#include <Geode/modify/ShareCommentLayer.hpp>
#include <Geode/modify/GJAccountSettingsLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/ChallengesPage.hpp>
#include <Geode/modify/DailyLevelPage.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/modify/GauntletLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/SongInfoLayer.hpp>
#include <Geode/modify/LikeItemLayer.hpp>
#include <Geode/modify/LevelLeaderboard.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/UIOptionsLayer.hpp>
#include <Geode/modify/SetIDPopup.hpp>
#include <Geode/modify/CreateGuidelinesLayer.hpp>
#include <Geode/modify/NCSInfoLayer.hpp>
#include <Geode/modify/MusicBrowser.hpp>
#include <Geode/modify/OptionsScrollLayer.hpp>
#include <Geode/modify/CustomSongLayer.hpp>
#include <Geode/modify/LevelOptionsLayer2.hpp>
#include <Geode/modify/LevelOptionsLayer.hpp>
#include <Geode/modify/LevelSettingsLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/GJPathPage.hpp>
#include <Geode/modify/GJPathsLayer.hpp>
#include <Geode/modify/SetTextPopup.hpp>
#include <Geode/modify/SetFolderPopup.hpp>
#include <Geode/modify/AudioAssetsBrowser.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/MoreSearchLayer.hpp>
#include <Geode/modify/AccountHelpLayer.hpp>
#include <Geode/modify/AccountLoginLayer.hpp>
#include <Geode/modify/AccountRegisterLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/RateDemonLayer.hpp>
#include <Geode/modify/RateStarsLayer.hpp>
#include <Geode/modify/UploadPopup.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelPage.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/BoomScrollLayer.hpp>
#include <Geode/modify/CCMenuItemToggler.hpp>
#include <Geode/modify/TableViewCell.hpp>
#include <Geode/modify/Slider.hpp>
#include <Geode/modify/EditorOptionsLayer.hpp>
#include <Geode/modify/GJColorSetupLayer.hpp>
#include <Geode/modify/ColorSelectPopup.hpp>
#include <Geode/modify/SelectArtLayer.hpp>

#define lol(LayerClass) \
class $modify(LayerClass) { \
    bool init() override { \
        if (!LayerClass::init()) return false; \
        applyStyles(this, #LayerClass); \
        return true; \
    } \
};

class $modify(LikeItemLayer) {
    bool init(LikeItemType itemType, int itemID, int commentSourceID) {
        if (!LikeItemLayer::init(itemType, itemID, commentSourceID))
            return false;
        applyStyles(this, "LikeItemLayer");
        return true;
    }
};

class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;
        applyStyles(this, "LevelInfoLayer");
        return true;
    }
};

class $modify(LevelBrowserLayer) {
    bool init(GJSearchObject* p0) {
        if (!LevelBrowserLayer::init(p0)) return false;
        applyStyles(this, "LevelBrowserLayer");
        return true;
    }
};

class $modify(GJShopLayer) {
    bool init(ShopType p0) {
        if (!GJShopLayer::init(p0)) return false;
        applyStyles(this, "GJShopLayer");
        return true;
    }
};

class $modify(LevelSelectLayer) {
    bool init(int page) {
        if (!LevelSelectLayer::init(page)) return false;
        applyStyles(this, "LevelSelectLayer");
        return true;
    }
};

class $modify(LevelAreaInnerLayer) {
    bool init(bool returning) {
        if (!LevelAreaInnerLayer::init(returning)) return false;
        applyStyles(this, "LevelAreaInnerLayer");
        return true;
    }
};

class $modify(ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) return false;
        applyStyles(this, "ProfilePage");
        return true;
    }
};

class $modify(MessagesProfilePage) {
    bool init(bool p0) {
        if (!MessagesProfilePage::init(p0)) return false;
        applyStyles(this, "MessagesProfilePage");
        return true;
    }
};

class $modify(FriendsProfilePage) {
    bool init(UserListType type) {
        if (!FriendsProfilePage::init(type)) return false;
        applyStyles(this, "FriendsProfilePage");
        return true;
    }
};

class $modify(FRequestProfilePage) {
    bool init(bool p0) {
        if (!FRequestProfilePage::init(p0)) return false;
        applyStyles(this, "FRequestProfilePage");
        return true;
    }
};

class $modify(FriendRequestPopup) {
    bool init(GJFriendRequest* p0) {
        if (!FriendRequestPopup::init(p0)) return false;
        applyStyles(this, "FriendRequestPopup");
        return true;
    }
};

class $modify(ShareCommentLayer) {
    bool init(gd::string title, int charLimit, CommentType type, int ID, gd::string desc) {
        if (!ShareCommentLayer::init(title, charLimit, type, ID, desc)) return false;
        applyStyles(this, "ShareCommentLayer");
        return true;
    }
};

class $modify(GJAccountSettingsLayer) {
    bool init(int p0) {
        if (!GJAccountSettingsLayer::init(p0)) return false;
        applyStyles(this, "GJAccountSettingsLayer");
        return true;
    }
};

class $modify(DailyLevelPage) {
    bool init(GJTimedLevelType type) {
        if (!DailyLevelPage::init(type)) return false;
        applyStyles(this, "DailyLevelPage");
        return true;
    }
};

class $modify(GauntletSelectLayer) {
    bool init(int p0) {
        if (!GauntletSelectLayer::init(p0)) return false;
        applyStyles(this, "GauntletSelectLayer");
        return true;
    }
};

class $modify(GauntletLayer) {
    bool init(GauntletType type) {
        if (!GauntletLayer::init(type)) return false;
        applyStyles(this, "GauntletLayer");
        return true;
    }
};

#if defined(_WIN32)
class $modify(SongInfoLayer) {
    bool init(gd::string p0, gd::string p1, gd::string p2, gd::string p3, gd::string p4, gd::string p5, int p6, gd::string p7, int p8) {
        if (!SongInfoLayer::init(p0, p1, p2, p3, p4, p5, p6, p7, p8)) return false;
        applyStyles(this, "SongInfoLayer");
        return true;
    }
};
#endif

class $modify(LevelLeaderboard) {
    bool init(GJGameLevel* level, LevelLeaderboardType type, LevelLeaderboardMode mode) {
        if (!LevelLeaderboard::init(level, type, mode)) return false;
        applyStyles(this, "LevelLeaderboard");
        return true;
    }
};

class $modify(InfoLayer) {
    bool init(GJGameLevel* level, GJUserScore* score, GJLevelList* list) {
        if (!InfoLayer::init(level, score, list)) return false;
        applyStyles(this, "InfoLayer");
        return true;
    }
};

class $modify(PauseLayer) {
    bool init(GJGameLevel* level) {
        if (!PauseLayer::init(level)) return false;
        applyStyles(this, "PauseLayer");
        return true;
    }
};

class $modify(UIOptionsLayer) {
    bool init(GJBaseGameLayer* gameLayer) {
        if (!UIOptionsLayer::init(gameLayer)) return false;
        applyStyles(this, "UIOptionsLayer");
        return true;
    }
};

class $modify(SetIDPopup) {
    bool init(int current, int begin, int end, gd::string title, gd::string button, bool p5, int p6, float p7, bool p8, bool p9) {
        if (!SetIDPopup::init(current, begin, end, title, button, p5, p6, p7, p8, p9)) return false;
        applyStyles(this, "SetIDPopup");
        return true;
    }
};

class $modify(CreateGuidelinesLayer) {
    bool init(CustomSongDelegate* delegate, AudioGuidelinesType type) {
        if (!CreateGuidelinesLayer::init(delegate, type)) return false;
        applyStyles(this, "CreateGuidelinesLayer");
        return true;
    }
};

#if defined(_WIN32)
class $modify(SelectArtLayer) {
    bool init(SelectArtType type, int p1) {
        if (!SelectArtLayer::init(type, p1)) return false;
        applyStyles(this, "SelectArtLayer");
        return true;
    }
};
#endif

class $modify(ColorSelectPopup) {
    bool init(EffectGameObject* effect, cocos2d::CCArray* array, ColorAction* action) {
        if (!ColorSelectPopup::init(effect, array, action)) return false;
        applyStyles(this, "ColorSelectPopup");
        return true;
    }
};

class $modify(CustomSongLayer) {
    bool init(CustomSongDelegate* delegate) {
        if (!CustomSongLayer::init(delegate)) return false;
        applyStyles(this, "CustomSongLayer");
        return true;
    }
};

class $modify(LevelSettingsLayer) {
    bool init(LevelSettingsObject* obj, LevelEditorLayer* editor) {
        if (!LevelSettingsLayer::init(obj, editor)) return false;
        applyStyles(this, "LevelSettingsLayer");
        return true;
    }
};

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelEditorLayer::init(level, p1)) return false;
        applyStyles(this, "LevelEditorLayer");
        return true;
    }
};

class $modify(EditLevelLayer) {
    bool init(GJGameLevel* level) {
        if (!EditLevelLayer::init(level)) return false;
        applyStyles(this, "EditLevelLayer");
        return true;
    }
};

#if defined(_WIN32)
class $modify(GJPathPage) {
    bool init(int p0, GJPathsLayer* p1) {
        if (!GJPathPage::init(p0, p1)) return false;
        applyStyles(this, "GJPathPage");
        return true;
    }
};

class $modify(SetTextPopup) {
    bool init(gd::string value, gd::string placeholder, int maxLength, gd::string title, gd::string okBtnText, bool showResetBtn, float p6) {
        if (!SetTextPopup::init(value, placeholder, maxLength, title, okBtnText, showResetBtn, p6)) return false;
        applyStyles(this, "SetTextPopup");
        return true;
    }
};


class $modify(SetFolderPopup) {
    bool init(int value, bool isCreated, gd::string title) {
        if (!SetFolderPopup::init(value, isCreated, title)) return false;
        applyStyles(this, "SetFolderPopup");
        return true;
    }
};
#endif

class $modify(AudioAssetsBrowser) {
    bool init(gd::vector<int>& songIds, gd::vector<int>& sfxIds) {
        if (!AudioAssetsBrowser::init(songIds, sfxIds)) return false;
        applyStyles(this, "AudioAssetsBrowser");
        return true;
    }
};

class $modify(LevelSearchLayer) {
    bool init(int p0) {
        if (!LevelSearchLayer::init(p0)) return false;
        applyStyles(this, "LevelSearchLayer");
        return true;
    }
};

#if defined(_WIN32)
class $modify(NCSInfoLayer) {
    bool init(CustomSongLayer* layer) {
        if (!NCSInfoLayer::init(layer)) return false;
        applyStyles(this, "NCSInfoLayer");
        return true;
    }
};

class $modify(MusicBrowser) {
    bool init(int p0, GJSongType p1) {
        if (!MusicBrowser::init(p0, p1)) return false;
        applyStyles(this, "MusicBrowser");
        return true;
    }
};
#endif

class $modify(GJColorSetupLayer) {
    bool init(LevelSettingsObject* p0) {
        if (!GJColorSetupLayer::init(p0)) return false;
        applyStyles(this, "GJColorSetupLayer");
        return true;
    }
};

class $modify(LevelPage) {
    bool init(GJGameLevel* level) {
        if (!LevelPage::init(level)) return false;
        applyStyles(this, "LevelPage");
        return true;
    }
};

lol(MenuLayer)
lol(CreatorLayer)
lol(GJGarageLayer)
lol(LevelAreaLayer)
lol(SecretLayer5)
lol(RewardsPage)
lol(ChallengesPage)
//lol(UIPOptionsLayer)
//lol(NewgroundsInfoLayer)
//lol(GJSongBrowser)
lol(EditorOptionsLayer)
lol(GJPathsLayer)
lol(MoreSearchLayer)
lol(LevelCell)
//lol(LevelListCell)
//lol(StatsLayer)
//lol(AchievementsLayer)
//lol(CustomListView)
