//
//  SoundController.hpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#ifndef SoundController_hpp
#define SoundController_hpp

#include <stdio.h>
#include "Sound.hpp"

#endif /* SoundController_hpp */


class SoundController {
    
public:
    
    void initialize ();
    
    vector<Sound> soundSwings;
    
    void playSwing(int id, int installation, int tempo);
    
    
    
};