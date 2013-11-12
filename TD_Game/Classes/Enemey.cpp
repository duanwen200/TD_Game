//
//  Enemey.cpp
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#include "Enemey.h"
#include "GameWorldScene.h"


bool Enemey::initWithGame(GameWorldScene *f){
    
    maxHp = 40;
    
    currentHp = maxHp;
    active = false;
    
    walkingSpeed = 0.5f;
    
    
    setGameWorldScene( f );
    
    _mysprite =  CCSprite::create( "res/enemy.png");
    
    f->addChild( _mysprite , 22 );
    
    Waypoint* waypoint = (Waypoint*)f->getWaypointArray()->objectAtIndex( f->getWaypointArray()->count() -1 );
    
    
    _mysprite->setPosition( waypoint->getMypoint()  );
    
    myPosition = waypoint->getMypoint();
    
    f->addChild( this );
    
    scheduleUpdate();
    
    return true;
}


Enemey* Enemey::createWithGame(GameWorldScene *f){
    
    
    Enemey* e = new Enemey;
    
    if ( e && e->initWithGame(f)) {
        e->autorelease();
        return e;
    }
    
    CC_SAFE_DELETE( e );
    return NULL;
}