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
				   OUT unsigned char* puchOutput, IN bool bIsStart, IN bool bIsEnd);
		
		int Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				   OUT unsigned char* puchOutput, IN int nLenofOutput, IN bool bIsStart, IN bool bIsEnd);
		
		vector<unsigned char> Digest(IN const vector<unsigned char>& vecInput, bool bIsStart, IN bool bIsEnd);

		void Change(IN const string strDigestName = "", IN ENGINE* psImpl = nullptr);

	private:
		void MDInit(void);//ctx初始化和degist初始化
		void MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  MDFinal(OUT unsigned char* puchOutput);
		
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
		bool				 __cm_bIsFinalable; //是否可以调用final
};


}

//CDigest
Openssl_evp::CDigest::CDigest(IN const string strDigestName,
							  IN ENGINE* psImpl /* = nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_bIsNeedInit(false)
	, __cm_bIsChangeable(true)
	, __cm_bIsFinalable(false)
{
	GetEVP_MD(strDigestName);
	MDInit();
}


Openssl_evp::CDigest::~CDigest(void)

{
	::EVP_MD_CTX_cleanup(&__cm_sMdCtx);
}


int
Openssl_evp::CDigest::Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
							 OUT unsigned char* puchOutput,
							 IN bool bIsStart, IN bool bIsEnd)  
{
	if ( bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		MDInit();
	}
	//不会出现新任务开始却没有数据进来的情况,只会在真实数据读入后才会调用函数
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		return MDFinal(puchOutput);
	}
	if (nLenOfInput == 0 && bIsEnd == false)
	{
		throw std::invalid_argument("参数非法");
	}

	MDUpdate(pcuchInput, nLenOfInput);
	
	if(bIsEnd == true)
	{
		return MDFinal(puchOutput);
	}
	return 0;
}

int 
Openssl_evp::CDigest::Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				   OUT unsigned char* puchOutput, IN int nLenofOutput, IN bool bIsStart, IN bool bIsEnd)
{
	if ( bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		MDInit();
	}

	if (nLenofOutput < __cm_psMD->md_size)
	{
		throw std::logic_error("输出缓冲区太小");
	}
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		return  MDFinal(puchOutput);
	}
	if (nLenOfInput == 0 && bIsEnd == false)
	{
		throw std::invalid_argument("参数非法");
	}
	MDUpdate(pcuchInput, nLenOfInput);
	if(bIsEnd == true)
	{
		return  MDFinal(puchOutput);
	}
	return 0;
}

Openssl_evp::vector<unsigned char> 
Openssl_evp::CDigest::Digest(IN const vector<unsigned char>& vecInput, bool bIsStart, IN bool bIsEnd)
{
	
	if ( bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		MDInit();
	}

	if (vecInput.size() == 0 && bIsEnd == true)
	{
		vector<unsigned char> vecTemp(__cm_psMD->md_size,0);
		MDFinal(vecTemp.data());
		return vecTemp;
	}
	if (vecInput.size() == 0 && bIsEnd == false)
	{
		throw std::invalid_argument("参数非法");
	}
	MDUpdate(vecInput.data(), vecInput.size());
	if(bIsEnd == true)
	{
		vector<unsigned char> vecTemp(__cm_psMD->md_size,0);
		MDFinal(vecTemp.data());
		return vecTemp;
	}
	return vector<unsigned char>();
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
	__cm_bIsNeedInit = false;
}

void 
Openssl_evp::CDigest::MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	__cm_bIsChangeable = false;
	if (!::EVP_DigestUpdate(&__cm_sMdCtx, pcuchInput, nLenOfInput))
	{
		 __cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
	__cm_bIsFinalable = true;
}

int 
Openssl_evp::CDigest::MDFinal(OUT unsigned char* puchOutput)
{
	int nLength = 0;
	if (__cm_bIsFinalable == true)
	{
		if (!::EVP_DigestFinal_ex(&__cm_sMdCtx, puchOutput, 
					reinterpret_cast<unsigned int*>(&nLength)))
		{
			 __cm_nError = ::ERR_get_error();
			::bzero(__cm_pchErrorInfo,1024);
			::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
			throw std::runtime_error(__cm_pchErrorInfo);
		}
		__cm_bIsFinalable = false;
		__cm_bIsChangeable = true;
		return nLength;
	}
	else
	{
		throw std::logic_error("还未调用update");
	}
}

#endif /* end of include guard: __MY_OPENSSL_EVP_DIGESTANDHMAC_H */
