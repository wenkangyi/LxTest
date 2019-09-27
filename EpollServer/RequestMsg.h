#pragma once
#include <iostream>

#include "RsaClass.h"


class RequestMsg
{
public:
	RequestMsg();
	~RequestMsg();
	//数据解密
	void DataDecryption();
	//数据加密
	void DataEncryption(std::string sStr);
	//设置接收字符串
	void SetReceStr(char *pbuf);
	//获取接收字符串
	std::string GetReceStr();
	//获取用户数据
	std::string GetUsrStr();
	//设置客户端FD
	void SetClientFD(int clientFD);
	//获取客户端的FD
	int GetClientFD();
	//获取发送字符串
	std::string GetSendStr();
private:
	//加密数据
	std::string _receStr;
	//解密后的用户数据
	std::string _usrStr;
	//加密后需要发送的数据
	std::string _sendStr;
	//发送数据长度
	//int _sendBufLen = 0;

	//客户端FD
	int _clientFD = 0;
};

