/*************************************************************************
    > File Name: epoll.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月25日 星期日 16时58分41秒
 ************************************************************************/
#ifndef MY_EPPLL_H
#define MY_EPPLL_H
#include"tcpConnection.h"
#include"mutex.h"
namespace MyNamespace
{
	using ::epoll_event;
	class CEpoll
	{
		public:
			CEpoll(IN CAcceptor& rcAcceptor);
			~CEpoll(void);
			
			void Loop(void); /* epoll循环监听,调用WaitEpoll*/
			void UnLoop(void); /* 停止epoll循环*/
		public:
			void RunInLoop(IN const std::function<void()>& cFunctor);
			void DoPendingFunctor(void);
		private:
			void HandleRead(void) const;
			void WakeUp(void) const;
		public:
			//用于设置三个私有成员
			void SetConnectCallBack(IN std::function<void(const CTcpConnection&)> cOnConnectCallback);
			void SetMessageCallBack(IN std::function<void(const CTcpConnection&)> cOnMessageCallBack);
			void SetCloseCallBack(IN  std::function<void(const CTcpConnection&)> cOnCloseCallBack);
		private:
			//这三个私有成员应该通过tcpconnection的set**callback方法传递给Tcpconnection类,
			//那个类中也有三个相应的方法来设置三个私有成员，以达到定制化的操作
			std::function<void(const CTcpConnection&)> __cm_cOnConnectCallback;/* 连接建时的处理*/
			std::function<void(const CTcpConnection&)> __cm_cOnMessageCallBack;/* 收到消息时的处理*/
			std::function<void(const CTcpConnection&)> __cm_cOnCloseCallBack;/* 连接关闭时的处理*/
		private:
			void WaitEpoll(void);/* 当epoll的标志位为真时一直循环监听每个注册的fd*/ 
			void HandleConnection(void);/* 新连接建立时的动作*/
			void HandleMessage(IN int nNewSocketFd);/* 有数据可读时的动作*/
			void ControlEpoll( IN int nOperation, IN int nFd, IN unsigned int events);/* 用于注册、删除、修改 fd*/
		private:
			CAcceptor& __cm_rcAcceptor;
			int __cm_nEpollFd; /*  epoll fd */
			int __cm_nEventFd;/* eventfd*/
			int __cm_nListenFd; /*原始sfd*/
			bool __cm_bIsLooping; /* 循环标志位*/
			map<int,const CTcpConnection&> __cm_maConnectMap; /* 存放套接字与其对应的连接*/
			vector<epoll_event> __cm_veEventList; /* 用于存放就绪fd的动态数组*/
			vector<std::function<void()>> __cm_vePendingFunctors;
			CMutexLock  __cm_cMutexLock;
	};



} /* MyNamespace */ 
#endif /* end of include guard: MY_EPPLL_H */
