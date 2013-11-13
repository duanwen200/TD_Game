//
//  GameWorldScene.cpp
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#include "GameWorldScene.h"
#include "Tower.h"
#include "Enemey.h"

GameWorldScene::GameWorldScene(){
    
    towerBases = CCArray::createWithCapacity( 10 );
    CC_SAFE_RETAIN( towerBases );
    
    towers = CCArray::create();
    CC_SAFE_RETAIN( towers );
    
    waypointsArray =  CCArray::create();
    CC_SAFE_RETAIN( waypointsArray );
    
    _enemies =  CCArray::create();
    CC_SAFE_RETAIN( _enemies );
    
    
}

GameWorldScene::~GameWorldScene(){
    
    CC_SAFE_RELEASE_NULL( towerBases );
    CC_SAFE_RELEASE_NULL( towers );
    CC_SAFE_RELEASE_NULL( waypointsArray );
    CC_SAFE_RELEASE_NULL( _enemies  );
    
    
}

bool GameWorldScene::init(){
    if ( !CCLayer::init()) {
        return false;
    }
    
    wave = 0;
    
    loadGameWorld();
    
    loadTowerPosition();
    
    loadWayPoinst();
    
    loadWave();

    setTouchEnabled( true );
    
    return true;
}

void GameWorldScene::loadTowerPosition(){
    
    CCArray* towerPostions = CCArray::createWithContentsOfFile( "res/TowersPosition.plist" );
    
    CCObject* o = NULL;
    
    CCARRAY_FOREACH( towerPostions, o ){
        
        CCDictionary* dic = (CCDictionary*)o;
        
        CCString* xstr = (CCString*)dic->objectForKey("x");
        CCString* ystr = (CCString*)dic->objectForKey("y");
        
        float x = xstr->floatValue();
        float y = ystr->floatValue();
        
        CCSprite* tower = CCSprite::create( "res/open_spot.png");
        
        tower->setPosition( ccp(x, y ));
        
        
        this->addChild( tower ,2 );
        
        towerBases->addObject( tower );
        
    }
    
    
}


CCScene* GameWorldScene::scene(){
    
    CCScene* s = CCScene::create();
    
    
    s->addChild( GameWorldScene::create() );
    
    return s;
}

void GameWorldScene::loadGameWorld(){
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create( "res/Bg.png");
    
    this->addChild( bg );
    
    bg->setPosition( ccp( s.width / 2 , s.height / 2 ));
    
}

bool GameWorldScene::loadWave(){
    
    CCArray* waveData = CCArray::createWithContentsOfFile( "res/Waves.plist");
    
    if ( wave >= waveData->count() ) {
        return false;
    }
    
    CCArray* currentWaveData = (CCArray*)waveData->objectAtIndex( wave );
    CCObject* obj = NULL;
    
    CCARRAY_FOREACH(currentWaveData, obj ){
        
        CCDictionary* dic = (CCDictionary*)obj;
        
        Enemey* e = Enemey::createWithGame( this );
        
        _enemies->addObject( e );
        
        CCString* str  = (CCString*)dic->valueForKey( "spawnTime");
        e->scheduleOnce( schedule_selector( Enemey::setActive), str->intValue() );
        
    }
    
    wave++;
    
    return true;
}
void GameWorldScene::loadWayPoinst(){
    
   
    
    Waypoint *waypoint1 = Waypoint::createWithGame(this, ccp(420, 35));
    waypointsArray->addObject(waypoint1);
    
    Waypoint *waypoint2 = Waypoint::createWithGame(this, ccp(35, 35));
    waypointsArray->addObject(waypoint2);
    waypoint2->setWaypoint(waypoint1);
    
    Waypoint *waypoint3 = Waypoint::createWithGame(this, ccp(35, 130));
    waypointsArray->addObject(waypoint3);
    waypoint3->setWaypoint(waypoint2);
    
    Waypoint *waypoint4 = Waypoint::createWithGame(this, ccp(445, 130));
    waypointsArray->addObject(waypoint4);
    waypoint4->setWaypoint(waypoint3);
    
    Waypoint *waypoint5 = Waypoint::createWithGame(this, ccp(445, 220));
    waypointsArray->addObject(waypoint5);
    waypoint5->setWaypoint(waypoint4);
    
    Waypoint *waypoint6 = Waypoint::createWithGame(this, ccp(-40, 220));
    waypointsArray->addObject(waypoint6);
    waypoint6->setWaypoint(waypoint5);
}

void GameWorldScene::registerWithTouchDispatcher(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this , 0,  true);
    
}

bool GameWorldScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCPoint touchPoint = pTouch->getLocation();
    
    CCObject* o = NULL;
    
    CCARRAY_FOREACH( towerBases, o ){
        
        CCSprite* tb =  (CCSprite*)o;
        
        if ( tb->boundingBox().containsPoint( touchPoint ) && !tb->getUserData()) {
            
            CCPoint p = tb->getPosition();
            Tower* tower = Tower::createWtihGame(this, p );
            
            towers->addObject( tower );
            
            //  将炮塔传递给炮塔作为userdata
            tb->setUserData( tower );
            
        }
        
    
    }
    
    
    return true;
}

bool GameWorldScene::collisionWithCircle(cocos2d::CCPoint ciclePoint1, float radius1, cocos2d::CCPoint ciclePoint2, float radius2){
    
    float distance = ccpDistance( ciclePoint1, ciclePoint2 );
    
    if ( distance <= radius1 + radius2 ) {
        
        return true;
    }
    
    return false;
}


void GameWorldScene::enmeyKilled(){
    
    if ( _enemies->count() <= 0 ) {
        if ( !this->loadWave() ) {
            
            CCLOG( "You Win");
            
            CCMessageBox("You Win", "提示");
        }
    }
    
    
    
}