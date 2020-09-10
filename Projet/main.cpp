#include <iostream>
#include "SNClientUDP.h"
using namespace std;

int main()
{
    SNClientUDP client;
    client.EnvoyerMessage("command",7);
    client.RecevoirMessage();
    client.EnvoyerMessage("takeoff",7);
    client.RecevoirMessage();

}

