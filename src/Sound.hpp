//
//  Sound.hpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#ifndef Sound_hpp
#define Sound_hpp

#include <stdio.h>
#include <ofMain.h>

#endif /* Sound_hpp */


class Sound {
    
public:
    
    int id;
    int installation;
    
    Sound (int id, int installation, string filename);
    
    ofSoundPlayer soL;
    ofSoundPlayer soM;
    ofSoundPlayer soH;
    
    
    void playSound(int tempo);
    
    
    
};