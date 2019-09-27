#include "RequestMsg.h"
#include "RsaClass.h"


RequestMsg::RequestMsg()
{
}


RequestMsg::~RequestMsg()
{
}

//解密
void RequestMsg::DataDecryption() {
	RsaClass *rsa = new RsaClass();
	this->_usrStr = rsa->DecodeRSAKeyFile("prikey.pem", this->_receStr);
}

void RequestMsg::DataEncryption(std::string sStr) {
	RsaClass *rsa = new RsaClass();
	this->_sendStr = rsa->EncodeRSAKeyFile("pubkey.pem", sStr);
	//this->_sendBufLen = this->_sendStr.size();
}

void RequestMsg::SetReceStr(char *pbuf)
{
	//这里将发生一次拷贝
	this->_receStr = pbuf;
}

void RequestMsg::SetClientFD(int clientFD)
{
	this->_clientFD = clientFD;
}

int RequestMsg::GetClientFD()
{
	return this->_clientFD;
}

std::string RequestMsg::GetSendStr()
{
	return this->_sendStr;
}

std::string RequestMsg::GetReceStr()
{
	return this->_receStr;
}

std::string RequestMsg::GetUsrStr()
{
	return this->_usrStr;
}

