//#define EUREKA_EXPORT
#include "networking.h"
#ifdef C_NETWORK_INTERFACE
#include <iostream>
#include <string>
#include <list>
#include <SDL_net.h>
#include "BST.h"
#include "typedefs.h"
#include "threading.h"
class Game;
#endif
#include "rand_generators.h"
#include "eureka.h"

#include <windows.h>

//Engine name space macro
//ENGINE_NAMESPACE

unsigned int ip_to_int(const char* ip);

NetNode::NetNode(size_t id, const std::string& host, size_t portValue, bool p_udp, int maxConn, bool hostIP)
{
    nodeID = id;
    if(SDLNet_ResolveHost(&ip, host.c_str(), portValue) == -1)
        std::cerr << "NetNode Error: Failed to resolve address! SDL_Net: " << SDLNet_GetError() << std::endl;
    if(hostIP)
    {
        uint32_t newIp = ip_to_int(host.c_str());
        SetNodeIP(newIp);
        SetNodePort(portValue);
    }
    badNode = false;
    if(p_udp)
    {
        /*The struct ip will contain the ip of the remote host and the port that host is operating on.*/
        UDPpacket connectPacket, ackPacket;
        size_t trys = 0;
        usocket = SDLNet_UDP_Open(NET_ANYUDPPORT);
        if(!usocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create UDP socket! SDL_Net: " << SDLNet_GetError() << std::endl;
            badNode = true;
        }
        //Bind to a channel
        //udpChannel = randUniform(Range(0, SDLNET_MAX_UDPCHANNELS - 1));
        udpChannel = SDLNet_UDP_Bind(usocket, ANY_CHANNEL, &ip);
        if(udpChannel == -1)
        {
            std::cerr << "NetNode Error: Failed to bind UDP socket to IP address! " << SDLNet_GetError() << std::endl;
            badNode = true;
        }
        /*Now that we are ready to send data over the protocol, let's fill a packet with a connect signal so the server can acknowledge
        this client connection!*/
        connectPacket.data = (Uint8*)new byte[10];//data buffer
        strcpy((char*)connectPacket.data, "CONNECT\0");//fill data buffer
        connectPacket.address = ip;//ip address of remote target
        connectPacket.channel = udpChannel;//This client's channel!
        connectPacket.len = 8;//size of msg
        connectPacket.maxlen = 10; //max size that can be expected from packet!
        //Let's send the signal and hope the server got it! Then, wait for acknowledgement signal
        SDLNet_UDP_Send(usocket, udpChannel, &connectPacket);
        //Let's set up a data buffer for the acknowledge packet
        ackPacket.data = new byte[10];
        ackPacket.maxlen = 10;
        while(SDLNet_UDP_Recv(usocket, &ackPacket) != -1)
        {
            if(!strcmp((const char*)ackPacket.data, "ACK\0"))
            {
                std::cout << "Server acknowledged connection!" << std::endl;
                break;
            }
            if(trys == TIMEOUT_TRYS)
            {
                std::cout << "Connection attempt timed out! :(" << std::endl;
                break;
            }
            trys++;
            sleep(100000);
        }
        //let's clean up
        delete[] connectPacket.data;
        delete[] ackPacket.data;
    }
    else
    {
        tsocket = SDLNet_TCP_Open(&ip);
        if(!tsocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create TCP socket! SDL_Net: " << SDLNet_GetError() << std::endl;
            badNode = true;
        }
    }
    maxConnections = maxConn;
    port = portValue;
    server = false;
    udp = p_udp;
}

NetNode::NetNode(size_t id, size_t portValue, bool p_udp, int maxConn)
{
    nodeID = id;
    if(SDLNet_ResolveHost(&ip, NULL, portValue) == -1)
        std::cerr << "NetNode Error: Failed to resolve address! SDL_Net: " << SDLNet_GetError() << std::endl;
    badNode = false;
    if(p_udp)
    {
        usocket = SDLNet_UDP_Open(portValue);
        if(!usocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create UDP socket! SDL_Net: " << SDLNet_GetError() << std::endl;
            badNode = true;
        }
        //Bind to a channel
        /*udpChannel = SDLNet_UDP_Bind(usocket, -1, &ip);
        if(udpChannel == -1)
        {
            std::cerr << "NetNode Error: Failed to bind UDP socket to IP address! " << SDLNet_GetError() << std::endl;
            badNode = true;
        }*/
    }
    else
    {
        tsocket = SDLNet_TCP_Open(&ip);
        if(!tsocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create TCP socket! SDL_Net: " << SDLNet_GetError() << std::endl;
            badNode = true;
        }
    }
    maxConnections = maxConn;
    port = portValue;
    server = true;
    udp = p_udp;
}

NetNode::~NetNode()
{
    //Clean all tcp connections
    std::vector<TCPClient> tmp = tcpClients.getContents();
    for(size_t i = 0; i < tmp.size(); i++)
    {
        SDLNet_TCP_Close(tmp[i].sock);
    }
    SDLNet_TCP_Close(tsocket);

    //Clean UDP socket
    SDLNet_UDP_Close(usocket);
}

const IPaddress& NetNode::GetAddress() const
{
    return ip;
}

TCPsocket& NetNode::GetTCPSocket(int client_id)
{
    if(client_id < 0)
        return tsocket;
    return tcpClients[client_id].sock;
}

TCPClient NetNode::GetTCPClientInfo(size_t client_id)
{
    return tcpClients[client_id];
}

UDPsocket& NetNode::GetUDPSocket()
{
    return usocket;
}

UDPClient NetNode::GetUDPClientInfo(int client_id) const
{
    UDPClient c;
    if(client_id == NO_CLIENT)
    {
        c.ip = ip;
        c.udp = true;
        return c;
    }
    if(udpClients.search(client_id, c))
        c = c;
    //Return default instance of udpclient if there was no client in channel! Default one has all channels set to -1!
    return c;
}

size_t NetNode::GetPort() const
{
    return port;
}

size_t NetNode::GetNodeID() const
{
    return nodeID;
}

size_t NetNode::GetClientCount() const
{
    if(udp)
        return tcpClients.size();
    return udpClients.size();
}

int NetNode::GenerateUDPID()
{
    //Create a random initial id
    int id = randUniform(Range(0, maxConnections));
    //Now, let's verify it is not taken and keep making ids until we find an empty spot.
    //We also check that the socket is not saturated with clients!
    while(isUDPIDUsed(id))
    {
        id = randUniform(Range(0, maxConnections));
    }
    return id;
}

bool NetNode::isUDP() const
{
    return udp;
}

bool NetNode::isServer() const
{
    return server;
}

bool NetNode::isBad() const
{
    return badNode;
}

bool NetNode::hasID(size_t client_id)
{
    TCPClient tmp;
    return tcpClients.search(client_id, tmp);
}

bool NetNode::isUDPIDUsed(int client_id) const
{
    UDPClient tmp;
    return udpClients.search(client_id, tmp);
}

size_t NetNode::AcceptTCPClient()
{
    //Create storage place for client info
    TCPClient client;
    //Accept client connections
    TCPsocket tmp;
    tmp = SDLNet_TCP_Accept(tsocket);// Accept socket
    if(tmp)
    {
        //Request hash for id
        size_t id = randUniform(Range(0, maxConnections));
        while(id < size_t(maxConnections) && hasID(id))//Make sure the max value of size_t is reserved
        {
            id = randUniform(Range(0, maxConnections));
        }
        //Fill client info!
        client.sock = tmp;
        client.host = SDLNet_TCP_GetPeerAddress(tmp)->host;
        client.port = SDLNet_TCP_GetPeerAddress(tmp)->port;
        client.host_name = SDLNet_ResolveIP(SDLNet_TCP_GetPeerAddress(tmp));
        client.id = id;
        //Add client to container
        tcpClients.insert(id, client);
        return id;
    }
    /*else
    {
        std::cerr << "NetNode Error: Failed to accept TCP client! " << SDLNet_GetError() << std::endl;
    }*/
    return GetMaxValueSizeT();//Return max value of size_t on error;
}

int NetNode::RegisterUDPClient(const IPaddress& ip, int channel)
{
    //Let's create a storage place for this client!
    UDPClient uclient;
    //Let's store metadata
    uclient.ip = ip;
    uclient.id = GenerateUDPID();
    udpClients.insert(uclient.id, uclient);
    return uclient.id;
}

void NetNode::UnRegisterTCPClient(int client_id)
{
    if(client_id < 0)
        return;
    TCPClient tmp;
    tcpClients.search(client_id, tmp);//Find client socket
    if(tmp.sock)
    {
        SDLNet_TCP_Close(tmp.sock);//Close socket
        tcpClients.remove(client_id);//Remove socket
    }
}

void NetNode::UnRegisterUDPClient(int channel)
{
    SDLNet_UDP_Unbind(usocket, channel);
}

void NetNode::SetNodeIP(uint32_t newip)
{
    SDLNet_Write32(newip, &newip);
    ip.host = newip;
}

void NetNode::SetNodePort(uint16_t newPort)
{
    SDLNet_Write16(newPort, &newPort);
    ip.port = newPort;
}

NetworkManager::NetworkManager(ThreadSystem* owner)
{
    owner_ref = owner;
    mtu = 1;
}

void NetworkManager::initNetSys()
{
    mutex_net_id = owner_ref->SpawnMutex();
}

NetworkManager::~NetworkManager()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    std::vector<NetNode*> tmp = connections.getContents();
    for(size_t i = 0; i < tmp.size(); i++)//Free nodes
    {
        delete tmp[i];
        tmp[i] = NULL;
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    //Destroy mutex
    owner_ref->DeleteMutex(mutex_net_id);
}

size_t NetworkManager::CreateClientConnection(const std::string& host, size_t port, bool udp)
{
    size_t id = hasher();
    NetNode* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    while(hasNetNode(id))//Renew id if it already exists in the connections container
    {
        id = hasher();
    }

    tmp = new NetNode(id, host, port, udp);
    if(tmp && !tmp->isBad())//If allocation was successful
        connections.insert(id, tmp);//Add to our connections storage tree.
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return id;
}

size_t NetworkManager::CreateClientConnectionIP(const std::string& ip, size_t port, bool udp)
{
    size_t id = hasher();
    uint32_t intIp = ip_to_int(ip.c_str());
    NetNode* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    while(hasNetNode(id))//Renew id if it already exists in the connections container
    {
        id = hasher();
    }

    tmp = new NetNode(id, ip, port, udp, 100, true);
    tmp->SetNodeIP(intIp);
    if(tmp && !tmp->isBad())//If allocation was successful
        connections.insert(id, tmp);//Add to our connections storage tree.
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return id;
}

bool NetworkManager::hasNetNode(size_t conn_id)
{
    if(!connections.size())
        return false;
    NetNode* tmp = NULL;
    connections.search(conn_id, tmp);
    if(tmp)
        return true;
    return false;
}

size_t NetworkManager::CreateServer(size_t port, bool udp)
{
    size_t id = hasher();
    NetNode* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    while(hasNetNode(id))//Renew id if it already exists in the connections container
    {
        id = hasher();
    }

    tmp = new NetNode(id, port, udp);
    if(tmp && !tmp->isBad())//If allocation was successful
        connections.insert(id, tmp);//Add to our connections storage tree.
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return id;
}

size_t NetworkManager::AcceptTCPClient(size_t socket_id)
{
    NetNode* tmp = NULL;
    size_t client_id = GetMaxValueSizeT();
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a server
    if(tmp && tmp->isServer())
    {
        client_id = tmp->AcceptTCPClient();
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return client_id;
}

int NetworkManager::AcceptUDPClient(size_t socket_id)
{
    NetNode* tmp = NULL;
    size_t res = 0, client_id;
    UDPpacket p = RecvUDPSignal(socket_id, res);//Read 1st packet
    while(strcmp((const char*)p.data, "CONNET\0") && res <= 0)
    {
        sleep(1000);
        delete[] p.data;
        p = RecvUDPSignal(socket_id, res);
    }
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a server
    if(tmp && tmp->isServer())
    {
        //Since we received a connection signal, let's register the client
        client_id = tmp->RegisterUDPClient(p.address, p.channel);
    }
    //Now, we reuse the packet to send an acknowledgment signal!
    strcpy((char*) p.data, "ACK\0");
    SDLNet_UDP_Send(tmp->GetUDPSocket(), ANY_CHANNEL, &p);
    //let's clean up
    delete[] p.data;
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    //return the channel id. It will serve the same purpose as the client id in the TCP component of this library
    return client_id;
}


void NetworkManager::CloseUDPClient(size_t socket_id, int channel)
{
    NetNode* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a server
    if(tmp && tmp->isServer())
    {
        tmp->UnRegisterUDPClient(channel);
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
}

void NetworkManager::SendData(void_ptr data, size_t len, size_t socket_id, int client_id)
{
    NetNode* tmp = NULL;
    UDPpacket** packets = NULL;
    size_t howmany = len / mtu;//# of packets for UDP transmission
    std::string buff = (const char*) data;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a valid node
    if(tmp)
    {
        if(tmp->isUDP())
        {
            UDPsocket& soc = tmp->GetUDPSocket();
            UDPClient c;
            if(howmany == 0)
                howmany = 1;
            std::string packetBuffers[howmany];
            packets = SDLNet_AllocPacketV(howmany, mtu);//Pre-alloc vector of packets
            if(packets)
            {
                c = tmp->GetUDPClientInfo(client_id);
               for(size_t i = 0; i < howmany; i++)//Fill packets
            {
                packetBuffers[i] = buff.substr(i * mtu, mtu);//allocate new copy of token
                packetBuffers[i] += '\0';
                strcpy((char*)packets[i]->data, packetBuffers[i].c_str());//copy contents
                packets[i]->address = c.ip;//ip address of remote target
                packets[i]->len = packetBuffers[i].size();//size of msg
                packets[i]->maxlen = mtu;
                packets[i]->channel = ANY_CHANNEL;
            }
            //Send packets
            if(!SDLNet_UDP_SendV(soc, packets, howmany))
                std::cout << "Error sending packets! @SendData! SDL_Net: " << SDLNet_GetError();
            }
            else
            {
                std::clog << "NetworkManager Error: Could not allocate packet buffers for transmission over UDP! " << __FILE__ << ":" <<
                    __LINE__ << ": " << SDLNet_GetError() << std::endl;
            }
            //Clean the packets
            SDLNet_FreePacketV(packets);
            packets = NULL;
        }
        else
        {
            if(SDLNet_TCP_Send(tmp->GetTCPSocket(client_id), data, len) < len)
            {
                std::clog << "NetworkManager Error: Could not send data to client " << client_id << ": "
                << SDLNet_TCP_GetPeerAddress(tmp->GetTCPSocket(client_id))->host << std::endl;
                std::clog << SDLNet_GetError() << std::endl;
                std::clog << "Client will be disconnected!" << std::endl;
                if(tmp->isServer())
                    tmp->UnRegisterTCPClient(client_id);
            }
        }
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
}

void NetworkManager::SendDataBoolean(const bool& data, size_t socket_id, int client_id)
{
    SendData((void_ptr)&data, sizeof(bool), socket_id, client_id);
}

void NetworkManager::SendDataStr(const std::string& data, size_t socket_id, int client_id)
{
    SendData((void_ptr)data.c_str(), data.size() + 1, socket_id, client_id);
}

void NetworkManager::SendDataInt(const int& data, size_t socket_id, int client_id)
{
    SendData((void_ptr)&data, sizeof(int), socket_id, client_id);
}

void NetworkManager::SendDataDouble(const double& data, size_t socket_id, int client_id)
{
    SendData((void_ptr)&data, sizeof(double), socket_id, client_id);
}

void NetworkManager::SendDataChar(const char data, size_t socket_id, int client_id)
{
    SendData((void_ptr)&data, sizeof(char), socket_id, client_id);
}

void NetworkManager::SendUDPSignal(size_t socket_id, const std::string& sig_data)
{
    SendData((void_ptr)sig_data.c_str(), sig_data.size() + 1, socket_id);
}

void NetworkManager::RecvData(void_ptr data, size_t maxlen, size_t socket_id, int client_id)
{
    NetNode* tmp = NULL;
    UDPpacket** packets = NULL;
    size_t howmany = maxlen / mtu;//# of packets for UDP transmission
    std::string dataBuff;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a valid node
    if(tmp)
    {
        if(tmp->isUDP())
        {
            UDPsocket& soc = tmp->GetUDPSocket();
            if(howmany == 0)
                howmany = 1;
            packets = SDLNet_AllocPacketV(howmany, mtu);//Pre-alloc vector of packets
            if(packets)
            {
                size_t res = SDLNet_UDP_RecvV(soc, packets);
                if(res < 0)
                {
                    //Report error
                    std::clog << "NetworkManager Error: Could not receive UDP packets! This may be caused by a connection error! " << __FILE__ << ":" <<
                        __LINE__ << ": " << SDLNet_GetError() << std::endl;
                    static_cast<char*>(data)[0] = '\0';//Set the first spot as a null character to indicate nothing could be received!
                }
                else if(res > 0)
                {
                    for(size_t i = 0; i < res; i++)//extract and package data buffers
                    {
                        dataBuff += (char*)packets[i]->data;
                    }
                    //copy final buffer
                    strcpy((char*) data, dataBuff.c_str());
                }
            }
            else
            {
                std::clog << "NetworkManager Error: Could not allocate packet buffers for storage of UDP data! " << __FILE__ << ":" <<
                    __LINE__ << ": " << SDLNet_GetError() << std::endl;
            }
            SDLNet_FreePacketV(packets);
            packets = NULL;
        }
        else
        {
            if(SDLNet_TCP_Recv(tmp->GetTCPSocket(client_id), data, maxlen) < 0)
            {
                std::clog << "NetworkManager Error: Could not receive data from client " << client_id << ": "
                << SDLNet_TCP_GetPeerAddress(tmp->GetTCPSocket(client_id))->host << std::endl;
                std::clog << SDLNet_GetError() << std::endl;
                std::clog << "Client will be disconnected!" << std::endl;
                tmp->UnRegisterTCPClient(client_id);
                static_cast<char*>(data)[0] = '\0';
            }
        }
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
}

void NetworkManager::RecvDataStr(std::string& data, size_t maxlen, size_t socket_id, int client_id)
{
    char* tmp = new char[maxlen];
    RecvData(tmp, maxlen, socket_id, client_id);
    data = tmp;
    delete[] tmp;
}

void NetworkManager::RecvDataInt(int& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(int);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    data = (int)(*tmp);
    delete[] tmp;
}

void NetworkManager::RecvDataChar(char& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(char);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    data = (char)(tmp[0]);
    delete[] tmp;
}

void NetworkManager::RecvDataBoolean(bool& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(bool);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    data = (bool)(*tmp);
    delete[] tmp;
}

void NetworkManager::RecvDataDouble(double& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(double);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    data = (double)(*tmp);
    delete[] tmp;
}

UDPpacket NetworkManager::RecvUDPSignal(size_t socket_id, size_t& r)
{
    NetNode* tmp = NULL;
    UDPpacket p;
    p.data = new byte[10];
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a valid node
    if(tmp)
    {
        if(tmp->isUDP())
        {
            UDPsocket& soc = tmp->GetUDPSocket();
            r = SDLNet_UDP_Recv(soc, &p);
            if(r > 0)
            {
                //Unlock mutex
                owner_ref->UnlockMutex(mutex_net_id);
                return p;
            }
        }
    }
    p.data[0] = '\0';
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return p;
}

void NetworkManager::PingUDPClient(size_t socket_id, int channel, size_t timeout)
{
    NetNode* tmp = NULL;
    UDPpacket p;
    size_t result, trys = 0;
    SendUDPSignal(socket_id, "PING");//Broadcast ping command
    sleep(timeout);//Give some time for the response to arrive
    p = RecvUDPSignal(socket_id, result);//attempt to get response
    while(p.data[0] == '\0')//Repeat a couple of times to rule out data transmission corruption
    {
        if(trys == TIMEOUT_TRYS)
            break;
        p = RecvUDPSignal(socket_id, result);//attempt to get response
        trys++;
    }
    if(p.data[0] == '\0')//If response failed to return a non empty message, kill the channel
    {
        p.channel = channel;
        CloseUDPClient(socket_id, p.channel);//kill the client
    }
    //lets clean up
    delete[] p.data;
}

size_t NetworkManager::GetMaxNumUDPChannels()
{
    return SDLNET_MAX_UDPCHANNELS;
}

UDPClient NetworkManager::GetUDPClientInfo(size_t socket_id, int channel)
{
    NetNode* tmp = NULL;
    connections.search(socket_id, tmp);
    return tmp->GetUDPClientInfo(channel);
}

TCPClient NetworkManager::GetTCPClientInfo(size_t socket_id, size_t client_id)
{
    NetNode* tmp = NULL;
    connections.search(socket_id, tmp);
   return tmp->GetTCPClientInfo(client_id);
}

void NetworkManager::SetMTU(size_t max)
{
    mtu = max;
}

#ifdef C_NETWORK_INTERFACE
//C interface
//vars
NetworkManager* mngr = NULL;
ThreadSystem* thrd = NULL;
void* initNetwork()
{
    thrd = new ThreadSystem();
    mngr = new NetworkManager(thrd);
    mngr->initNetSys();
    SDLNet_Init();
    return mngr;
}
//Setters
size_t CreateClientConnection(void* network, const char* host, size_t port, int udp)
{
    return ((NetworkManager*)network)->CreateClientConnection(host, port, udp);
}

size_t CreateClientConnectionIP(void* network, const char* ip, size_t port, int udp)
{
    return ((NetworkManager*)network)->CreateClientConnectionIP(ip, port, udp);
}

size_t CreateServer(void* network, size_t port, int udp)
{
    return ((NetworkManager*)network)->CreateServer(port, udp);
}
size_t AcceptTCPClient(void* network, size_t socket_id)
{
    return ((NetworkManager*)network)->AcceptTCPClient(socket_id);
}
int AcceptUDPClient(void* network, size_t socket_id)
{
    return ((NetworkManager*)network)->AcceptUDPClient(socket_id);
}
void CloseUDPClient(void* network, size_t socket_id, int channel)
{
    ((NetworkManager*)network)->CloseUDPClient(socket_id, channel);
}
void SetMTU(void* network, size_t max)
{
    ((NetworkManager*)network)->SetMTU(max);
}

//Sockets stuff
void SendData(void* network, void_ptr data, size_t len, size_t socket_id, int client_id)
{
    ((NetworkManager*)network)->SendData(data, len, socket_id, client_id);
}
void SendDataStr(void* network, const char* data, size_t socket_id, int client_id)
{
    ((NetworkManager*)network)->SendDataStr(data, socket_id, client_id);
}
void SendDataInt(void* network, const int data, size_t socket_id, int client_id)
{
    ((NetworkManager*)network)->SendDataInt(data, socket_id, client_id);
}
void SendDataDouble(void* network, const double data, size_t socket_id, int client_id)
{
    ((NetworkManager*)network)->SendDataDouble(data, socket_id, client_id);
}
void SendDataChar(void* network, const char data, size_t socket_id, int client_id)
{
    ((NetworkManager*)network)->SendDataChar(data, socket_id, client_id);
}
void SendUDPSignal(void* network, size_t socket_id, const char* sig_data)
{
    ((NetworkManager*)network)->SendUDPSignal(socket_id, sig_data);
}
void RecvData(void* network, void_ptr data, size_t maxlen, size_t socket_id, int client_id)
{
    ((NetworkManager*)network)->RecvData(data, maxlen, socket_id, client_id);
}
char* RecvDataStr(void* network, size_t maxlen, size_t socket_id, int client_id)
{
    char* tmp = new char[maxlen];
    ((NetworkManager*)network)->RecvData(tmp, maxlen, socket_id, client_id);
    return tmp;
}
int RecvDataInt(void* network, size_t socket_id, int client_id)
{
    int data;
    ((NetworkManager*)network)->RecvDataInt(data, socket_id, client_id);
    return data;
}
char RecvDataChar(void* network, size_t socket_id, int client_id)
{
    char data;
    ((NetworkManager*)network)->RecvDataChar(data, socket_id, client_id);
    return data;
}

double RecvDataDouble(void* network, size_t socket_id, int client_id)
{
    double data;
    ((NetworkManager*)network)->RecvDataDouble(data, socket_id, client_id);
    return data;
}
void PingUDPClient(void* network, size_t socket_id, int channel, size_t timeout)
{
    ((NetworkManager*)network)->PingUDPClient(socket_id, channel, timeout);
}

//Getters
size_t GetMaxNumUDPChannels(void* network)
{
    return ((NetworkManager*)network)->GetMaxNumUDPChannels();
}
UDPClient GetUDPClientInfo(void* network, size_t socket_id, int channel)
{
    return((NetworkManager*)network)->GetUDPClientInfo(socket_id, channel);
}
TCPClient GetTCPClientInfo(void* network, size_t socket_id, size_t client_id)
{
    return ((NetworkManager*)network)->GetTCPClientInfo(socket_id, client_id);
}

unsigned int ip_to_int(const char* ip)
{
    unsigned v = 0;
    int i;
    const char* start = ip;

    for(i = 0; i < 4; i++)
    {
        char c;
        int n = 0;
        while(1)
        {
            c = *start;
            start++;
            if(c >= '0' && c <= '9')
            {
                n *= 10;
                n += c - '0';
            }
            else if((i < 3 && c == '.') || i == 3)
                break;
            else
            {
                return 0;
            }
        }
        if(n >= 256)
        {
            return 0;
        }
        v *= 256;
        v += n;
    }
    return v;
}

#endif
//End of namespace macro
//ENGINE_NAMESPACE_END
