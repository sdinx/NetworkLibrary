#include "Network.h"

int main()
{
		auto wsaInstance = _Singleton<Network::WSANet>::GetInstance();
		wsaInstance->Init();

		Network::SocketServer server( 12345, NET_SOCKET_IPv4, NET_SOCKET_TCP );
		server.Bind();
		server.Listen( 1 );
		int num = server.Accept();
		char data[] = "test";
		server.Send( num, data, sizeof( data ) );

		getchar();
		wsaInstance->Release();

		return 0;
}