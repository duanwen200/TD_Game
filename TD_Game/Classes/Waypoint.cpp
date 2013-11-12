//
//  Waypoint.cpp
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#include "Waypoint.h"
#include "GameWorldScene.h"

Waypoint::Waypoint(){
    
    
}
Waypoint::~Waypoint(){
    
    _nextWayPoint = NULL;
}

bool Waypoint::initWithGame(GameWorldScene *father, cocos2d::CCPoint p){
    
    setGameWorldScene( father );
    setMypoint( p );
    
    this->setPosition( CCPointZero );
    getGameWorldScene()->addChild( this );
    
    
    return true;
}



Waypoint* Waypoint::createWithGame(GameWorldScene *f, cocos2d::CCPoint p){
    
    
    Waypoint* w = new Waypoint;
    if ( w && w->initWithGame(f, p )) {
        
        w->autorelease();
        return w;
    }
    
    CC_SAFE_DELETE( w );
    return NULL;
}


void Waypoint::draw(){
    
#ifdef COCOS2D_DEBUG
    ccDrawColor4B(0, 255, 0, 255);
    ccDrawCircle(getMypoint(), 6, 360, 30, false );
    ccDrawCircle(getMypoint(), 2, 360, 30, false );
    
    if ( _nextWayPoint) {
        ccDrawLine(getMypoint(), _nextWayPoint->getMypoint() );
    }
    
    
#endif
    
    CCNode::draw();
    
}