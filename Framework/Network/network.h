
#pragma once

#ifdef NETWORK_SUPPORT

#include "../includes.h"

/*
	Class: Network
	This class allows connection to one other networked computer for communication.
	Hopefully, at a later date, I'll fix this to support multiple clients
*/
class Network
{

	private:
		bool isServer;
		ENetAddress serverAddress;
		ENetHost*		localHost;
		ENetPeer*		networkPeer;
		std::vector<ENetPeer*> networkPeers;

	public:
		/*
			Constructor: Network
			Creates a listening server on provided port
			Parameters: 
				Port - Port number to listen on
    */
		Network( int Port );

		/*
			Constructor: Network
			Creates a client and tries to connect to a server
			Parameters: 
				Server - Server name/IP address to connect to
				Port - Port number to connect on
    */
		Network( std::string Server, int Port );

		/*
			Destructor: ~Network
			Shuts down the network server/client, disconnecting the client
    */
		~Network();

		/*
			Function: AcceptConnection
			Accepts an incoming connection
		*/
		void AcceptConnection( ENetPeer* From );

		/*
			Function: Disconnect
			Disconnects the current client, not really much use because you can't reconnect without creating a new object yet
    */
		void Disconnect();

		/*
			Function: IsActive
			Indicates if the local socket is still active. This is generally used for Server objects waiting for connections
			Returns:
				*Boolean*
    */
		bool IsActive();

		/*
			Function: IsConnected
			Indicates whether the connection to the other computer is still alive
			Returns:
				*Boolean*
    */
		bool IsConnected();

		/*
			Function: IsServer
			Indicates whether the instance is acting as a server (listening)
			Returns:
				*Boolean*
    */
		bool IsServer();

		/*
			Function: Update
			Let's enet process all packets and pushes them into the framework event list
    */
		void Update();

		/*
			Function: Send
			Sends a data packet to the other side
    */
		void Send( Memory* Packet, bool Reliable );

		/*
			Function: Send
			Sends a data packet to the other side
    */
		void Send( void* Packet, int PacketLength, bool Reliable );

};

#endif