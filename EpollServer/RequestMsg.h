#pragma once
#include <iostream>

#include "RsaClass.h"


class RequestMsg
{
public:
	RequestMsg();
	~RequestMsg();
	//���ݽ���
	void DataDecryption();
	//���ݼ���
	void DataEncryption(std::string sStr);
	//���ý����ַ���
	void SetReceStr(char *pbuf);
	//��ȡ�����ַ���
	std::string GetReceStr();
	//��ȡ�û�����
	std::string GetUsrStr();
	//���ÿͻ���FD
	void SetClientFD(int clientFD);
	//��ȡ�ͻ��˵�FD
	int GetClientFD();
	//��ȡ�����ַ���
	std::string GetSendStr();
private:
	//��������
	std::string _receStr;
	//���ܺ���û�����
	std::string _usrStr;
	//���ܺ���Ҫ���͵�����
	std::string _sendStr;
	//�������ݳ���
	//int _sendBufLen = 0;

	//�ͻ���FD
	int _clientFD = 0;
};

