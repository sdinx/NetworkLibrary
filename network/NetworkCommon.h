//----------------------------------------------------------------------------------
// file: Network.h
// date: 02/17/2019
// desc: 
//----------------------------------------------------------------------------------

#ifndef _INCLUDED_NETWORK_NETWORK_COMMON_
#define _INCLUDED_NETWORK_NETWORK_COMMON_

//----------------------------------------------------------------------------------
// includes
//----------------------------------------------------------------------------------
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "../Singleton.h"

//----------------------------------------------------------------------------------
// defines
//----------------------------------------------------------------------------------
#define NET_SOCKET_IPv4			PF_INET
#define NET_SOCKET_IPv6			PF_INET6
#define NET_SOCKET_TCP			SOCK_STREAM
#define MAX_SOCKET_COUNTS			(3)

#ifdef _DEBUG
#define ErrorMessage(msg, ...)			_ErrorMessage(*this, msg, __func__, __LINE__, __VA_ARGS__)
#else // _RELEASE
#define ErrorMessage
#endif

//----------------------------------------------------------------------------------
// pragmas
//----------------------------------------------------------------------------------
#pragma comment(lib, "Ws2_32.lib") 
#pragma warning(disable:4996)

//----------------------------------------------------------------------------------
// utilities
//----------------------------------------------------------------------------------
namespace Network
{
		class WSANet final :public _Singleton<WSANet>
		{
				friend class _Singleton<WSANet>;
				WSADATA m_wsaData;

		public:
				~WSANet() { Release(); }
				void Init() { WSAStartup( MAKEWORD( 2, 0 ), &m_wsaData ); }
				void Release() { WSACleanup(); }

		};// class WSANet

}// namespace Network

template<class T, typename ...P>
void _ErrorMessage( T type, std::string message, P...param )
{
		std::string name = typeid( type ).name();
		message = "[" + name + "] {%s()=%d} " + message + "\n";
		printf( message.c_str(), std::forward<P>( param )... );
}

#endif // ! _INCLUDED_NETWORK_NETWORK_COMMON_