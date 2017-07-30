/*************************************************************************
    > File Name: inetAddress.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月16日 星期五 02时03分51秒
 ************************************************************************/
#ifndef MY_INET_ADDRESS_H
#define MY_INET_ADDRESS_H
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	using ::sockaddr;
	using ::sockaddr_in;
	
	//此类用于创建一个sockaddr结构体
	class CSocketAddress
	{
		public:
			CSocketAddress(IN unsigned short int usnPort); /* 以默认地址建立sockaddr结构体*/
			explicit CSocketAddress(IN unsigned short int usnPort, IN const char* cpchIp);/* 以c风格字符串ip建立sockaddr结构体*/
			explicit CSocketAddress(IN unsigned short int usnPort, IN const string& cstrIP); /* 以string型IP建立sockaddr结构体*/
			explicit CSocketAddress(IN const sockaddr& csSockaddr);/* 以 sockaddr 建立此类*/
			explicit CSocketAddress(IN const sockaddr_in& csSockaddr_in);/*  以sockaddr_in建立此类*/
			
			unsigned short int GetPort(void) const; /* 获取端口号*/
			string GetIp(void) const; /*  获取string 类型的ip*/
			const char* GetIp_c(void) const;/* 获取c字符串的ip*/
			const sockaddr* GetSockaddr(void) const; /* 获取sockaddr类型的地址*/
			const sockaddr_in* GetSockaddr_in(void) const;/* 获取sockaddr_in的地址*/
			void SetFamily(IN unsigned short int usnFamily = AF_INET);
			void SetPort(IN unsigned short int usnPort);
			void SetIP(const char* cpchIp);
			void SetIP(const string& cstrIP);
		private:
			sockaddr_in __cm_sAddress;
	};
	

}
#endif /* end of include guard: MY_INET_ADDRESS_H */

