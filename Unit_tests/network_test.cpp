#include "../eureka.h"
#include <SDL_net.h>
#include <iostream>
#include <string>

#include <windows.h>


//prototypes
void Send(Game& g, std::string& d, size_t socket_id, size_t client_id, bool server = true);
std::string Receive(Game& g, size_t socket_id, size_t client_id, bool server = true);

#ifdef SERVER_TEST

#ifdef TCP_TEST

int main(int argc, char *argv[])
{
    SDLNet_Init();
    Game g(false);
    size_t server_id, socket_id, client_id = GetMaxValueSizeT();
    size_t x;
    std::string d = "<empty>";

    //make server
    std::cout << "Creating TCP server!" << std::endl;
    server_id = g.CreateServer(1234, false);
    //Accept client
    std::cout << "Accepting client!" << std::endl;
    while(client_id == GetMaxValueSizeT())
    {
        client_id = g.AcceptTCPClient(server_id);
    }

    //receive msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        d = Receive(g, server_id, client_id, true);
        if(d != "<empty>\0")
        std::cout << "Client: " << d << std::endl;
    }

    d = "<empty>";

    //send msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        std::cin >> d;
        Send(g, d, server_id, client_id, true);
        if(d != "\0")
        std::cout << "Server: " << d << std::endl;
    }

    std::cout << "The session is over! Type anything to close the program!" << std::endl;
    std::cin >> x;

}

#else

int main(int argc, char *argv[])
{
    SDLNet_Init();
    Game g(false);
    size_t server_id, socket_id, client_id = GetMaxValueSizeT();
    size_t x;
    std::string d = "<empty>\0";

    //make server
    std::cout << "Creating UDP server!" << std::endl;
    server_id = g.CreateServer(1234, true);
    g.SetMTU(20);
    //Accept client
    std::cout << "Accepting client!" << std::endl;
    while(client_id == GetMaxValueSizeT())
    {
        client_id = g.AcceptUDPClient(server_id);
    }

    if(client_id == SDLNET_MAX_UDPCHANNELS)
    {
        std::cout << "Failed to accept client" << std::endl;
        std::cin >> x;
        return 0;
    }
    //receive msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        d = Receive(g, server_id, client_id, true);
        if(d != "<empty>\0")
        std::cout << "Client: " << d << std::endl;
    }

    d = "<empty>\0";
    std::cout << d << std::endl;

    //send msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        std::cin >> d;
        Send(g, d, server_id, client_id, true);
        if(d != "\0")
        std::cout << "Server: " << d << std::endl;
    }

    std::cout << "The session is over! Type anything to close the program!" << std::endl;
    std::cin >> x;

}
#endif
#else
#ifdef TCP_TEST
int main(int argc, char *argv[])
{
    SDLNet_Init();
    Game g(false);
    size_t server_id, socket_id, client_id = 0;
    size_t x;
    std::string d = "<empty>";

    //make server
    std::cout << "Connecting to TCP server!" << std::endl;
    socket_id = g.CreateClientConnection("localhost", 1234, false);

    //send msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        std::cin >> d;
        Send(g, d, socket_id, 0, false);
        std::cout << "Client: " << d << std::endl;
    }

    d = "<empty>";

    //receive msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        d = Receive(g, socket_id, client_id, false);
        if(d != "<empty>\0")
        std::cout << "Server: " << d << std::endl;
    }

    std::cout << "The session is over! Type anything to close the program!" << std::endl;
    std::cin >> x;

}
#else
int main(int argc, char *argv[])
{
    SDLNet_Init();
    Game g(false);
    size_t server_id, socket_id, client_id = 0;
    size_t x;
    std::string d = "<empty>";

    //make server
    std::cout << "Connecting to UDP server!" << std::endl;
    socket_id = g.CreateClientConnection("localhost", 1234, true);
    g.SetMTU(20);

    //send msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        std::cin >> d;
        Send(g, d, socket_id, 0, false);
        std::cout << "Client: " << d << std::endl;
    }

    d = "<empty>\0";
    std::cout << d << std::endl;

    //receive msgs
    while(d.size() > 0 && d != "Yourturn!")
    {
        d = Receive(g, socket_id, client_id, false);
        if(d != "<empty>\0")
        std::cout << "Server: " << d << std::endl;
    }

    std::cout << "The session is over! Type anything to close the program!" << std::endl;
    std::cin >> x;

}
#endif
#endif

std::string Receive(Game& g, size_t socket_id, size_t client_id, bool server)
{
    std::string d = "<empty>\0";
    if(server)
        g.RecvDataStr(d, 20, socket_id, client_id);
    else
        g.RecvDataStr(d, 20, socket_id, NO_CLIENT);
    if(d[0] != 'm')
    {
        d = "<empty>\0";
        return d;
    }
    sleep(10000000);
    if(d.size() > 0)
        return d.substr(1, d.find("11") - 1);
    return d;
}


void Send(Game& g, std::string& d, size_t socket_id, size_t client_id, bool server)
{
    if(server)
        g.SendDataStr("m" + d + "1111", socket_id, client_id);
    else
        g.SendDataStr("m" + d + "1111", socket_id, NO_CLIENT);
}
