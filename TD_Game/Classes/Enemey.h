//
//  Enemey.h
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#ifndef __TD_Game__Enemey__
#define __TD_Game__Enemey__

#include "cocos2d.h"
#include "Waypoint.h"
USING_NS_CC;


class GameWorldScene;
class Enemey : public CCNode {
    
    
public:
    
    static Enemey* createWithGame( GameWorldScene* f );
    
    bool initWithGame( GameWorldScene* f );
    
    CC_SYNTHESIZE(GameWorldScene*, father, GameWorldScene );
    
    void update(float dt );
    
    void draw();
    
    CC_SYNTHESIZE(CCSprite*, _mysprite, Mysprit );
private:
    CCPoint myPosition;
    
    float walkingSpeed;
    
    int maxHp;
    
    int currentHp;
    
    bool active;
    
    Waypoint* destinaWayPoint;
};
#endif /* defined(__TD_Game__Enemey__) */
