#include "stdio.h"
#include "include.hpp"
#include "SDL_net.h"
#include "process.hpp"
#include "workCodes.hpp"

// Function of initialasing all libraries
Process::Process(){
    // Initialising network libarary
    /*#if BASE_PORT
    if(SDLNet_Init()){
        printf("Couldn't initialize network library: %s\n", SDLNet_GetError());
        exit(ERR_SDL_NET);
    }
    #endif*/
}


// Function of closing all outside libraries and files
Process::~Process(){
    // Closing all outside libraries in reverce order
    /*#if BASE_PORT
    SDLNet_Quit();    // Closing network libarary
    #endif*/
}

// Main function of running process
int Process::run(){
    return 0;
}