//
//  Sound.cpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#include "Sound.hpp"



Sound::Sound(int id_, int installation_, string instrument){
    
    string tempFilename = instrument + "Lent.mp3";
    soL.load(tempFilename,true);
    soL.setLoop(true);
    
    string tempFilename1 = instrument + "Mitja.mp3";
    soM.load(tempFilename1, true);
    soM.setLoop(true);
    
    string tempFilename2 = instrument + "Rapid.mp3";
    soH.load(tempFilename2, true);
    soH.setLoop(true);
    
}


void Sound::playSound(int tempo){
    switch (tempo) {
        case 1:
            soL.play();
            soM.stop();
            soH.stop();
            break;
        case 2:
            soL.stop();
            soM.play();
            soH.stop();
            
            break;
        case 3:
            soL.stop();
            soM.stop();
            soH.play();
            break;
            
        default:
            break;
    }
    
}


