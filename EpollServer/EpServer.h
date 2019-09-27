#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "RequestMsg.h"
#include "MyQueue.h"

//系统调试
//#define SYS_DEBUG

//最大连接数
#define MAX_CONNECT_NUM		(65536)

//接收缓冲区的最大长度
#define RECE_BUF_MAX		(1024)

/************************************************
**				通讯端口
************************************************/
//工具软件端口
#define TOOL_SOFT_PORT	(6043)
//设备软件端口
#define DEVICE_PORT		(6044)
//UI软件端口
#define UI_SOFT_PORT	(6045)

//软件服务端
class EpServer
{
public:
	EpServer();
	EpServer(int serverPort);
	~EpServer();

	//启动
	void Start();
	bool SendData(int fd, char *pBuf);
	int GetConnectNum();

private:
	//服务端所使用的端口
	int _serverPort = TOOL_SOFT_PORT;
	//服务端的FD
	int _serverFD = 0;
	//ssize_t位于头文件#include <sys/types.h>
	//Epoll的管理者
	ssize_t _efd;
	//用于_efd的控制
	pthread_mutex_t _epollMutex = PTHREAD_MUTEX_INITIALIZER;
	//最大连接数
	int _maxConnNum = 1000;
	//监听线程休眠时间
	int _listenSleepms = 10;
	//发送线程休眠时间
	int _sendSleepms = 10;
	//超时线程休眠时间
	int _timeOutSleepms = 1000;
	//socket 的 FD 数组
	//当使用时，被置为1
	int _fdArr[MAX_CONNECT_NUM];
	//消息容器
	MyQueue<RequestMsg> *mq = new MyQueue<RequestMsg>();

	/************************************************
	**				线程ID
	************************************************/
	//接收线程ID
	pthread_t _tReceID;
	//发送线程ID
	pthread_t _tSendID;
	//超时线程ID
	pthread_t _tTimeOutID;

	/************************************************
	**				私有接口
	************************************************/

	//销毁
	void Destroy();
	//初始化资源
	void InitializeResources();
	//初始化服务端
	void InitServer();
	void InitServerSocket();
	void InitServerEpoll();
	//监听客户端连接线程以及接收数据
 	static void* ListenAndReceive(void* args);
	//发送数据给客户端
	//接收到的数据，直接在这里处理，并发回给工具软件
	static void* SendMessage(void* args);
	//用于连接的超时检测，连接超时，还是直接删除吧
	static void* TimerOut(void* args);

	void plog(std::string log) {
		std::cout << log << std::endl;
	}
};

