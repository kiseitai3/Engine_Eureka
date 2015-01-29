#include "networking.h"

NetNode::NetNode(size_t id, const std::string& host, size_t portValue, bool udp = false, int maxConn = 0)
{
    nodeID = id;
    SDLNet_ResolveHost(&ip, host.c_str(), portValue);
    badNode = false;
    if(udp)
    {
        usocket = SDLNet_UDP_Open(0);
        if(!usocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create UDP socket! " << SDLNet_GetError() << std::end;
            badNode = true;
        }
        //Bind to a channel
        /*udpChannel = SDLNet_UDP_Bind(usocket, -1, &ip);
        if(udpChannel == -1)
        {
            std::cerr << "NetNode Error: Failed to bind UDP socket to IP address! " << SDLNet_GetError() << std::end;
            badNode = true;
        }*/
    }
    else
    {
        tsocket = SDLNet_TCP_Open(&ip);
        if(!tsocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create TCP socket! " << SDLNet_GetError() << std::end;
            badNode = true;
        }
    }
    maxConnections = maxConn;
    server = false;
}

NetNode::NetNode(size_t id, size_t portValue, bool udp = false, int maxConn = 0)
{
    nodeID = id;
    SDLNet_ResolveHost(&ip, host.c_str(), portValue);
    badNode = false;
    if(udp)
    {
        usocket = SDLNet_UDP_Open(portValue);
        if(!usocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create UDP socket! " << SDLNet_GetError() << std::end;
            badNode = true;
        }
        //Bind to a channel
        /*udpChannel = SDLNet_UDP_Bind(usocket, -1, &ip);
        if(udpChannel == -1)
        {
            std::cerr << "NetNode Error: Failed to bind UDP socket to IP address! " << SDLNet_GetError() << std::end;
            badNode = true;
        }*/
    }
    else
    {
        tsocket = SDLNet_TCP_Open(&ip);
        if(!tsocket)//An error occurred
        {
            std::cerr << "NetNode Error: Failed to create TCP socket! " << SDLNet_GetError() << std::end;
            badNode = true;
        }
    }
    maxConnections = maxConn;
    server = true;
}

NetNode::~NetNode()
{
    //Clean all tcp connections
    std::vector<TCPsocket*> tmp = tcpClients.GetContents();
    for(size_t i = 0; i < tmp.size(); i++)
    {
        SDLNet_TCP_Close(tmp[i]);
    }
    SDLNet_TCP_Close(tsocket);

    //Clean UDP socket
    SDLNet_UDP_Close(usocket);
}

IPaddress& NetNode::GetAddress() const
{
    return ip;
}

TCPsocket& NetNode::GetTCPSocket(int client_id)
{
    if(client_id < 0)
        return tsocket;
    return *tcpClients[client_id];
}

UDPsocket& NetNode::GetUDPSocket()
{
    return usocket;
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
    switch(udp)
    {
    case 0:
        return tcpClients.size();
        break;
    case 1:
        return udpClients.size();
        break;
    default:

    }
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

size_t NetNode::AcceptTCPClient()
{
    //Accept client connections
    TCPsocket* tmp = new TCPsocket;
    *tmp = SDLNet_TCP_Accept(tsocket);// Accept socket
    if(*tmp)
    {
        //Request hash for id
        size_t id = Game::hasher() % maxConnections;
        while(id < Game::GetMaxValueSizeT() && hashID(id))//Make sure the max value of size_t is reserved
        {
            id = Game::hasher() % maxConnections;
        }
        tcpClients.insert(id, tmp);
        return id;
    }
    else
    {
        std::cerr << "NetNode Error: Failed to accept TCP client! " << SDLNet_GetError() << std::endl;
    }
    return Game::GetMaxValueSizeT();//Return max value of size_t on error;
}

void NetNode::RegisterUDPClient(const IPaddress& ip)
{
    //Bind to a channel
    int channel = SDLNet_UDP_Bind(usocket, -1, &ip);
    if(channel == -1)
    {
        std::cerr << "NetNode Error: Failed to bind client IP to server socket! " << SDLNet_GetError() << std::end;
    }
}

void NetNode::UnregisterTCPClient(int client_id)
{
    TCPsocket* tmp = NULL;
    tcpClients.search(client_id, tmp);//Find client socket
    if(tmp)
    {
        SDLNet_TCP_Close(*tmp);//Close socket
        tcpClients.remove(client_id);//Remove socket
    }
}

void NetNode::UnRegisterUDPClient(int channel)
{
    SDLNet_UDP_Unbind(usocket, channel);
}

NetworkManager::NetworkManager(Game& owner)
{
    owner_ref = &owner;
    mutex_net_id = game.SpawnMutex();
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
    size_t id = Game::hasher();
    NetNode* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    while(hasNetNode(id))//Renew id if it already exists in the connections container
    {
        id = Game::hasher();
    }

    tmp = new NetNode(id, host, port, udp);
    if(tmp && !tmp->isBad())//If allocation was successful
        connections.insert(id, tmp);//Add to our connections storage tree.
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return id;
}

size_t NetworkManager::CreateServer(size_t port, bool udp)
{
    size_t id = Game::hasher();
    NetNode* tmp = NULL;
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    while(hasNetNode(id))//Renew id if it already exists in the connections container
    {
        id = Game::hasher();
    }

    tmp = new NetNode(id, port, udp);
    if(tmp && !tmp->isBad())//If allocation was successful
        connections.insert(id, tmp);//Add to our connections storage tree.
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
    return id;
}

void NetworkManager::AcceptTCPClient(size_t socket_id)
{
    NetNode* tmp = NULL;
    size_t client_id = Game::GetMaxValueSizeT();
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

void NetworkManager::AcceptUDPClient(size_t socket_id)
{
    NetNode* tmp = NULL;
    size_t res = 0;
    UDPpacket p = RecvUDPSignal(socket_id, res);//Read 1st packet
    while(p.data != "CONNET\0" && res <= 0)
    {
        p = RecvUDPSignal(socket_id, res);
    }
    //Lock mutex
    owner_ref->LockMutex(mutex_net_id);
    //Grab socket
    connections.search(socket_id, tmp);
    //Make sure it is a server
    if(tmp && tmp->isServer())
    {
        if(p.data[0] != '\0')
            tmp->RegisterUDPClient(p.address);
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
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
            std::string packetBuffers[howmany];
            packets = SDLNet_AllocPacketV(howmany, mtu);//Pre-alloc vector of packets
            if(packets)
            {
               for(size_t i = 0; i < howmany; i++)//Fill packets
            {
                packetBuffers[i] = buff.substr(i * mtu, mtu - 1);//allocate new copy of token
                packetBuffers[i] += '\0';
                strcpy(packets[i]->data, packetBuffers[i].c_str());//copy contents
            }
            //Send packets
            SDLNet_UDP_SendV(soc, packets, howmany);
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
            TCPsocket& soc = tmp->GetTCPSocket();
            if(SDLNet_TCP_Send(tmp->GetTCPSocket(client_id), data, len) < len)
            {
                std::clog << "NetworkManager Error: Could not send data to client " << client_id << ": "
                << SDLNet_TCP_GetPeerAddress(tmp->GetTCPSocket(client_id))->host << std::endl;
                std::clog << SDLNet_GetError() << std::endl;
                std::clog << "Client will be disconnected!" << std::endl;
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

void NetworkManager::SendDataChar(const char& data, size_t socket_id, int client_id)
{
    SendData((void_ptr)&data, sizeof(char), socket_id, client_id);
}

void NetworkManager::SendUDPSignal(size_t socket_id, const std::string& sig_data)
{
    SendData((void_ptr)sig_data.c_str(), sig_data.size() + 1, socket_id);
}

void NetworkManager::RecvData(void_ptr& data, size_t maxlen, size_t socket_id, int client_id)
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
            packets = SDLNet_AllocPacketV(howmany, mtu);//Pre-alloc vector of packets
            if(packets)
            {
                size_t res = SDLNet_UDP_RecvV(soc, packets);
                if(res < 0)
                {
                    //Report error
                    std::clog << "NetworkManager Error: Could not receive UDP packets! This may be caused by a connection error! " << __FILE__ << ":" <<
                        __LINE__ << ": " << SDLNet_GetError() << std::endl;
                    (char*) data[0] = '\0';//Set the first spot as a null character to indicate nothing could be received!
                }
                else
                {
                    for(size_t i = 0; i < res; i++)//extract and package data buffers
                    {
                        dataBuff += packets[i]->data;
                    }
                    //copy final buffer
                    strncpy((char*) data, dataBuff.c_str(), maxlen - 1);
                    (char*)data[maxlen - 1] = '\0';
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
            TCPsocket& soc = tmp->GetTCPSocket();
            if(SDLNet_TCP_Recv(tmp->GetTCPSocket(client_id), data, maxlen) < maxlen)
            {
                std::clog << "NetworkManager Error: Could not receive data from client " << client_id << ": "
                << SDLNet_TCP_GetPeerAddress(tmp->GetTCPSocket(client_id))->host << std::endl;
                std::clog << SDLNet_GetError() << std::endl;
                std::clog << "Client will be disconnected!" << std::endl;
                tmp->UnRegisterTCPClient(client_id);
                char* data[0] = "\0";
            }
        }
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_net_id);
}

void NetworkManager::RecvDataStr(size_t socket_id, std::string& data, size_t maxlen, size_t socket_id, int client_id)
{
    char* tmp = new char[maxlen];
    RecvData(tmp, maxlen, socket_id, client_id);
    if(tmp[0] == '\0')
    {
        std::clog << "Error @ RecvDataStr!" << std::endl;
        data = tmp;
    }
    else
        data = tmp;
    delete[] tmp;
}

void NetworkManager::RecvDataInt(int& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(int);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    if(tmp[0] == '\0')
    {
        std::clog << "Error @ RecvDataInt!" << std::endl;
        data = 0;
    }
    else
        data = (int)(*tmp);
    delete[] tmp;
}

void NetworkManager::RecvDataChar(char& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(char);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    if(tmp[0] == "\0")
    {
        std::clog << "Error @ RecvDataChar!" << std::endl;
        data = 0;
    }
    else
        data = (char)(tmp[0]);
    delete[] tmp;
}

void RecvDataBoolean(bool& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(bool);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    if(tmp[0] == "\0")
    {
        std::clog << "Error @ RecvDataBool!" << std::endl;
        data = 0;
    }
    else
        data = (bool)(*tmp);
    delete[] tmp;
}

void NetworkManager::RecvDataDouble(double& data, size_t socket_id, int client_id)
{
    size_t len = sizeof(double);
    char* tmp = new char[len];
    RecvData(tmp, len, socket_id, client_id);
    if(tmp[0] == "\0")
    {
        std::clog << "Error @ RecvDataDouble!" << std::endl;
        data = 0;
    }
    else
        data = (double)(*tmp);
    delete[] tmp;
}

UDPpacket NetworkManager::RecvUDPSignal(size_t socket_id, size_t& r)
{
    NetNode* tmp = NULL;
    UDPpacket p;
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
            r = SDLNet_UDP_Recv(soc, &p)
            if(r > 0)
                return p;
        }
    }
    p.data[i] = '\0';
    return p;
}

void NetworkManager::PingUDPClient(size_t socket_id, int channel, size_t timeout)
{
    NetNode* tmp = NULL;
    UDPpacket p;
    SendUDPSignal(socket_id, "PING");//Broadcast ping command
    sleep(timeout);//Give some time for the response to arrive
    p = RecvUDPSignal(socket_id);//attempt to get response
    if(p.data[0] == '\0')//If response failed to return a non empty message, kill the channel
    {
        p.channel = channel;
        CloseUDPClient(socket_id, p.channel);//kill the client
    }
}

size_t NetworkManager::GetMaxNumUDPChannels()
{
    return SDLNET_MAX_UDPCHANNELS;
}
