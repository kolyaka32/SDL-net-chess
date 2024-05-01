#include "internetServer.hpp"


//
InternetServerCycle::InternetServerCycle(){
    // Openning UDP port to recieve data from client
    while(!(socket = SDLNet_UDP_Open(serverPort))){
        // Checking, if not open port - setting random 
        serverPort = rand() % 4000;
    }
    
    // Simulated packet loss for packets for better testing
    #if DEBUG
    SDLNet_UDP_SetPacketLoss(socket, CONNECTION_LOST_PERCENT);
    #endif
}

//
InternetServerCycle::~InternetServerCycle(){

}

