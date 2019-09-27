//-lcrypto -pthread


#include <iostream>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/epoll.h>
//#include <netinet/in.h>
//#include <pthread.h>
//#include <unistd.h>
//#include <string.h>
#include "EpServer.h"
#include "MyQueue.h"
#include "RequestMsg.h"
#include "RsaClass.h"

using namespace std;

#pragma pack (4)
class  A
{
public:
	 A();
	~ A();

private:

};

 A:: A()
{
}

 A::~ A()
{
}


int main() {
	//RequestMsg *msg = new RequestMsg();
	//MyQueue<RequestMsg> *mq = new MyQueue<RequestMsg>();
	//char *p = new char[8];
	//memcpy(p, "12345678", 8);
	//msg->SetReceStr(p);
	//delete[] p;
	//p = NULL;
	//std::cout << "ReceStr:" << msg->GetReceStr() << std::endl;
	//
	//mq->InQueue(msg);
	//RequestMsg *msg2 = mq->OutQueue();
	//if (msg2 == NULL) std::cout << "msg2 in null" << std::endl;
	//else std::cout << "ReceStr:" << msg2->GetReceStr() << std::endl;
	//delete msg2;
	
	//MyQueue<A> *mq = new MyQueue<A>();
	//char *p = new char[7];
	//memcpy(p, "123456", 6);
	//std::string str = p;
	//delete p;
	//p = NULL;
	////std::cout << "&p:" << &p << std::endl;
	//std::cout << "str:" << str << std::endl;

	EpServer *server = new EpServer();
	server->Start();

	pthread_exit(NULL);
	return 0;
}


