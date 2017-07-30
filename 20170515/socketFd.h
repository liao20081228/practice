/*************************************************************************
    > File Name: socket.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月16日 星期五 15时29分35秒
 ************************************************************************/
#ifndef MY_SOCKET_H
#define MY_SOCKET_H
#include<myhead_cpp.h>
namespace MyNamespace
{
	class CSocketFd
	{
		public:
			CSocketFd(void); /* 创建一个socketfd*/
			CSocketFd(IN int nSocketFd);/* 将传入的socketfd封装为对象*/
			~CSocketFd(void);/* 关闭fd*/
			
			int GetSocketFd(void) const;/* 获取fd*/
			void ShutDown(IN int nHow = SHUT_WR) const; /* 以某种方式关闭fd*/
			
		private:
			int __cm_nSocketFd;
	};
	

}
#endif /* end of include guard: MY_SOCKET_H */
