/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_digest.cpp
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
#ifndef __MY_OPENSSL_EVP_DIGEST_H
#define __MY_OPENSSL_EVP_DIGEST_H

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
#include"unistd.h"
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
#include"openssl_evp_loadconf.h"
#include<iostream>
#include<exception>
#include<vector>


namespace Openssl_evp
{
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
/*!@Class
********************************************************************************
Class Name     : CDigest
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


class CDigest
{
	public:
		CDigest(IN const string strDigestName,IN ENGINE* psImpl = nullptr);
		~CDigest(void);

		CDigest(IN const CDigest & lref) = delete;
		CDigest(IN CDigest && rref) = delete;
		CDigest& operator = (IN const CDigest & lref) = delete;
		CDigest& operator = (IN CDigest && rref) = delete;
	public:
		int Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				   OUT unsigned char* puchOutput, IN bool bIsEnd);

		void Change(IN const string strDigestName = "", IN ENGINE* psImpl = nullptr);
	private:
		void MDInit(void);//ctx初始化和degist初始化
		void MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  MDFinal(OUT unsigned char* puchOutput);
		
		void ThrowException(IN const char* pchInfo) const;
	private:
		void GetEVP_MD(IN const string& strDigestName);
	private:
		EVP_MD_CTX           __cm_sMdCtx;
		ENGINE*              __cm_psImpl;
		const EVP_MD*        __cm_psMD;
		int          		 __cm_nError;
		char                 __cm_pchErrorInfo[1024] = {0};
		bool				 __cm_bIsNeedInit; //是否需要初始化
		bool				 __cm_bIsChangeable; //是否可以修改参数
};


}
#endif /* end of include guard: __MY_OPENSSL_EVP_DIGESTANDHMAC_H */

//CDigest
Openssl_evp::CDigest::CDigest(IN const string strDigestName,
							  IN ENGINE* psImpl /* = nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_bIsNeedInit(false)
	, __cm_bIsChangeable(true)
{
	GetEVP_MD(strDigestName);
	MDInit();
}


Openssl_evp::CDigest::~CDigest(void)

{
	::EVP_MD_CTX_cleanup(&__cm_sMdCtx);
}


int
Openssl_evp::CDigest::Digest(IN const unsigned char* pcuchInput, 
							 IN int nLenOfInput, 
							 OUT unsigned char* puchOutput, 
							 IN bool bIsEnd/*=false*/)  
{
	int nLen = 0;
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		nLen = MDFinal(puchOutput);
		__cm_bIsChangeable = true;
		MDInit();
		return nLen;
	}
	if (nLenOfInput == 0 && bIsEnd == false)
	{
		throw std::invalid_argument("参数非法");
	}
	__cm_bIsChangeable = false;
	MDUpdate(pcuchInput, nLenOfInput);
	if(bIsEnd == true)
	{
		nLen = MDFinal(puchOutput);
		MDInit();
		__cm_bIsChangeable = true;
		return nLen;
	}
	return 0;
}

void 
Openssl_evp::CDigest::Change(IN const string strDigestName /*=nullptr*/,
		                     IN ENGINE* psImpl /*= nullptr*/)
{
	if (__cm_bIsChangeable == true)
	{
		if (!strDigestName.empty())
		{
			GetEVP_MD(strDigestName);
			__cm_bIsNeedInit = true;
		}
		if (psImpl != nullptr)
		{
			__cm_psImpl = psImpl;
			__cm_bIsNeedInit = true;
		}
		if (__cm_bIsNeedInit == true)
		{
			MDInit();
			__cm_bIsNeedInit = false;
		}
	}
	else
	{
		throw std::logic_error("现在不可以更改属性");
	}
}

void 
Openssl_evp::CDigest::GetEVP_MD(IN const string& strDigestName)
{
	__cm_psMD = ::EVP_get_digestbyname(strDigestName.c_str());
   if (__cm_psMD == nullptr)
   {
		throw std::invalid_argument("不支持该算法");
   }
}


void 
Openssl_evp::CDigest::MDInit(void)
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
Openssl_evp::CDigest::MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput)
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
Openssl_evp::CDigest::MDFinal(OUT unsigned char* puchOutput)
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

