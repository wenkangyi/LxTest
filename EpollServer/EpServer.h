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

//ϵͳ����
//#define SYS_DEBUG

//���������
#define MAX_CONNECT_NUM		(65536)

//���ջ���������󳤶�
#define RECE_BUF_MAX		(1024)

/************************************************
**				ͨѶ�˿�
************************************************/
//��������˿�
#define TOOL_SOFT_PORT	(6043)
//�豸����˿�
#define DEVICE_PORT		(6044)
//UI����˿�
#define UI_SOFT_PORT	(6045)

//��������
class EpServer
{
public:
	EpServer();
	EpServer(int serverPort);
	~EpServer();

	//����
	void Start();
	bool SendData(int fd, char *pBuf);
	int GetConnectNum();

private:
	//�������ʹ�õĶ˿�
	int _serverPort = TOOL_SOFT_PORT;
	//����˵�FD
	int _serverFD = 0;
	//ssize_tλ��ͷ�ļ�#include <sys/types.h>
	//Epoll�Ĺ�����
	ssize_t _efd;
	//����_efd�Ŀ���
	pthread_mutex_t _epollMutex = PTHREAD_MUTEX_INITIALIZER;
	//���������
	int _maxConnNum = 1000;
	//�����߳�����ʱ��
	int _listenSleepms = 10;
	//�����߳�����ʱ��
	int _sendSleepms = 10;
	//��ʱ�߳�����ʱ��
	int _timeOutSleepms = 1000;
	//socket �� FD ����
	//��ʹ��ʱ������Ϊ1
	int _fdArr[MAX_CONNECT_NUM];
	//��Ϣ����
	MyQueue<RequestMsg> *mq = new MyQueue<RequestMsg>();

	/************************************************
	**				�߳�ID
	************************************************/
	//�����߳�ID
	pthread_t _tReceID;
	//�����߳�ID
	pthread_t _tSendID;
	//��ʱ�߳�ID
	pthread_t _tTimeOutID;

	/************************************************
	**				˽�нӿ�
	************************************************/

	//����
	void Destroy();
	//��ʼ����Դ
	void InitializeResources();
	//��ʼ�������
	void InitServer();
	void InitServerSocket();
	void InitServerEpoll();
	//�����ͻ��������߳��Լ���������
 	static void* ListenAndReceive(void* args);
	//�������ݸ��ͻ���
	//���յ������ݣ�ֱ�������ﴦ�������ظ��������
	static void* SendMessage(void* args);
	//�������ӵĳ�ʱ��⣬���ӳ�ʱ������ֱ��ɾ����
	static void* TimerOut(void* args);

	void plog(std::string log) {
		std::cout << log << std::endl;
	}
};

