//
//  Sound.cpp
//  HereFabraICoats
//
//  Created by Helena Bantulà i Fonts on 16/06/16.
//
//

#include "SoundSwing.h"



void SoundSwing::initialize(int id_, int installation_, string instrument_){
    
    id = id_;
    installation = installation_;
    instrument = instrument_;
    
    string tempFilename = instrument + "Lent.mp3";
    soL.load(tempFilename,true);
    soL.setLoop(true);
    soL.setMultiPlay(true);
    
    string tempFilename1 = instrument + "Mitja.mp3";
    soM.load(tempFilename1, true);
    soM.setLoop(true);
    soM.setMultiPlay(true);

    
    string tempFilename2 = instrument + "Rapid.mp3";
    soH.load(tempFilename2, true);
    soH.setLoop(true);
    soH.setMultiPlay(true);

    
}


void SoundSwing::playSound(int tempo){
    switch (tempo) {
        case 0:
            soL.stop();
            soM.stop();
            soH.stop();
            break;
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


