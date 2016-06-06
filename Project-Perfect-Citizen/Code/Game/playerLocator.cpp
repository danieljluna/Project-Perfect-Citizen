//
//  playerLocator.cpp
//  Project-Perfect-Citizen
//
//  Created by Michael Lowe on 5/31/16.
//  Copyright © 2016 Hyperfocus Games. All rights reserved.
//

#ifdef WINDOWS_MARKER
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib") //this may cause issues with CMAKE
#endif

#include "playerLocator.hpp"


PlayerLocator::PlayerLocator() {
    fullLocation = generateLocation();
    reader.parse(fullLocation, value);
    ip_ = value["ip"].asString();
    loc_ = value["loc"].asString();
    lat_ = loc_.substr(0, loc_.find_first_of(','));
    long_ = loc_.substr(loc_.find_first_of(','));
    city_ = value["city"].asString();
    postal_ = value["postal"].asString();
    region_ = value["region"].asString();
    country_ = value["country"].asString();
}

PlayerLocator::~PlayerLocator() {
    
}

std::string PlayerLocator::generateLocation() {
        std::string tmp;
    try {
#ifdef WINDOWS_MARKER
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::exception("WSAStartup failed");
        }

        char *hostname = "ipinfo.io";
        struct addrinfo hints, *res;
        struct in_addr addr;
        int err;
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_INET;
        hints.ai_flags = AI_PASSIVE;

        if ((err = getaddrinfo(hostname, "http", &hints, &res)) != 0) {
            throw std::exception("Error in getaddrinfo: " + err);
        }

        addr.S_un = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.S_un;

        int s;
        if ((s = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
            throw std::exception("Error getting socket");
        }

        if (connect(s, res->ai_addr, res->ai_addrlen) == -1) {
            throw std::exception("Error connecting to host");
        }

        send(s, "GET / HTTP/1.1\r\nHost: ipinfo.io\r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: ipinfo.io\r\nConnection: close\r\n\r\n"), 0);
        char buffer[10000];
        std::stringstream strs;
        int nDataLength;
        while ((nDataLength = recv(s, buffer, 10000, 0)) > 0) {
            int i = 0;
            while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
                strs << buffer[i];
                i++;
            }
        }

        closesocket(s);

        freeaddrinfo(res);

        WSACleanup();

        tmp = strs.str();
        tmp = tmp.substr(tmp.find_first_of("{"));

#else
        FILE *pipe;


        char str[1000];

        pipe = popen("curl ipinfo.io", "r");

        while (fgets(str, 1000, pipe)) {
            tmp += str;
        }
        pclose(pipe);
#endif

        return tmp;

    }
    catch (std::exception& e) {
        //No member named 'cerr' in namespace 'std'
        //std::cerr << e.what() << std::endl;
		e.what(); //to mute the warning
        return "{\n   \"ip\": \"127.0.0.1\",\n   \"hostname\" : \"Your Computer\",\n   \"city\" : \"Your City\",\n   \"region\" : \"Your State\",\n   \"country\" : \"Your Country\",\n   \"loc\" : \"____,____\",\n   \"org\" : \"Your Home\",\n   \"postal\" : \"We're Watching\",\n   \"phone\" : \"###\" \n}";
    }
}