//
//  GameGuide.cpp
//  sangu
//
//  Created by YUN on 15/3/11.
//
//

#include "GameGuide.h"
#include "Funtion.h"

GameGuide::GameGuide()
{
    mCurPage = -3;
    mbeginPoint = 0;
    laynode = CCNode::create();
    laynode->setPosition(ccp(mCurPage*mWinsize.width,0));
    this->addChild(laynode,1);
}
GameGuide::~GameGuide()
{
    
}

void GameGuide::onEnter()
{
    CCLayer::onEnter();
    
    initGuide();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, true);
}
void GameGuide::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void GameGuide::initGuide()
{
    char buff[64];
    for(int i = 0;i < 4;i++)
    {
        sprintf(buff, "guideBg%d.png",i+1);
        CCSprite* guideBg1 = CCSprite::create(buff);
        guideBg1->setPosition(getpos(320+640*i, 568));
        guideBg1->setScaleX(mWinScaleX);
        guideBg1->setScaleY(mWinScaleY);
        laynode->addChild(guideBg1);
    }
    
    returnbtn = CCSprite::create("goOnBtn.png");
    returnbtn->setScaleX(mWinScaleX);
    returnbtn->setScaleY(mWinScaleY);
    returnbtn->setPosition(getpos(537+640*3, 80));
    laynode->addChild(returnbtn,2,1);
    
    CCSprite* returnText = CCSprite::create("GuidereturnText.png");
    returnText->setPosition(ccp(returnbtn->getContentSize().width*0.5,returnbtn->getContentSize().height*0.5));
    returnbtn->addChild(returnText);
}

bool GameGuide::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    mbeginPoint = pTouch->getLocation().x;
    
    CCPoint point = pTouch->getLocation();
    point.x += mWinsize.width*3;

    if(returnbtn->boundingBox().containsPoint(point))
    {
        returnbtn->setScaleX(mWinScaleX*0.8);
        returnbtn->setScaleY(mWinScaleY*0.8);
    }
    
    
    return true;
}
void GameGuide::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    CCPoint point = pTouch->getLocation();
    point.x += mWinsize.width*3;
    if(mCurPage == -3 && returnbtn->boundingBox().containsPoint(point))
    {
        this->removeFromParent();
        
        return;
    }
    
    returnbtn->setScaleX(mWinScaleX);
    returnbtn->setScaleY(mWinScaleY);
    
    /*
    float dispox = pTouch->getLocation().x - mbeginPoint;
    if(dispox <= -40)
        mCurPage--;
    else if(dispox >= 40)
        mCurPage++;

    
    if(mCurPage >= 0)
        mCurPage = 0;
    if(mCurPage <= -3)
        mCurPage = -3;
    
    CCMoveTo* moveto = CCMoveTo::create(0.2, ccp(mCurPage*mWinsize.width,laynode->getPositionY()));
    laynode->runAction(moveto);
     */
    
}
