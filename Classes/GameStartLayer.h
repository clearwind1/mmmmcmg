//
//  GameStartLayer.h
//  sangu
//
//  Created by YUN on 15/3/11.
//
//

#ifndef __sangu__GameStartLayer__
#define __sangu__GameStartLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class GameStartLayer : public CCLayer
{
public:
    GameStartLayer();
    ~GameStartLayer();
    
    CREATE_FUNC(GameStartLayer);
    
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    
    void initLayer();
    void changeSoundEffect();
    void guideLayer();
    void exitLayer(bool bNewGame = false);
    
    void menuEvent(int tag);
    
private:
    int mSelectMenuTag;
};

#endif /* defined(__sangu__GameStartLayer__) */
