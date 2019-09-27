#pragma once
// g++ demo.cpp -o demo -lcrypto
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h> 
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>


class RsaClass
{
public:
	RsaClass();
	~RsaClass();
	//����
	std::string EncodeRSAKeyFile(const std::string& strPemFileName, const std::string& strData);
	//����
	std::string DecodeRSAKeyFile(const std::string& strPemFileName, const std::string& strData);
};

