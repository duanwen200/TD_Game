//
//  GameScene.h
//  TD_Game
//
//  Created by cesc on 13-11-11.
//
//

#ifndef __TD_Game__GameScene__
#define __TD_Game__GameScene__

#include "cocos2d.h"
using namespace cocos2d;


class GameScene : public CCLayer {
    
    
public:
   
    virtual bool init();
    
    
    CREATE_FUNC(  GameScene );
    static CCScene* scene();
    
    void init_game();
};

#endif /* defined(__TD_Game__GameScene__) */
