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
		bool		   __cm_bIsEncode = true;
		bool		   __cm_bIsChangeable = true;
		bool		   __cm_bIsNeedInit;
		bool		   __cm_bIsFinalable;
};
}






inline 
Openssl_evp::CBase64::CBase64(void)
	: __cm_bIsEncode(true)
	, __cm_bIsChangeable(true)
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
	if (nLenOfOutput < nLenOfInput * 4 / 3 + 3)
	{
		throw std::invalid_argument("输出缓冲区太小");
	}

	int nLength = 0;
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		nLength += Encode_Final(puchOutput);
		Encode_Init();
		__cm_bIsChangeable = true;
		return nLength;
	}
	else if (nLenOfInput ==0 && bIsEnd == false)
	{
		throw std::runtime_error("没有传入数据");
	}

	if (__cm_bIsEncode == false && __cm_bIsChangeable == true)
	{
		Encode_Init();
		__cm_bIsEncode = true;
	}
	else if( __cm_bIsEncode == false && __cm_bIsChangeable == false )
	{
		throw std::logic_error("上次解码还未完成");
	}
	__cm_bIsChangeable = false;
	nLength = Encode_Update(pcuchInput, nLenOfInput, puchOutput);
	if (bIsEnd == true)
	{
		nLength += Encode_Final(puchOutput);
		Encode_Init();
		__cm_bIsChangeable = true;
	}
	return nLength;
}


int 
Openssl_evp::CBase64::Decode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput, IN int nLenOfOutput,IN bool bIsEnd)

{
	if (nLenOfOutput < nLenOfInput * 3 / 4 )
	{
		throw std::invalid_argument("输出缓冲区太小");
	}

	int nLength = 0;
	if (nLenOfInput == 0 && bIsEnd == true)
	{
		nLength += Decode_Final(puchOutput);
		Decode_Init();
		__cm_bIsChangeable = true;
		return nLength;
	}
	else if (nLenOfInput == 0 && bIsEnd == false)
	{
		throw std::runtime_error("没有传入数据");
	}
	if (__cm_bIsEncode == true && __cm_bIsChangeable == true)
	{
		Decode_Init();
		__cm_bIsEncode = true;
	}
	else if( __cm_bIsEncode == false && __cm_bIsChangeable == false )
	{
		throw std::logic_error("上次编码还未完成");
	}

	__cm_bIsChangeable = false;
	nLength = Decode_Update(pcuchInput, nLenOfInput, puchOutput);
	if (bIsEnd == true)
	{
		nLength += Decode_Final(puchOutput);
		Decode_Init();
		__cm_bIsChangeable = true;
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
	::EVP_EncodeUpdate(&__cm_sCtx, puchOutput, &nLength, pcuchInput, nLenOfInput);
	return nLength;
}

int 
Openssl_evp::CBase64::Encode_Final(OUT  unsigned char* puchOutput)
{
	int nLength = 0;
	::EVP_EncodeFinal(&__cm_sCtx, puchOutput, &nLength);
	return nLength;
}

void Openssl_evp::CBase64::Decode_Init(void)
{
	::EVP_DecodeInit(&__cm_sCtx);
}

int
Openssl_evp::CBase64::Decode_Update(IN const unsigned char* pcuchInput, IN int nLenOfInput,
							OUT unsigned char* puchOutput)
{
	int nLength = 0;
	::EVP_DecodeUpdate(&__cm_sCtx, puchOutput, &nLength, pcuchInput, nLenOfInput);
	return nLength;
}

int 
Openssl_evp::CBase64::Decode_Final(OUT  unsigned char* puchOutput)
{
	int nLength = 0;
	::EVP_DecodeFinal(&__cm_sCtx, puchOutput, &nLength);
	return nLength;
}

