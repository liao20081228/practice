/*************************************************************************
    > File Name: socketFd.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 11时36分50秒
 ************************************************************************/
#ifndef MY_SOCKET_FD_H
#define MY_SOCKET_FD_H

#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace NetworkLibrary
{
	class CSocketFd
	{
		public:
			CSocketFd(int nSocketFd);
			CSocketFd(void);


	}
}
#endif /* end of include guard: MY_SOCKET_FD_H */
