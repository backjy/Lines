//
//  LinesDateHandle.h
//  Lines
//
//  Created by CpyShine on 13-4-26.
//
//

#ifndef __Lines__LinesDateHandle__
#define __Lines__LinesDateHandle__

#include <iostream>

#include "cocos2d.h"
#include "LinesConfig.h"

using namespace cocos2d;

class LinesDataHandle {
    
    CCArray * Astar_openList;
    CCArray * Astar_closeList;

    int total_x;
    int total_y;
    int total_count;
    
    int * stateArray;
    CCPoint * pointArray;
public:
    
#pragma mark - calc dissappear ,add functions
    
    
    int LD_calcAddSpriteAt();//计算生成sprite的位置 当返回-1时 加入新元素失败 fuck shit
    
    int LD_calcDisappear(int _type,const LinesProperty &start);//计算 消除
    
#pragma mark  - Astar functions
    
    CCArray * LD_calcWayFromeAtoB(const LinesProperty &start,const LinesProperty &end);
    
    void LD_openListAddElement(AStarProperty * _p,const LinesProperty &end);
    
    AStarProperty * LD_calcAstarProperty(AStarProperty * _p,LinesProperty start, const LinesProperty &end);
    
    int LD_calcValueH(const LinesProperty &start,const LinesProperty &end);
    
    bool LD_checkCanAddThisPropertyToOpenlist(const LinesProperty &_p);
    
    void LD_calcWay(AStarProperty * _p,CCArray * _way);
    
#pragma mark -  calc index & get state|position
    
    inline int LD_getIndexWith(int _x,int _y){
        int _index = _y * total_x + _x;
//        printf("%d ",_index);
        if (_index<0 || _index>=total_count) {
            return -1;
        }
        return _index;
    }
    
    inline void LD_resetStateAtIndex(int _index,int _value){
        stateArray[_index] = _value;
    }
    
    inline int LD_getIndexAt(const LinesProperty & _p){
        int _index = _p.y * total_x + _p.x;
        if (_index<0 ||_index>=total_count) {
            return -1;
        }
        return _index;
    }
    
    inline CCPoint LD_getPositionAtIndex(int _index){//
        return pointArray[_index];
    }
    
    inline int LD_getStateAtIndex(int _index){
        return stateArray[_index];
    }
    
    inline int LD_getStateAtProperty(const LinesProperty &_p){
        int _index = LD_getIndexAt(_p);
        if (_index<0||_index>=total_count) {
            return 0;
        }
        return LD_getStateAtIndex(_index);
    }
    inline CCPoint LD_getPositionAtProperty(const LinesProperty &_p) {
        int _index = LD_getIndexAt(_p);
        if (_index<0||_index>=total_count) {
            return CCPointZero;
        }
        return LD_getPositionAtIndex(_index);
    }
    
    int LD_getIndexAtPosition(CCPoint _pos,float _diatance){
        int _index=-1;
        for (int i=0; i<total_count; i++) {
            CCPoint pos = pointArray[i];
            if (ccpDistance(pos, _pos)<=_diatance) {
                _index = i;
                break;
            }
        }
        return _index;
    }
    
    LinesProperty LD_convertIndexToLinesProperty(int _index){
        LinesProperty _pro;
        _pro.x = _index % total_x;
        _pro.y = (int)(_index/total_x);
        return _pro;
    }
    
#pragma mark - init constructor & destructor
    
    
    void initDateHandleWith(int _column,int _row,float _width,float _height){
        
        total_x = _column;
        total_y = _row;
        total_count = _column * _row;
        
        stateArray = new int[total_count]();
        memset(stateArray, 0, sizeof(int)*total_count);
        pointArray = new CCPoint[total_count]();
        
        float _halfWi = _width * 0.5f;
        float _halfHe = _height * 0.5f;
        
        for (int y = 0; y<total_y; y++) {
            for (int x = 0; x<total_x; x++) {
                
                int _index = (y * total_x) + x;
                
                if (_index<0 || _index>=total_count) {continue;}
                
                CCPoint pos = CCPoint(_width*x + _halfWi, _height*y + _halfHe);
                
                pointArray[_index] = pos;
            }
        }
    }
    
    void LD_ShowDebug(){
        printf("abcdefghijklmnopqrstuvwxyz\n");
        for (int r=total_y-1; r>=0; r--) {
            for (int i=0; i<total_x; i++) {
                int index = r*total_x +i;
                printf("%d",stateArray[index]);
            }
            printf("-----%02d\n",r);
        }
        printf("abcdefghijklmnopqrstuvwxyz\n");
    }
    
    LinesDataHandle(){
        Astar_openList = new CCArray();
        Astar_closeList = new CCArray();
        stateArray = NULL;
        pointArray = NULL;
    }
    ~LinesDataHandle(){
        Astar_openList->removeAllObjects();
        CC_SAFE_RELEASE_NULL(Astar_openList);
        Astar_closeList->removeAllObjects();
        CC_SAFE_RELEASE_NULL(Astar_closeList);
        
        delete [] stateArray;
        delete [] pointArray;
    }
};

#endif /* defined(__Lines__LinesDateHandle__) */
