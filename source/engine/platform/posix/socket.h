

#ifndef _SHARED_PLATFORM_SOCKET_H_
#define _SHARED_PLATFORM_SOCKET_H_

#include <string>

#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>




namespace Glest {

// =====================================================
//	class IP
// =====================================================

class Ip{
private:
	unsigned char bytes[4];

public:
	Ip();
	Ip(unsigned char byte0, unsigned char byte1, unsigned char byte2, unsigned char byte3);
	Ip(const string& ipString);

	unsigned char getByte(int byteIndex)	{return bytes[byteIndex];}
	std::string getString() const;
};

// =====================================================
//	class Socket
// =====================================================

class Socket {
protected:
	int sock;
	
public:
	Socket(int sock);
	Socket();
	~Socket();

	int getDataToRead();
	int send(const void *data, int dataSize);
	int receive(void *data, int dataSize);
	int peek(void *data, int dataSize);
	
	void setBlock(bool block);
	bool isReadable();
	bool isWritable();
	bool isConnected();

	std::string getHostName() const;
	std::string getIp() const;

protected:
	static void throwException(const std::string &str);
};

// =====================================================
//	class ClientSocket
// =====================================================

class ClientSocket: public Socket{
public:
	void connect(const Ip &ip, int port);
};

// =====================================================
//	class ServerSocket
// =====================================================

class ServerSocket: public Socket{
public:
	void bind(int port);
	void listen(int connectionQueueSize= SOMAXCONN);
	Socket *accept();
};

}//end namespace

#endif
