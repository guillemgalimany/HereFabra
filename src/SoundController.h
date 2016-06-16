//
//  SoundController.hpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#ifndef SoundController_h
#define SoundController_h

#include <iostream>
#include "SoundSwing.h"

#endif /* SoundController_hpp */


class SoundController {
    
public:
    
    void initialize ();
    
    vector<SoundSwing> soundSwings;
    
    void playSwing(int id, int installation, int tempo);
    
    
    
};