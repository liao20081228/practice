/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_base64.h
Related Files  : no
File Function  : base64编解码
Author         : liaoweizhi
Department     : 技术研发总部
Email          : liaowz@koal.com
Version        : 0.0
--------------------------------------------------------------------------------
Note           : 采用c的方式
--------------------------------------------------------------------------------
Date:          : 2017/07/30
Version:       : 0.0
Modifier       : no
Department     : no
Email          : no
Changes        : create
*******************************************************************************/
#ifndef __MY_OPENSSL_EVP_BASE64_H
#define __MY_OPENSSL_EVP_BASE64_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef __MY_OPENSSL_ERROR
#define __MY_OPENSSL_ERROR
#endif /* end of include guard: __MY_OPENSSL_ERROR */

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
Class Name     : Base64
Function       : 以十六进制输出或者以base64编码输出
Exception Class: <exception class belonging to this class (if any)>
--------------------------------------------------------------------------------
Note           : no
Typical Usage  : no
--------------------------------------------------------------------------------
Date:          : 2017/08/09
Version:       : 0.0
Author         : liaoweizhi
Department     : 技术研发总部
Email          : liaowz@koal.com
Modifier       : no
Department     : no
Email          : no
Changes        : create
*******************************************************************************/

class CBase64
{
	public:
		CBase64(void);
		~CBase64(void);
	public:
		int Encode(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
					OUT unsigned char* puchOutput, IN int nLenOfOutput, 
					IN bool bIsStart, IN bool bIsEnd);

		int Decode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput, IN int nLenOfOutput,
					IN bool  bIsStart, IN bool bIsEnd);

		vector<unsigned char> Encode(IN const vector<unsigned char>& vecInput,
									 IN bool bIsStart, IN bool bIsEnd);

		vector<unsigned char> Decode(IN const vector<unsigned char>& vecInput,
									 IN bool bIsStart, IN bool bIsEnd);

	private:
		void Encode_Init();
		int  Encode_Update(IN const unsigned char* pcuchInput, IN int nLenOfInput,
							OUT unsigned char* puchOutput);
		int  Encode_Final(OUT unsigned char* puchOutput);
		
		void Decode_Init();
		int  Decode_Update(IN const unsigned char* pcuchInput, IN int nLenOfInput,
							OUT unsigned char* puchOutput);
		int  Decode_Final(OUT unsigned char* puchOutput);
	private:
		EVP_ENCODE_CTX __cm_sCtx;
		bool		   __cm_bIsChangeable = true;
		bool		   __cm_bIsNeedInit;
		bool		   __cm_bIsFinalable;
};
}






inline 
Openssl_evp::CBase64::CBase64(void)
	: __cm_bIsChangeable(true)
	, __cm_bIsNeedInit(false)
	, __cm_bIsFinalable(false)
{
	Encode_Init();
}


inline
Openssl_evp::CBase64::~CBase64(void)
{
}

int 
Openssl_evp::CBase64::Encode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput,IN int nLenOfOutput, 
					IN bool bIsStart, IN bool bIsEnd)
{
	//判断缓冲区大小
	if( nLenOfInput % 3 == 0 && nLenOfOutput < nLenOfInput / 3 * 4)
	{
		throw std::invalid_argument("输出缓冲区太小");
	}
	else if (nLenOfInput % 3 != 0 && nLenOfInput < nLenOfInput / 3 *4 + 4)
	{
		throw std::invalid_argument("输出缓冲区太小");
	}
	//判断是否可开始新的任务
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		Encode_Init();
	}
	
	int nLength = 0;
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		return  Encode_Final(puchOutput);
	}
	else if (nLenOfInput ==0 && bIsEnd == false)
	{
		throw std::runtime_error("没有传入数据");
	}
	
	nLength = Encode_Update(pcuchInput, nLenOfInput, puchOutput);
	
	if (bIsEnd == true)
	{
		nLength += Encode_Final(puchOutput);
	}
	return nLength;
}

	
	
Openssl_evp::vector<unsigned char> 
Openssl_evp::CBase64::Encode(IN const vector<unsigned char>& vecInput,
									 IN bool bIsStart, IN bool bIsEnd)
{
	//判断是否可开始新的任务
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		Encode_Init();
	}
	vector<unsigned char> vecTemp(vecInput.size() / 3 * 4 , 0);
	if (vecInput.size() % 3 != 0)
	{
		 vecTemp.resize(vecInput.size() / 3 * 4 + 4 , 0);
	}
	if (vecInput.size() == 0 && bIsEnd == true)
	{
		Encode_Final(vecTemp.data());
		return vecTemp;
	}
	else if (vecTemp.size() == 0 && bIsEnd == false)
	{
		throw std::runtime_error("没有传入数据");
	}
	
	Encode_Update(vecInput.data(), vecInput.size(), vecTemp.data());
	
	if (bIsEnd == true)
	{
		Encode_Final(vecTemp.data());
		return vecTemp;
	}
	return vecTemp;


}

Openssl_evp::vector<unsigned char> 
Openssl_evp::CBase64::Decode(IN const vector<unsigned char>& vecInput,
									 IN bool bIsStart, IN bool bIsEnd)
{
	//判断是否可开始新的任务
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		Decode_Init();
	}
	
	vector<unsigned char> vecTemp(vecInput.size() / 4 * 3,  0);
	if (vecInput[vecInput.size() - 1] == '=' )
	{
		vecTemp.resize(vecInput.size() / 4 * 3 - 1 );
	}
	if (vecInput[vecInput.size() - 2] == '=')
	{
		vecTemp.resize(vecInput.size() / 4 * 3 - 2 );
	}
	
	if (vecInput.size() == 0 && bIsEnd == true)
	{
		Decode_Final(vecTemp.data());
		return vecTemp;
	}
	else if (vecTemp.size() == 0 && bIsEnd == false)
	{
		throw std::runtime_error("没有传入数据");
	}
	
	Decode_Update(vecInput.data(), vecInput.size(), vecTemp.data());
	
	if (bIsEnd == true)
	{
		Decode_Final(vecTemp.data());
		return vecTemp;
	}
	return vecTemp;


}

	
	
	
	
	
	
int 
Openssl_evp::CBase64::Decode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput,IN int nLenOfOutput, 
					IN bool bIsStart, IN bool bIsEnd)
{
	//判断缓冲区大小
	if( nLenOfInput % 3 == 0 && nLenOfOutput < nLenOfInput / 3 * 4)
	{
		throw std::invalid_argument("输出缓冲区太小");
	}
	else if (nLenOfInput % 3 != 0 && nLenOfInput < nLenOfInput / 3 *4 + 3)
	{
		throw std::invalid_argument("输出缓冲区太小");
	}
	//判断是否可开始新的任务
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一次数据还未处理完成");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		Decode_Init();
	}
	
	int nLength = 0;
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		return  Decode_Final(puchOutput);
	}
	else if (nLenOfInput ==0 && bIsEnd == false)
	{
		throw std::runtime_error("没有传入数据");
	}
	
	nLength = Encode_Update(pcuchInput, nLenOfInput, puchOutput);
	
	if (bIsEnd == true)
	{
		nLength += Decode_Final(puchOutput);
	}
	return nLength;
}




void Openssl_evp::CBase64::Encode_Init(void)
{
	::EVP_EncodeInit(&__cm_sCtx);
	__cm_bIsNeedInit = false;
}

int
Openssl_evp::CBase64::Encode_Update(IN const unsigned char* pcuchInput, IN int nLenOfInput,
							OUT unsigned char* puchOutput)
{
	int nLength = 0;
	__cm_bIsChangeable = false;
	::EVP_EncodeUpdate(&__cm_sCtx, puchOutput, &nLength, pcuchInput, nLenOfInput);
	__cm_bIsFinalable = true;
	return nLength;
}

int 
Openssl_evp::CBase64::Encode_Final(OUT  unsigned char* puchOutput)
{
	int nLength = 0;
	if (__cm_bIsFinalable == true)
	{
		::EVP_EncodeFinal(&__cm_sCtx, puchOutput, &nLength);
		__cm_bIsFinalable = false;
		__cm_bIsChangeable = true;
		return nLength;
	}
	else 
	{
		throw std::logic_error("未调用update，不能使用final");
	}
}

void Openssl_evp::CBase64::Decode_Init(void)
{
	::EVP_DecodeInit(&__cm_sCtx);
	__cm_bIsNeedInit = false;
}

int
Openssl_evp::CBase64::Decode_Update(IN const unsigned char* pcuchInput, IN int nLenOfInput,
							OUT unsigned char* puchOutput)
{
	int nLength = 0;
	__cm_bIsChangeable = false;
	::EVP_DecodeUpdate(&__cm_sCtx, puchOutput, &nLength, pcuchInput, nLenOfInput);
	__cm_bIsFinalable = true;
	return nLength;
}

int 
Openssl_evp::CBase64::Decode_Final(OUT  unsigned char* puchOutput)
{
	int nLength = 0;
	if (__cm_bIsFinalable == true)
	{
		::EVP_DecodeFinal(&__cm_sCtx, puchOutput, &nLength);
		__cm_bIsFinalable = false;
		__cm_bIsChangeable = true;
		return nLength;
	}
	else 
	{
		throw std::logic_error("未调用update，不能使用final");
	}
}


#endif
