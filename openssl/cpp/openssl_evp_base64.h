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

/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
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
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
namespace Openssl_evp
{

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
					OUT unsigned char* puchOutput, IN bool bIsEnd);
		int Decode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput, IN bool bIsEnd);

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
};
}
#endif /* end of include guard: __MY_OPENSSL_EVP */






inline 
Openssl_evp::CBase64::CBase64(void)
	: __cm_bIsEncode(true)
{
	Encode_Init();
}


inline
Openssl_evp::CBase64::~CBase64(void)
{
}

void Openssl_evp::CBase64::Encode_Init(void)
{
	::EVP_EncodeInit(&__cm_sCtx);
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


void
Openssl_evp::CBase64::Change(bool bIsEncode)
{
	__cm_bIsEncode = bIsEncode;
	if(__cm_bIsEncode == true)
	{
		Encode_Init();
	}
	else
	{
		Decode_Init();
	}
}

int 
Openssl_evp::CBase64::Encode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput, IN bool bIsEnd)
{
	int nLength = 0;
	nLength = Encode_Update(pcuchInput, nLenOfInput, puchOutput);
	if (bIsEnd == true)
	{
		nLength += Encode_Final(puchOutput);
		Encode_Init();
	}
	return nLength;
}

	
int 
Openssl_evp::CBase64::Decode(IN const unsigned char* pcuchInput, IN int nLenOfInput,
					OUT unsigned char* puchOutput, IN bool bIsEnd)

{
	int nLength = 0;
	nLength = Decode_Update(pcuchInput, nLenOfInput, puchOutput);
	if (bIsEnd == true)
	{
		nLength += Encode_Final(puchOutput);
		Decode_Init();
	}
	return nLength;
}

