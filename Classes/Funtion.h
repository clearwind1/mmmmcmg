//
//  Funtion.h
//  Markbels
//
//  Created by YUN on 15-1-12.
//
//

#ifndef __Markbels__Funtion__
#define __Markbels__Funtion__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


#define GameName        "MMMMCGBMG"

#define CanBuyGold      0
#define testMode        0
#define HaveGameCenter  0


#define ClassicMode     1
#define EndlessMode     2

#define VirgourShop     1
#define ToolsShop       2
#define FirstGiftShop   9
#define BigGiftShop     10
#define FGameGiftShop   11

enum{GameStart,GamePause,GameOver};
enum{SlowMachineTool,BinderTool,PoleTool,NextGameTool,TotalToolNum};

const float acWinsizeWidth  = 640.0;
const float acWinsizeHeight = 1136.0;

const float spriteWidth     = 60.0;
const float spriteHeight    = 60.0;

const int   SCORELISTNUM    = 20;

#define mWinsize CCDirector::sharedDirector()->getWinSize()
#define cache CCSpriteFrameCache::sharedSpriteFrameCache()
#define changeChar  CCString::createWithFormat

#define LayeronEnter(p) \
void onEnter()\
{ \
    CCLayer::onEnter(); \
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority-p,true); \
}

#define LayeronExit() \
void onExit()\
{ \
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this); \
    CCLayer::onExit(); \
}

#define mWinScale MIN(mWinsize.width/acWinsizeWidth,mWinsize.height/acWinsizeHeight)
#define mMaxWinScale MAX(mWinsize.width/acWinsizeWidth,mWinsize.height/acWinsizeHeight)
#define mWinScaleX mWinsize.width/acWinsizeWidth
#define mWinScaleY mWinsize.height/acWinsizeHeight

#define SaveStringToXML     CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML    CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveBooleanToXML    CCUserDefault::sharedUserDefault()->setBoolForKey
#define LoadStringFromXML   CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML  CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFromXML  CCUserDefault::sharedUserDefault()->getBoolForKey
#define SaveFlush           CCUserDefault::sharedUserDefault()->flush()

#define PlaySound           SimpleAudioEngine::sharedEngine()->playEffect

#define NORMALBTNIMAGE  "Normalbtn.png"
#define SELECTBTNIMAGE  "NormalbtnD.png"

#define LONGNORMALBTNIMAGE  "LongNormalbtn.png"
#define LONGSELECTBTNIMAGE  "LongNormalbtnD.png"

enum{NUMBERLEFT,NUMBERCENTER,NUMBERRIGHT};

void setSpriteScale(CCNode* sp);
CCPoint getacPos(float pox,float poy);
CCPoint getwinPos(float pox,float poy);
CCPoint getpos(float pox,float poy);
CCAction* createAction(const char* actioname,int actionNum,int bloop,float delay = -1,bool bframe = true);
CCSprite* createPlistSprite(const char* spname,float pox,float poy);
CCSprite* createSprite(const char* spname,float pox,float poy,bool bscale = true);
CCMenuItemImage* createPlistMenu(const char* normalImage,const char* seleteImage,CCObject *rec,SEL_MenuHandler callfun,float pox,float poy);
CCMenuItemImage* createMenu(const char* normalImage,const char* seleteImage,CCObject *rec,SEL_MenuHandler callfun,float pox,float poy,bool bscale = true);

CCMenuItemImage* createMenu(const char* normalImage,const char* seleteImage,const char* ttf,CCObject *rec,SEL_MenuHandler callfun,float pox,float poy,bool bscale = true);

CCLabelTTF* createTTF(const char* ttf,float size, float pox,float poy,CCPoint anpot = ccp(0.5,0.5),bool bscale = true);
CCProgressTimer* createProgress(const char* spname,float pox,float poy,float percent);
CCSprite* createRect(float rectwidth,float rectheight,ccColor3B col,float pox,float poy,bool bscale = true);
void showPicNum(const char* numName,int mNum,CCNode* mNode,float pox,float poy,int tag = -1,bool sc = false);
void showOnePicNum(const char* numName,int mNum,CCNode* mNode,float pox,float poy,int dir,int tag = -1,bool sc = true);


int getSystemTime();
void saveLastTime();
int readLastTime();

bool getHaveFirstGameRun();
void setHaveFirstGameRun(bool e = true);

bool getHaveFirstShopRun();
void setHaveFirstShopRun(bool e = true);

void saveHistoryScore(int score);
int readHightestScore();
void saveHightestScore(int score);

int readGameVirgour();
void saveGameVirgour(int virgour);

int readGameTools(int tooltag);
void saveGameTools(int tooltag,int toolnum);

int readGameLevel();
void saveGameLevel(int gamelevel);

void saveBackStepTimes(int times);
int readBackStepTimes();

void saveHaveSoundEffect(bool e);
void saveHaveMuicsEffect(bool e);

bool haveSoundEffect();
bool haveMuicsEffect();

bool readAchievement(int tag);
void saveAchievement(int tag);

#endif /* defined(__Markbels__Funtion__) */
