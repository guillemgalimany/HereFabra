//
//  SoundController.cpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#include "SoundController.hpp"


void SoundController::initialize(){
    
    
    vector<Sound> tempSoundSwings(8);
    soundSwings = tempSoundSwings;
    
    
    Sound tempSound1(1, 2, "Synth");
    soundSwings.push_back(tempSound1);
    Sound tempSound2(2, 2, "Kick");
    soundSwings.push_back(tempSound2);
    Sound tempSound3(3, 2, "Horns");
    soundSwings.push_back(tempSound3);
    Sound tempSound4(4, 2, "Percu");
    soundSwings.push_back(tempSound4);
    
    

    Sound tempSound5(1, 3, "Ambient");
    soundSwings.push_back(tempSound5);
    Sound tempSound6(2, 3, "Cavall");
    soundSwings.push_back(tempSound6);
    Sound tempSound7(3, 3, "Guitarra");
    soundSwings.push_back(tempSound7);
    Sound tempSound8(4, 3, "Baix");
    soundSwings.push_back(tempSound8);
    
}

void SoundController::playSwing(int id, int installation, int tempo){

    for (int i = 0; i < soundSwings.size(); i++){
        
        if (installation == soundSwings[i].installation)
            if (id == soundSwings[i].id) {
                soundSwings[i].playSound(tempo);
            }
    }

}





