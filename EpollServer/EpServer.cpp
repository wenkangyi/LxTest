#include "EpServer.h"


/************************************************
**				公共接口
************************************************/

EpServer::EpServer()
{
	for (int i = 0; i < MAX_CONNECT_NUM; i++)
		this->_fdArr[i] = 0;
}

EpServer::EpServer(int serverPort):EpServer()
{
	this->_serverPort = serverPort;
}


EpServer::~EpServer()
{
}

void EpServer::Start() {
	plog("server start!");

	this->InitializeResources();
	this->InitServer();

	int ret = pthread_create(&this->_tReceID, NULL, ListenAndReceive, (void*)this);
	if (ret != 0)
	{
		std::cout << "ListenAndReceive thread create error: error_code=" << ret << std::endl;
	}

	ret = pthread_create(&this->_tReceID, NULL, SendMessage, (void*)this);
	if (ret != 0)
	{
		std::cout << "SendMessage thread create error: error_code=" << ret << std::endl;
	}

	ret = pthread_create(&this->_tReceID, NULL, TimerOut, (void*)this);
	if (ret != 0)
	{
		std::cout << "TimerOut thread create error: error_code=" << ret << std::endl;
	}
}

bool EpServer::SendData(int fd, char *pBuf) {

}

int EpServer::GetConnectNum() {

}


/************************************************
**				私有接口
************************************************/

void EpServer::Destroy() {

}

void EpServer::InitializeResources() {
	
}

void EpServer::InitServer() {
	this->InitServerSocket();
	this->InitServerEpoll();
}

void EpServer::InitServerSocket()
{
	plog("InitServerSocket!");
	struct sockaddr_in serv_addr, clie_addr;
	int opt = 1;
	this->_serverFD = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->_serverPort);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 端口复用
	setsockopt(this->_serverFD, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
	bind(this->_serverFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(this->_serverFD, MAX_CONNECT_NUM);
}

void EpServer::InitServerEpoll()
{
	plog("InitServerEpoll!");
	struct epoll_event ep;
	//创建一个池
	this->_efd = epoll_create(MAX_CONNECT_NUM);
	ep.events = EPOLLIN;
	ep.data.fd = this->_serverFD;
	ssize_t res = epoll_ctl(this->_efd, EPOLL_CTL_ADD, this->_serverFD, &ep);
}

void* EpServer::ListenAndReceive(void* args) {
	EpServer *server = (EpServer*)args;
	socklen_t clie_addr_len;
	struct sockaddr_in clie_addr;
	ssize_t nready;
	struct epoll_event deviceTep, gDeviceEp[MAX_CONNECT_NUM];
	int clientFD;
	char buf[RECE_BUF_MAX];
	
	clie_addr_len = sizeof(clie_addr);
	server->plog("ListenAndReceive Thread Start!");
	while (true)
	{
		nready = epoll_wait(server->_efd, gDeviceEp, MAX_CONNECT_NUM, -1);
		for (int i = 0; i < nready; i++) {
			if (gDeviceEp[i].data.fd == server->_serverFD) {
				//新的连接
				clientFD = accept(server->_serverFD, (struct sockaddr *)&clie_addr, &clie_addr_len);
				#if SYS_DEBUG
				printf("received from %s at port %d\n", inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)), clie_addr.sin_port);
				#endif
				deviceTep.events = EPOLLIN;
				deviceTep.data.fd = clientFD;
				pthread_mutex_lock(&server->_epollMutex);
				ssize_t res = epoll_ctl(server->_efd, EPOLL_CTL_ADD, clientFD, &deviceTep);
				pthread_mutex_unlock(&server->_epollMutex);
				write(clientFD, "hello,Client!\r\n", 15);
				if (server->_serverPort == TOOL_SOFT_PORT) {
					//为工具软件
				}else {
					//为非工具软件
				}
			}else{
				//有数据请求
				clientFD = gDeviceEp[i].data.fd;
				int receLen = read(clientFD, buf, RECE_BUF_MAX);
				server->plog("ListenAndReceive->read");
				if (receLen == 0) {
					server->plog("ListenAndReceive->client auto close");
					pthread_mutex_lock(&server->_epollMutex);
					ssize_t res = epoll_ctl(server->_efd, EPOLL_CTL_DEL, clientFD, NULL);
					pthread_mutex_unlock(&server->_epollMutex);
					close(clientFD);
				}
				else if (receLen > 0) {
					server->plog("ListenAndReceive->Deal with receiving");
					//接收长度小于0的情况暂不处理
					char *p = new char[receLen];
					RequestMsg *msg = new RequestMsg();
					memset(p, 0, receLen);
					memcpy(p, buf, receLen);
					msg->SetReceStr(p);
					delete p;//测试的时候可以删除
					msg->SetClientFD(clientFD);
					server->mq->InQueue(msg);
				}
				else {


				}
			}
		}
	}
}

void* EpServer::SendMessage(void* args) {
	EpServer *server = (EpServer*)args;
	server->plog("SendMessage Thread Start!");
	while (true)
	{
		usleep(server->_sendSleepms * 1000);
		//server->plog("SendMessage");
		if (server->mq->IsEmpty() == 1) continue;
		int mqLen = server->mq->GetEffectiveElements();
		int queueSize = server->mq->QueueSize();
		for (int i = 0; i < queueSize; i++) {
			RequestMsg *msg = server->mq->OutQueue();
			if (msg == NULL) break;
			//msg->DataDecryption();
			//数据处理
			std::cout << "Recevice Data:" << msg->GetReceStr() << std::endl;
			
			//应答
			/*msg->DataEncryption("OK!");
			std::string sendStr = msg->GetSendStr();
			int size = sendStr.size();
			char *p = (char*)sendStr.c_str();*/
			//write(msg->GetClientFD(), p, size);
			write(msg->GetClientFD(), "OK\r\n", 4);

			delete msg;
			server->plog("delete msg");
		}
	}
}

void* EpServer::TimerOut(void* args) {
	EpServer *server = (EpServer*)args;
	server->plog("TimerOut Thread Start!");

	while (true)
	{
		usleep(server->_timeOutSleepms * 1000);

	}
}

