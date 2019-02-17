//----------------------------------------------------------------------------------
// includes
//----------------------------------------------------------------------------------
#include "SocketServer.h"

//----------------------------------------------------------------------------------
// using
//----------------------------------------------------------------------------------
using namespace Network;

//----------------------------------------------------------------------------------
//! @func:			Constructor( nPortNumber, ipVersion, type, protocol )
//! @brief:			descriptor を作成する.
//! @param:		(nPortNumber) 接続ポート番号を指定.
//! @param:		(ipVersion) IPv4 または IPv6 を指定.
//! @param:		(type) TCP または UDP を指定.
//! @param:		(protocol) ?
//----------------------------------------------------------------------------------
SocketServer::SocketServer( const int nPortNumber, int ipVersion, int type, int protocol ) :
		Descriptor( nPortNumber, ipVersion, type, protocol ),
		m_nSocketCounts( 0 )
{
		m_socket = socket( ipVersion, type, protocol );
		if ( m_socket == SOCKET_ERROR )
		{
				ErrorMessage( "failed create a socket." );
		}// if ( m_socket == SOCKET_ERROR )
}


int SocketServer::Accept()
{
		struct sockaddr_in acceptAddr = { 0, };
		socklen_t acceptAddrSize = sizeof( acceptAddr );

		m_clients[m_nSocketCounts] = accept( m_socket, ( struct sockaddr* )&acceptAddr, &acceptAddrSize );
		if ( m_clients[m_nSocketCounts] == SOCKET_ERROR )
		{
				ErrorMessage( "failed accept." );

				return SOCKET_ERROR;
		}

		printf( "connected" );
		m_nSocketCounts++;
		return m_nSocketCounts - 1;
}


int SocketServer::Send( int index, char* pData, size_t uDataSize )
{
		int err = send( m_clients[index], pData, uDataSize, 0 );
		if ( err == SOCKET_ERROR )
		{
				ErrorMessage( "failed send data to client." );

				return SOCKET_ERROR;
		}

		return S_OK;
}