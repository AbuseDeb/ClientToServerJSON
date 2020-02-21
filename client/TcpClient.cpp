#include "pch.h"
#include "tcpclient.h"


TcpClient::TcpClient()
{
	
}


TcpClient::~TcpClient()
{
	Close();
}


void ClientHandler(TcpClient *obj)
{
	if (obj == nullptr)
		return;


	char msg[1024] = { 0 };

	int bytes_recv = 0;

	while (true)
	{
		
		bytes_recv = recv(obj->m_hClientSocket, &msg[0], sizeof(msg), 0);
		if (bytes_recv == SOCKET_ERROR)
			break;

		std::string cBuff = msg;
		obj->OnReceive(cBuff);

	}

	obj->m_hClientSocket = INVALID_SOCKET;
}

bool TcpClient::IsActive() const
{
	if (m_hClientSocket != INVALID_SOCKET)
		return true;
	else
		return false;
}

void TcpClient::Close()
{
	closesocket(m_hClientSocket);

	int nMs = 1000;
	while (IsActive() && nMs > 0)
	{
		nMs -= 10;
		Sleep(10);
	}
}

//void TcpClient::OnReceive(const std::string &data)
//{
//
//}

void TcpClient::Send(const std::string &data)
{
	char message[1024];

	strcpy_s(message, data.c_str());

	send(m_hClientSocket, message, sizeof(message), NULL);
}


bool TcpClient::ConnetToIp(const std::string &ip, int port)
{
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//инициализация
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: %d\n" << iResult;
		return 1;
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	inet_pton(AF_INET, ip.c_str(), &(addr.sin_addr));


	m_hClientSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(m_hClientSocket, (SOCKADDR*)&addr, sizeof(addr)))
	{
		std::cout << "connection error\n";
		return 1;
	}
	else
	{
		std::cout << "connection ok\n";
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, this, NULL, NULL);

}
void TcpClient::ConnectToHandle(SOCKET ClientSocket)
{
	m_hClientSocket = ClientSocket;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, this, NULL, NULL);
}


void TcpClient::OnReceive(const std::string &data)
{
	std::cout << data;
}