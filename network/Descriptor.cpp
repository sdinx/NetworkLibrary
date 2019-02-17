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
//! @brief:			descriptor ���쐬����.
//! @param:		(nPortNumber) �ڑ��|�[�g�ԍ����w��.
//! @param:		(ipVersion) IPv4 �܂��� IPv6 ���w��.
//! @param:		(type) TCP �܂��� UDP ���w��.
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
//! @brief:			descriptor �� �|�[�g�ԍ������т���.
//! @param:		(strAddr) IP�A�h���X���w��.
//----------------------------------------------------------------------------------
int Descriptor::Bind()
{
		struct sockaddr_in toaddr = { 0, };
		toaddr.sin_family = m_ipVersion;
		// �r�b�O�G���f�B�A��32bit�ɕϊ�.
		toaddr.sin_port = htons( m_nPort );
		// �l�b�g���[�N�o�C�g�I�[�_�[(�r�b�O�G���f�B�A��)��32bit�ɕϊ����Đݒ�.
		toaddr.sin_addr.S_un.S_addr = INADDR_ANY;

		// descriptor �� �|�[�g�ԍ������т���.
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
//! @brief:			�T�[�o�ɐڑ����s��.
//! @param:		(strAddr) IP�A�h���X���w��.
//----------------------------------------------------------------------------------
int Descriptor::Connect()
{
		struct sockaddr_in toaddr = { 0, };
		toaddr.sin_family = m_ipVersion;
		// �r�b�O�G���f�B�A��32bit�ɕϊ�.
		toaddr.sin_port = htons( m_nPort );
		// �l�b�g���[�N�o�C�g�I�[�_�[(�r�b�O�G���f�B�A��)��32bit�ɕϊ����Đݒ�.
		toaddr.sin_addr.S_un.S_addr = inet_addr( m_strAddress.c_str() );

		// �����Ŋ֐����u���b�N����.
		if ( connect( m_socket, ( struct sockaddr* )&toaddr, sizeof( toaddr ) ) == SOCKET_ERROR )
		{
				ErrorMessage( "connecting error." );

				return SOCKET_ERROR;
		}

		return S_OK;
}

//----------------------------------------------------------------------------------
//! @func:			Connect( nQuery )
//! @brief:			�N���C�A���g����̃R�l�N�g��҂�.
//! @param:		(nQuery) �N���C�A���g�̃L���[�̐�.
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