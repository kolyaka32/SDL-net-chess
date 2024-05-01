
#include "internetCycle.hpp"


//
InternetCycle::InternetCycle(){
    // Launching process
    running = true;

    // Stopping from pre-launch
    gettingMutex.lock();
}

//
InternetCycle::~InternetCycle(){
    // Stopping all working proceses
    running = false;

    // Closing thread
    gettingCycle.join();
}

//
void InternetCycle::lauchCycle(){
    // Waiting for allowing to start
    gettingMutex.lock();

    // First, waiting start cycle
    while(running){
        // Getting data with check on exit
        if(startUpdate()){
            // Starting main cycle
            break;
        }

        // Waiting next cycle (for better process time)
        data.waitDraw();
    }

    // Checking on exit
    if(!running){
        return;
    }

    // Initialasing data for main cycle
    initConnection();

    // Updating times of last sended messages
    lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
    lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL_TIMEOUT;
    
    // Main getting cycle
    while(running){
        // Waiting for posobility for get data
        gettingMutex.lock();

        // Getting data with check on exit
        if(update()){
            running = false;
        }

        // Unlocking mutex for another actions
        gettingMutex.unlock();

        // Waiting next cycle (for better process time)
        data.waitDraw();
    }
}

// Action, launch after connection
void InternetCycle::initConnection(){

};