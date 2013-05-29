//
//  LinesLayer.cpp
//  Lines
//
//  Created by CpyShine on 13-4-26.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "LinesLayer.h"

#include "LinesConfig.h"
#include "LinesDateHandle.h"
#include "LinesSprite.h"

static LinesLayer * _sharedLinesSprite=NULL;

LinesLayer * LinesLayer::getSharedLinesLayer(){
    if (!_sharedLinesSprite) {
        _sharedLinesSprite = LinesLayer::create();
    }
    return _sharedLinesSprite;
}

bool LinesLayer::init(void){
    if (!CCLayer::init()) {
        return false;
    }
    _sharedLinesSprite = this;
    
    this->setAnchorPoint(ccp(0,0));
    
    dataHandle = NULL;
    
    nextLabel = NULL;
    
    return true;
}

void LinesLayer::onEnter(void){
    CCLayer::onEnter();
    
    //set touch enable = yes,and delegate is oneByone
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
    
}

void LinesLayer::onEnterTransitionDidFinish(void){
    CCLayer::onEnterTransitionDidFinish();
}

void LinesLayer::onExit(void){
    CCLayer::onExit();
}

bool LinesLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    if (!ll_canDoCheck) {//
        return false;
    }
    
    
    CCPoint touchLocation = pTouch->getLocation();
    
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
//    CCLog("TouchLocation:%f,%f",touchLocation.x,touchLocation.y);
//    CCLog("TouchLocation:%f,%f",local.x,local.y);
    
    int _index = dataHandle->LD_getIndexAtPosition(local, width/2);
    if (_index>=0) {
        
        LinesProperty _pro = dataHandle->LD_convertIndexToLinesProperty(_index);
//        CCLog("x:%d,y:%d",_pro.x,_pro.y);
        
        CCLOG("select property is :%d",dataHandle->LD_getStateAtIndex(_index));
        
        if (!dataHandle->LD_getStateAtIndex(_index)) {//如果返回是 false 就可以做move检查
            // do move to
            LL_doCheckMoveAndSoON(_pro);
//            dataHandle->LD_ShowDebug();
            
        }else{// 得到当前的方块 然后设置currentlinesSprite
            
            if (currentSelectSprite) {
                currentSelectSprite->LS_disSelect();
            }
            currentSelectSprite = LL_getCurrentSelectLinesSprite(_pro);
            
            if (currentSelectSprite) {
                currentSelectSprite->LS_selected();
            }
//            ll_canDoCheck = true;
        }
        
    }else{
        if (currentSelectSprite) {
            currentSelectSprite->LS_disSelect();
            currentSelectSprite = NULL;
        }
//        ll_canDoCheck = true;
    }
    
    
//    ll_canDoCheck = true;
    
    return false;
}

void LinesLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}
void LinesLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
}
void LinesLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    
}


void LinesLayer::draw(void){
    CCLayer::draw();
    for (int x=0; x<9; x++) {
        CCPoint pos1 = ccp(0,width*x);
        CCPoint pos2 = ccp(9*height,width*x);
        ccDrawLine(pos1, pos2);
    }
    for (int y=0; y<9; y++) {
        CCPoint pos1 = ccp(height*y,0);
        CCPoint pos2 = ccp(height*y,9*width);
        ccDrawLine(pos1, pos2);
    }
}

LinesLayer::~LinesLayer(){
    _sharedLinesSprite = NULL;
    
    if (dataHandle) {
        delete dataHandle;
    }
}


#pragma mark - touch handle s

LinesSprite * LinesLayer::LL_getCurrentSelectLinesSprite(const LinesProperty &_pro){
    CCObject * _obj = NULL;
    LinesSprite * _sprite = NULL;
    CCARRAY_FOREACH(linesSpriteParent->getChildren(), _obj){
        _sprite = dynamic_cast<LinesSprite*>(_obj);
        if (_sprite) {
            if ((_sprite->s_property.x == _pro.x &&
                _sprite->s_property.y == _pro.y)) {
                break;
            }
        }
    }
    return _sprite;
}

void LinesLayer::LL_doCheckMoveAndSoON(const LinesProperty &start){
    
    if (currentSelectSprite) {//如果 currneselect 不为空
        
        CCArray * array = dataHandle->LD_calcWayFromeAtoB(start,
                                                          currentSelectSprite->s_property);
//        CCLOG("Array count %d",array->count());
        
        if (array->count()>0) {
            
            CCSequence * seq = dynamic_cast<CCSequence*>(array->objectAtIndex(0));
            
            if (!seq) {//如果sequence 为空 return
                return;
            }
            
            ll_canDoCheck = false;//
            
            currentSelectSprite->s_property = start;//把位置更新到 移动到的位置；
            int  _index = dataHandle->LD_getIndexAt(currentSelectSprite->s_property);
            dataHandle->LD_resetStateAtIndex(_index, currentSelectSprite->type);
            currentSelectSprite->LS_runMoveAction(seq);
        }
    }
}

void LinesLayer::LinesSpriteMoveEndDoCheck(){
    
    int count = dataHandle->LD_calcDisappear(currentSelectSprite->type,
                                             currentSelectSprite->s_property);
    if(count>1){
    
        LL_clearupUnusedSprite(count+1);
        dataHandle->LD_ShowDebug();
        totalscore += count;
        
        CCString * str = CCString::createWithFormat("Score:%04d",totalscore);
        std::string s = str->getCString();
        scoreLabel->setString(s.c_str());
        
    }else{
       LL_doAddLinesSprite(); 
    }
    
    ll_canDoCheck = true;
}

void LinesLayer::LL_clearupUnusedSprite(int count){
    if (LL_clearupUnusedSpriteAd()!=count && count) {
        LL_clearupUnusedSpriteAd();
    }
}

int LinesLayer::LL_clearupUnusedSpriteAd(){
    
    currentSelectSprite = NULL;
    
    CCObject * _obj = NULL;
    
    int count = 0;
    
    
    for (unsigned int i=0; i<linesSpriteParent->getChildrenCount(); i++) {
        
        _obj    = linesSpriteParent->getChildren()->objectAtIndex(i);
        
        LinesSprite * _sprite = dynamic_cast<LinesSprite*>(_obj);
        
        if(!_sprite) {  printf("The will disappear Sprite is NULL"); continue;}
        
        int _index = dataHandle->LD_getIndexAt(_sprite->s_property);
        
        if(_index<0 ){
            CCLOG("error !!!!!!_index<0");
        }
        
        int _value = dataHandle->LD_getStateAtIndex(_index);
        
//        printf("%d,%d:%d-%d ",_sprite->s_property.x,_sprite->s_property.y,_index,_value);
        if (_value==0) {
            
            _sprite->LS_disappear();
            count++;
//            printf("\n will disappear %d-%d \n",_index,_value);
        }
    }
    
//    CCARRAY_FOREACH(linesSpriteParent->getChildren(), _obj){
//        
//        
//        //        printf("%d,%d:%d-%d ",_sprite->s_property.x,_sprite->s_property.y,_index,_value);
//    }
    printf("\n");
    
    return --count;
}

void LinesLayer::LL_doAddLinesSprite(){
    
    
    for (int i=0; i<3; i++) {
        int _index = dataHandle->LD_calcAddSpriteAt();//
        
        if (_index<0) {
            LL_gameOver();
        }
        
//        code
        
        LinesSprite * sprite = LinesSprite::create();
        
        sprite->initWith(dataHandle->LD_convertIndexToLinesProperty(_index),
                         nextTypeArray[i]);
        
        sprite->setPosition(dataHandle->LD_getPositionAtIndex(_index));
        
        linesSpriteParent->addChild(sprite);
        
        dataHandle->LD_resetStateAtIndex(_index, sprite->type);
        
        if (dataHandle->LD_calcDisappear(sprite->type, sprite->s_property)) {
            LL_clearupUnusedSprite(0);
        }
        nextTypeArray[i] = arc4random() % 7;
    }
    
//    dataHandle->LD_ShowDebug();
//     ---------------------------------
    
    CCString * str = CCString::createWithFormat("Next->O:%d T:%d T:%d",
                                                nextTypeArray[0],nextTypeArray[1],nextTypeArray[2]);
    std::string s = str->getCString();
    
    nextLabel->setString(s.c_str());

}

void LinesLayer::LL_startGame(){
    
    if (dataHandle) {
        delete dataHandle;
        dataHandle = NULL;
    }
    
    totalscore = 0;
    
    dataHandle = new LinesDataHandle();
    
    CCTexture2D * texture =
    CCTextureCache::sharedTextureCache()->addImage("chess0.png");
    
    width   = texture->getPixelsWide() * 2;
    height  = texture->getPixelsHigh() * 2;
    
    dataHandle->initDateHandleWith(9, 9, width , height);
    
    currentSelectSprite = NULL;
    
    linesSpriteParent = CCNode::create();
    this->addChild(linesSpriteParent);
    linesSpriteParent->setAnchorPoint(ccp(0,0));
    linesSpriteParent->setPosition(0, 0);
    
    ll_canDoCheck = true;
    
    nextTypeArray = new int[5]();
    
    nextTypeArray[0] = arc4random() % 7;
    nextTypeArray[1] = arc4random() % 7;
    nextTypeArray[2] = arc4random() % 7;
    
    CCString * str = CCString::createWithFormat("Next->O:%d T:%d T:%d",
                                                 nextTypeArray[0],nextTypeArray[1],nextTypeArray[2]);
    std::string s = str->getCString();
    
    nextLabel  = CCLabelTTF::create(s.c_str(), "Thonburi", 24);
    
    nextLabel->setPosition(ccp(10, height * 10));
    nextLabel->setAnchorPoint(ccp(0, 0));
    this->addChild(nextLabel);
    
    scoreLabel = CCLabelTTF::create("Score:0000", "Thonburi", 24);
    scoreLabel->setPosition(ccp(width * 5, height * 10));
    scoreLabel->setAnchorPoint(ccp(0, 0));
    
    this->addChild(scoreLabel);
//    nextLabel->retain();

    
    LL_doAddLinesSprite();
}

void LinesLayer::LL_gameOver(){
//    if (nextLabel) {
//        nextLabel->removeFromParentAndCleanup(true);
//        nextLabel = NULL;
//    }
    
    CCLOG("GameOver!!!!!!!!!");
}



