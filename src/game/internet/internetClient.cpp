#include "internetClient.hpp"


// Client part
//
InternetClientCycle::InternetClientCycle(){
    // Creating socket to get data
    socket = SDLNet_UDP_Open(0);

    // Simulated packet loss for packets for better testing
    #if DEBUG
    SDLNet_UDP_SetPacketLoss(socket, CONNECTION_LOST_PERCENT);
    #endif
}

//
InternetClientCycle::~InternetClientCycle(){

}

//
Uint8 InternetClientCycle::tryConnect(const char* ipText, const char* portText){
    IPaddress sendIP;  // IP of reciever
    if(SDLNet_ResolveHost(&sendIP, ipText, std::stoi(portText)) == 0){
        // Setting send address
        sendData->address = sendIP;

        // Creating socket set to search for new messages
        SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);
        SDLNet_UDP_AddSocket(set, socket);
        
        // Try send activation code at specifed coordinats
        send(MES_INIT);
        
        // Checking get pachage
        if(SDLNet_CheckSockets(set, 1000) && SDLNet_UDP_Recv(socket, recieveData)){
            // Connection correct
            // Saving entered parameters for next conncetion
            data.baseIP = (std::string)ipText;
            data.basePort = (std::string)portText;

            // Breaking wait cycle
            return 1;
        }
        else{
            showCantConnect();
        }
        SDLNet_FreeSocketSet(set);
        return 0;
    }
    // Can't resolve this host
    return 0;
}
