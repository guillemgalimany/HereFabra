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
    
    string tempFilename = instrument + "Mitja.mp3";
    soM.load(tempFilename, true);
    soM.setLoop(true);
    
    string tempFilename = instrument + "Rapid.mp3";
    soH.load(tempFilename, true);
    soH.setLoop(true);
    
}


Sound::playSound(int tempo){
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


