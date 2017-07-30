/*************************************************************************
    > File Name: InetAddress.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 13时08分09秒
 ************************************************************************/
#ifndef MY_INET_ADDRESS_H
#define MY_INET_ADDRESS_H
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace NetworkLibrary
{
	using  ::sockaddr;
	using ::sockaddr_in;
	
	class CSocketAddress
	{
		public:
			explicit CSocketAddress(IN uint16_t usnPort, IN const char* cpchIp);
			explicit CSocketAddress(IN uint16_t usnPort, IN const string& cstrIp);
			explicit CSocketAddress(IN const sockaddr& csSocketaddr);
			explicit CSocketAddress(IN const sockaddr_in& csSocketaddr_in);
			explicit CSocketAddress(IN uint16_t usnPort);

			const sockaddr* Getsockaddr(void) const;
			const sockaddr_in* Getsockaddr_in(void) const;
			const char* GetIp_c(void) const;
			const string GetIp(void) const;
			unsigned short int GetPort(void) const;
			
			void SetPort(IN uint16_t usnPort);
			void SetFamily(IN uint16_t usnFamily);
			void SetIp(IN const char* cpchIp);
			void SetIp(IN const string& cstrIp);
		private:
			sockaddr_in __cm_sSockaddress;
	};

	/*explicit*/ inline
	CSocketAddress::CSocketAddress(IN uint16_t usnPort, IN const char* cpchIp)
	{
		assert(usnPort >= 0);
		std::memset(&__cm_sSockaddress, 0, sizeof(__cm_sSockaddress));
		__cm_sSockaddress.sin_family = AF_INET;
		__cm_sSockaddress.sin_port = ::htons(usnPort);
		::inet_aton(cpchIp, &__cm_sSockaddress.sin_addr);
		/*__cm_sSockaddress.sin_addr.s_addr = ::inet_addr(cpchIp);*/
	}

	/* explicit*/inline
	CSocketAddress::CSocketAddress(IN uint16_t usnPort, IN const string& cstrIp)
	{
		assert(usnPort >= 0);
		std::memset(&__cm_sSockaddress, 0, sizeof(__cm_sSockaddress));
		__cm_sSockaddress.sin_family = AF_INET;
		__cm_sSockaddress.sin_port = ::htons(usnPort);
		::inet_aton(cstrIp.c_str(), &__cm_sSockaddress.sin_addr);
		/*__cm_sSockaddress.sin_addr.s_addr = ::inet_addr(cpchIp);*/
	}
	/*explicit*/ inline
	CSocketAddress::CSocketAddress(IN const sockaddr& csSocketaddr)
	{
		__cm_sSockaddress = reinterpret_cast<const sockaddr_in&>(csSocketaddr);
	}
	/*explicit*/inline
	CSocketAddress::CSocketAddress(IN const sockaddr_in& csSocketaddr_in)
	{
		__cm_sSockaddress = csSocketaddr_in;
	}
	/*explicit*/ inline
	CSocketAddress::CSocketAddress(IN uint16_t usnPort)
	{
		assert(usnPort >= 0);
		__cm_sSockaddress.sin_family = AF_INET;
		__cm_sSockaddress.sin_port = ::htons(usnPort);
		__cm_sSockaddress.sin_addr.s_addr = INADDR_ANY;
	}

	inline const sockaddr* 
	CSocketAddress::Getsockaddr(void) const
	{
		return reinterpret_cast<const sockaddr*>(&__cm_sSockaddress);
	}
	inline const sockaddr_in* 
	CSocketAddress::Getsockaddr_in(void) const
	{
		return &__cm_sSockaddress;
	}
	inline const char* 
	CSocketAddress::GetIp_c(void) const
	{
		return ::inet_ntoa(__cm_sSockaddress.sin_addr);
	}
	inline const string 
	CSocketAddress::GetIp(void) const
	{
		return string(::inet_ntoa(__cm_sSockaddress.sin_addr));
	}
	inline unsigned short int 
	CSocketAddress::GetPort(void) const
	{
		return ::ntohs(__cm_sSockaddress.sin_port);
	}
	
	inline void 
	CSocketAddress::SetPort(IN uint16_t usnPort)
	{
		__cm_sSockaddress.sin_port = ::htons(usnPort);
	}
	inline void 
	CSocketAddress::SetFamily(IN uint16_t usnFamily)
	{
		__cm_sSockaddress.sin_family = usnFamily;
	}
	inline void 
	CSocketAddress::SetIp(IN const char* cpchIp)
	{
		::inet_aton(cpchIp, &__cm_sSockaddress.sin_addr);
	}
	
	inline void 
	CSocketAddress::SetIp(IN const string& cstrIp)
	{
		::inet_aton(cstrIp.c_str(), &__cm_sSockaddress.sin_addr);
	}

} /* NetworkLibrary */ 
#endif /* end of include guard: MY_INET_ADDRESS_H */
