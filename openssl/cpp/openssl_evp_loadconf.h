/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_loadconf.h
Related Files  : no
File Function  : 载入配置
Author         : liaoweizhi
Department     : 技术研发总部
Email          : liaowz@koal.com
Version        : 0.0
--------------------------------------------------------------------------------
Note           : 采用c++的方式
--------------------------------------------------------------------------------
Date:          : 2017/07/30
Version:       : 0.0
Modifier       : no
Department     : no
Email          : no
Changes        : create
*******************************************************************************/
#ifndef __MY_OPENSSL_EVP_LOADCONF_H
#define __MY_OPENSSL_EVP_LOADCONF_H

#include<openssl/err.h>
#include<openssl/evp.h>
#include<pthread.h>
#include<cstdlib>
/*!@Class
********************************************************************************
Class Name     : CLoadConf
Function       : loading globle algorithm and error Information string
Exception Class: no exception
--------------------------------------------------------------------------------
Note           : it is a singleton class
Typical Usage  : CLoadConf once
--------------------------------------------------------------------------------
Date:          : 2017/08/07
Version:       : 0.0
Author         : liaoweizhi
Department     : 技¯研发总部
Email          : liaowz@koal.com
Modifier       : no
Department     : no
Email          : 
Changes        : create
*******************************************************************************/
namespace Openssl_evp
{
class CLoadConf
{
	public:
		static CLoadConf *Getinstance(void);
		static void Destroy(void);
		static void Init(void);

		/*member*/
	protected:
		/*member*/
	private:
		CLoadConf(void);
		~CLoadConf(void);
	
	private:
		static CLoadConf *__cm_pCLoadConf; //静态指针
		static pthread_once_t __cm_sOnce;  //线程相关变量
};
}
#endif /* end of include guard: __MY_OPENSSL_EVP_LOADCONF_H */


//class CLoadConf,单例饿汉式，线程安全
Openssl_evp::CLoadConf* Openssl_evp::CLoadConf::__cm_pCLoadConf = Getinstance();
pthread_once_t Openssl_evp::CLoadConf::__cm_sOnce = PTHREAD_ONCE_INIT;

inline  /* static */ Openssl_evp::CLoadConf* 
Openssl_evp::CLoadConf::Getinstance(void)
{
	::pthread_once(&__cm_sOnce, Init);
	return __cm_pCLoadConf;
}

/* static */ void 
Openssl_evp::CLoadConf::Init(void)
{
	if(nullptr == __cm_pCLoadConf)
	{
		__cm_pCLoadConf = new CLoadConf;
		::OpenSSL_add_all_algorithms();
#ifdef __MY_OPENSSL_ERROR
		::ERR_load_crypto_strings();
#endif
		std::atexit(Destroy);
	}
}

/* static */ void 
Openssl_evp::CLoadConf::Destroy(void)
{
	if(nullptr != __cm_pCLoadConf)
	{
		::EVP_cleanup();
		::ERR_free_strings();
		delete __cm_pCLoadConf;
	}
}

inline
Openssl_evp::CLoadConf::CLoadConf(void)
{

}

inline
Openssl_evp::CLoadConf::~CLoadConf(void)
{
}

