//----------------------------------------------------------------------------------
// file: Descriptor.h
// date: 02/17/2019
// desc: 
//----------------------------------------------------------------------------------

#ifndef _INCLUDED_NETWORK_DESCRIPTOR_
#define _INCLUDED_NETWORK_DESCRIPTOR_

//----------------------------------------------------------------------------------
// includes
//----------------------------------------------------------------------------------
#include "NetworkCommon.h"

namespace Network
{
		class Descriptor
		{
		public:
				//----------------------------------------------------------------------------------
				// other
				//----------------------------------------------------------------------------------
				Descriptor() = delete;
				Descriptor( const int nPortNumber, int ipVersion, int type, int protocol = 0 );
				~Descriptor();

		protected:
				//----------------------------------------------------------------------------------
				// protected  variables
				//----------------------------------------------------------------------------------
				SOCKET m_socket;
				const int m_nPort;
				const int m_ipVersion;
				const int m_type;
				std::string m_strAddress;

		public:
				//----------------------------------------------------------------------------------
				// public  variables
				//----------------------------------------------------------------------------------
				/* NOTHING */

		private:
				//----------------------------------------------------------------------------------
				// private  methods
				//----------------------------------------------------------------------------------
				/* NOTHING */

		public:
				//----------------------------------------------------------------------------------
				// public  methods
				//----------------------------------------------------------------------------------
				int Bind();
				int Connect();
				int Listen( int nQuery );
				void* Received();
				virtual int Send( void* pData, size_t uDataSize );
				void SetAddress( std::string strAddr ) { m_strAddress = strAddr; }

		};// class Descriptor

}// namespace Network

#endif // ! _INCLUDED_NETWORK_DESCRIPTOR_