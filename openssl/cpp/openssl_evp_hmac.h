/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_hmac.cpp
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
#ifndef __MY_OPENSSL_EVP_HMAC_H
#define __MY_OPENSSL_EVP_HMAC_H

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


namespace Openssl_evp
{
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
/*!@Class
********************************************************************************
Class Name     : CHmac
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


class CHmac
{
	public:
		CHmac(IN const string strDigestName, IN const unsigned char* pcuchKey, 
				IN int nLenOfKey, IN ENGINE* psImpl = nullptr);
		CHmac(IN const string strDigestName, IN const vector<unsigned char> vecKey, 
			  IN ENGINE* psImpl = nullptr);
		~CHmac(void);

		CHmac(IN const CHmac & lref) = delete;
		CHmac(IN CHmac && rref) = delete;
		CHmac& operator = (IN const CHmac & lref) = delete;
		CHmac& operator = (IN CHmac && rref) = delete;
	public:
		int HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				 OUT unsigned char* puchOutput, IN bool IsStart,  IN bool bIsEnd);

		int HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				 OUT unsigned char* puchOutput, IN int nLenofOutput, 
				 IN bool IsStart,  IN bool bIsEnd);

		vector<unsigned char> HMAC(IN const vector<unsigned char>& vecInput,  
									 IN bool IsStart,  IN bool bIsEnd);

		void Change(IN const string strDigestName = "", IN ENGINE* psImpl = nullptr,
					IN const unsigned char* pcuchKey = nullptr, IN int nLenOfKey = 0);
	private:
		void HMACInit();//ctx初始化和haac初始化
		void HMACUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  HMACFinal(OUT unsigned char* puchOutput);
	private:
		void GetEVP_MD(IN const string& strDigestName);
	private:
		ENGINE*              __cm_psImpl;
		const EVP_MD*        __cm_psMD;
		HMAC_CTX             __cm_sHmacCtx;
		const unsigned char* __cm_pcuchKey;
		int					 __cm_nLenOfKey;
		int          		 __cm_nError;
		char                 __cm_pchErrorInfo[1024] = {0};

		bool				 __cm_bIsNeedInit;
		bool				 __cm_bIsChangeable;
		bool				 __cm_bIsFinalable;
};
}



//CHmac
Openssl_evp::CHmac::CHmac(IN const string strDigestName,
		                  IN const unsigned char* pcuchKey, 
						  IN int nLenOfKey, IN ENGINE* psImpl /* = nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_nLenOfKey(nLenOfKey)
	, __cm_bIsNeedInit(false)
	, __cm_bIsChangeable(true)
	, __cm_bIsFinalable(false)
{
	GetEVP_MD(strDigestName);
	HMACInit();
}


Openssl_evp::CHmac::~CHmac(void)

{
	::HMAC_CTX_cleanup(&__cm_sHmacCtx);
}

int 
Openssl_evp::CHmac::HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput,
						 OUT unsigned char* puchOutput,IN bool bIsStart, IN bool bIsEnd)
{
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据处理还未完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		HMACInit();
	}

	if (nLenOfInput == 0 && bIsEnd == true)
	{
		return   HMACFinal(puchOutput);
	}
	else if (nLenOfInput == 0 &&bIsEnd == false)
	{
		throw std::runtime_error("未传入数据");
	}
	
	HMACUpdate(pcuchInput, nLenOfInput);
	
	if(bIsEnd == true)
	{
		return  HMACFinal(puchOutput);
	}
	return 0;
}

int 
Openssl_evp::CHmac::HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput,
						OUT unsigned char* puchOutput, IN int nLenOfOutput,
						IN bool bIsStart, IN bool bIsEnd)
{
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据处理还未完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		HMACInit();
	}
		
	if (nLenOfOutput < __cm_psMD->md_size)
	{
		throw std::logic_error("输出缓冲区太小");
	}

	if (nLenOfInput == 0 && bIsEnd == true)
	{
		return   HMACFinal(puchOutput);
	}
	else if (nLenOfInput == 0 &&bIsEnd == false)
	{
		throw std::runtime_error("未传入数据");
	}
	
	HMACUpdate(pcuchInput, nLenOfInput);
	
	if(bIsEnd == true)
	{
		return  HMACFinal(puchOutput);
	}
	return 0;
}

Openssl_evp::vector<unsigned char>  
Openssl_evp::CHmac::HMAC(IN const vector<unsigned char>& vecInput, 
						IN bool bIsStart, IN bool bIsEnd)
{
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据处理还未完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		HMACInit();
	}

	if (vecInput.size() == 0 && bIsEnd == true)
	{
		vector<unsigned char> vecTemp(__cm_psMD->md_size , 0);
		HMACFinal(vecTemp.data());
		return   vecTemp;
	}
	else if (vecInput.size() == 0 &&bIsEnd == false)
	{
		throw std::runtime_error("未传入数据");
	}
	
	HMACUpdate(vecInput.data(), vecInput.size());
	
	if(bIsEnd == true)
	{
		vector<unsigned char> vecTemp(__cm_psMD->md_size , 0);
		HMACFinal(vecTemp.data());
		return   vecTemp;
	}
	return vector<unsigned char>();
}

void 
Openssl_evp::CHmac::Change(IN const string strDigestName /*=nullptr*/,
		                     IN ENGINE* psImpl /*= nullptr*/,
							 IN const unsigned char* pcuchKey /*= nullpt*/, 
							 IN int nLenOfKey /*= 0*/)
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
		if (pcuchKey != nullptr && nLenOfKey != 0)
		{
			__cm_pcuchKey = pcuchKey;
			__cm_nLenOfKey = nLenOfKey;
			 __cm_bIsNeedInit = true;
		}
		else if ((pcuchKey != nullptr && nLenOfKey <=0) || (pcuchKey == nullptr && nLenOfKey > 0))
		{
			throw std::invalid_argument("参数不正确");
		}

		if (__cm_bIsNeedInit == true)
		{
			HMACInit();
		}
	}
	else
	{
		throw std::logic_error("上一任务还未完成，进制修改");
	}
}
void 
Openssl_evp::CHmac::GetEVP_MD(IN const string& strDigestName)
{
	__cm_psMD = ::EVP_get_digestbyname(strDigestName.c_str());
   if (__cm_psMD == nullptr)
   {
		throw std::invalid_argument("不支持该算法");
   }
}


void
Openssl_evp::CHmac::HMACInit()
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
	__cm_bIsNeedInit = false;
}


void
Openssl_evp::CHmac::HMACUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	__cm_bIsChangeable = false;
	if (!::HMAC_Update(&__cm_sHmacCtx, pcuchInput, nLenOfInput))
	{
		__cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw std::runtime_error(__cm_pchErrorInfo);
	}
	__cm_bIsFinalable = true;
}

int
Openssl_evp::CHmac::HMACFinal(IN unsigned char* puchOutput)
{
	int nLen = 0;
	if (__cm_bIsFinalable == true)
	{
		if (!::HMAC_Final(&__cm_sHmacCtx, puchOutput, 
					reinterpret_cast<unsigned int*>(&nLen)))
		{
			__cm_nError = ::ERR_get_error();
			::bzero(__cm_pchErrorInfo,1024);
			::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
			throw std::runtime_error(__cm_pchErrorInfo);
		}
		__cm_bIsFinalable = false;
		__cm_bIsChangeable = true;
		return nLen;
	}
	else
	{
		throw std::logic_error("还未调用update");
	}
}

#endif /* end of include guard: __MY_OPENSSL_EVP_DIGESTANDHMAC_H */
