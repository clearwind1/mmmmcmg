//
//  GameGuide.h
//  sangu
//
//  Created by YUN on 15/3/11.
//
//

#ifndef __sangu__GameGuide__
#define __sangu__GameGuide__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class GameGuide : public CCLayer
{
public:
    GameGuide();
    ~GameGuide();
    
    CREATE_FUNC(GameGuide);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    void initGuide();
    
private:
    
    CCNode* laynode;
    int mCurPage;
    
    CCSprite* returnbtn;
    
    float mbeginPoint;
    
};

#endif /* defined(__sangu__GameGuide__) */
