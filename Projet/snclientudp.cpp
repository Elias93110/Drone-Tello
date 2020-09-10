#include "snclientudp.h"
#include <iostream>
using namespace std;
#include <Ws2tcpip.h>

SNClientUDP::SNClientUDP(){
    /* ETAPE 1 */
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0){
        cout << "Echec lors de l'initialisation de la DLL Winsock2." << endl;
        etat = -1;
    }

    /* ETAPE 2 */
    sock = INVALID_SOCKET;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock == INVALID_SOCKET){
        cout << "socket function failed with error = " << WSAGetLastError() << endl;
        etat = -2;
    }
    else {
        cout << "socket function succeeded" << endl;
        etat = 0;
    }

    /* ETAPE 3 */
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = htonl(INADDR_ANY);
    service.sin_port = htons(8890);

    iResult = bind(sock,(SOCKADDR *)&service, sizeof(service));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"bind failed with error %u\n", WSAGetLastError());
        closesocket(sock);
        etat = -3;
    }
    else {
        wprintf(L"bind returned success\n");
    }

}

SNClientUDP::~SNClientUDP(){
    /*Destructeur*/
    closesocket(sock);
    WSACleanup();
}

bool SNClientUDP::EnvoyerMessage(const char* message, int taille){
    int iResult;
    sockaddr_in EnvoyerMessage;
    EnvoyerMessage.sin_family = AF_INET;
    EnvoyerMessage.sin_addr.s_addr = inet_addr("192.168.10.1");
    EnvoyerMessage.sin_port = htons(8889);

    iResult = sendto(sock, message, taille,0, (SOCKADDR *)&EnvoyerMessage, sizeof(EnvoyerMessage));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(sock);
        etat = -4;
        return 0;

    }
    return 1;
}

bool SNClientUDP::RecevoirMessage(){
    int iResult;
    char message[100];
    int taille=100;
    sockaddr_in RecevoirMessage;
    RecevoirMessage.sin_family = AF_INET;
    RecevoirMessage.sin_addr.s_addr = inet_addr("192.168.10.1");
    RecevoirMessage.sin_port = htons(8889);
    int RMessage = sizeof(RecevoirMessage);

    iResult = recvfrom(sock,message, taille, 0, (SOCKADDR *)&RecevoirMessage, &RMessage);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
        etat = -5;
        return 0;
    }
    cout << message <<endl;;
    return 1;

}

/*
void SNClientUDP::ModifierPortServeur(unsigned short port){

}

void SNClientUDP::ModifierAdresseIPServeur(const char adresse[16]){

}
*/
