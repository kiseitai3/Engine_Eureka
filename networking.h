#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED
#include <iostream>
#include <string>
#include <list>
#include <SDL_net.h>
#include "BST.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class Game;

struct UDPClient
{
    IPaddress ip;
    int nativeChannel;
    int serverChannel;
    bool udp;

    UDPClient()
    {
        nativeChannel = -1;
        serverChannel = -1;
        udp = true;
    }
};

struct TCPClient
{
    size_t id;
    size_t host;
    short port;
    std::string host_name;
    TCPsocket sock;

    TCPClient()
    {
        host_name = "INVALID";
    }
};

class NetNode
{
public:
    //ctors and dtor
    NetNode(size_t id, const std::string& host, size_t portValue, bool udp = false, int maxConn = 0);//Client constructor
    NetNode(size_t id, size_t portValue, bool udp = false, int maxConn = 0);//Server constructor
    ~NetNode();

    //Getters
    const IPaddress& GetAddress() const;
    TCPsocket& GetTCPSocket(int client_id = -1);
    TCPClient GetTCPClientInfo(size_t client_id);
    UDPsocket& GetUDPSocket();
    UDPClient GetUDPClientInfo(int channel) const;
    size_t GetPort() const;
    size_t GetNodeID() const;
    size_t GetClientCount() const;
    size_t GenerateUDPChannel();
    bool isUDP() const;
    bool isServer() const;
    bool isBad() const;
    bool isUDPChannelFull(int channel) const;

    //Setters
    size_t AcceptTCPClient();
    void RegisterUDPClient(const IPaddress& ip, int channel);
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
    TCPsocket tsocket;
    UDPsocket usocket;
    //Connection stuff
    int maxConnections;

    //Clients
    BinarySearchTree<size_t, TCPClient> tcpClients;
    std::list<UDPClient> udpClients;

    bool hasID(size_t client_id);
};

class NetworkManager
{
public:
    //ctors and dtor
    NetworkManager(Game* owner);
    ~NetworkManager();

    //Setters
    size_t CreateClientConnection(const std::string& host, size_t port, bool udp = false);
    size_t CreateServer(size_t port, bool udp = false);
    size_t AcceptTCPClient(size_t socket_id);
    size_t AcceptUDPClient(size_t socket_id);
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
    void RecvData(void_ptr data, size_t maxlen, size_t socket_id, int client_id = -1);
    void RecvDataStr(std::string& data, size_t maxlen, size_t socket_id, int client_id = -1);
    void RecvDataInt(int& data, size_t socket_id, int client_id = -1);
    void RecvDataChar(char& data, size_t socket_id, int client_id = -1);
    void RecvDataBoolean(bool& data, size_t socket_id, int client_id = -1);
    void RecvDataDouble(double& data, size_t socket_id, int client_id = -1);
    void PingUDPClient(size_t socket_id, int channel, size_t timeout = 5000);

    //Getters
    size_t GetMaxNumUDPChannels();
    UDPClient GetUDPClientInfo(size_t socket_id, int channel);
    TCPClient GetTCPClientInfo(size_t socket_id, size_t client_id);


private:
    BinarySearchTree<size_t, NetNode*> connections;
    Game* owner_ref;
    size_t mutex_net_id;
    size_t mtu;

    bool hasNetNode(size_t conn_id);
    UDPpacket RecvUDPSignal(size_t socket_id, size_t& r);
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // NETWORKING_H_INCLUDED
