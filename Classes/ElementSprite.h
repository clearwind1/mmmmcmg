//
//  ElementSprite.h
//  sangu
//
//  Created by YUN on 15/3/9.
//
//

#ifndef __sangu__ElementSprite__
#define __sangu__ElementSprite__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ElementSprite : public CCSprite
{
public:
    ElementSprite();
    ~ElementSprite();
    
    static ElementSprite* create(const char* spname,float pox,float poy);
    
    CC_SYNTHESIZE(int, melementID, elementID);
    
};

#endif /* defined(__sangu__ElementSprite__) */
