//
//  GameStartLayer.cpp
//  sangu
//
//  Created by YUN on 15/3/11.
//
//

#include "GameStartLayer.h"
#include "Funtion.h"
#include "HelloWorldScene.h"
#include "GameGuide.h"
#include "Shop.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

GameStartLayer::GameStartLayer()
{
    mSelectMenuTag = -1;
}

GameStartLayer::~GameStartLayer()
{
    
}

void GameStartLayer::onEnter()
{
    CCLayer::onEnter();
    
    initLayer();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, true);
}
void GameStartLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void GameStartLayer::initLayer()
{
    CCSprite* gamebg = createSprite("startGameBg.png", 320, 568);
    gamebg->setScaleX(mWinScaleX);
    gamebg->setScaleY(mWinScaleY);
    this->addChild(gamebg);
    
    CCSprite* gameTitle = createSprite("gameTitle.png", 320, 220);
    this->addChild(gameTitle);
    
    const char* menuName[4] = {"continuBtn.png","newGameBtn.png","helpText.png","goOnBtn.png"};
    const float menuPos[4][2] = {{320,626},{320,521},{107,910},{550,910}};
    const char* menuTextName[4] = {"goOnText.png","newGameText.png","","gameExitText.png"};
    const float menuTextPos[4][2] ={{245,122-47},{310,155-56},{107,910},{81,51}};
    for(int i = 0;i < 4;i++)
    {
        CCSprite* menuSprite = createSprite(menuName[i], menuPos[i][0], menuPos[i][1]);
        this->addChild(menuSprite,2,i);
        
        
        CCSprite* menuText = CCSprite::create(menuTextName[i]);
        if(menuText == NULL)
            continue;
        menuText->setPosition(ccp(menuTextPos[i][0],menuTextPos[i][1]));
        menuSprite->addChild(menuText);
    }
    
    CCSprite* soundMenu;
    if(haveMuicsEffect())
        soundMenu = createSprite("soundOnBtn.png", 107, 1040);
    else
        soundMenu = createSprite("soundOffBtn.png", 107, 1040);
    
    this->addChild(soundMenu,2,4);
    
    
}

void GameStartLayer::menuEvent(int tag)
{
    switch (tag) {
        case 0:
            exitLayer();
            break;
        case 1:
            exitLayer(true);
            break;
        case 2:
            guideLayer();
            break;
        case 4:
            changeSoundEffect();
            break;
        case 3:
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
            CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#else
            JniMethodInfo minfo;
            bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/game/mmmmcmg/zwdzz","getIntence","()Ljava/lang/Object;");
            //CCLog("开始调用!");
            jobject jobj=NULL;
            if (isHave)
            {
                jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
            }
            //CCLog("取得jobj");
            isHave = JniHelper::getMethodInfo(minfo,"com/game/mmmmcmg/zwdzz","exitGame","()V");
            //CCLog("处理中!");
            std::cout<<isHave<<std::endl;
            if (isHave)
            {
                //CCLog("接收!");
                minfo.env->CallVoidMethod(jobj, minfo.methodID);
                CCLog("完成!");
            }
            else
            {
                // CCLog("jni-java函数执行完毕");
            }
#endif
#endif
        }
            break;
        default:
            break;
    }
}

void GameStartLayer::guideLayer()
{
    CCNode* parentnode = this->getParent();
    GameGuide* guidelay = GameGuide::create();
    parentnode->addChild(guidelay,100);
    
    exitLayer();
}

void GameStartLayer::changeSoundEffect()
{
    this->removeChildByTag(4);
    if(haveMuicsEffect())
        saveHaveMuicsEffect(false);
    else
        saveHaveMuicsEffect(true);
    
    CCSprite* soundMenu;
    if(haveMuicsEffect())
        soundMenu = createSprite("soundOnBtn.png", 107, 1040);
    else
        soundMenu = createSprite("soundOffBtn.png", 107, 1040);
    
    this->addChild(soundMenu,2,4);
}

void GameStartLayer::exitLayer(bool bNewGame)
{
    CCLog("readGameVirgour===========%d",readGameVirgour());
    if(bNewGame && readGameVirgour()!= 0)
    {
        HelloWorld::getsharder()->restratGame();
        this->removeFromParent();
    }
    if(readGameVirgour()== 0)
    {
        Shop* shoplay = Shop::create();
        this->addChild(shoplay,30);
    }
    
    if(!bNewGame && readGameVirgour() !=0)
        this->removeFromParent();
}



bool GameStartLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    for(int i = 0;i < 5;i++)
    {
        CCSprite* menusprite = (CCSprite*)this->getChildByTag(i);
        if(menusprite->boundingBox().containsPoint(pTouch->getLocation()))
        {
            mSelectMenuTag = i;
            menusprite->setScale(mWinScale*0.9);
            break;
        }
    }
    
    return true;
}
void GameStartLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(mSelectMenuTag != -1)
    {
        CCSprite* menusprite = (CCSprite*)this->getChildByTag(mSelectMenuTag);
        if(menusprite->boundingBox().containsPoint(pTouch->getLocation()))
        {
            menuEvent(mSelectMenuTag);
        }
        
        if(mSelectMenuTag != 4)
            menusprite->setScale(mWinScale);
        mSelectMenuTag = -1;
    }
    
}



