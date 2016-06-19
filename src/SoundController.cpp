//
//  SoundController.cpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#include "SoundController.h"


void SoundController::initialize(){
    
    SoundSwing tempSound1;
    tempSound1.initialize(1, 2, "Synth");
    soundSwings.push_back(tempSound1);
    tempSound1.initialize(2, 2, "Kick");
    soundSwings.push_back(tempSound1);
    tempSound1.initialize(3, 2, "Horns");
    soundSwings.push_back(tempSound1);
    tempSound1.initialize(4, 2, "Percu");
    soundSwings.push_back(tempSound1);
    
    
    tempSound1.initialize(1, 3, "Ambient");
    soundSwings.push_back(tempSound1);
    tempSound1.initialize(2, 3, "Cavall");
    soundSwings.push_back(tempSound1);
    tempSound1.initialize(3, 3, "Guitarra");
    soundSwings.push_back(tempSound1);
    tempSound1.initialize(4, 3, "Baix");
    soundSwings.push_back(tempSound1);
    
}

void SoundController::playSwing(int id, int installation, int tempo){

    for (int i = 0; i < soundSwings.size(); i++){
        
        if (installation == soundSwings[i].installation) {
            if (id == soundSwings[i].id) {
                soundSwings[i].playSound(tempo);
                break;
            }
        }
    }

}





