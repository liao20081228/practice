/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_digestandhmac.cpp
Related Files  : no
File Function  : 摘要 mac
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

/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#ifndef __MY_OPENSSL_EVP_DIGESTANDHMAC_H
#define __MY_OPENSSL_EVP_DIGESTANDHMAC_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef __MY_OPENSSL_ERROR
#define  __MY_OPENSSL_ERROR
#endif


#include<openssl/err.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include"unistd.h"
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
#include"openssl_evp_loadconf.h"
#include<iostream>
#include<exception>
#include<vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


namespace Openssl_evp
{
/*!@Class
********************************************************************************
Class Name     : CDigestAndHmac
Function       : calculate message digest value
Exception Class: no
--------------------------------------------------------------------------------
Note           : pnLenOfOutput must equal to the size of puchOutput
Typical Usage  : no
--------------------------------------------------------------------------------
Date:          : 2017/07/31
Version:       : 0.0
Author         : liaoweizhi
Department     : 技术研发总部 
Email          : liaowz@koal.com
Modifier       : no
Department     : no
Email          : no
Changes        : create
*******************************************************************************/


class CDigestAndHmac
{
	public:
		CDigestAndHmac(IN const string strDigestName,IN ENGINE* psImpl = nullptr,
				IN const unsigned char* pcuchKey = nullptr,IN int nLenOfKey = 0);
		~CDigestAndHmac(void);

		CDigestAndHmac(IN const CDigestAndHmac & lref) = delete;
		CDigestAndHmac(IN CDigestAndHmac && rref) = delete;
		CDigestAndHmac& operator = (IN const CDigestAndHmac & lref) = delete;
		CDigestAndHmac& operator = (IN CDigestAndHmac && rref) = delete;
	public:
		int Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				   OUT unsigned char* puchOutput, IN bool bIsEnd);
		int HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				 OUT unsigned char* puchOutput, IN bool bIsEnd);


		void Change(IN const string strDigestName, IN ENGINE* psImpl = nullptr,
					IN const unsigned char* pcuchKey = nullptr, IN int nLenOfKey = 0);
	private:
		void MDInit(void);//ctx初始化和degist初始化
		void MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  MDFinal(OUT unsigned char* puchOutput);
		
		void HMACInit();//ctx初始化和haac初始化
		void HMACUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  HMACFinal(OUT unsigned char* puchOutput);
	private:
		void GetEVP_MD(IN const string& strDigestName);
	private:
		EVP_MD_CTX           __cm_sMdCtx;
		ENGINE*              __cm_psImpl;
		const EVP_MD*        __cm_psMD;
		HMAC_CTX             __cm_sHmacCtx;
		const unsigned char* __cm_pcuchKey;
		int					 __cm_nLenOfKey;
		int          		 __cm_nError;
		char                 __cm_pchErrorInfo[1024] = {0};
};



#endif /* end of include guard: __MY_OPENSSL_EVP_DIGESTANDHMAC_H */

//CDigestAndHmac
Openssl_evp::CDigestAndHmac::CDigestAndHmac(IN const string strDigestName,
							  IN ENGINE* psImpl /* = nullptr*/,
		                      IN const unsigned char* pcuchKey /*=nullptr*/,
							  IN int nLenOfKey/*=0*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_nLenOfKey(nLenOfKey)
{
	GetEVP_MD(strDigestName);
	if(__cm_pcuchKey != nullptr && __cm_nLenOfKey > 0)
	{
		HMACInit();
	}
	else
	{
		MDInit();
	}
}


Openssl_evp::CDigestAndHmac::~CDigestAndHmac(void)

{
	::EVP_MD_CTX_cleanup(&__cm_sMdCtx);
	::HMAC_CTX_cleanup(&__cm_sHmacCtx);
}


int
Openssl_evp::CDigestAndHmac::Digest(IN const unsigned char* pcuchInput, 
							 IN int nLenOfInput, 
							 OUT unsigned char* puchOutput, 
							 IN bool bIsEnd/*=false*/)  
{
	int nLen = 0;
	MDUpdate(pcuchInput, nLenOfInput);
	if(bIsEnd == true)
	{
		nLen = MDFinal(puchOutput);
		MDInit();
		return nLen;
	}
	return 0;
}


int 
Openssl_evp::CDigestAndHmac::HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput,
		IN OUT unsigned char* puchOutput, IN bool bIsEnd)
{	
	int nLen = 0;
	HMACUpdate(pcuchInput, nLenOfInput);
	if(bIsEnd == true)
	{
		nLen = HMACFinal(puchOutput);
		HMACInit();
		return nLen;
	}
	return 0;
}

void 
Openssl_evp::CDigestAndHmac::GetEVP_MD(IN const string& strDigestName)
{
	__cm_psMD = ::EVP_get_digestbyname(strDigestName.c_str());
   if (__cm_psMD == nullptr)
   {
		throw std::invalid_argument("不支持该算法");
   }
}


void 
Openssl_evp::CDigestAndHmac::MDInit(void)
{
	::EVP_MD_CTX_init(&__cm_sMdCtx);
	if (!::EVP_DigestInit_ex(&__cm_sMdCtx, __cm_psMD, __cm_psImpl))
	{
		 __cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
}

void 
Openssl_evp::CDigestAndHmac::MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	if (!::EVP_DigestUpdate(&__cm_sMdCtx, pcuchInput, nLenOfInput))
	{
		 __cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
}

int 
Openssl_evp::CDigestAndHmac::MDFinal(OUT unsigned char* puchOutput)
{
	int nLength = 0;
	if (!::EVP_DigestFinal_ex(&__cm_sMdCtx, puchOutput, 
				reinterpret_cast<unsigned int*>(&nLength)))
	{
		 __cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
	return nLength;
}

void
Openssl_evp::CDigestAndHmac::HMACInit()
{
	::HMAC_CTX_init(&__cm_sHmacCtx);
	if (!::HMAC_Init_ex(&__cm_sHmacCtx, __cm_pcuchKey, __cm_nLenOfKey, 
		__cm_psMD, __cm_psImpl))
	{
		__cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
}


void
Openssl_evp::CDigestAndHmac::HMACUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	if (!::HMAC_Update(&__cm_sHmacCtx, pcuchInput, nLenOfInput))
	{
		__cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
}

int
Openssl_evp::CDigestAndHmac::HMACFinal(IN unsigned char* puchOutput)
{
	int nLen = 0;
	if (!::HMAC_Final(&__cm_sHmacCtx, puchOutput, 
				reinterpret_cast<unsigned int*>(&nLen)))
	{
		__cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
	return nLen;
}



void 
Openssl_evp::CDigestAndHmac::Change(IN const string strDigestName /*=nullptr*/,
		                     IN ENGINE* psImpl /*= nullptr*/,
							 IN const unsigned char* pcuchKey /*= nullpt*/, 
							 IN int nLenOfKey /*= 0*/)
{
	if (!strDigestName.empty())
	{
		 GetEVP_MD(strDigestName);
	}
	if (psImpl != nullptr)
	{
		__cm_psImpl = psImpl;
	}
	if (pcuchKey != nullptr && nLenOfKey != 0)
	{
		__cm_pcuchKey = pcuchKey;
		__cm_nLenOfKey = nLenOfKey;
	}
	else if ((pcuchKey != nullptr && nLenOfKey <=0) || (pcuchKey == nullptr && nLenOfKey > 0))
	{
		throw std::invalid_argument("参数不正确");
	}
	if (__cm_pcuchKey != nullptr && __cm_nLenOfKey > 0)
	{
		HMACInit();
	}
	else
	{
		MDInit();
	}
}

}
