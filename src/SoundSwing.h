//
//  Sound.hpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#ifndef SoundSwing_h
#define SoundSwing_h

#include <stdio.h>
#include <ofMain.h>
#include <iostream>

#endif /* Sound_hpp */


class SoundSwing {
    
public:
    
    int id;
    int installation;
    string instrument;
    
    
    //SoundSwing();
    
    ofSoundPlayer soL;
    ofSoundPlayer soM;
    ofSoundPlayer soH;
    
    void initialize(int id_, int installation_, string instrument);
    
    void playSound(int tempo);

    
    
    
};