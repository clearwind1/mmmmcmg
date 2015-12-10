//
//  Funtion.cpp
//  Markbels
//
//  Created by YUN on 15-1-12.
//
//

#include "Funtion.h"


void setSpriteScale(CCNode* sp)
{
    sp->setScale(mWinScale);
}

CCPoint getacPos(float pox,float poy)
{
    return ccp((mWinsize.width-acWinsizeWidth*mWinScale)/2+mWinScale*pox,(mWinsize.height-acWinsizeHeight*mWinScale)/2+mWinScale*(acWinsizeHeight-poy));
}

CCPoint getpos(float pox, float poy)
{
    return ccp(mWinsize.width*(pox/acWinsizeWidth),mWinsize.height*((acWinsizeHeight-poy)/acWinsizeHeight));
}

CCPoint getwinPos(float pox,float poy)
{
    float wpox = (pox-(mWinsize.width-acWinsizeWidth*mWinScale)/2)/mWinScale;
    float wpoy = acWinsizeHeight-(poy-(mWinsize.height-acWinsizeHeight*mWinScale)/2)/mWinScale;
    
    return ccp(wpox,wpoy);
}

CCAction* createAction(const char* actioname,int actionNum,int bloop,float delay,bool bframe)
{
    CCArray* actionarray = CCArray::create();
    char buff[128];
    for(int i = 1;i <= actionNum;i++)
    {
        sprintf(buff, "%s%d.png",actioname,i);
        
        if(!bframe)
        {
            CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(buff);
            CCSpriteFrame* spriteframe = CCSpriteFrame::createWithTexture(texture, CCRectMake(0,0,texture->getContentSize().width,texture->getContentSize().height));
            actionarray->addObject(spriteframe);
        }
        else
            actionarray->addObject(cache->spriteFrameByName(buff));
    }
    
    float num = delay;
    if(delay == -1)
        num = CCRANDOM_0_1() * 0.15 + 0.1;
    
    CCAnimation* action = CCAnimation::createWithSpriteFrames(actionarray,num);
    CCAnimate* animate = CCAnimate::create(action);
    
    if(bloop == -1)
    {
        CCRepeatForever* repeat = CCRepeatForever::create(animate);
        return repeat;
    }
    else
    {
        CCRepeat* repeat = CCRepeat::create(animate, bloop);
        return repeat;
    }
}
CCSprite* createPlistSprite(const char* spname,float pox,float poy)
{
    CCSprite* sp = CCSprite::createWithSpriteFrameName(spname);
    sp->setPosition(getacPos(pox, poy));
    setSpriteScale(sp);
    return sp;
}

//重写，根据x y 轴返回精灵
CCSprite* createSprite(const char* spname,float pox,float poy,bool bscale)
{
    CCSprite* sp = CCSprite::create(spname);
    sp->setPosition(ccp(pox,poy));
    if(bscale) sp->setPosition(getacPos(pox, poy));
    if(bscale) setSpriteScale(sp);
    return sp;
}

CCMenuItemImage* createPlistMenu(const char* normalImage,const char* seleteImage,CCObject *rec,SEL_MenuHandler callfun,float pox,float poy)
{
    CCMenuItemImage* menuitem = CCMenuItemImage::create();
    menuitem->setNormalSpriteFrame(cache->spriteFrameByName(normalImage));
    menuitem->setSelectedSpriteFrame(cache->spriteFrameByName(seleteImage));
    menuitem->initWithTarget(rec, callfun);
    menuitem->setPosition(getacPos(pox, poy));
    setSpriteScale(menuitem);
    
    return menuitem;
}
CCMenuItemImage* createMenu(const char* normalImage,const char* seleteImage,CCObject *rec,SEL_MenuHandler callfun,float pox,float poy,bool bscale)
{
    CCMenuItemImage* menuitem = CCMenuItemImage::create(normalImage,seleteImage);
    menuitem->initWithTarget(rec, callfun);
    menuitem->setPosition(ccp(pox,poy));
    if(bscale) menuitem->setPosition(getacPos(pox, poy));
    if(bscale) setSpriteScale(menuitem);
    
    return menuitem;
}

CCMenuItemImage* createMenu(const char* normalImage,const char* seleteImage,const char* ttf,CCObject *rec,SEL_MenuHandler callfun,float pox,float poy,bool bscale)
{
    CCMenuItemImage* menuitem = CCMenuItemImage::create(normalImage,seleteImage);
    menuitem->initWithTarget(rec, callfun);
    menuitem->setPosition(ccp(pox,poy));
    if(bscale) menuitem->setPosition(getacPos(pox, poy));
    if(bscale) setSpriteScale(menuitem);
    
    CCSprite* text = CCSprite::create(ttf);
    text->setPosition(ccp(menuitem->getContentSize().width*0.5,menuitem->getContentSize().height*0.5));
    menuitem->addChild(text);
    
    return menuitem;
}

CCLabelTTF* createTTF(const char* ttf,float size,float pox,float poy,CCPoint anpot,bool bscale)
{
    CCLabelTTF* labelttf = CCLabelTTF::create(ttf, "Marker Felt", size);
    labelttf->setAnchorPoint(anpot);
    labelttf->setPosition(ccp(pox,poy));
    if(bscale) labelttf->setPosition(getacPos(pox, poy));
    if(bscale) setSpriteScale(labelttf);
    
    return labelttf;
}

CCProgressTimer* createProgress(const char* spname,float pox,float poy,float percent)
{
    CCSprite* timeprosp = createSprite(spname, 0, 0);
    CCProgressTimer* timepro = CCProgressTimer::create(timeprosp);
    timepro->setType(kCCProgressTimerTypeBar);
    timepro->setPosition(getacPos(pox, poy));
    timepro->setMidpoint(ccp(0,0));
    timepro->setBarChangeRate(ccp(1,0));
    timepro->setPercentage(percent);
    setSpriteScale(timepro);
    
    return timepro;
}

CCSprite* createRect(float rectwidth,float rectheight,ccColor3B col,float pox,float poy,bool bscale)
{
    CCSprite* rectsp = CCSprite::create();
    rectsp->setTextureRect(CCRect(0, 0, rectwidth, rectheight));
    rectsp->setColor(col);
    rectsp->setPosition(ccp(pox,poy));
    if(bscale) rectsp->setPosition(getacPos(pox, poy));
    if(bscale) setSpriteScale(rectsp);
    
    return rectsp;
}

void showPicNum(const char* numName,int mNum,CCNode* mNode,float pox,float poy,int tag,bool sc)
{
    char buff[32];
    sprintf(buff, "%d",mNum);
    string mNumstr = buff;
    
    int numCount = (int)mNumstr.length();
    for(int i = 0;i < numCount;i++)
    {
        string signum = mNumstr.substr(i,1);
        sprintf(buff, "%s%s.png",numName,signum.c_str());
        
        if(!sc)
        {
            CCSprite* numsp = CCSprite::create(buff);
            CCSize numsize = numsp->getContentSize();
            float posx = pox+(i+0.5-numCount/2.0)*numsize.width;
            
            numsp->setPosition(ccp(posx,poy));
            mNode->addChild(numsp,9,tag);
        }
        else
        {
            CCSprite* numsp = CCSprite::create(buff);
            numsp->setScale(mWinScale);
            CCSize numsize = numsp->getContentSize();
            float posx = pox+(i+0.5-numCount/2.0)*numsize.width;
            
            numsp->setPosition(getacPos(posx,poy));
            mNode->addChild(numsp,9,tag);
        }
    }
}

void showOnePicNum(const char* numName,int mNum,CCNode* mNode,float pox,float poy,int dir,int tag ,bool sc)
{
    char buff[32];
    sprintf(buff, "%d",mNum);
    string mNumstr = buff;
    
    int numCount = (int)mNumstr.length();
    for(int i = 0;i < numCount;i++)
    {
        string signum = mNumstr.substr(i,1);
        sprintf(buff, "%s%s.png",numName,signum.c_str());
        
        if(!sc)
        {
            CCSprite* numsp = CCSprite::create(buff);
            CCSize numsize = numsp->getContentSize();
            float posx;
            if(dir == NUMBERCENTER)
                posx = pox+(i+0.5-numCount/2.0)*numsize.width;
            else if(dir == NUMBERLEFT)
                posx = pox + i*(numsize.width);
            
            numsp->setPosition(ccp(posx,poy));
            mNode->addChild(numsp,9,tag);
        }
        else
        {
            CCSprite* numsp = CCSprite::create(buff);
            numsp->setScale(mWinScale);
            CCSize numsize = numsp->getContentSize();
            float posx;
            if(dir == NUMBERCENTER)
                posx = pox+(i+0.5-numCount/2.0)*numsize.width;
            else if(dir == NUMBERLEFT)
                posx = pox + i*(numsize.width);
            
            numsp->setPosition(getacPos(posx,poy));
            mNode->addChild(numsp,9,tag);
        }
    }
}

int getSystemTime()
{
    struct cc_timeval tv;
    CCTime::gettimeofdayCocos2d(&tv, NULL);
    return (int)tv.tv_sec;
}

void saveLastTime()
{
    char buff[32];
    sprintf(buff, "%s_LastTime",GameName);
    SaveIntegerToXML(buff,getSystemTime());
    SaveFlush;
}
int readLastTime()
{
    char buff[32];
    sprintf(buff, "%s_LastTime",GameName);
    return LoadIntegerFromXML(buff);
}

bool getHaveFirstGameRun()
{
    char buff[32];
    sprintf(buff, "%s_FirstRun",GameName);
    return LoadBooleanFromXML(buff);
}
void setHaveFirstGameRun(bool e)
{
    char buff[32];
    sprintf(buff, "%s_FirstRun",GameName);
    SaveBooleanToXML(buff,e);
    SaveFlush;
}

bool getHaveFirstShopRun()
{
    char buff[32];
    sprintf(buff, "%s_FirstShopRun",GameName);
    return LoadBooleanFromXML(buff);
}
void setHaveFirstShopRun(bool e)
{
    char buff[32];
    sprintf(buff, "%s_FirstShopRun",GameName);
    SaveBooleanToXML(buff,e);
    SaveFlush;
}

void saveHistoryScore(int score)
{
    char buff[64];
    for(int i = SCORELISTNUM;i >= 0;i--)
    {
        sprintf(buff, "%s_HisScore_%d",GameName,i);
        int hisscore = LoadIntegerFromXML(buff);
        if(score <= hisscore)
            break;
        else
        {
            SaveIntegerToXML(buff,score);
            sprintf(buff, "%s_HisScore_%d",GameName,i+1);
            SaveIntegerToXML(buff,hisscore);
            SaveFlush;
        }
    }
}
int readHightestScore()
{
    char buff[64];
    sprintf(buff, "%s_HisScore_0",GameName);
    return LoadIntegerFromXML(buff);
}
void saveHightestScore(int score)
{
    char buff[64];
    sprintf(buff, "%s_HisScore_0",GameName);
    SaveIntegerToXML(buff,score);
    SaveFlush;
}


int readGameVirgour()
{
    return LoadIntegerFromXML(CCString::createWithFormat("%s_GameVirgour",GameName)->getCString());
}
void saveGameVirgour(int virgour)
{
    SaveIntegerToXML(CCString::createWithFormat("%s_GameVirgour",GameName)->getCString(),virgour);
    SaveFlush;
}

int readGameTools(int tooltag)
{
    return LoadIntegerFromXML(CCString::createWithFormat("%s_GameTools_%d",GameName,tooltag)->getCString());
}
void saveGameTools(int tooltag,int toolnum)
{
    SaveIntegerToXML(CCString::createWithFormat("%s_GameTools_%d",GameName,tooltag)->getCString(),toolnum);
    SaveFlush;
}

int readGameLevel()
{
    char buff[64];
    sprintf(buff, "%s_GameLevel",GameName);
    return LoadIntegerFromXML(buff);
}
void saveGameLevel(int gamelevel)
{
    char buff[64];
    sprintf(buff, "%s_GameLevel",GameName);
    SaveIntegerToXML(buff,gamelevel);
    SaveFlush;
}

void saveBackStepTimes(int times)
{
    SaveIntegerToXML("BackStepTimes",times);
    SaveFlush;
}
int readBackStepTimes()
{
    return LoadIntegerFromXML("BackStepTimes");
}

bool haveSoundEffect()
{
    char buff[64];
    sprintf(buff, "%s_GameSound",GameName);
    return LoadBooleanFromXML(buff);
}
bool haveMuicsEffect()
{
    char buff[64];
    sprintf(buff, "%s_GameMuics",GameName);
    return LoadBooleanFromXML(buff);
}
void saveHaveSoundEffect(bool e)
{
    char buff[64];
    sprintf(buff, "%s_GameSound",GameName);
    SaveBooleanToXML(buff,e);
    SaveFlush;
    
    if(e)
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
    else
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
    
}
void saveHaveMuicsEffect(bool e)
{
    char buff[64];
    sprintf(buff, "%s_GameMuics",GameName);
    SaveBooleanToXML(buff,e);
    SaveFlush;
    
    if(e)
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
    else
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
}

bool readAchievement(int tag)
{
    char buff[64];
    sprintf(buff, "IsGotAchievement_%d",tag);
    return LoadBooleanFromXML(buff);
}
void saveAchievement(int tag)
{
    char buff[64];
    sprintf(buff, "IsGotAchievement_%d",tag);
    SaveBooleanToXML(buff,true);
    SaveFlush;
}




