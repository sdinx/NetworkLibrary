//----------------------------------------------------------------------------------
// includes
//----------------------------------------------------------------------------------
#include "Descriptor.h"

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
Descriptor::Descriptor( const int nPortNumber, int ipVersion, int type, int protocol ) :
		m_nPort( nPortNumber ),
		m_ipVersion( ipVersion ),
		m_type( type ),
		m_strAddress( "127.0.0.1" )
{
		m_socket = socket( ipVersion, type, protocol );
		if ( m_socket == INVALID_SOCKET )
		{
				ErrorMessage( "failed create a socket." );
		}// if ( m_socket == INVALID_SOCKET )
}

Descriptor::~Descriptor()
{
		closesocket( m_socket );
}

//----------------------------------------------------------------------------------
//! @func:			Bind( strAddr )
//! @brief:			descriptor と ポート番号を結びつける.
//! @param:		(strAddr) IPアドレスを指定.
//----------------------------------------------------------------------------------
int Descriptor::Bind()
{
		struct sockaddr_in toaddr = { 0, };
		toaddr.sin_family = m_ipVersion;
		// ビッグエンディアン32bitに変換.
		toaddr.sin_port = htons( m_nPort );
		// ネットワークバイトオーダー(ビッグエンディアン)の32bitに変換して設定.
		toaddr.sin_addr.S_un.S_addr = INADDR_ANY;

		// descriptor と ポート番号を結びつける.
		if ( bind( m_socket, ( struct sockaddr* )&toaddr, sizeof( toaddr ) ) == SOCKET_ERROR )
		{
				ErrorMessage( "failed bind a port to descriptor." );

				closesocket( m_socket );
				return SOCKET_ERROR;
		}

		return S_OK;
}

//----------------------------------------------------------------------------------
//! @func:			Connect( strAddr )
//! @brief:			サーバに接続を行う.
//! @param:		(strAddr) IPアドレスを指定.
//----------------------------------------------------------------------------------
int Descriptor::Connect()
{
		struct sockaddr_in toaddr = { 0, };
		toaddr.sin_family = m_ipVersion;
		// ビッグエンディアン32bitに変換.
		toaddr.sin_port = htons( m_nPort );
		// ネットワークバイトオーダー(ビッグエンディアン)の32bitに変換して設定.
		toaddr.sin_addr.S_un.S_addr = inet_addr( m_strAddress.c_str() );

		// ここで関数がブロックする.
		if ( connect( m_socket, ( struct sockaddr* )&toaddr, sizeof( toaddr ) ) == SOCKET_ERROR )
		{
				ErrorMessage( "connecting error." );

				return SOCKET_ERROR;
		}

		return S_OK;
}

//----------------------------------------------------------------------------------
//! @func:			Connect( nQuery )
//! @brief:			クライアントからのコネクトを待つ.
//! @param:		(nQuery) クライアントのキューの数.
//----------------------------------------------------------------------------------
int Descriptor::Listen( int nQuery )
{
		if ( listen( m_socket, nQuery ) == SOCKET_ERROR )
		{
				ErrorMessage( "failed listen query." );

				closesocket( m_socket );
				return SOCKET_ERROR;
		}

		return S_OK;
}


void* Descriptor::Received()
{
		char data[10];

		int n = recv( m_socket, data, sizeof( data ), 0 );
		printf( "%s", data );
		return data;
}


int Descriptor::Send( void* pData, size_t uDataSize )
{

		return S_OK;
}