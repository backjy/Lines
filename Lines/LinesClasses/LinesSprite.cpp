//
//  LinesSprite.cpp
//  Lines
//
//  Created by CpyShine on 13-4-27.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "LinesSprite.h"
#include "LinesLayer.h"

bool LinesSprite::init(void){
    if (!CCSprite::init()) {
        return false;
    }
    
    return true;
}

void LinesSprite::draw(void){
    CCSprite::draw();
}

void LinesSprite::LS_moveEnd(){
    LinesLayer::getSharedLinesLayer()->LinesSpriteMoveEndDoCheck();
}