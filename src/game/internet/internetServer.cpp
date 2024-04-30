#include "internetServer.hpp"


//
InternetServerCycle::InternetServerCycle(){
    // Setting base port to show next
    Uint16 port = BASE_PORT;
    
    // Openning UDP port to recieve data from client
    while(!(socket = SDLNet_UDP_Open(port))){
        // Checking, if not open port - setting random 
        port = rand() % 4000;
    }
    // Simulated packet loss for packets for better testing
    #if DEBUG
    SDLNet_UDP_SetPacketLoss(socket, CONNECTION_LOST_PERCENT);
    #endif
}

//
InternetServerCycle::~InternetServerCycle(){

}

