//

//  Tower.cpp
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#include "Tower.h"
#include "Enemey.h"

#include "GameWorldScene.h"

Tower::Tower(){
    
    
}

Tower::~Tower(){
    
    _chooseEnemy = NULL;
    
}


bool Tower::initWithGame( GameWorldScene* father , CCPoint& p ){
    
    attactRange = 70;
    damage = 10;
    fireRate = 1;
    _chooseEnemy = NULL;
    
    _mySprite = CCSprite::create( "res/tower.png" );
    father->addChild( _mySprite, 10000 );
    
    _mySprite->setPosition( p );
    setGameWorldScene( father );
    father->addChild( this );
    
    scheduleUpdate();
    
    
    return true;
}

void Tower::lostSightofEnemey(){
    
    
    // 1.停止子弹运动的schedule
    
    this->unschedule( schedule_selector( Tower::shootEnemy));
    
    // 2.将敌人设为空
    
   _chooseEnemy = NULL;
    
    
    
    
}

void Tower::update(float dt){
    
    
    if ( _chooseEnemy  ) {
        
      // 如果已经选择到了敌人，计算敌人的旋转角度
        CCPoint normalize = ccpNormalize(ccp(  _chooseEnemy->getMysprit()->getPosition().x - _mySprite->getPosition().x     , _chooseEnemy->getMysprit()->getPosition().y - _mySprite->getPosition().y ));
        
        // 选择
        _mySprite->setRotation( CC_RADIANS_TO_DEGREES( atan2(normalize.y, -normalize.x) + 90 ));
        
        
        //  再次判断敌人是否离开了视野
        if ( !getGameWorldScene()->collisionWithCircle(_mySprite->getPosition(), attactRange, _chooseEnemy->getMysprit()->getPosition(), 1 )) {
            
            this->lostSightofEnemey();
           
        }
        
        
        
    }else{
        
        CCObject* o = NULL;
        CCARRAY_FOREACH( getGameWorldScene()->_enemies, o ){
            
            Enemey* e =  (Enemey*)o;
            
            if ( getGameWorldScene()->collisionWithCircle( getMySprite()->getPosition(), attactRange, e->getMysprit()->getPosition(), 1 )) {
               
                CCLOG( "选择到敌人");
                this->chooseEnemy( e );
                
            }
            
            
            
        }
        
    }
    
    
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


void Tower::chooseEnemy(Enemey *e){
    
    this->unschedule( schedule_selector( Tower::shootEnemy));
    _chooseEnemy = e;

    this->schedule( schedule_selector( Tower::shootEnemy), fireRate );
    
}

void Tower::shootEnemy(float dt ){
    
    CCPoint targetPoint = _chooseEnemy->getMysprit()->getPosition();
    
    CCMoveTo* moveTo =  CCMoveTo::create( 0.1f, targetPoint );
    
    CCSprite* b = CCSprite::create( "res/bullet.png");
    
    getGameWorldScene()->addChild( b, 100000);
    
    b->setPosition( getMySprite()->getPosition() );
    
    CCCallFuncN* bulletCallback = CCCallFuncN::create( b , callfuncN_selector( Tower::killBullet));
    
    CCCallFunc* damage_callback = CCCallFunc::create( this , callfunc_selector( Tower::damage_enemey));
    
    
    b->runAction( CCSequence::create( moveTo,damage_callback,bulletCallback,NULL));
    
}
void Tower::damage_enemey(){
    
    _chooseEnemy->damage( damage );
    
}
void Tower::killBullet(cocos2d::CCNode *n){
    
    
    n->removeFromParentAndCleanup( true );
    
}