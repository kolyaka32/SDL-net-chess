#include "message.hpp"

//
/*Message::Message(const MESSAGE_types _type) : type(_type){};

//
Message::~Message(){

}

//
void Message::send(UDPpacket* _packet){
    // Copying data to send buffer
    memcpy(_packet->data, data, INTERNET_BUFFER);

    // Updating send timer
    lastSended = SDL_GetTicks64();
};

//
const bool Message::checkTime() const{
    return SDL_GetTicks64() > lastSended;
};
*/