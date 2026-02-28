/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "library.hpp"
#include <stdio.h>


// Winsocket realisation
#if (USE_WINSOCK)

bool InternetLibrary::findHostName() {
    // Allocating static memory for that process
    char buffer[10000];
    PIP_ADAPTER_ADDRESSES addresses = (PIP_ADAPTER_ADDRESSES)buffer;
    unsigned long length = sizeof(buffer);

    // Getting names
    u_long dwRetVal = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, 
        NULL, addresses, &length);

    // Searching for local address from linked list
    while (addresses) {
        PIP_ADAPTER_UNICAST_ADDRESS pUnicast = addresses->FirstUnicastAddress;

        while (pUnicast != NULL) {
            sockaddr_in* sa_in = (sockaddr_in*)pUnicast->Address.lpSockaddr;

            char* ipStr = inet_ntoa(sa_in->sin_addr);
            // Check if not loopback
            if (strcmp(ipStr, "127.0.0.1")) {
                // Writing getted address
                snprintf(hostName, sizeof(hostName), "%s", ipStr);
                logAdditional("Hostname: %s", ipStr);
                return false;
            }
            pUnicast = pUnicast->Next;
        }
        addresses = addresses->Next;
    }
    return true;
}

#endif  // (USE_WINSOCK)

// Socket realisation
#if (USE_SOCKET)

#include <ifaddrs.h>

bool InternetLibrary::findHostName() {
    ifaddrs* ifAddrStruct = nullptr;

    // Getting address as linked list
    getifaddrs(&ifAddrStruct);

    // Check, if empty
    if (ifAddrStruct == nullptr) {
        return true;
    }

    // Checking them, until find need
    for (ifaddrs * ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        // check it is IP4
        if (ifa->ifa_addr->sa_family == AF_INET) {
            // Getting string representation
            char* ipStr = inet_ntoa(((sockaddr_in*)ifa->ifa_addr)->sin_addr);

            // Check if not loopback
            if (strcmp(ipStr, "127.0.0.1")) {
                // Writing getted address
                snprintf(hostName, sizeof(hostName), "%s", ipStr);
                logAdditional("Hostname: %s", ipStr);
                return false;
            }
        }
    }
    freeifaddrs(ifAddrStruct);
    return true;
}

#endif // (USE_SOCKET)


InternetLibrary::InternetLibrary() {
    #if (USE_WINSOCK)
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        logImportant("WSAStartup() failed: %d", getError);
        return;
    }
    #endif

    if (findHostName()) {
        logImportant("Can't find hostname");
        return;
    }
}

InternetLibrary::~InternetLibrary() {
    #if (USE_WINSOCK)
    if (WSACleanup() < 0) {
        logImportant("Can't cleanup");
        return;
    }
    #endif  // (USE_WINSOCK)
}

const char* InternetLibrary::getHostName() const {
    return hostName;
}


Uint8 writeNet(Uint8 _object) {
    return _object;
}

/*Sint8 writeNet(Sint8 _object) {
    return _object;
}*/

char writeNet(char _object) {
    return _object;
}

Uint8 writeNet(ConnectionCode _object) {
    return (Uint8)_object;
}

Uint16 writeNet(Uint16 _object) {
    return htons(_object);
}

/*Sint16 writeNet(Sint16 _object) {
    return (Uint8)_object;
}*/

Uint32 writeNet(Uint32 _object) {
    return htonl(_object);
}

Sint32 writeNet(Sint32 _object) {
    return htonl(_object);;
}

/*float writeNet(float _object) {
    return (Uint8)_object;
}*/

/*Uint64 writeNet(Uint64 _object) {
    return htonll(_object);
}*/

/*Sint64 writeNet(Sint64 _object) {
    return (Uint8)_object;
}*/

Uint8 readNet(Uint8 _object) {
    return _object;
}

/*Sint8 readNet(Sint8 _object) {
    return ;
}*/

char readNet(char _object) {
    return _object;
}

ConnectionCode readNet(ConnectionCode _object) {
    return _object;
}

Uint16 readNet(Uint16 _object) {
    return ntohs(_object);
}

/*Sint16 readNet(Sint16 _object) {
    return ;
}*/

Uint32 readNet(Uint32 _object) {
    return ntohl(ntohl(_object));
}

/*Sint32 readNet(Sint32 _object) {
    return ;
}*/

/*float readNet(float _object) {
    return ;
}*/

/*Uint64 readNet(Uint64 _object) {
    return ntohll(_object);
}*/

/*Sint64 readNet(Sint64 _object) {
    return ;
}*/
