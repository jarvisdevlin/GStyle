# GStyle
GStyle is a Geometry Dash mod that lets you manually customize areas of your game in a CSS-like syntax.  
## Tutorial
### 1. Create the file
Create a file with any name you want but it has to end in .gstyle and then you have to import it from the mod's settings page.
You can use other peoples stylesheets if you want.
### 2. Create the stylesheet
Open the file and start creating your stylesheet.  
Using the DevTools mod to find things you want to edit is HIGHLY reccomended to create the stylesheet.
### 3. Done
You can now go anywhere in-game to see the horrible things you've done!
## Examples
### Skewing
```
MenuLayer CCLabelBMFont:player-username {
    skew-x: 25;
}

MenuLayer CCSprite:main-title {
    skew-x: 25;
}
```
### EVIL!!!
```
LikeItemLayer {
    scale: 1.4;
    skew-x: 15;
    color: 120,0,0;
    opacity: 200;
}
```
## Editing
To edit something, make sure it has a Node ID.  
Here is a list of stuff you can edit.
### You can use the following styles:
x: float,  
y: float,  
scale: float,  
scale-x: float,  
scale-y: float,  
rotation: float,  
skew-x: float,  
skew-y: float,  
anchor-x: float,  
anchor-y: float,  
z-order: int,  
visible: bool,  
color: int,int,int,  
opacity: float,  
content-width: float,  
content-height: float
### You can edit the following types:
CCMenu, CCMenuItemSpriteExtra, CCSprite, CCSpriteExtra, CCSpriteBatchNode, CCLabelBMFont, CCCounterLabel, BoomScrollLayer, CCTextInputNode, CCScale9Sprite, GJGroundLayer, CCNode, GJEffectManager, GJUINode, Slider, CCParticleSystemQuad, EditorUI, UILayer, EditButtonBar, CustomSongWidget
### You can edit the following layers:
LikeItemLayer, LevelInfoLayer, LevelBrowserLayer, GJShopLayer, LevelSelectLayer, LevelAreaInnerLayer, ProfilePage, MessagesProfilePage, FriendsProfilePage, FRequestProfilePage, FriendRequestPopup, ShareCommentLayer, GJAccountSettingsLayer, DailyLevelPage, GauntletSelectLayer, GauntletLayer, SongInfoLayer, LevelLeaderboard, InfoLayer, PauseLayer, UIOptionsLayer, SetIDPopup, CreateGuidelinesLayer, SelectArtLayer, ColorSelectPopup, CustomSongLayer, LevelSettingsLayer, LevelEditorLayer, EditLevelLayer, GJPathPage, SetTextPopup, SetFolderPopup, AudioAssetsBrowser, LevelSearchLayer, NCSInfoLayer, MusicBrowser, GJColorSetupLayer, LevelPage, MenuLayer, CreatorLayer, GJGarageLayer, LevelAreaLayer, SecretLayer5, RewardsPage, ChallengesPage, EditorOptionsLayer, GJPathsLayer, MoreSearchLayer, LevelCell