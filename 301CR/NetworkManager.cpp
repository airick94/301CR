#include "pch.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

NetworkManager::NetworkManager(const sf::IpAddress ip, unsigned short port)
{
	IPADDRESS = ip;
	PORT = port;
}

void NetworkManager::Init()
{
}

void NetworkManager::Communicate(sf::TcpSocket socket)
{
	sf::Packet packetSend;
	globalMutex.lock();
	packetSend << msgToSend;
	globalMutex.unlock();

	socket.send(packetSend);

	std::string msg;
	sf::Packet packetReceive;

	socket.receive(packetReceive);
	if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
	{
		std::cout << msg << std::endl;
		oldMsg = msg;
	}
}

void NetworkManager::Server(sf::TcpSocket socket)
{
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

bool NetworkManager::Client(sf::TcpSocket socket)
{
	if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}
