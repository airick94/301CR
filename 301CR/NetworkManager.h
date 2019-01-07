#pragma once
#include "pch.h"
#include <SFML/Network.hpp>
#include <iostream>

class NetworkManager
{
public:
	std::string oldMsg;
	std::string msgToSend;
	
	sf::Mutex globalMutex;

	unsigned short PORT;
	sf::IpAddress IPADDRESS = "192.168.0.100";

	NetworkManager();
	~NetworkManager();
	NetworkManager(sf::IpAddress ip, unsigned short port);
	void Init();
	void Communicate(sf::TcpSocket socket);
	void Server(sf::TcpSocket socket);
	bool Client(sf::TcpSocket socket);
};
