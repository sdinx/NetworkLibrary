#include "Network.h"

int main()
{
		auto wsaInstance = _Singleton<Network::WSANet>::GetInstance();
		wsaInstance->Init();

		Network::Descriptor client( 12345, NET_SOCKET_IPv4, NET_SOCKET_TCP );
		client.Connect();
		void* data = client.Received();
		char* d = ( char* ) data;
		printf( "%s", d );

		getchar();
		wsaInstance->Release();

		return 0;
}