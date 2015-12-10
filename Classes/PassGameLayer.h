//
//  PassGameLayer.h
//  sangu
//
//  Created by YUN on 15/3/11.
//
//

#ifndef __sangu__PassGameLayer__
#define __sangu__PassGameLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class PassGameLayer : public CCLayer
{
public:
    PassGameLayer();
    ~PassGameLayer();
    
    CREATE_FUNC(PassGameLayer);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    void initLayer();
    void exitLayer(bool bNewGame = false);
    
    void menuEvent(int tag);
    
private:
    int mSelectMenuTag;
    
};

#endif /* defined(__sangu__PassGameLayer__) */
