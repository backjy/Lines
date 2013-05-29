//
//  LinesDateHandle.cpp
//  Lines
//
//  Created by CpyShine on 13-4-26.
//
//

#include "LinesDateHandle.h"

#include <list.h>


#pragma mark - calc dissappear ,add functions

int LinesDataHandle::LD_calcAddSpriteAt(){
    int _index = arc4random() % total_count;
    int count = 0;
    while (LD_getStateAtIndex(_index)) {
        _index++;
        if (_index>(total_count-1)) {
            _index = 0;
        }
        count++;
        if (count>(total_count-1)) {
            return -1;
        }
    }
    return _index;
}

int LinesDataHandle::LD_calcDisappear(int _type, const LinesProperty &start){
    
    int x = start.x;
    int y = start.y;
    
    int index = LD_getIndexWith(x, y);
// check updown
    std::list<int> upDownList;
    
    for (int i = 1; i < 5; i++) {
        
        int _y = y+i;
        if (_y >= total_y) {
            break;
        }
        int _index = LD_getIndexWith(x, _y);
        
        if ( _index > 0 &&
            LD_getStateAtIndex(_index) == _type) {
            upDownList.push_back(_index);
        }else
            break;
    }
    for (int i = 1; i < 5; i++) {
        
        int _y = y-i;
        if (_y < 0) {
            break;
        }
        int _index = LD_getIndexWith(x, _y);
        if ( _index >= 0 &&
            LD_getStateAtIndex(_index) == _type) {
            upDownList.push_back(_index);
        }else
            break;
    }
    
// check leftright
//    printf("\t");
    std::list<int> leftRightList;
    
    for (int i = 1; i < 5; i++) {
        
        int _x = x-i;
        if (_x < 0) {
            break;
        }
        int _index = LD_getIndexWith(_x, y);
        if (_index >= 0 &&
            LD_getStateAtIndex(_index) == _type) {
            leftRightList.push_back(_index);
        }else
            break;
    }
    for (int i = 1; i < 5; i++) {
        
        int _x = x+i;
        if (_x >= total_x ) {
            break;
        }
        int _index = LD_getIndexWith(_x, y);
        if ( _index >= 0 &&
            LD_getStateAtIndex(_index) == _type) {
            leftRightList.push_back(_index);
        }else
            break;
    }
    
//    check leftup->rightdown
//    printf("\t");

    std::list<int> leftupTorightdownlist;
    
    for (int i = 1; i < 5; i++) {
        
        int _x = x-i;
        int _y = y+i;
        if ( _x < 0 || y>=total_y) {
            break;
        }
        int _index = LD_getIndexWith(_x, _y);
        if (_index >= 0 &&
            LD_getStateAtIndex(_index) == _type) {
            leftupTorightdownlist.push_back(_index);
        }else
            break;
    }
    for (int i = 1; i < 5; i++) {
        
        int _x = x+i;
        int _y = y-i;
        if (_x >= total_x || _y<0) {
            break;
        }
        int _index = LD_getIndexWith(_x, _y);
        if (_index >= 0 &&
            LD_getStateAtIndex(_index) == _type) {
            leftupTorightdownlist.push_back(_index);
        }else
            break;
    }
    
//    check leftdown->rightup
    
//    printf("\t");

    std::list<int> leftdownTorightup;
    
    for (int i = 1; i < 5; i++) {
        
        int _x = x-i;
        int _y = y-i;
        if (_x < 0 || _y < 0) {
            break;
        }
        int _index = LD_getIndexWith(_x, _y);
        if (_index >=0 &&
            LD_getStateAtIndex(_index) == _type) {
            leftdownTorightup.push_back(_index);
        }else
            break;
    }
    
    for (int i = 1; i < 5; i++) {
        
        int _x = x+i;
        int _y = y+i;
        if (_x >= total_x || _y >= total_y) {
            break;
        }        
        int _index = LD_getIndexWith(_x, _y);
        if (_index >=0 &&
            LD_getStateAtIndex(_index) == _type) {
            leftdownTorightup.push_back(_index);
        }else
            break;
    }
    
    
//    printf("\n===================================\n");
    int count = 1;
//    CCLOG("upDownList:%d",upDownList.size());
    if (upDownList.size() >= 4) {
        count += 4;
        printf("start upDown:");
        std::list<int>::iterator theIterator;
        for (theIterator = upDownList.begin(); theIterator != upDownList.end(); theIterator++) {
            LD_resetStateAtIndex(*theIterator, 0);
            printf("%d ",*theIterator);
        }
        printf("\n");
        upDownList.clear();
    }
    
    
//    CCLOG("leftRightList:%d",leftRightList.size());
    if (leftRightList.size() >= 4) {
        count += 4;
        printf("start leftRight:");
        std::list<int>::iterator theIterator;
        for (theIterator = leftRightList.begin(); theIterator != leftRightList.end(); theIterator++) {
            LD_resetStateAtIndex(*theIterator, 0);
            printf("%d ",*theIterator);
        }
        printf("\n");
        leftRightList.clear();
    }
    
    
//    CCLOG("leftup->rightdownlist:%d",leftupTorightdownlist.size());
    if (leftupTorightdownlist.size() >= 4) {
        count += 4;
        printf("start leftup->rightdown:");
        std::list<int>::iterator theIterator;
        for (theIterator = leftupTorightdownlist.begin(); theIterator != leftupTorightdownlist.end();
             theIterator++) {
            LD_resetStateAtIndex(*theIterator, 0);
            printf("%d ",*theIterator);
        }
        printf("\n");
        leftupTorightdownlist.clear();
    }
    
    
//    CCLOG("leftDown->RightUplist:%d",leftdownTorightup.size());
    if (leftdownTorightup.size() >= 4) {
        count +=4;
        printf("start leftdown->rightUp:");
        std::list<int>::iterator theIterator;
        for (theIterator = leftdownTorightup.begin(); theIterator != leftdownTorightup.end();
             theIterator++) {
            LD_resetStateAtIndex(*theIterator, 0);
            printf("%d ",*theIterator);
        }
        printf("\n");
        leftdownTorightup.clear();
    }
    
    
    if (count>1) {
        LD_resetStateAtIndex(index, 0);
    }
    
    return count;
}



#pragma mark -  Astar calc

CCArray * LinesDataHandle::LD_calcWayFromeAtoB(const LinesProperty &start,
                                               const LinesProperty &end){
    
//    CCLog("start    x:%d,y:%d",start.x,start.y);
//    CCLog("end      x:%d,y:%d",end.x,end.y);
    
    int _index = LD_getIndexAt(end);
    int _value = LD_getStateAtIndex(_index);
    LD_resetStateAtIndex(_index, 0);
    
    CCArray * _way = CCArray::create();
    
    AStarProperty * _start = AStarProperty::create();
    _start->curentNode = start;
    _start->parentNode = NULL;
    Astar_openList->addObject(_start);
    
    do {
        bool _flag = true;
        CCObject * _obj;
        AStarProperty * _p=dynamic_cast<AStarProperty*>(Astar_openList->objectAtIndex(0));
        CCARRAY_FOREACH(Astar_openList, _obj){//找到F值最低的那个
            AStarProperty * _tp = dynamic_cast<AStarProperty*>(_obj);
            if (_p && _tp) {
                if (_p->A_getF()>_tp->A_getF()) {
                    _p = _tp;
                }
            }
        }
        if (!_p) { continue; }
        
        LD_openListAddElement(_p, end);//给 openlist 添加新的 AstarProperty
        
        if (!Astar_closeList->containsObject(_p)) {//将 _p添加到closelist中去，且从openlist中移除
            Astar_closeList->addObject(_p);
        }
        Astar_openList->removeObject(_p);
        
        CCARRAY_FOREACH(Astar_closeList, _obj){//找到F值最低的那个
            AStarProperty * _tp = dynamic_cast<AStarProperty*>(_obj);
            if (_tp) {
                if (_tp->curentNode.x==end.x && _tp->curentNode.y== end.y) {//如果里面的currentnode == end点的时候break；
                    LD_calcWay(_p, _way);
                    _flag = false;
                    break;
                }
            }
        }
        
        if (!_flag) {
            break;
        }
        
    } while (Astar_openList->count()!=0);
    
    Astar_openList->removeAllObjects();
    Astar_closeList->removeAllObjects();
    
    if (!_way->count()>0) {//
        
        LD_resetStateAtIndex(_index, _value);
    }
    
    return _way;
}

void LinesDataHandle::LD_openListAddElement(AStarProperty * _p,
                                            const LinesProperty &end){
    LinesProperty _pro = _p->curentNode;
    
    LinesProperty _pro2;
    _pro2.x = _pro.x;_pro2.y = _pro.y+1;//up
    
    if (_pro2.y<=(total_y-1) &&
        LD_checkCanAddThisPropertyToOpenlist(_pro2) &&
        !LD_getStateAtProperty(_pro2)) {
        
//        CCLog("加入点:%d,%d",_pro2.x,_pro2.y);
        AStarProperty * asp = LD_calcAstarProperty(_p, _pro2, end);
        Astar_openList->addObject(asp);
    }
    
    _pro2.x = _pro.x-1 ;_pro2.y = _pro.y;//left
    
    if (_pro2.x>=0 &&
        LD_checkCanAddThisPropertyToOpenlist(_pro2) &&
        !LD_getStateAtProperty(_pro2)) {
        
//        CCLog("加入点:%d,%d",_pro2.x,_pro2.y);
        AStarProperty * asp = LD_calcAstarProperty(_p, _pro2, end);
        Astar_openList->addObject(asp);
    }
    
    _pro2.x = _pro.x;_pro2.y = _pro.y-1;//down
    
    if (_pro2.y>=0 &&
        LD_checkCanAddThisPropertyToOpenlist(_pro2) &&
        !LD_getStateAtProperty(_pro2)) {
        
//        CCLog("加入点:%d,%d",_pro2.x,_pro2.y);
        AStarProperty * asp = LD_calcAstarProperty(_p, _pro2, end);
        Astar_openList->addObject(asp);
    }
    
    _pro2.x = _pro.x + 1;_pro2.y = _pro.y;//right
    
    if (_pro2.x<=(total_x-1) &&
        LD_checkCanAddThisPropertyToOpenlist(_pro2)&&
        !LD_getStateAtProperty(_pro2)) {
        
//        CCLog("加入点:%d,%d",_pro2.x,_pro2.y);
        AStarProperty * asp = LD_calcAstarProperty(_p, _pro2, end);
        Astar_openList->addObject(asp);
    }
}

AStarProperty * LinesDataHandle::LD_calcAstarProperty(AStarProperty * _p,
                                                     LinesProperty start,
                                                     const LinesProperty &end){// 计算Astart 单元的属性  param1 是上一个单元，2是生成单元的当前节点的 属性 3是目标点的属性
    
    AStarProperty * _property = AStarProperty::create();
    
    int _g = _p->A_getG();
    
    _property->setValue_G(_g+1);
    _property->setValue_H(LD_calcValueH(_p->curentNode, end));
    _property->parentNode = _p;
    _property->curentNode = start;
    
    return _property;
}

int LinesDataHandle::LD_calcValueH(const LinesProperty &start,
                                   const LinesProperty &end){
    
    int _h = abs(start.x - end.x) +abs(start.y-end.y);
    return _h;
}

bool LinesDataHandle::LD_checkCanAddThisPropertyToOpenlist(const LinesProperty &_p){//看这个点能不能加入openlist中
   
    bool _checkInOpenList = true;
    CCObject * _obj;
    CCARRAY_FOREACH(Astar_openList, _obj){//查找 open列表里面是否有存在了点_P
        AStarProperty * _tp = dynamic_cast<AStarProperty*>(_obj);
        if (!_tp) {
            continue;
        }
        if (_tp->curentNode.x==_p.x && _tp->curentNode.y==_p.y){
//            CCLog("这个点已经存在与openlist，不能加进去啊！:%d,%d",_p.x,_p.y);
            _checkInOpenList = false;
            break;
        }
    }
    
    bool _checkINCloseList = true;
    
    CCARRAY_FOREACH(Astar_closeList, _obj){//查找 open列表里面是否有存在了点_P

        AStarProperty * _tp = dynamic_cast<AStarProperty*>(_obj);
        if (!_tp) {
            continue;
        }
        if (_tp->curentNode.x==_p.x && _tp->curentNode.y==_p.y){
//            CCLog("这个点已经存在与closelist，不能加进去啊！:%d,%d",_p.x,_p.y);
            _checkINCloseList = false;
            break;
        }
    }
    
    return _checkINCloseList&&_checkInOpenList;
}

void LinesDataHandle::LD_calcWay(AStarProperty *_p,
                                 cocos2d::CCArray *_way){//算出路径
    CCArray * moveToArray = CCArray::create();
    while (_p->parentNode!=NULL) {
        
        CCPoint pos = LD_getPositionAtProperty(_p->curentNode);
        
//        CCLog("位置:%f,%f",pos.x,pos.y);
        
        CCMoveTo * moveTo = CCMoveTo::create(0.1, pos);
        moveToArray->addObject(moveTo);
        
        _p = _p->parentNode;
    }
    
    CCPoint pos = LD_getPositionAtProperty(_p->curentNode);
    CCMoveTo * moveTo = CCMoveTo::create(0.2, pos);
    moveToArray->addObject(moveTo);
    
    if (moveToArray && _way) {
        CCSequence * moveSequence = CCSequence::create(moveToArray);
        _way->addObject(moveSequence);
    }
}



