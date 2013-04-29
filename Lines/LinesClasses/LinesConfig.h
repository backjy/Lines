//
//  LinesConfig.h
//  Lines
//
//  Created by CpyShine on 13-4-26.
//
//

#ifndef Lines_LinesConfig_h
#define Lines_LinesConfig_h


#include "cocos2d.h"

struct LinesProperty {
    int x=0;
    int y=0;
//    int type=0;
};

class LinesSprite_Protocol {
    
public:
    virtual void LineSpriteMoveEnd()=0;
};

class AStarProperty :public cocos2d::CCNode{
    
    int value_G;
    int value_H;
    int value_F;
public:
    
    bool isClosed;
    
    LinesProperty curentNode;
    AStarProperty * parentNode;
    
    AStarProperty(){
        value_H = 0;
        value_G = 0;
        value_F = 0;
        isClosed = false;
    }
    
    ~AStarProperty(){
    
    }
    
    CREATE_FUNC(AStarProperty);
    
    virtual bool init(void){
        return true;
    }
    
    inline void setValue_G(int _g){
        value_G = _g;
        value_F = value_G+value_H;
    }
    inline void setValue_H(int _h){
        value_H = _h;
        value_F = value_G+value_H;
    }
    inline int A_getF(){ return value_F;}
    inline int A_getG(){ return value_G;}
    inline int A_getH(){ return value_H;}
};

#endif
