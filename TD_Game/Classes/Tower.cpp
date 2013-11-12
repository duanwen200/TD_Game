//
//  Tower.cpp
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#include "Tower.h"

#include "GameWorldScene.h"

bool Tower::initWithGame( GameWorldScene* father , CCPoint& p ){
    
    attactRange = 70;
    damage = 10;
    fireRate = 1;
    
    _mySprite = CCSprite::create( "res/tower.png" );
    father->addChild( _mySprite, 10000 );
    
    _mySprite->setPosition( p );
    setGameWorldScene( father );
    father->addChild( this );
    
    scheduleUpdate();
    
    
    return true;
}

void Tower::update(float dt){
    
    
    
}

void Tower::draw(){
    
#ifdef COCOS2D_DEBUG
    ccDrawColor4B(255, 255, 255, 255);

    ccDrawCircle(_mySprite->getPosition(), attactRange, 360, 30, false );
#endif
    
    CCNode::draw();
}



Tower* Tower::createWtihGame(GameWorldScene *father, cocos2d::CCPoint &p){
    
    Tower* t = new Tower;
    if ( t && t->initWithGame(father, p )) {
        
        t->autorelease();
        
        return t;
    }
    
    CC_SAFE_DELETE( t );
    
    return NULL;
}