#include "HelloWorldScene.h"

#include "Funtion.h"
#include "GameStartLayer.h"
#include "GameGuide.h"
#include "PassGameLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;


const float elementPos[19][2] = {{110,410},{110,410+122},{110,410+122*2},{215,350},{215,350+122},{215,350+122*2},{215,350+122*3},{320,288},{320,288+122},{320,288+122*2},
                                {320,288+122*3},{320,288+122*4},{425,350},{425,350+122},{425,350+122*2},{425,350+122*3},{530,410},{530,410+122},{530,410+122*2}};

const int elementTag[19] = {28,29,30,23,24,25,26,18,19,20,21,22,14,15,16,17,10,11,12};
const int elementID[3] = {1,3,9};

const char* levelName[8] = {"9","27","81","243","729","2187","6561","19683"};
const int levelNum[7] = {9,27,81,243,719,2187,6561};


static HelloWorld* HelloSharder;

int HelloWorld::g_buyItemSuccess[ITEMNUM];

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    HelloSharder = layer;
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld* HelloWorld::getsharder()
{
    if(HelloSharder)
        return HelloSharder;
    
    return NULL;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    FrameNode = CCNode::create();
    FrameNode->setPosition(CCPointZero);
    this->addChild(FrameNode,22);
    
    elementNode = CCNode::create();
    elementNode->setPosition(CCPointZero);
    FrameNode->addChild(elementNode,10);
    
    for(int i = 0;i > ITEMNUM;i++)
        g_buyItemSuccess[i] = 0;
    
    GameBg();
    
    return true;
}

void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    
    seletePoint = -1;
    m_bcombining = false;
    mCurScore = 0;
    m_bGameOver = false;
    m_bPassGame = false;
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
void HelloWorld::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void HelloWorld::GameBg()
{
    
    if(!getHaveFirstGameRun())
    {
        saveHaveSoundEffect(true);
        setHaveFirstGameRun();
        saveGameVirgour(5);
        GameGuide* guidelay = GameGuide::create();
        this->addChild(guidelay,100);
        saveLastTime();
    }
    
    bool bhavesound = true;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo jmi;
    
    jboolean jbl;
    
    if(JniHelper::getStaticMethodInfo(jmi ,"com/game/mmmmcmg/zwdzz" ,"isSound" ,"()Z"))
    {
        jbl = jmi.env->CallStaticBooleanMethod(jmi.classID , jmi.methodID);
        
        CCLog("jbl=====%d",jbl);
        if(jbl == 0)
            bhavesound = false;
        else
            bhavesound = true;
    }
#endif
    
    CCLog("bhavesound=======%d",bhavesound);
    
    saveHaveMuicsEffect(bhavesound);
    saveHaveSoundEffect(bhavesound);
    
    
//    if(haveMuicsEffect())
//        saveHaveMuicsEffect(true);
//    else
//        saveHaveMuicsEffect(false);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("soundeffect.mp3", true);
    
    checkBuyVirgour();
    
    m_vigour = readGameVirgour();
    
    if(m_vigour <= 0)
    {
        GameStartLayer* lay = GameStartLayer::create();
        this->addChild(lay,30);
        Shop* shoplay = Shop::create();
        this->addChild(shoplay,31);
    }
    
    CCSprite* gamebg = createSprite("gameBG.png", 320, 568);
    gamebg->setScaleX(mWinScaleX);
    gamebg->setScaleY(mWinScaleY);
    this->addChild(gamebg);
    
    
    CCSprite* recordComNum = createSprite("recordComNum.png", 116, 175);
    this->addChild(recordComNum,22);
    CCLabelTTF* recordComNumtext = createTTF(levelName[readGameLevel()], 30, 116, 195);
    recordComNumtext->setColor(ccBLACK);
    this->addChild(recordComNumtext,22,18);
    
    CCSprite* gameScroe = createSprite("gameScroe.png", 512, 44);
    this->addChild(gameScroe,22);
    CCSprite* gameScroeText = createSprite("scoreText.png", 440, 44);
    this->addChild(gameScroeText,22);
    CCLabelTTF* scroetext = createTTF(CCString::createWithFormat("%d",mCurScore)->getCString(), 30, 518, 44,ccp(0,0.5));
    this->addChild(scroetext,22,19);
    
    CCSprite* hightestScroe = createSprite("gameScroe.png", 512, 127);
    this->addChild(hightestScroe,22);
    CCSprite* hightestScroeText = createSprite("hightestScoreText.png", 455, 127);
    this->addChild(hightestScroeText,22);
    
    CCLabelTTF* hiscroetext = createTTF(CCString::createWithFormat("%d",readHightestScore())->getCString(), 30, 518, 127,ccp(0,0.5));
    this->addChild(hiscroetext,22,20);
    
    
    CCSprite* vigourFrame = createSprite("vigourFrame.png", 165, 60);
    this->addChild(vigourFrame,32,555);
    CCSprite* vigouradd = createSprite("addBtn.png", 165+160, 60);
    this->addChild(vigouradd,33);
    
    CCSprite* comTip = createSprite("comTip.png", 505, 960);
    this->addChild(comTip,2);
    CCSprite* comTipText = createSprite("comTipText.png", 505, 960);
    this->addChild(comTipText,2);
    
    returnBtn = createSprite("goOnBtn.png", 100, 960);
    this->addChild(returnBtn,3);
    CCSprite* returnText = CCSprite::create("returnText.png");
    returnText->setPosition(ccp(returnBtn->getContentSize().width*0.5,returnBtn->getContentSize().height*0.5));
    returnBtn->addChild(returnText);
    
    CCSprite* elementFrame = createSprite("elmentFrame.png", 320, 532);
    FrameNode->addChild(elementFrame,1);
    
    srand((unsigned)time(NULL));
    
    createElement();
    
    showVirgour();
    
    this->schedule(schedule_selector(HelloWorld::checkBuyVirgour), 0.1);
    
}

void HelloWorld::checkBuyVirgour()
{
    for(int i = 0;i < ITEMNUM;i++)
    {
        if(g_buyItemSuccess[i]!=0)
        {
            g_buyItemSuccess[i] = 0;
            int times[ITEMNUM] = {1,21,44,58,72,100,130,210};
            m_vigour += times[i];
            saveGameVirgour(m_vigour);
            showVirgour();
        }
    }
    
    if(getSystemTime()-readLastTime() >= 60*10 && m_vigour < 5)
    {
        m_vigour += (getSystemTime()-readLastTime())/600;
        
        if(m_vigour >= 5) m_vigour = 5;
        saveLastTime();
        saveGameVirgour(m_vigour);
        showVirgour();
    }
    
    if(m_vigour >= 5)
    {
        saveLastTime();
    }
}

void HelloWorld::showVirgour()
{
    for(int i = 0;i < 5;i++)
    {
        if(this->getChildByTag(100+i) != NULL)
            this->removeChildByTag(100+i);
    }
    if(m_vigour <= 5)
    {
        for(int i = 0;i < m_vigour;i++)
        {
            CCSprite* virgoursp = createSprite("vigourLight.png", 60+i*55, 62);
            this->addChild(virgoursp,32,100+i);
        }
    }
    else
    {
        CCSprite* virgoursp = createSprite("vigourLight.png", 60, 62);
        this->addChild(virgoursp,32,100);
        
        
        CCLabelTTF* vircount = createTTF(CCString::createWithFormat("X %d",m_vigour)->getCString(), 25, 95, 62,ccp(0,0.5));
        this->addChild(vircount,33,101);
    }
    
}

void HelloWorld::restratGame()
{
    m_vigour--;
    if(m_vigour <= 0) m_vigour = 0;
    m_bPassGame = false;
    mCurScore = 0;
    showCurScore();
    elementNode->removeAllChildren();
    createElement();
    
    saveGameVirgour(m_vigour);
    showVirgour();
}

void HelloWorld::showRecordCom(int comNum)
{
    int curlevel = readGameLevel();
    while (1) {
        if(comNum > levelNum[curlevel])
        {
            curlevel++;
        }
        else
            break;
    }
    
    saveGameLevel(curlevel);
    
    CCLabelTTF* recordComNumtext = (CCLabelTTF*)this->getChildByTag(18);
    recordComNumtext->setString(levelName[curlevel]);
    
}

void HelloWorld::createElement(int eID,bool brunAction)
{
    
    char buff[16];
    for(int i = 0;i < 19;i++)
    {
        int randNum = rand()%3;
        
        if(elementNode->getChildByTag(elementTag[i]) == NULL)
        {
            if(eID == -1)
                sprintf(buff, "%d.png",elementID[randNum]);
            else
                sprintf(buff, "%d.png",eID);
            ElementSprite* element = ElementSprite::create(buff, elementPos[i][0], elementPos[i][1]);
            element->setTag(elementTag[i]);
            if(eID == -1)
                element->setelementID(elementID[randNum]);
            else
                element->setelementID(eID);
            elementNode->addChild(element);
            
            if(brunAction)
            {
                element->setScale(mWinScale*0.7);
                CCScaleTo *s = CCScaleTo::create(0.1, mWinScale);
                element->runAction(s);
            }
        }
    }
}

bool HelloWorld::checkPointTouch(int p,bool bcheckgameover)
{
    bool bgameover = false;
    //CCLog("%d",p);
    ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(p);
    
    int selectEleID = element->getelementID();
    
    //六个方向，第一个
    int dirTag = p-5;
    if(elementNode->getChildByTag(dirTag) !=NULL && !findVec(dirTag) && ((ElementSprite*)elementNode->getChildByTag(dirTag))->getelementID() == selectEleID)
    {
        choseVec.push_back(dirTag);
        checkPointTouch(dirTag,bcheckgameover);
    }
    
    dirTag = p-4;
    if(elementNode->getChildByTag(dirTag) !=NULL && p!=22 && !findVec(dirTag) && ((ElementSprite*)elementNode->getChildByTag(dirTag))->getelementID() == selectEleID)
    {
        choseVec.push_back(dirTag);
        checkPointTouch(dirTag,bcheckgameover);
    }
    
    dirTag = p+5;
    if(elementNode->getChildByTag(dirTag) !=NULL && !findVec(dirTag) && ((ElementSprite*)elementNode->getChildByTag(dirTag))->getelementID() == selectEleID)
    {
        choseVec.push_back(dirTag);
        checkPointTouch(dirTag,bcheckgameover);
    }
    
    dirTag = p+4;
    if(elementNode->getChildByTag(dirTag) !=NULL && p!=18 && !findVec(dirTag) && ((ElementSprite*)elementNode->getChildByTag(dirTag))->getelementID() == selectEleID)
    {
        choseVec.push_back(dirTag);
        checkPointTouch(dirTag,bcheckgameover);
    }
    
    dirTag = p-1;
    if(elementNode->getChildByTag(dirTag) !=NULL && p!=18 && p!=23 &&!findVec(dirTag) && ((ElementSprite*)elementNode->getChildByTag(dirTag))->getelementID() == selectEleID)
    {
        choseVec.push_back(dirTag);
        checkPointTouch(dirTag,bcheckgameover);
    }
    
    dirTag = p+1;
    if(elementNode->getChildByTag(dirTag) !=NULL && p!=17 && p!=22 && !findVec(dirTag) && ((ElementSprite*)elementNode->getChildByTag(dirTag))->getelementID() == selectEleID)
    {
        choseVec.push_back(dirTag);
        checkPointTouch(dirTag,bcheckgameover);
    }
    
    
    if(!bcheckgameover)
        endCheckPointT();
    else
    {
        if(choseVec.size() < 3)
            bgameover = true;
    }
    
    return bgameover;
}

void HelloWorld::endCheckPointT()
{
    vector<int>::iterator it;
    for(it = choseVec.begin();it!=choseVec.end();it++)
    {
        ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(*it);
        element->setScale(0.9*mWinScale);
        
        CCSprite* seleteElment = CCSprite::create("seleteElment.png");
        seleteElment->setPosition(ccp(element->getContentSize().width*0.5,element->getContentSize().height*0.5));
        element->addChild(seleteElment,1);
        
        if(choseVec.size() >= 3 && (*it) == elementTag[seletePoint])
        {
            CCSprite* seletePoint = CCSprite::create("seletePoint.png");
            seletePoint->setPosition(ccp(element->getContentSize().width*0.5,element->getContentSize().height*0.5));
            element->addChild(seletePoint,1);
        }
    }
    
   // comTipShow();
    
}

bool HelloWorld::findVec(int p)
{
    bool b = false;
    vector<int>::iterator it;
    for(it = choseVec.begin();it != choseVec.end();it++)
    {
        if((*it) == p)
        {
            b = true;
            break;
        }
    }
    
    return b;
}

void HelloWorld::comTipShow()
{
    
    if(this->getChildByTag(1000) != NULL)
        this->removeChildByTag(1000);
    
    if(choseVec.size() >= 3)
    {
        int eid = ((ElementSprite*)elementNode->getChildByTag(elementTag[seletePoint]))->getelementID();
        if(choseVec.size() >= 9)
            eid = 9*eid;
        else if(choseVec.size() >= 3)
            eid = 3*eid;
        
        char buff[32];
        sprintf(buff, "%d.png",eid);
        CCSprite* tipsp = createSprite(buff, 503, 958);
        this->addChild(tipsp,3,1000);
    }
}

void HelloWorld::clearSeleteFrame()
{
    vector<int>::iterator it;
    for(it = choseVec.begin();it != choseVec.end();it++)
    {
        ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(*it);
        element->setScale(mWinScale);
        element->removeAllChildren();
    }
}

void HelloWorld::showCurScore()
{
    CCLabelTTF* curscorettf = (CCLabelTTF*)this->getChildByTag(19);
    curscorettf->setString(CCString::createWithFormat("%d",mCurScore)->getCString());
    
    if(mCurScore > readHightestScore())
    {
        saveHightestScore(mCurScore);
        CCLabelTTF* hightttf = (CCLabelTTF*)this->getChildByTag(20);
        hightttf->setString(CCString::createWithFormat("%d",mCurScore)->getCString());
    }
    
}

void HelloWorld::combinElement()
{
    if(choseVec.size() < 3)
        return;
    
    m_bcombining = true;
    
    //CCLog("choseVec.size():  %d",choseVec.size());
    
    ElementSprite* elementSelete = (ElementSprite*)elementNode->getChildByTag(elementTag[seletePoint]);
    elementSelete->setZOrder(10);
    
    mCurScore += elementSelete->getelementID();
    showCurScore();
    
    float i = 0.1;
    vector<int>::iterator it;
    for(it = choseVec.begin();it != choseVec.end();it++)
    {
        if(*it == elementTag[seletePoint])
            continue;
        
        CCCallFuncND* callback = CCCallFuncND::create(this, callfuncND_selector(HelloWorld::comElementCallback),&(*it));
        CCAction* moveto = CCMoveTo::create(0.2+i, elementSelete->getPosition());
        ((ElementSprite*)elementNode->getChildByTag(*it))->runAction(CCSequence::create((CCActionInterval*)moveto,callback,NULL));
        
        i += 0.05;
    }
    
}

void HelloWorld::comElementCallback(CCNode* sender, void* data)
{
    static int comNum = 0;
    comNum++;
    int tag = *((int*)data);
    
    elementNode->removeChildByTag(tag);
    createElement();
    
    ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(elementTag[seletePoint]);
    int startid = element->getelementID();
    
    if(comNum == 8 || comNum == 2)
    {
        int eId = element->getelementID();
        eId = eId*3;
        
        elementNode->removeChildByTag(elementTag[seletePoint]);
        
        createElement(eId,false);
        ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(elementTag[seletePoint]);
        element->setZOrder(10);
        
        showRecordCom(eId);
    }
    //CCLog("comNum:  %d",comNum);
    
    mCurScore += startid;
    showCurScore();
    
    if(comNum == choseVec.size()-1)
    {
        ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(elementTag[seletePoint]);
        clearSeleteFrame();
        choseVec.clear();
        seletePoint = -1;
        comNum = 0;
        element->setZOrder(1);
        
        m_bcombining = false;
        
        comTipShow();
        
        if(!m_bPassGame && element->getelementID() == 2187)
        {
            m_bPassGame = true;
            PassGameLayer* passlayer = PassGameLayer::create();
            this->addChild(passlayer,100);
        }
        
        checkGameOver();
    }
}

void HelloWorld::checkGameOver()
{
    bool bgameover = true;
    
    if(mCurScore > readHightestScore())
        saveHightestScore(mCurScore);
    
    for(int i = 0;i < 19;i++)
    {
        bgameover = checkPointTouch(elementTag[i],true);
        choseVec.clear();
        if(!bgameover)
        {
            break;
        }
    }
    
    if(bgameover)
    {
        CCLog("Gameover");
        m_bGameOver = true;
        showGameOver();
    }
    
}

void HelloWorld::showGameOver()
{
    CCSprite* gamebg = createSprite("gameBG.png", 320, 568);
    gamebg->setScaleX(mWinScaleX);
    gamebg->setScaleY(mWinScaleY);
    this->addChild(gamebg,21,36);
    
    FrameNode->setScale(0.7);
    FrameNode->setPosition(getacPos(0, 808));
    
    CCSprite* gameoverText = createSprite("gameOverText.png", 320, 876);
    this->addChild(gameoverText,22,37);
    
    
    CCSprite* newgameBtn = createSprite("newGameBtn.png", 457, 684);
    this->addChild(newgameBtn,22,35);
    CCSprite* menuText = CCSprite::create("newGameText.png");
    menuText->setPosition(ccp(newgameBtn->getContentSize().width*0.5,newgameBtn->getContentSize().height*0.5));
    newgameBtn->addChild(menuText);
    
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if(m_bGameOver)
    {
        CCSprite* newgamebtn = (CCSprite*)this->getChildByTag(35);
        if(newgamebtn->boundingBox().containsPoint(pTouch->getLocation()))
        {
            newgamebtn->setScale(mWinScale*0.9);
        }
        return true;
    }
    
    if(m_bcombining)
        return true;
    
    bool btouchNull = true;
    for(int i = 0;i < 19;i++)
    {
        ElementSprite* element = (ElementSprite*)elementNode->getChildByTag(elementTag[i]);
        if(element->boundingBox().containsPoint(pTouch->getLocation()))
        {
            if(seletePoint != i)
            {
                clearSeleteFrame();
                choseVec.clear();
                seletePoint = i;
                choseVec.push_back(elementTag[i]);
                checkPointTouch(elementTag[i]);
            }
            else
            {
                combinElement();
            }
            
            btouchNull = false;
            
            break;
        }
    }
    
    if(btouchNull)
    {
        clearSeleteFrame();
        choseVec.clear();
        seletePoint = -1;
    }
    
    comTipShow();
    
    
    if(returnBtn->boundingBox().containsPoint(pTouch->getLocation()))
    {
        returnBtn->setScale(mWinScale*0.9);
    }
    
    return true;
}
void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite* virgourframe = (CCSprite*)this->getChildByTag(555);
    if(virgourframe && virgourframe->boundingBox().containsPoint(pTouch->getLocation()))
    {
        Shop* shoplay = Shop::create();
        this->addChild(shoplay,100);
    }
    
    if(m_bGameOver)
    {
        CCSprite* newgamebtn = (CCSprite*)this->getChildByTag(35);
        if(newgamebtn->boundingBox().containsPoint(pTouch->getLocation()))
        {
            
            if(m_vigour == 0)
            {
                m_vigour = 0;
                Shop* shoplay = Shop::create();
                this->addChild(shoplay,30);
                
            }
            else
            {
                m_bGameOver = false;
                FrameNode->setScale(1);
                FrameNode->setPosition(CCPointZero);
                this->removeChildByTag(35);
                this->removeChildByTag(36);
                this->removeChildByTag(37);
                restratGame();
            }
        }
        else
            newgamebtn->setScale(mWinScale);
        
        return;
    }
    
    returnBtn->setScale(mWinScale);
    if(returnBtn->boundingBox().containsPoint(pTouch->getLocation()))
    {
        //do something
        GameStartLayer* lay = GameStartLayer::create();
        this->addChild(lay,30);
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
