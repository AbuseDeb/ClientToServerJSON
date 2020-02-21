#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "tcpclient.h"
#pragma comment (lib, "Ws2_32.lib")  


int main()
{	
	TcpClient Client;
	Client.ConnetToIp("127.0.0.1", 1111);

	char msg[1024];
	while (true)
	{
		std::cin.getline(msg, sizeof(msg));
		if (msg[0] == NULL)
		{
			std::cout << "Null string!\n";
		}
		else
			Client.Send(msg);
	}

	system("pause");
	return 1;
}
