//
//  LinesSprite.h
//  Lines
//
//  Created by CpyShine on 13-4-27.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _LinesSprite_H
#define _LinesSprite_H

#include "cocos2d.h"

#include "LinesConfig.h"

using namespace cocos2d;

class LinesSprite :public CCSprite {
    
    
public:
    
    LinesProperty s_property;
    
    int type;
    
    void initWith(LinesProperty _p,int _type){
        s_property = _p;
        type = _type+1;
        
        std::string s;
        switch (_type) {
            case 0:
                s="chess0.png";
                break;
            case 1:
                s="chess1.png";
                break;
            case 2:
                s="chess2.png";
                break;
            case 3:
                s="chess3.png";
                break;
            case 4:
                s="chess4.png";
                break;
            case 5:
                s="chess5.png";
                break;
            case 6:
                s="chess6.png";
                break;
            default:
                break;
        }
        
        this->initWithFile(s.c_str());
        this->setScale(2.0);
//        this->setVisible(true);
    }
    
    void LS_runMoveAction(CCSequence * action){
        this->stopAllActions();
        this->setScale(2.0);
        CCCallFunc * callfunc = CCCallFunc::create(this,callfunc_selector(LinesSprite::LS_moveEnd));
        CCSequence * sequence = CCSequence::create(action,callfunc);
        this->runAction(sequence);
    }
    
    void LS_moveEnd();
    
    void LS_selected(){
        this->stopAllActions();
        
        CCScaleTo * scaleTo = CCScaleTo::create(0.5, 1.2);
        CCScaleTo * scaleBack = CCScaleTo::create(0.5, 2);
        CCSequence * sequence = CCSequence::create(scaleTo,scaleBack,NULL);
        CCRepeatForever * repeateF = CCRepeatForever::create(sequence);
        
        this->getActionManager()->addAction(repeateF, this, false);
    }
    void LS_disSelect(){
        if (this->numberOfRunningActions()==0) {
            return;
        }
        this->stopAllActions();
        this->setScale(2);
    }
    
    void LS_disappear(){
        this->removeFromParent();
    }
    
    virtual bool init(void);
    virtual void draw(void);
    CREATE_FUNC(LinesSprite);
};

#endif