/*************************************************************************
    > File Name: utility.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 14时25分51秒
 ************************************************************************/
#ifndef MY_UTILITY_H
#define MY_UTILITY_H
#include"inetAddress.h"
namespace MyNamespace
{
	using ::socklen_t;
	CSocketAddress gGetLocalAddress(IN int nSocketFd);
	CSocketAddress gGetPeerAddress(IN int nSocketFd);
	void gSetNonBlock(IN int nSocketFd);
	void gSetReuseAddress(IN int nSocketFd, IN int nflags = 1);
	void gSetReusePort(IN int nSocketFd, IN int nflags = 1);
	bool gIsConnectionClosed(IN int nSocketFd);
	int gCreateSocketFd(void);
}
#endif /* end of include guard: MY_UTILITY_H */
