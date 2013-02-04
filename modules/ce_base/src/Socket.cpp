//- Centhra Engine -
#include <CE/ConfigBase.h>
#include <CE/Socket.h>
#include <CE/Base.h>

#if CE_BASE_USEPOSIXSOCKET
	//- POSIX -
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
#endif

#ifdef _WIN32
	#if CE_BASE_USEWINSOCKET
		//- WSA -
		#include <winsock2.h>
		#include <ws2tcpip.h>
	#endif
	#include <windows.h>
#endif

namespace ce
{
	int Socket::ms_count = 0;

	#if CE_BASE_USEWINSOCKET
		WSADATA g_wsaData;
	#endif

	Socket *Socket::Create(Domain domain, Type type, Protocol protocol)
	{
		int sDomain = -1, sType = -1, sProtocol = -1;

		#if CE_BASE_USEPOSIXSOCKET
			switch(domain)
			{
			case IP4:
				sDomain = PF_INET;
				break;
			case IP6:
				sDomain = PF_INET6;
				break;
			}
		#endif

		#if CE_BASE_USEWINSOCKET
			if(!ms_count)
			{
				int res = WSAStartup(MAKEWORD(2,2), &g_wsaData);
				if(res != 0)
				{
					error("[Error] Socket::create - WSAStartup failed with error: %d\n", res);
					return 0;
				}
			}

			switch(domain)
			{
			case IP4:
				sDomain = IPPROTO_IP;
				break;
			case IP6:
				sDomain = IPPROTO_IPV6;
				break;
			}
		#endif

		switch(type)
		{
		case Raw:
			sType = SOCK_RAW;
			break;
		case Stream:
			sType = SOCK_STREAM;
			break;
		case Datagram:
			sType = SOCK_DGRAM;
			break;
		case SequencedPacket:
			sType = SOCK_SEQPACKET;
			break;
		}

		switch(protocol)
		{
		case TCP:
			sProtocol = IPPROTO_TCP;
			break;
		case UDP:
			sProtocol = IPPROTO_UDP;
		}

		if(sDomain == -1 || sType == -1 || sProtocol == -1)
		{
			error("[Error] Socket::create - Unrecognized socket configuration.\n");
			return 0;
		}

		int sSocket = socket(sDomain, sType, sProtocol);

		if(sSocket == -1)
		{
			#if CE_BASE_USEPOSIXSOCKET
				close(sSocket);
			#endif
			#if CE_BASE_USEWINSOCKET
				closesocket(sSocket);
			#endif

			error("[Error] Socket::create - Failed to create Socket.\n");
		}

		Socket *sock = new Socket();
		sock->m_socket = sSocket;
		return sock;
	}

	Socket::Socket()
	{
		m_socket = 0;
		ms_count++;
	}
	Socket::~Socket()
	{
		#if CE_BASE_USEPOSIXSOCKET
			close(m_socket);
		#endif
		#if CE_BASE_USEWINSOCKET
			closesocket(m_socket);
		#endif

		ms_count--;
		
		#if CE_BASE_USEWINSOCKET
			if(!ms_count)
				WSACleanup();
		#endif
	}
	Socket *Socket::Accept()
	{
		int ret = accept(m_socket, NULL, NULL);

		if(ret == -1)
		{
			error("[Error] Socket::Accept - Unable to accept incomming connection.\n");
			return 0;
		}

		Socket *client = new Socket();
		client->m_socket = ret;
		return client;
	}
	bool Socket::Bind(unsigned int port)
	{
		struct sockaddr_in stSockAddr;
		memset(&stSockAddr, 0, sizeof(stSockAddr));
		
		stSockAddr.sin_family = AF_INET;
		stSockAddr.sin_port = htons(port);
		stSockAddr.sin_addr.s_addr = INADDR_ANY;
		if(bind(m_socket,(struct sockaddr *)&stSockAddr, sizeof(stSockAddr)) == -1)
		{
			error("[Error] Socket::Bind - Unable to bind to port %d.\n", port);
			return false;
		}

		return true;
	}
	bool Socket::Connect(const char *address, unsigned int port)
	{
		struct sockaddr_in stSockAddr;
		memset(&stSockAddr, 0, sizeof(stSockAddr));

		stSockAddr.sin_family = AF_INET;
		stSockAddr.sin_port = htons(port);
		int ret = inet_pton(AF_INET, address, &stSockAddr.sin_addr);

		if(ret < 0)
		{
			error("[Error] Socket::Connect - \"%s\" is not a valid address family.\n", address);
			return false;
		}
		else if(ret == 0)
		{
			error("[Error] Socket::Connect - \"%s:%d\" is not a valid ip address.\n", address, port);
			return false;
		}

		if(connect(m_socket, (struct sockaddr *)&stSockAddr, sizeof(stSockAddr)) == -1)
		{
			error("[Error] Socket::Connect - Unable to connect to \"%s:%d\"\n", address, port);
			return false;
		}

		return true;
	}
	bool Socket::Listen(unsigned int backlog)
	{
		if(listen(m_socket, backlog) == -1)
		{
			error("[Error] Socket::Listen - Unable to listen.\n");
			return false;
		}

		return true;
	}
	void Socket::Read(char *buffer, unsigned int length)
	{
		#if CE_BASE_USEPOSIXSOCKET
			read(m_socket, buffer, length);
		#endif
		#if CE_BASE_USEWINSOCKET
			recv(m_socket, buffer, length, 0);
		#endif
	}
	bool Socket::Shutdown()
	{
		#if CE_BASE_USEPOSIXSOCKET
			if(shutdown(m_socket, SHUT_RDWR) == -1)
		#endif
		#if CE_BASE_USEWINSOCKET
			if(shutdown(m_socket, SD_SEND) == SOCKET_ERROR)
		#endif
			{
				error("[Error] Socket::Listen - Unable to shutdown socket.\n");
				return false;
			}

		return true;
	}
	void Socket::Write(char *buffer, unsigned int length)
	{
		send(m_socket, buffer, length, 0);
	}
}