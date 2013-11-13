//
//  Enemey.cpp
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#include "Enemey.h"
#include "GameWorldScene.h"
#include "Tower.h"

Enemey::Enemey(){
    
    attackArray = CCArray::create();
    CC_SAFE_RETAIN( attackArray );
    
}

Enemey::~Enemey(){
    
    CC_SAFE_RELEASE_NULL( attackArray );
    
}
bool Enemey::initWithGame(GameWorldScene *f){
    
    maxHp = 1000;
    
    currentHp = maxHp;
    active = false;
    
    walkingSpeed = 0.5f;
    
    
    setGameWorldScene( f );
    
    _mysprite =  CCSprite::create( "res/enemy.png");
    
    setMysprit( _mysprite );
    
    f->addChild( _mysprite , 22 );
    
    // 设定起始的位置点
    Waypoint* waypoint = (Waypoint*)f->getWaypointArray()->objectAtIndex( f->getWaypointArray()->count() -1 );
    
    CCAssert(waypoint != NULL, "enemy waypoint is null");
    
    destinaWayPoint = waypoint;
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

void Enemey::update(float dt){
    
    if ( !active )
            return;
   
    //  1.判断 是否与位置点的圆碰撞 -- 说明到达了一个目标点,然后可以获取下一个点
    
    //CCLOG("x:%f === y%f", myPosition.x ,myPosition.y);
    CCAssert( destinaWayPoint != NULL, "destin null");
    //CCLOG("dest x:%f ===dest y%f", destinaWayPoint->getMypoint().x ,destinaWayPoint->getMypoint().y);
    bool rlt = getGameWorldScene()->collisionWithCircle( myPosition, 1, destinaWayPoint->getMypoint(), 1 );
    if ( rlt ) {
        if ( destinaWayPoint->getWaypoint() ) {
            destinaWayPoint = destinaWayPoint->getWaypoint();
        }else{
            
            
            CCLOG( "到达终点");
            getRemoved();
            getGameWorldScene()->enmeyKilled();
            
        
            return;
        }
        
    }
    
    //  2.如果没有碰撞,进行移动
    CCPoint targetPoint = destinaWayPoint->getMypoint();
    
    float movement =  walkingSpeed;
    
    CCPoint normalized = ccpNormalize( ccp( targetPoint.x -  myPosition.x , targetPoint.y - myPosition.y ));
    
    // 设置是否旋转
    _mysprite->setRotation( CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x )));
    
    myPosition = ccp(myPosition.x + normalized.x * movement, myPosition.y + normalized.y * movement );

    _mysprite->setPosition( myPosition );
    
}

void Enemey::draw(){
    
    
    
    CCNode::draw();
}


void Enemey::getRemoved(){
    
    this->removeFromParentAndCleanup(true );
    
    getGameWorldScene()->_enemies->removeObject( this );
    
    _mysprite->removeFromParentAndCleanup( true );
    
    // notify game that this enmey is killed
    
}


void Enemey::setActive( float dt ){
    
    
    active = true;
}


/**
    damage
 **/
void Enemey::damage(int damage){
    
    CCLOG( "current hp %i:", currentHp );
    currentHp -= damage;
    
    if ( currentHp <= 0 ) {
    
        getRemoved();
    }
    
    
}
