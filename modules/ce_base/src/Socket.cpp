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
	#include <cstdio>
	#include <cstdlib>
	#include <cstring>
	#include <unistd.h>
	#include <fcntl.h>
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

	Socket *Socket::Create(Domain domain, Type type, Protocol protocol, bool isBlocking)
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

		int reuse = 1;
		#ifdef linux
			setsockopt(sSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		#endif
		#ifdef _WIN32
			setsockopt(sSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
		#endif
		Socket *sock = new Socket();
		sock->m_socket = sSocket;
		if(!isBlocking)
			sock->SetBlocking(isBlocking);
		return sock;
	}

	Socket::Socket()
	{
		m_socket = 0;
		m_isBlocking = true;
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
			if(m_isBlocking)
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
		if(bind(m_socket, (struct sockaddr *)&stSockAddr, sizeof(stSockAddr)) != 0)
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
	int Socket::Read(char *buffer, unsigned int length)
	{
		#if CE_BASE_USEPOSIXSOCKET
			return read(m_socket, buffer, length);
		#endif
			
		#if CE_BASE_USEWINSOCKET
			return recv(m_socket, buffer, length, 0);
		#endif
	}
	bool Socket::Shutdown()
	{
		SetBlocking(true);

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
	bool Socket::Close()
	{
		SetBlocking(true);

		#if CE_BASE_USEPOSIXSOCKET
			if(close(m_socket) == -1)
		#endif
		#if CE_BASE_USEWINSOCKET
			if(closesocket(m_socket) != 0)
		#endif
			{
				error("[Error] Socket::Listen - Unable to close socket.\n");
				return false;
			}

		return true;
	}
	int Socket::Write(char *buffer, unsigned int length)
	{
		return send(m_socket, buffer, length, 0);
	}
	int Socket::HasRead()
	{
		fd_set readFlags, writeFlags;
		struct timeval waitd = {0, 0};
		FD_ZERO(&readFlags);
		FD_ZERO(&writeFlags);
		FD_SET(m_socket, &readFlags);

		int ret = select(m_socket + 1, &readFlags, &writeFlags, (fd_set *)0, &waitd);
		
		int hasRead = 0;
		#ifdef _WIN32
			hasRead = FD_ISSET(m_socket, &readFlags) != 0 ? 1 : 0;
		#endif
		#ifdef linux
			hasRead = FD_ISSET(m_socket, &readFlags) ? 1 : 0;
		#endif
			
		if(hasRead > 0)
		{
			char c = 0;
			ret = recv(m_socket, &c, 1, MSG_PEEK);

			if(ret == 0) //- TODO: Verify this means client terminated connection -
				hasRead = -1;
		}

		return hasRead;
	}
	bool Socket::SetBlocking(bool isBlocking)
	{
		#if CE_BASE_USEPOSIXSOCKET
			int flags = isBlocking ? 0 : SOCK_NONBLOCK;
			fcntl(m_socket, F_SETFL, flags);
		#endif

		#if CE_BASE_USEWINSOCKET
			unsigned long mode = isBlocking ? 0 : 1;
			int res = ioctlsocket(m_socket, FIONBIO, &mode);
			if(res != NO_ERROR)
				error("[Error] Setting socket blocking mode failed. Code: %ld\n", res);
		#endif

		m_isBlocking = isBlocking;
		return true;
	}
	void Socket::GetPeerIP4Info(unsigned long *addr, unsigned short *port)
	{
		#if CE_BASE_USEPOSIXSOCKET
			struct sockaddr_in Addr;
			socklen_t AddrLen = sizeof(Addr);
			getpeername(m_socket, (sockaddr *)&Addr, &AddrLen);
			*addr = Addr.sin_addr.s_addr;
			*port = Addr.sin_port;
		#endif

		#if CE_BASE_USEWINSOCKET
			struct sockaddr_in Addr;
			socklen_t AddrLen = sizeof(Addr);
			getpeername(m_socket, (sockaddr *)&Addr, &AddrLen);
			*addr = Addr.sin_addr.S_un.S_addr;
			*port = Addr.sin_port;
		#endif
	}
}
