//
//  Shop.cpp
//  Timo
//
//  Created by YUN on 14-12-30.
//
//

#include "Shop.h"
#include "Funtion.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#else
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#include "HelloWorldScene.h"

static int buyTag = -1;

//0.1   5
//2    1
//4     4
//5     10
//6     18
//8    32
//10    50
//15    100
const float money[8] = {0.1,2,4,5,6,8,10,15};

static Shop* sharedInstatShop = NULL;

Shop::Shop()
:m_bcantouch(true)
{
    m_bItemMenu = false;
    sharedInstatShop = this;
}
Shop::~Shop()
{
    sharedInstatShop = NULL;
}

Shop* Shop::shared()
{
    return sharedInstatShop;
}

Shop* Shop::create(int kind)
{
    Shop* dia = new Shop();
    if(dia && dia->init())
    {
        dia->autorelease();
        dia->m_pKind = kind;
        return dia;
    }
    CC_SAFE_DELETE(dia);
    return NULL;
}

void Shop::onEnter()
{
    CCLayer::onEnter();
    
    initBg();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, true);
}
void Shop::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

void Shop::initBg()
{
    CCLayerColor* collayer = CCLayerColor::create(ccc4(0, 0, 0, 120));
    this->addChild(collayer);
    
    if(m_pKind== 1)
    {
        CCSprite* buyItemBG = createSprite("libao.png", 320, 568);
        this->addChild(buyItemBG,1,BuyItemBgTag);
        
        itemMenu = CCMenu::create();
        itemMenu->setPosition(CCPointZero);
        buyItemBG->addChild(itemMenu,2);
        
        CCMenuItemImage* buyitembtn = createMenu("btn.png", "btn.png", "buytext.png",this, menu_selector(Shop::buyGold), 284, 534-460,false);
        itemMenu->addChild(buyitembtn,1,ITEMNUM);
        
        CCMenuItemImage* closebtn = CCMenuItemImage::create("closebtn.png", "closebtn.png",this,menu_selector(Shop::exit));
        closebtn->setPosition(ccp(530,534-30));
        itemMenu->addChild(closebtn,2,2);
        
        return;
    }
    
    CCSprite* buyItemBG = createSprite("buyitembg.png", 320, 568);
    this->addChild(buyItemBG,1,BuyItemBgTag);
    
    itemMenu = CCMenu::create();
    itemMenu->setPosition(CCPointZero);
    buyItemBG->addChild(itemMenu,2);
    
    for(int i = 0;i < ITEMNUM;i++)
    {
        const char* moneytext = CCString::createWithFormat("money%d.png",(int)money[i])->getCString();
        CCMenuItemImage* buyitembtn = createMenu("btn.png", "btn.png", moneytext,this, menu_selector(Shop::buyGold), 440,699-(90+i*78),false);
        itemMenu->addChild(buyitembtn,1,i);
    }
    
    CCMenuItemImage* closebtn = CCMenuItemImage::create("closebtn.png", "closebtn.png",this,menu_selector(Shop::exit));
    closebtn->setPosition(ccp(507,699-20));
    itemMenu->addChild(closebtn,2,2);
    
}


void Shop::removeTinyLoadingDelay()
{
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
    
}

void Shop::buyGold(CCObject* obj)
{
    
    if(!m_bcantouch)
        return;
    
    m_bcantouch = false;
    
    CCMenuItemImage* mm = (CCMenuItemImage*)obj;
    buyTag = mm->getTag();
    
#if testMode
    HelloWorld::g_buyItemSuccess[buyTag] = 1;
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Shop::shared()->m_bcantouch = true;
    
    HelloWorld::g_buyItemSuccess[buyTag] = 1;
    if(Shop::shared() && Shop::shared()->m_pKind==1)
    {
        Shop::shared()->exit(NULL);
    }
#else
    /*
    JniMethodInfo jmi;
    
    if(JniHelper::getStaticMethodInfo(jmi ,"IAP/IAPJni" ,"orderBomb" ,"(I)V"))
    {
        jmi.env->CallStaticVoidMethod(jmi.classID , jmi.methodID, buyTag);
    }
     */
    
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/game/mmmmcmg/zwdzz","getIntence","()Ljava/lang/Object;");
    //CCLog("开始调用!");
    jobject jobj=NULL;
    if (isHave)
    {
        jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    //CCLog("取得jobj");
    isHave = JniHelper::getMethodInfo(minfo,"com/game/mmmmcmg/zwdzz","orderBomb","(I)V");
    //CCLog("处理中!");
    std::cout<<isHave<<std::endl;
    if (isHave)
    {
        //CCLog("接收!");
        minfo.env->CallVoidMethod(jobj, minfo.methodID,buyTag);
        CCLog("完成!");
    }
    else
    {
        // CCLog("jni-java函数执行完毕");
    }

#endif
#endif
}

void Shop::exit(cocos2d::CCObject *obj)
{
    this->removeFromParent();
}

bool Shop::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bItemMenu = itemMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}
void Shop::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_bItemMenu)
        itemMenu->ccTouchMoved(pTouch, pEvent);
}
void Shop::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if(m_bItemMenu)
        itemMenu->ccTouchEnded(pTouch, pEvent);
    
    m_bItemMenu = false;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
    void Java_com_game_mmmmcmg_zwdzz_orderBombSuccess(JNIEnv *env,jclass thiz)
    {
        
        Shop::shared()->m_bcantouch = true;
        
        HelloWorld::g_buyItemSuccess[buyTag] = 1;
        if(Shop::shared() && Shop::shared()->m_pKind==1)
        {
            Shop::shared()->exit(NULL);
        }
        
    }
    
    void Java_com_game_mmmmcmg_zwdzz_orderFaild()
    {
        Shop::shared()->m_bcantouch = true;
    }
}
#endif


