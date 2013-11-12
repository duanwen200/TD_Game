//
//  Waypoint.h
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#ifndef __TD_Game__Waypoint__
#define __TD_Game__Waypoint__

#include "cocos2d.h"
USING_NS_CC;

class GameWorldScene;
class Waypoint : public CCNode  {
    
    
public:
    
    Waypoint();
    ~Waypoint();
    
    bool initWithGame( GameWorldScene* father, CCPoint p );
    
    static Waypoint* createWithGame( GameWorldScene* f , CCPoint p );
    
    
    void draw();
    
    CC_SYNTHESIZE(Waypoint*, _nextWayPoint, Waypoint );
    
    CC_SYNTHESIZE(CCPoint, myPoint, Mypoint );
    
    CC_SYNTHESIZE(GameWorldScene*, father, GameWorldScene );
    
};

#endif /* defined(__TD_Game__Waypoint__) */
