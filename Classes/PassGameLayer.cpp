//
//  PassGameLayer.cpp
//  sangu
//
//  Created by YUN on 15/3/11.
//
//

#include "PassGameLayer.h"
#include "Funtion.h"
#include "HelloWorldScene.h"

PassGameLayer::PassGameLayer()
{
    mSelectMenuTag = -1;
}

PassGameLayer::~PassGameLayer()
{
    
}

void PassGameLayer::onEnter()
{
    CCLayer::onEnter();
    
    initLayer();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, true);
}
void PassGameLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void PassGameLayer::initLayer()
{
    CCSprite* gamebg = createSprite("gameBG.png", 320, 568);
    gamebg->setScale(mWinScale*1.5);
    this->addChild(gamebg);
    
    CCSprite* gameTitle = createSprite("passTitle.png", 320, 220);
    this->addChild(gameTitle);
    
    const char* menuName[2] = {"goOnBtn.png","newGameBtn.png"};
    const float menuPos[2][2] = {{224,626},{410,521}};
    const char* menuTextName[3] = {"passGoOn.png","newGameText.png"};
    for(int i = 0;i < 2;i++)
    {
        CCSprite* menuSprite = createSprite(menuName[i], menuPos[i][0], menuPos[i][1]);
        this->addChild(menuSprite,2,i);
        
        CCSprite* menuText = CCSprite::create(menuTextName[i]);
        menuText->setPosition(ccp(menuSprite->getContentSize().width*0.5,menuSprite->getContentSize().height*0.5));
        menuSprite->addChild(menuText);
    }
    
    CCSprite* passText = createSprite("passText.png", 320, 876);
    this->addChild(passText,3);
    
    CCSprite* effect = createSprite("passEffect1.png", 320, 876);
    this->addChild(effect,2);
    
    effect->runAction(createAction("passEffect", 3, -1,0.1,false));
}

void PassGameLayer::menuEvent(int tag)
{
    switch (tag) {
        case 0:
            exitLayer();
            break;
        case 1:
            exitLayer(true);
            break;

        default:
            break;
    }
}


void PassGameLayer::exitLayer(bool bNewGame)
{
    if(bNewGame)
    {
        HelloWorld::getsharder()->restratGame();
    }
    
    this->removeFromParent();
}



bool PassGameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    for(int i = 0;i < 2;i++)
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
void PassGameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(mSelectMenuTag != -1)
    {
        CCSprite* menusprite = (CCSprite*)this->getChildByTag(mSelectMenuTag);
        if(menusprite->boundingBox().containsPoint(pTouch->getLocation()))
        {
            menuEvent(mSelectMenuTag);
        }
        
        menusprite->setScale(mWinScale);
        mSelectMenuTag = -1;
    }
    
}
