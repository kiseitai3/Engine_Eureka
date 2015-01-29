#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED
#include <iostream>
#include <string>
#include <list>
#include <SDL_net>
#include "game.h"
#include "BST.h"
#include "typedefs.h"


class NetNode
{
public:
    //ctors and dtor
    NetNode(size_t id, const std::string& host, size_t portValue, bool udp = false, int maxConn = 0);
    NetNode(size_t id, size_t portValue, bool udp = false, int maxConn = 0);
    ~NetNode();

    //Getters
    IPaddress& GetAddress() const;
    TCPsocket& GetTCPSocket(int client_id = -1);
    UDPsocket& GetUDPSocket();
    size_t GetPort() const;
    size_t GetNodeID() const;
    size_t GetClientCount() const;
    bool isUDP() const;
    bool isServer() const;
    bool isBad() const;

    //Setters
    size_t AcceptTCPClient();
    void RegisterUDPClient(const IPaddress& ip);
    void UnRegisterTCPClient(int client_id);
    void UnRegisterUDPClient(int channel);

private:
    //IP address
    IPaddress ip;
    //Port
    size_t port;
    //ID
    size_t nodeID;
    //Flags
    bool udp;
    bool server;
    bool badNode;
    //Socket by protocol
    TCPsocket* tsocket;
    UDPsocket* usocket;
    //Connection stuff
    int maxConnections;
    int udpChannel;

    //Clients
    BinarySearchTree<size_t, TCPsocket*> tcpClients;

    bool hasID(size_t client_id) const;
};

class NetworkManager
{
public:
    //ctors and dtor
    NetworkManager(Game& owner);
    ~NetworkManager();

    //Setters
    size_t CreateClientConnection(const std::string& host, size_t port, bool udp = false);
    size_t CreateServer(size_t port, bool udp = false);
    void AcceptTCPClients(size_t socket_id);
    void AcceptUDPClient(size_t socket_id);
    void CloseUDPClient(size_t socket_id, int channel);
    void SetMTU(size_t max);

    //Sockets stuff
    void SendData(void_ptr data, size_t len, size_t socket_id, int client_id = -1);
    void SendDataStr(const std::string& data, size_t socket_id, int client_id = -1);
    void SendDataInt(const int& data, size_t socket_id, int client_id = -1);
    void SendDataBoolean(const bool& data, size_t socket_id, int client_id = -1);
    void SendDataDouble(const double& data, size_t socket_id, int client_id = -1);
    void SendDataChar(const char data, size_t socket_id, int client_id = -1);
    void SendUDPSignal(size_t socket_id, const std::string& sig_data);
    void RecvData(void_ptr& data, size_t maxlen, size_t socket_id, int client_id = -1);
    void RecvDataStr(std::string& data, size_t maxlen, size_t socket_id, int client_id = -1);
    void RecvDataInt(int& data, size_t socket_id, int client_id = -1);
    void RecvDataChar(char& data, size_t socket_id, int client_id = -1);
    void RecvDataBoolean(bool& data, size_t socket_id, int client_id = -1);
    void RecvDataDouble(double& data, size_t socket_id, int client_id = -1);
    void PingUDPClient(size_t socket_id, int channel, size_t timeout = 5000);

    //Getters
    size_t GetMaxNumUDPChannels();


private:
    BinarySearchTree<size_t, NetNode*> connections;
    Game* owner_ref;
    size_t mutex_net_id;
    size_t mtu;

    bool hasNetNode(size_t conn_id);
    UDPpacket RecvUDPSignal(size_t socket_id, size_t& r);
};


#endif // NETWORKING_H_INCLUDED
