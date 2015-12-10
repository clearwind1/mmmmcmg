//
//  ElementSprite.cpp
//  sangu
//
//  Created by YUN on 15/3/9.
//
//

#include "ElementSprite.h"
#include "Funtion.h"

ElementSprite::ElementSprite()
{
    melementID = -1;
    
}

ElementSprite::~ElementSprite()
{
    
}

ElementSprite* ElementSprite::create(const char *spname, float pox, float poy)
{
    ElementSprite* element = new ElementSprite();
    if(element && element->initWithFile(spname))
    {
        element->autorelease();
        element->setScale(mWinScale);
        element->setPosition(getacPos(pox, poy));
        return element;
    }
    
    CC_SAFE_DELETE(element);
    return NULL;
}