//
//  Cover.h
//  TD_Game
//
//  Created by cesc on 13-11-11.
//
//

#ifndef __TD_Game__Cover__
#define __TD_Game__Cover__

#include "cocos2d.h"
USING_NS_CC;


class Cover : public CCLayer {
    
    
public:
    
    
    virtual bool init();
    
    CREATE_FUNC( Cover );
    
    static CCScene* scene();
    
    void start_game();
    
    
    void menu_callback( CCObject* o );
    
    void init_ui();
};

#endif /* defined(__TD_Game__Cover__) */
