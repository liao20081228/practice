/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_getopt_writor.h
Related Files  : no
File Function  : base64编解码
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
#ifndef _MY_OPENSSL_EVP_GETOPT_WRITOR_H
#define _MY_OPENSSL_EVP_GETOPT_WRITOR_H
#ifndef IN
#define IN
#endif /* end of include guard: IN */
#ifndef OUT
#define OUT
#endif /* end of include guard: OUT */
#ifndef _MY_OPENSSL_ERROR
#define _MY_OPENSSL_ERROR
#endif /* end of include guard: _MY_OPENSSL_ERROR */

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<assert.h>
#include<array>
#include"openssl_evp_base64.h"
#include"openssl_evp_conversion.h"
using std::cout;
using std::cin;
using std::endl;
using std::array;
namespace Openssl_evp
{

class CWritor
{
	public:
		CWritor(IN const string strOutputFile = "", IN const string strFormat = "BINARY");
		~CWritor(void);
	public:
		void Output(IN const unsigned char* pchdata, IN int nLen, IN bool bIsEnd = false);
		void Change(IN const string strOutputFile, IN const string strFormat = "BINARY");
	private:
		CBase64 __cm_cBase64;
		CConversion __cm_cConversion;
		string __cm_strFormat;
		int __cm_nFdOutput;
};

}
#endif


inline
Openssl_evp::CWritor::CWritor(IN const string strOutputFile, IN const string strFormat)
	: __cm_cBase64()
	, __cm_cConversion()
	, __cm_strFormat(strFormat)
{
	if (strOutputFile.empty())
	{
		__cm_nFdOutput = 1;
	}
	else
	{
		__cm_nFdOutput = ::open(strOutputFile.c_str(), O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, 0644);
		if (__cm_nFdOutput == -1)
		{
			throw std::runtime_error("文件打开出错");
		}
	}
}


void
Openssl_evp::CWritor::Change(IN const string strOutputFile, IN const string strFormat)
{
	__cm_strFormat = strFormat;
	if (__cm_nFdOutput != 1)
	{
		::close(__cm_nFdOutput);
	}
	if (strOutputFile.empty())
	{
		__cm_nFdOutput = 1;
	}
	else
	{
		__cm_nFdOutput = ::open(strOutputFile.c_str(), O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, 0644);
		if (__cm_nFdOutput == -1)
		{
			throw std::runtime_error("文件打开出错");
		}
	}
}

void 
Openssl_evp::CWritor::Output(IN const unsigned char* pchdata, IN int nLen, bool bIsEnd )
{
	if (__cm_strFormat.compare("BINARY") == 0)
	{
		::write(__cm_nFdOutput, pchdata, nLen);
		if (bIsEnd == true && __cm_nFdOutput != 1)
		{
			::close(__cm_nFdOutput);
		}
	}

	if (__cm_strFormat.compare("BASE64") == 0)
	{
		char temp[nLen*2];
		int tempLen = __cm_cBase64.Encode(pchdata, nLen, reinterpret_cast<unsigned char*>(temp), bIsEnd);
		::write(__cm_nFdOutput, temp, tempLen);
		if (bIsEnd == true && __cm_nFdOutput != 1)
		{
			::close(__cm_nFdOutput);
		}
	}
		
	if (__cm_strFormat.compare("HEX") == 0)
	{
		string temp  = __cm_cConversion.DataToStr(pchdata, nLen, 16);
		::write(__cm_nFdOutput, temp.c_str(), temp.length());
		if (bIsEnd == true && __cm_nFdOutput != 1)
		{
			::close(__cm_nFdOutput);
		}
	}
}



