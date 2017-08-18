/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_cipher.cpp
Related Files  : no
File Function  : 加密，解密
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




#ifndef __MY_OPENSSL_EVP_CIPHER_H
#define __MY_OPENSSL_EVP_CIPHER_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef __MY_OPENSSL_ERROR
#define __MY_OPENSSL_ERROR
#endif



#include<openssl/err.h>
#include<openssl/evp.h>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<exception>
#include<vector>
#include"openssl_evp_loadconf.h"


namespace Openssl_evp
{
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


/*!@Class
********************************************************************************
Class Name     : CCipher
Function       : encry and decry according __cm_nIsEncry
Exception Class: no
--------------------------------------------------------------------------------
Note           : pnLenOfOutput must equal to the size of puchOutput,
				 forbidden copy and assign （include move semantics）
Typical Usage  : CCipher ciper("aes-128-cbc", nullptr, pKey,piv,1);
				 unsigned char* in = "dasda";
				 int inlen = 5,outlen;
				 unsigned char* out = inlen + EVP_MAX_BLOCK_LENGTH  
				 int out = ciper.Cipher(in,inlen,out,false);
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
class CCipher
{
	public:
		CCipher(IN const string strCipherName, IN const unsigned char* pcuchKey, 
				IN const unsigned char* pcuchInitVec, IN ENGINE* psImpl = nullptr);
		CCipher(IN const string strCipherName, IN const vector<unsigned char>&  vecKey, 
				IN const vector<unsigned char>& vecInitVec, IN ENGINE* psImpl = nullptr);
		
		~CCipher(void) noexcept;
		
		CCipher(IN const CCipher & lref) = delete; //不可拷贝
		CCipher(IN CCipher && rref) = delete; //不可赋值
		CCipher& operator = (IN const CCipher & lref) = delete; //不可移动拷贝
		CCipher& operator = (IN CCipher && rref) = delete; //不可移动赋值
	public:
		int Encry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			      OUT unsigned char* puchOutput,IN bool bIsStart,  IN bool IsEnd);   

		int Decry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN bool bIsStart, IN bool IsEnd); 
		
		int Encry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput,IN int nLenofoutput, IN bool bIsStart, IN bool IsEnd); 
		
		int Decry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN int nLenOfOutput,IN bool bIsStart, IN bool IsEnd);   
		
		vector<unsigned char> Encry(IN const vector<unsigned char>& vecInput,
									IN bool bIsStart,  IN bool IsEnd);
		
		vector<unsigned char> Decry(IN const vector<unsigned char>& vecInput,
									IN bool bIsStart,  IN bool IsEnd);
	
	private:
		int Cipher(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN bool bIsStart, IN bool bIsEnd);  
	public:
		void Change(IN const string strCipherName = "", 
					IN const unsigned char* pcuchKey = nullptr, 
					IN const unsigned char* pcuchInitVec = nullptr,
					IN ENGINE* psImpl = nullptr);
	private:
		void Init(void); //包括CTX初始化和cipher初始化
		int  Final(OUT unsigned char* puchOutput);
		int  Update(IN const unsigned char* pcuchInput, 
				   IN int nLenOfInput, 
				   OUT unsigned char* puchOutput);
	private:
		void GetEVP_CIPHER(IN const string& strCipherName);
	private:
		EVP_CIPHER_CTX       __cm_sCtx;
		IN ENGINE*           __cm_psImpl;
		const unsigned char* __cm_pcuchKey;
		const unsigned char* __cm_pcuchInitVec;
		const EVP_CIPHER*    __cm_psCipher;

		bool                 __cm_bIsEncry; //是否是加密
		bool				 __cm_bIsNeedInit;//是够需要初始化
		bool				 __cm_bIsChangeable;//是否可以改变参数
		bool				 __cm_bIsFinalable;//是否可以调用final函数
		
		int          		 __cm_nError;
		char                 __cm_pchErrorInfo[1024] = {0}; //C++11新特性只有静态非常量才需要在类外初始化
};
}


//class CCipher
inline
Openssl_evp::CCipher::CCipher(IN const string strCipherName, IN const unsigned char* pcuchKey, 
							  IN const unsigned char* pcuchInitVec, IN ENGINE* psImpl /*=nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_pcuchInitVec(pcuchInitVec)
	, __cm_bIsEncry(true) //初始设置为加密
	, __cm_bIsNeedInit(false) //不需初始化,因为构造时已经初始化了
	, __cm_bIsChangeable(true) //可以改变参数，构造的时候是加密，可以构造后立刻解密
	, __cm_bIsFinalable(false)//不可调用Final函数，初始时未调用update，不可调用Final
{
	GetEVP_CIPHER(strCipherName);//获取算法名字
	Init(); 
}

Openssl_evp::CCipher::CCipher(IN const string strCipherName, IN const vector<unsigned char>&  vecKey, 
				IN const vector<unsigned char>& vecInitVec, IN ENGINE* psImpl /*= nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(vecKey.data())
	, __cm_pcuchInitVec(vecInitVec.data())
	, __cm_bIsEncry(true) //初始设置为加密
	, __cm_bIsNeedInit(false) //不需初始化
	, __cm_bIsChangeable(true) //可以改变参数
	, __cm_bIsFinalable(false)//不可调用Final函数
{
	GetEVP_CIPHER(strCipherName);//获取算法名字
	Init(); 
}
inline
Openssl_evp::CCipher::~CCipher(void) noexcept
{
	::EVP_CIPHER_CTX_cleanup(&__cm_sCtx);
}






int 
Openssl_evp::CCipher::Encry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN bool bIsStart, IN bool IsEnd/* = false*/)     //标志位标记是否是最后一次数据
{
	if (__cm_bIsEncry == false && __cm_bIsChangeable == true)
	{
		__cm_bIsEncry = true;
	}
	else if (__cm_bIsEncry == false  && __cm_bIsChangeable == false)
	{
		throw std::logic_error("加密还未完成");
	}
	return Cipher(pcuchInput, nLenOfInput, puchOutput,bIsStart,  IsEnd);
}

Openssl_evp::vector<unsigned char> 
Openssl_evp::CCipher::Encry(IN const vector<unsigned char>& vecInput, IN bool bIsStart, IN bool IsEnd /*= false*/)
{
	if (__cm_bIsEncry == false && __cm_bIsChangeable == true)
	{
		__cm_bIsEncry = true;
	}
	else if (__cm_bIsEncry == false  && __cm_bIsChangeable == false)
	{
		throw std::logic_error("加密还未完成");
	}
	vector<unsigned char> vecTemp(vecInput);
	vecTemp.clear();
	Cipher(vecInput.data(), vecInput.size(), vecTemp.data(), bIsStart, IsEnd);
	return vecTemp;
}



int 
Openssl_evp::CCipher::Encry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN int nLenOfOutput,IN bool bIsStart,  IN bool IsEnd/* = false*/)     //标志位标记是否是最后一次数据
{
	if ( nLenOfOutput < nLenOfInput )
	{
		throw std::invalid_argument("输出缓冲区太小");
	}
	if (__cm_bIsEncry == false && __cm_bIsChangeable == true)
	{
		__cm_bIsEncry = true;
	}
	else if (__cm_bIsEncry == false  && __cm_bIsChangeable == false)
	{
		throw std::logic_error("加密还未完成");
	}
	return Cipher(pcuchInput, nLenOfInput, puchOutput,bIsStart, IsEnd);
}

int 
Openssl_evp::CCipher::Decry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput,IN bool bIsStart,  IN bool IsEnd )     //标志位标记是否是最后一次数据
{
	if (__cm_bIsEncry == true && __cm_bIsChangeable == true)
	{
		__cm_bIsEncry = false;
	}
	else if (__cm_bIsEncry == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("加密还未完成");
	}
	return Cipher(pcuchInput, nLenOfInput, puchOutput, bIsStart, IsEnd);
}

int 
Openssl_evp::CCipher::Decry(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput,IN int nLenOfOutput, IN bool bIsStart, IN bool IsEnd )     //标志位标记是否是最后一次数据
{
	if ( nLenOfOutput < nLenOfInput )
	{
		throw std::invalid_argument("输出缓冲区");
	}
	if (__cm_bIsEncry == true && __cm_bIsChangeable == true)
	{
		__cm_bIsEncry = false;
	}
	else if (__cm_bIsEncry == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("加密还未完成");
	}
	return Cipher(pcuchInput, nLenOfInput, puchOutput, bIsStart, IsEnd);
}

Openssl_evp::vector<unsigned char>
Openssl_evp::CCipher::Decry(IN const vector<unsigned char>& vecInput, IN bool bIsStart, IN bool IsEnd)
{
	if (__cm_bIsEncry == true && __cm_bIsChangeable == true)
	{
		__cm_bIsEncry = false;
	}
	else if (__cm_bIsEncry == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("加密还未完成");
	}
	vector<unsigned char> vecTemp(vecInput);
	vecTemp.clear();
	Cipher(vecInput.data(), vecInput.size(), vecTemp.data(), bIsStart, IsEnd);
	return vecTemp;
}

void
Openssl_evp::CCipher::Change(IN const string strCipherName /*=""*/, 
		                     IN const unsigned char* pcuchKey /*=nulptr8*/, 
							 IN const unsigned char* pcuchInitVec /*=nullptr*/, 
							 IN ENGINE* psImpl /*=nullptr*/)
{
	if (__cm_bIsChangeable == true)
	{
		if (!strCipherName.empty() )
		{
			GetEVP_CIPHER(strCipherName);
			__cm_bIsNeedInit = true;
		}
		if (pcuchKey != nullptr)
		{
			__cm_pcuchKey = pcuchKey;
			__cm_bIsNeedInit = true;
		}
		if (pcuchInitVec != nullptr)
		{
			__cm_pcuchInitVec = pcuchInitVec;
			__cm_bIsNeedInit = true;
		}
		if (psImpl != nullptr)
		{
			__cm_psImpl = psImpl;
			__cm_bIsNeedInit = true;
		}
		if(__cm_bIsNeedInit == true)
		{
			Init();
		}
	}
	else
	{
		throw std::logic_error("上次任务还未完成不可更改参数");
	}
}

void
Openssl_evp::CCipher::Init()
{
	::EVP_CIPHER_CTX_init(&__cm_sCtx);
	if (!::EVP_CipherInit_ex(&__cm_sCtx, __cm_psCipher, __cm_psImpl,
		__cm_pcuchKey, __cm_pcuchInitVec, __cm_bIsEncry))
	{
		__cm_nError = ::ERR_get_error();
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw (std::runtime_error(__cm_pchErrorInfo));
	}
	__cm_bIsNeedInit = false;
}


int 
Openssl_evp::CCipher::Update(IN const unsigned char* pcuchInput, 
							 IN int nLenOfInput, OUT unsigned char* puchOutput)
{
	int nLength = 0;
	__cm_bIsChangeable = false; //调用了update之后不可更改参数
	if (!::EVP_CipherUpdate(&__cm_sCtx, puchOutput, &nLength, 
							pcuchInput, nLenOfInput))
	{
		__cm_nError = 0;
		__cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw (std::runtime_error(__cm_pchErrorInfo));
	}
	__cm_bIsFinalable = true; //调用了update之后，可以调用Final
	return nLength;
} 

void
Openssl_evp::CCipher::GetEVP_CIPHER(IN const string& strCipherName)
{
	__cm_psCipher = ::EVP_get_cipherbyname(strCipherName.c_str());
	if (__cm_psCipher == nullptr)
	{
		throw(std::invalid_argument("不支持此算法"));
	}
}

int 
Openssl_evp::CCipher::Final(OUT unsigned char* puchOutput)
{
	int nLength = 0;
	if(__cm_bIsFinalable == false)
	{
		throw std::logic_error("没有调用过update");
	}
	else
	{
		if (!::EVP_CipherFinal_ex(&__cm_sCtx, puchOutput, &nLength))
		{
			 __cm_nError = ::ERR_get_error();
			::bzero(__cm_pchErrorInfo,1024);
			::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
			throw (std::runtime_error(__cm_pchErrorInfo));
		}
		__cm_bIsChangeable = true;//调用final后，可以更改参数
		__cm_bIsFinalable = false;//调用final后，没有调用Update之前，不可调用final
		return nLength;
	}
}

int 
Openssl_evp::CCipher::Cipher(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
							 OUT unsigned char* puchOutput, 
							 IN bool bIsStart,  IN bool bIsEnd)
{
	int nLength = 0;                         // the length of output data
	if (bIsStart == true && __cm_bIsChangeable == false)
	{
		throw std::logic_error("上一个任务还未完成，不可以开始");
	}
	else if (bIsStart == true && __cm_bIsChangeable == true)
	{
		Init();
	}

	if(nLenOfInput == 0 && bIsEnd == true)
	{
		nLength += Final(puchOutput + nLength);
		return nLength;
	}
	else if (nLenOfInput == 0 && bIsEnd == false )
	{
		throw std::invalid_argument("非法参数");
	}

	nLength = Update(pcuchInput, nLenOfInput, puchOutput);
	
	if (bIsEnd == true ) // if the data is last,then call final
	{
		nLength += Final(puchOutput + nLength);
		return nLength;
	}
	return nLength;
}

#endif
