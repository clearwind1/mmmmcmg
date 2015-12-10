#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ElementSprite.h"
#include "Shop.h"

using namespace cocos2d;
using namespace std;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    
    void restratGame();
    
    
private:
    
    void GameBg();
    
    void createElement(int eID = -1,bool brunAction = true);
    
    bool checkPointTouch(int p,bool bcheckgameover = false);
    
    bool findVec(int p);
    
    void endCheckPointT();
    
    void clearSeleteFrame();
    
    void combinElement();
    
    void comElementCallback(CCNode* sender, void* data);
    
    void checkGameOver();
    
    void comTipShow();
    
    void showCurScore();
    void showRecordCom(int comNum);
    
    void showGameOver();
    
    void checkBuyVirgour();
    void showVirgour();
    
public:
    
    static HelloWorld* getsharder();
    
    static int g_buyItemSuccess[ITEMNUM];
    
private:
    
    CCNode* FrameNode;
    
    CCNode* elementNode;
    
    int seletePoint;
    vector<int> choseVec;
    
    bool m_bcombining;
    
    CCSprite* returnBtn;
    
    int mCurScore;
    
    int m_vigour;
    
    
    bool m_bGameOver;
    
    bool m_bPassGame;
    
};

#endif // __HELLOWORLD_SCENE_H__
