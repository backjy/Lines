//
//  LinesLayer.h
//  Lines
//
//  Created by CpyShine on 13-4-26.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _LinesLayer_H
#define _LinesLayer_H

#include "cocos2d.h"
#include "LinesConfig.h"

using namespace cocos2d;

class LinesDataHandle;
class LinesSprite;

class LinesLayer :public CCLayer {
    
    LinesDataHandle * dataHandle;
    
    LinesSprite * currentSelectSprite;
    
    CCNode * linesSpriteParent;
    
    CCLabelTTF * nextLabel;
    CCLabelTTF * scoreLabel;
    
    float width;
    float height;
    
    bool ll_canDoCheck;
    
    int * nextTypeArray;
    
    int totalscore;
    
public:
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish(void);
    virtual void draw(void);
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    // default implements are used to call script callback if exist
    CREATE_FUNC(LinesLayer);
    
    virtual ~LinesLayer();
    
    static LinesLayer * getSharedLinesLayer();

    void LinesSpriteMoveEndDoCheck();
    
    LinesSprite * LL_getCurrentSelectLinesSprite(const LinesProperty &_pro);
    
    void LL_doCheckMoveAndSoON(const LinesProperty &start);
    
    void LL_clearupUnusedSprite(int count);
    
    int  LL_clearupUnusedSpriteAd();
    
    void LL_doAddLinesSprite();
    
    void LL_showNext();
    
    void LL_startGame();
    void LL_gameOver();
};

#endif