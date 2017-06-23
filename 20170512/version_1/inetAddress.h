/*************************************************************************
    > File Name: inetAddress.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月16日 星期五 02时03分51秒
 ************************************************************************/
#ifndef MY_INET_ADDRESS_H
#define MY_INET_ADDRESS_H
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
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
	

	inline 
	CSocketAddress::CSocketAddress(IN unsigned short int usnPort)
	{
		std::memset(&__cm_sAddress, 0, sizeof(__cm_sAddress));
		__cm_sAddress.sin_family = AF_INET;
		__cm_sAddress.sin_port = ::htons(usnPort);
		__cm_sAddress.sin_addr.s_addr = INADDR_ANY;
	}
	
	
	/* explicit*/
	CSocketAddress::CSocketAddress(IN unsigned short int usnPort, IN const char* cpchIp)
	{
		std::memset(&__cm_sAddress, 0, sizeof(__cm_sAddress));
		__cm_sAddress.sin_family = AF_INET;
		__cm_sAddress.sin_port = ::htons(usnPort);
		if(::inet_aton(cpchIp, &__cm_sAddress.sin_addr) != 1)
		{
			cout << "inet_aton failed" << endl;
			exit(-1);
		}
		//或者用__cm_sAddress.sin_addr.s_addr = ::inet_addr(cpchIp);//由于-1==255.255.255.255所以有bug
	}


	inline /* explicit*/
	CSocketAddress::CSocketAddress(IN unsigned short int usnPort, IN const string& cstrIP) 
	{
		std::memset(&__cm_sAddress,0, sizeof(__cm_sAddress));
		__cm_sAddress.sin_family = AF_INET;
		__cm_sAddress.sin_port = htons(usnPort);
		if(::inet_aton(cstrIP.c_str(), &__cm_sAddress.sin_addr) != 1)
		{
			cout << "inet_aton failed" << endl;
			exit(-1);
		}
	}


	inline /* explicit*/
	CSocketAddress::CSocketAddress(IN const sockaddr& csSockaddr)
		:__cm_sAddress(reinterpret_cast<sockaddr_in&>(const_cast<sockaddr&>(csSockaddr)))
	{
		/*
		 * static_cast 用于基类与派生类的指针或引用之间的转换，基本数据类型及其指针或引用之间的转化。不能有const修饰。
		 * const_cast 用于将增加或删除指针或引用的const属性
		 * reinterpret_cast 用于无关类型的指针，引用，指针与整数之间的转化，不能有const修饰。从底层二进制位重新解释。
		 * dynamic_cast 用于基类与派生类的指针或引用之间的转化，上行转化和static_cast一样，下行转换会坚检查操作是否有效，不能有const修饰
		 */
	}


	inline /*explicit*/
	CSocketAddress::CSocketAddress(IN const sockaddr_in& csSockaddr_in)
		: __cm_sAddress(csSockaddr_in)
	{
	}


	inline unsigned short int
	CSocketAddress::GetPort(void) const
	{
		return ::ntohs(__cm_sAddress.sin_port);
	}


	inline string
	CSocketAddress::GetIp(void) const
	{
		return string(::inet_ntoa(__cm_sAddress.sin_addr));
	}
	

	inline const char*
	CSocketAddress::GetIp_c(void) const
	{
		return ::inet_ntoa(__cm_sAddress.sin_addr);
	}


	inline const sockaddr* 
	CSocketAddress::GetSockaddr(void) const 
	{
		return (sockaddr*)&__cm_sAddress;
	}


	inline const sockaddr_in* 
	CSocketAddress::GetSockaddr_in(void) const
	{
		return &__cm_sAddress;
	}
	
	
	inline void
	CSocketAddress::SetFamily(IN unsigned short int usnFamily)
	{
		__cm_sAddress.sin_family =  usnFamily;
	}

	inline void 
	CSocketAddress::SetPort(IN unsigned short int usnPort)
	{
		__cm_sAddress.sin_port =  ::htons(usnPort);
	}
	
	inline void 
	CSocketAddress::SetIP(const char* cpchIp)
	{
		::inet_aton(cpchIp, &__cm_sAddress.sin_addr);
	}
	
	
	inline void 
	CSocketAddress::SetIP(const string& cstrIP)
	{
		::inet_aton(cstrIP.c_str(), &__cm_sAddress.sin_addr);
	}
}
#endif /* end of include guard: MY_INET_ADDRESS_H */

