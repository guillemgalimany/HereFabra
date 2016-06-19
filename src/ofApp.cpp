#include "ofApp.h"
#include "ofxNetwork.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


//--------------------------------------------------------------
void ofApp::setup(){
    

    ofHideCursor();
    
    Light::getInstance().initialize();      // Els pars es posen tots a tope
    //Light::getInstance().fadePars(1, 'O', '0', warmingTime, 3);
    
    TCP.setup(8081);
    
    
    Cube tempCube1(1,4,1);
    cubes.push_back(tempCube1);
    Cube tempCube2(2,1,2);
    cubes.push_back(tempCube2);
    Cube tempCube3(3,2,3);
    cubes.push_back(tempCube3);
    Cube tempCube4(4,3,4);
    cubes.push_back(tempCube4);
    Cube tempCube5(5,4,1);
    cubes.push_back(tempCube5);
    
    //soundController.initialize();
    
    
    //soundController.playSwing(1, 2, 2);
    //soundController.playSwing(2, 3, 2);
//    swing21.load("SynthLent.mp3");
//    swing21.setLoop(true);
//    swing21.play();
//    
//    swing33.load("GuitarraMitja.mp3");
//    swing33.setLoop(true);
//    swing33.play();

}

//--------------------------------------------------------------
void ofApp::update(){

    ofSoundUpdate();
    
    // LIGHT
    Light::getInstance().getInfo();
    
    //ofColor myPrevColor = myTestColor;
    
    
    //--------------------------------------------------------------

    cout << ofGetElapsedTimeMillis() - requestDataTimer << endl;

    
    if (ofGetElapsedTimeMillis() - requestDataTimer > 5000)
    {
        requestDataServer();
        
        requestDataTimer = ofGetElapsedTimeMillis();
    
    }
    
    
    
    
    //--------------------------------------------------------------

    // TCP
    for(int i = 0; i < TCP.getLastID(); i++) // getLastID is UID of all clients
    {
     
        //std::cout <<TCP.getLastID();
        
        if( TCP.isClientConnected(i) ) { // check and see if it's still around
            // maybe the client is sending something
            std::string str = TCP.receive(i);
            
            //std::cout <<"received"<< endl;


            if (str != "")
            {
                
                //std::cout <<"RECEIVED"<< endl;

                
                std::cout <<str<< endl;

                std::vector<int> vect;
                
                std::stringstream ss(str);
                
                int j;
                
                while (ss >> j)
                {
                    vect.push_back(j);
                    
                    if (ss.peek() == ',')
                        ss.ignore();
                }
                
                int id = vect.at(1);
                int tempo = vect.at(2);
                
                //std::cout <<tempo<< endl;
                
                swingsTempo[id-1][0] = tempo;


                setIntensityCube();

            }

        }
    }
    

    //myPrevColor.lerp(myTestColor,ofGetElapsedTimef());
    
    //Light::getInstance().setParsColor(myPrevColor);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
        case 'f':
            Light::getInstance().setParsColor(ofColor(255,0,0));
            break;
        case 'j':
            Light::getInstance().setParsColor(ofColor(0,255,0));

            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key)
    {
        case 'f':
            break;
        case 'j':
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::setIntensityCube()
{
    
    for (int i = 0; i < cubes.size(); i++)
    {
        
        int swing1 = cubes[i].swingLeft;
        
        int swing2 = cubes[i].swingRight;
        
        int tempIntensity = swingsTempo[swing1-1][0] + swingsTempo[swing2-1][0] ;
        
        cubes[i].setIntensityLevel(tempIntensity);
        
    }
}

//--------------------------------------------------------------
void ofApp::requestDataServer()
{
    
    //Es crea un objecte http amb l'adreça del servidor
    ofHttpResponse resp = ofLoadURL("http://here.alquimia.io/backend/api/measurements-last/?format=json");
    cout << resp.data << endl;
    
    
    //S'emmagatzemen les dades en un fitxer de text
    string str = resp.data;
    ofBuffer msg(str.c_str(), str.length());
    ofBufferToFile("out.txt", msg);
    
    
    //Es posa la matriu de dades a 0
    for (int i = 0; i < 3 ; i++ )
    {
        for (int j = 0; j < 5 ; j++ )
        {
            serverData[i][j] = 0 ;
        }
    }
    
    
    //Si el cont¡ngut de la url no és buit, és llegeix i s'omple la matriu de dades, canvia el color del truss en funció de les dades
    if (str != "[]")
    {
            
        result.open("out.txt");
        
        int numMissatges = (int)result.type();
        
        for(int i = 0; i < numMissatges; i++)
        {
            string intallationIdStr = result[i]["installationId"].asString();
            
            string swingIdStr =result[i]["swingId"].asString();
            
            if (intallationIdStr != "" && swingIdStr != "")
            {
                
                std::string::size_type sz;   // alias of size_t
                
                int installationId = std::stoi (intallationIdStr);
                
                int swingId = std::stoi (swingIdStr,&sz);
                
                int tempoValue = result[i]["tempoValue"].asInt();
                
                serverData[ installationId - 1 ][ swingId - 1 ] = tempoValue;
                
            }
        }
    
        for (int i = 0; i < cubes.size()+1; i++)
        {
            installation1weight += serverData[1][i];
            installation2weight += serverData[2][i];
        }
        
        ofColor installation1color = ofColor(255,0,0);
        ofColor installation2color = ofColor(0,255,0);

        
        Light::getInstance().lightTheTruss(6, installation1color, installation2color, installation1weight, installation2weight);

        installation1weight = 0;
        installation2weight = 0;
    }
    
    
    
    //Si les dades han canviat respecte a la consulta anterior, és canvien els sons que s'estàn reproduïnt
    for (int i = 0; i < 3 ; i++ )
    {
        for (int j = 0; j < 5 ; j++ )
        {
            
            if ( prevServerData[i][j] != serverData[i][j])
            {
                playSound(i+1, j+1, serverData[i][j]);
            }
            
            prevServerData[i][j] = serverData[i][j];
            
        }
    }
    
    
    
}


//--------------------------------------------------------------
void ofApp::draw()
{
    ofDrawBitmapString(swingsTempo[0][0],20, 20);
    
    ofDrawBitmapString(swingsTempo[1][0],50, 20);

    ofDrawBitmapString(swingsTempo[2][0],80, 20);

    ofDrawBitmapString(swingsTempo[3][0],110, 20);

    
}

void ofApp::exit()
{
    
    TCP.close();

}

void ofApp::playSound(int installation, int swingID, int tempo){
    
    //string swing = "swing" + installation + swingID;
    
    string ritme;
    switch (tempo) {
        case 0:
            ritme = "NO_MUSIC";
            break;
        case 1:
            ritme = "Lent.mp3";
            break;
        case 2:
            ritme = "Mitja.mp3";
            break;
        case 3:
            ritme = "Rapid.mp3";
            break;
            
        default:
            break;
    } 
    
    string filename;
    switch (installation) {
        case 2:
            switch (swingID) {
                case 1:
                    if (ritme != "NO_MUSIC"){
                    filename = "Synth" + ritme;
                        swing21.load(filename);
                        swing21.setLoop(true);
                        swing21.play();
                    }
                    else
                        swing21.stop();
                    break;
                case 2:
                    if (ritme != "NO_MUSIC"){
                        filename = "Kick" + ritme;
                        swing22.load(filename);
                        swing22.setLoop(true);
                        swing22.play();
                    }
                    else
                        swing22.stop();
                    break;
                case 3:
                    if (ritme != "NO_MUSIC"){
                        filename = "Horns" + ritme;
                        swing23.load(filename);
                        swing23.setLoop(true);
                        swing23.play();
                    }
                    else
                        swing23.stop();
                    break;
                    
                case 4:
                    if (ritme != "NO_MUSIC"){
                        filename = "Percu" + ritme;
                        swing24.load(filename);
                        swing24.setLoop(true);
                        swing24.play();
                      }
                    else
                        swing24.stop();
                    break;
                    
                default:
                    break;
            }

            break;
            
        case 3:
            switch (swingID) {
                case 1:
                    if (ritme != "NO_MUSIC"){
                        filename = "Ambient" + ritme;
                        swing31.load(filename);
                        swing31.setLoop(true);
                        swing31.play();
                    }
                    else
                        swing31.stop();
                    break;
                case 2:
                    if (ritme != "NO_MUSIC"){
                        filename = "Cavall" + ritme;
                        swing32.load(filename);
                        swing32.setLoop(true);
                        swing32.play();
                    }
                    swing32.stop();
                    break;
                case 3:
                    if (ritme != "NO_MUSIC"){
                        filename = "Guitarra" + ritme;
                        swing33.load(filename);
                        swing33.setLoop(true);
                        swing33.play();
                    }
                    else
                        swing33.stop();
                    break;
                    
                case 4:
                    if (ritme != "NO_MUSIC"){
                        filename = "Baix" + ritme;
                        swing34.load(filename);
                        swing34.setLoop(true);
                        swing34.play();
                    }
                    else
                        swing34.stop();
                    break;
                    
                default:
                    break;
            }
            break;

            
        default:
            break;
    }




}




