//
//  GameScene.cpp
//  TD_Game
//
//  Created by cesc on 13-11-11.
//
//

#include "GameScene.h"

bool GameScene::init(){
    
    if ( !CCLayer::init () ) {
        return false;
    }
    
    
    return true;
}


CCScene* GameScene::scene(){
    
    CCScene* sc = CCScene::create();
    sc->addChild( GameScene::create () );
    
    return sc;
    
}