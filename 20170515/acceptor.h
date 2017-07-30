/*************************************************************************
    > File Name: acceptor.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月17日 星期六 15时30分10秒
 ************************************************************************/
#ifndef MY_ACCEPTOR_H
#define MY_ACCEPTOR_H
#include"inetAddress.h"
#include"socketFd.h"
#include"utility.h"
namespace MyNamespace
{
	class CAcceptor
	{
		public:
			CAcceptor(IN int nListenSocketFd, IN const CSocketAddress& cAddress);/*  接收一个原始套接字*/
			
			void Ready(void) const;
			int AcceptConnect(void) const; /* 接收连接*/ 
			int GetSocketFd(void) const;
		private:
			void __BindSocketAddress(void) const; /* 绑定*/
			void __ListenSocket(void) const; /*监听*/
		private:
			CSocketFd __cm_cListenSocketFd; /* 生成一个类，由类的析构函数来管理原始套接字的关闭*/
			CSocketAddress __cm_cAddress;
	};
}
#endif /* end of include guard: MY_ACCEPTOR_H */
