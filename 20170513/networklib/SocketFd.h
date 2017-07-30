/*************************************************************************
    > File Name: socketFd.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 11时36分50秒
 ************************************************************************/
#ifndef MY_SOCKET_FD_H
#define MY_SOCKET_FD_H
#include"FobidCopyAndAssign.h"
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace NetworkLibrary
{
	class CSocketFd :  public CForbidCopyAndAssign
	{
		public:
			CSocketFd(IN int nSocketFd);
			CSocketFd(void);
			~CSocketFd(void);/* explcit static virtual 不许在类外实现时给出，inline可以给出，但是inline函数
			不应该有选择、开关、循环语句*/

			int GetSocketFd(void) const;/* 默认值应该在声明中给出而不是定义中给出*/
			void ShutDownSocketFd(IN int nHow = SHUT_WR) const; /* 对数据成员不做修改的都应该加const*/
		private:
			int __cm_nScoketFd;
	};

	CSocketFd::CSocketFd(IN int nSocketFd)
		: __cm_nScoketFd(nSocketFd)
	{
		if (__cm_nScoketFd < 0)
		{
			cout << "input arguement error" << endl;
			std::exit(-1);
		}
	}
	
	CSocketFd::~CSocketFd(void)
	{
		if(::close(__cm_nScoketFd) == -1)
		{
			std::perror("close() failed or occur error");
			std::exit(-1);
		}
	}

	CSocketFd::CSocketFd(void)
		: __cm_nScoketFd(::socket(AF_INET, SOCK_STREAM, 0))
	{
		if (__cm_nScoketFd == -1)
		{
			std::perror("socket ");
			std::exit(-1);
		}
	}

	inline int
	CSocketFd::GetSocketFd(void) const
	{
		return __cm_nScoketFd;
	}

	void
	CSocketFd::ShutDownSocketFd(IN int nHow /* = SHUT_WR*/) const
	{
		if (::shutdown(__cm_nScoketFd, nHow) == -1)
		{
			std::perror("shutdown() failed");
			std::exit(-1);
		}
	}
}
#endif /* end of include guard: MY_SOCKET_FD_H */
