#pragma once

#include <iostream>
#include <Ws2tcpip.h>
#include <string>

class TcpClient
{
public:
	TcpClient();
	~TcpClient();
	void OnReceive(const std::string &data);
	void Send(const std::string &data);
	bool IsActive() const;
	void Close();

	bool ConnetToIp(const std::string &ip, int port);
	void ConnectToHandle(SOCKET ClientSocket);

public:
	SOCKET m_hClientSocket;

};

