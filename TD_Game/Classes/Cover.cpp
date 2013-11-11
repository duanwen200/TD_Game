//
//  Cover.cpp
//  TD_Game
//
//  Created by cesc on 13-11-11.
//
//

#include "Cover.h"


bool Cover::init(){
    if (!CCLayer::init() ) {
        return false;
    }
    
    
    init_ui();
    
    return true;
}


void Cover::init_ui(){
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create( "gmbg/welcomebg.png");
    
    this->addChild( bg , 1 );
    bg->setPosition( ccp( s.width / 2 , s.height / 2 ));
    
    
    CCMenuItemImage* code_item = CCMenuItemImage::create("gmme/coder_up.png", "gmme/coder_down.png", this, menu_selector( Cover::menu_callback) );
    
    code_item->setPosition( ccp( s.width - 150,200 ));
    code_item->setTag( 11 );

    CCMenu* m = CCMenu::create( code_item , NULL );
    
    m->setPosition( CCPointZero );
    
    this->addChild( m ,2 );
    
}

CCScene* Cover::scene(){
    CCScene* sc = CCScene::create();
    
    sc->addChild( Cover::create() );
    
    return sc;
}

void Cover::menu_callback(cocos2d::CCObject *o){
    
    CCMenuItem* i  = (CCMenuItem*)o;
    
    int tag = i->getTag();
    
    switch ( tag) {
        case 11:
            
            start_game();
            
            break;
            
        default:
            break;
    }
    
    
}

void Cover::start_game(){
    
    
    CCMessageBox("ok", "Title");
    
}