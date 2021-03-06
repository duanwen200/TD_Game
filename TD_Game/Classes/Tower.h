//
//  Tower.h
//  TD_Game
//
//  Created by cesc on 13-11-12.
//
//

#ifndef __TD_Game__Tower__
#define __TD_Game__Tower__

#include "cocos2d.h"
USING_NS_CC;

#define kTower_COST  300

class GameWorldScene;
class Enemey;

class Tower : public CCNode {
    
    
public:
    
    Tower();
    ~Tower();
    
    virtual bool initWithGame( GameWorldScene* father ,CCPoint& location );
    
    static Tower* createWtihGame( GameWorldScene* father, CCPoint& p );
    
    void update( float dt );
    
    void draw();
    
    CC_SYNTHESIZE(GameWorldScene*, world, GameWorldScene );
    
    
    void shootEnemy( float  dt );
    
    void chooseEnemy( Enemey* e );

    void lostSightofEnemey();
    
    CC_SYNTHESIZE(CCSprite*, _mySprite, MySprite);
    
    void killBullet( CCNode* n );

    
    void damage_enemey();
    
private:
    
    int attactRange;
    
    int damage;
    
    float fireRate;
    
    Enemey* _chooseEnemy;
    
};

#endif /* defined(__TD_Game__Tower__) */
