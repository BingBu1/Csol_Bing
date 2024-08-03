#pragma once
#include <vector>
#include <winsock.h>
#include <Windows.h>
#include <thread>
#include <memory>
#include <functional>
#include <xorstr.hpp>
#pragma comment(lib, "ws2_32.lib")
class Tcp{
public:
	Tcp() = default;
	Tcp(int port) : port(port), IsInit(), IsVip(), Socket() {}
	inline void Start();
	inline void RecvData();
	inline void RecvDateCallBack(char * Buff);
	inline bool GetIsVip()const { return this->IsVip; }
	inline bool GetIsInit()const { return this->IsInit; }
private:
	inline void Recv();
private:
	int port;
	SOCKET Socket;
	std::vector<unsigned char> Buff;
	bool IsInit;
	bool IsVip;
	bool IsThreadInit = false;
};
void Tcp::Start() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	sockaddr_in sockadd;
	auto socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_ == INVALID_SOCKET) {
		auto ErrorCode = WSAGetLastError();
		printf(xorstr_("Socket创建失败 错误码：%d\n"), ErrorCode);
		exit(0);
	}
	Socket = socket_;
	sockadd.sin_family = AF_INET;
	sockadd.sin_port = htons(port);
	sockadd.sin_addr.S_un.S_addr = inet_addr(xorstr_("127.0.0.1"));
	auto c_retval = connect(socket_, reinterpret_cast<sockaddr*>(&sockadd), sizeof(sockadd));
	if (c_retval == SOCKET_ERROR) {
		printf(xorstr_("连接失败\n"));
		exit(0);
	}
	send(Socket, xorstr_("Ok Im'In"), 10, NULL);
	RecvData();
}

void Tcp::RecvData() {
	std::thread RecvThread(&Tcp::Recv, this);
	RecvThread.detach();
}

void Tcp::Recv() {
	IsThreadInit = true;
	char Buff_[1024]{};
	try {
		auto r_retval = recv(Socket, Buff_, sizeof(Buff_), NULL);
		if (r_retval == SOCKET_ERROR) {
			auto ErrorCode = WSAGetLastError();
			if (ErrorCode == 10054)exit(0);
			printf(xorstr_("接受出错 错误码：%d\n"), ErrorCode);
			closesocket(Socket);
			exit(0);
		}
		RecvDateCallBack(Buff_);
		if (this->IsInit = true)return;
	}catch (...) {
		return;
	}
	Recv();
}

void Tcp::RecvDateCallBack(char * Buff) {
	std::string Tmp(Buff);
	std::string VipKey = xorstr_("SDsdlakjdlkjawiodjasmldnasjkdhiowale");
	if (Tmp == xorstr_("bingbu") || Tmp == VipKey) {
		if (Tmp == VipKey) {
			this->IsVip = true;
		}
		this->IsInit = true;
	}
}