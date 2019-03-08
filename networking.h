#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED
//#ifndef C_NETWORK_INTERFACE
#include <iostream>
#include <string>
#include <list>
#include <SDL_net.h>
#include "BST.h"
#include "typedefs.h"
#include "threading.h"

//Engine name space macro
//ENGINE_NAMESPACE

#define NO_CLIENT -1
#define TIMEOUT_TRYS 50
#define NET_ANYUDPPORT 0
#define ANY_CHANNEL -1

class Game;

struct UDPClient
{
    IPaddress ip;
    int id;
    bool udp;

    UDPClient()
    {
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
    NetNode(size_t id, const std::string& host, size_t portValue, bool p_udp = false, int maxConn = 100, bool hostIP = false);//Client constructor
    NetNode(size_t id, size_t portValue, bool p_udp = false, int maxConn = 100);//Server constructor
    ~NetNode();

    //Getters
    const IPaddress& GetAddress() const;
    TCPsocket& GetTCPSocket(int client_id = -1);
    TCPClient GetTCPClientInfo(size_t client_id);
    UDPsocket& GetUDPSocket();
    UDPClient GetUDPClientInfo(int client_id) const;
    size_t GetPort() const;
    size_t GetNodeID() const;
    size_t GetClientCount() const;
    void SetNodePort(uint16_t newPort);
    void SetNodeIP(uint32_t newip);
    int GenerateUDPID();
    bool isUDP() const;
    bool isServer() const;
    bool isBad() const;
    bool isUDPIDUsed(int client_id) const;

    //Setters
    size_t AcceptTCPClient();
    int RegisterUDPClient(const IPaddress& ip, int channel);
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
    int udpChannel;

    //Clients
    BinarySearchTree<size_t, TCPClient> tcpClients;
    BinarySearchTree<int, UDPClient> udpClients;

    bool hasID(size_t client_id);
};

class NetworkManager
{
public:
    //ctors and dtor
    NetworkManager(ThreadSystem* owner);
    ~NetworkManager();
    void initNetSys();

    //Setters
    size_t CreateClientConnection(const std::string& host, size_t port, bool udp = false);
    size_t CreateClientConnectionIP(const std::string& ip, size_t port, bool udp = false);
    size_t CreateServer(size_t port, bool udp = false);
    size_t AcceptTCPClient(size_t socket_id);
    int AcceptUDPClient(size_t socket_id);
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
    ThreadSystem* owner_ref;
    size_t mutex_net_id;
    size_t mtu;

    bool hasNetNode(size_t conn_id);
    UDPpacket RecvUDPSignal(size_t socket_id, size_t& r);
};
//#endif
#ifdef C_NETWORK_INTERFACE
#define CDECL __attribute__((cdecl))
typedef void* void_ptr;
typedef unsigned int size_t;
#ifdef __cplusplus
extern "C"
{
#endif
//C interface
CDECL void* initNetwork();
//Setters
CDECL size_t CreateClientConnection(void* network, const char* host, size_t port, int udp);
CDECL size_t CreateClientConnectionIP(void* network, const char* ip, size_t port, int udp);
CDECL size_t CreateServer(void* network, size_t port, int udp);
CDECL size_t AcceptTCPClient(void* network, size_t socket_id);
CDECL int AcceptUDPClient(void* network, size_t socket_id);
CDECL void CloseUDPClient(void* network, size_t socket_id, int channel);
CDECL void SetMTU(void* network, size_t max);

//Sockets stuff
CDECL void SendData(void* network, void_ptr data, size_t len, size_t socket_id, int client_id);
CDECL void SendDataStr(void* network, const char* data, size_t socket_id, int client_id);
CDECL void SendDataInt(void* network, const int data, size_t socket_id, int client_id);
CDECL void SendDataDouble(void* network, const double data, size_t socket_id, int client_id);
CDECL void SendDataChar(void* network, const char data, size_t socket_id, int client_id);
CDECL void SendUDPSignal(void* network, size_t socket_id, const char* sig_data);
CDECL void RecvData(void* network, void_ptr data, size_t maxlen, size_t socket_id, int client_id);
CDECL char* RecvDataStr(void* network, size_t maxlen, size_t socket_id, int client_id);
CDECL int RecvDataInt(void* network, size_t socket_id, int client_id);
CDECL char RecvDataChar(void* network, size_t socket_id, int client_id);
CDECL double RecvDataDouble(void* network, size_t socket_id, int client_id);
CDECL void PingUDPClient(void* network, size_t socket_id, int channel, size_t timeout);

//Getters
CDECL size_t GetMaxNumUDPChannels(void* network);
//CDECL UDPClient GetUDPClientInfo(void* network, size_t socket_id, int channel);
//CDECL TCPClient GetTCPClientInfo(void* network, size_t socket_id, size_t client_id);
CDECL unsigned int ip_to_int(const char* ip);
#ifdef __cplusplus
}
#endif
#else
unsigned int ip_to_int(const char* ip);
#endif
//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // NETWORKING_H_INCLUDED
