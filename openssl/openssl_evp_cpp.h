/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_cpp.cpp
Related Files  : no
File Function  : 加密，解密，摘要，签名，认证，写信，读写
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
#ifndef __MY_OPENSSL_EVP_CPP_H
#define __MY_OPENSSL_EVP_CPP_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif


#include<openssl/err.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include"unistd.h"
#include<cstring>
#include<fcntl.h>
#include<cstdlib>
#include<cstdio>
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
		CCipher(IN const char* pcchCipherName, IN const unsigned char* pcuchKey, 
				IN const unsigned char* pcuchInitVec, IN int nIsEncry = 1, 
				IN ENGINE* psImpl = nullptr);
		~CCipher(void) noexcept;
		
		CCipher(IN const CCipher & lref) = delete; //不可拷贝
		CCipher(IN CCipher && rref) = delete; //不可赋值
		CCipher& operator = (IN const CCipher & lref) = delete; //不可移动拷贝
		CCipher& operator = (IN CCipher && rref) = delete; //不可移动赋值
	public:
		int Cipher(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN bool bIsEnd);     //标志位标记是否是最后一次数据
	public:
		void Change(IN const char* pcchCipherName = nullptr, 
					IN const unsigned char* pcuchKey = nullptr, 
					IN const unsigned char* pcuchInitVec = nullptr, IN int nIsEncry = 1, 
					IN ENGINE* psImpl = nullptr);
	private:
		void Init(void); //包括CTX初始化和cipher初始化
		int Final(OUT unsigned char* puchOutput);
		int Update(IN const unsigned char* pcuchInput, 
				   IN int nLenOfInput, 
				   OUT unsigned char* puchOutput);
	private:
		void GetEVP_CIPHER(IN const char* pcchCipherName);
	private:
		EVP_CIPHER_CTX       __cm_sCtx;
		IN ENGINE*           __cm_psImpl;
		const unsigned char* __cm_pcuchKey;
		const unsigned char* __cm_pcuchInitVec;
		const EVP_CIPHER*    __cm_psCipher;
		int                  __cm_nIsEncry;
		int          		 __cm_nError;
		char                 __cm_pchErrorInfo[1024] = {0}; //C++11新特性只有静态非常量才需要在类外初始化
};

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
		CDigestAndHmac(IN const char* pcchDigestName,IN ENGINE* psImpl = nullptr,
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


		void Change(IN const char* pcchDigestName = nullptr, IN ENGINE* psImpl = nullptr,
					IN const unsigned char* pcuchKey = nullptr, IN int nLenOfKey = 0);
	private:
		void MDInit(void);//ctx初始化和degist初始化
		void MDUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  MDFinal(OUT unsigned char* puchOutput);
		
		void HMACInit();//ctx初始化和haac初始化
		void HMACUpdate(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		int  HMACFinal(OUT unsigned char* puchOutput);
	private:
		void GetEVP_MD(IN const char* pcchDigestName);
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

		void Change(bool bIsEncode);
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



class CConversion
{
	public:
		string DataToStr(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN int nBase);
		vector<unsigned char> StrToData(IN const  char* pcuchInput, IN int nLenOfInput, IN int nBase);

	private:
		 string DataToHexStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 string DataToDecStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 string DataToBinStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 string DataToOctStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  HexStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  DecStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  BinStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  OctStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
	private:
		 string __cm_strResult;
		 vector<unsigned char> __cm_veData;
};

}
#endif /* end of include guard: __MY_OPENSSL_EVP */

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
		::ERR_load_crypto_strings();
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

//class CCipher
inline
Openssl_evp::CCipher::CCipher(IN const char* pcchCipherName, IN const unsigned char* pcuchKey, 
							  IN const unsigned char* pcuchInitVec, IN int nIsEncry /* =1 */
				                                    , IN ENGINE* psImpl /*=nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_pcuchInitVec(pcuchInitVec)
	, __cm_nIsEncry(nIsEncry)
{
	GetEVP_CIPHER(pcchCipherName);//获取算法名字
	Init();
}

inline
Openssl_evp::CCipher::~CCipher(void) noexcept
{
	::EVP_CIPHER_CTX_cleanup(&__cm_sCtx);
}


int 
Openssl_evp::CCipher::Cipher(IN const unsigned char* pcuchInput, 
		                     IN int nLenOfInput, OUT unsigned char* puchOutput, 
							 IN bool bIsEnd)
{
	int nLength = 0,                         // the length of output data
		nTempLen = 0;                       
	nLength = Update(pcuchInput, nLenOfInput, puchOutput);
	if (bIsEnd == true) // if the data is last,then call final
	{
		nTempLen = Final(puchOutput + nLength);
		nLength += nTempLen;
		Init();
	}
	return nLength;
}

void
Openssl_evp::CCipher::GetEVP_CIPHER(IN const char* pcchCipherName)
{
	__cm_psCipher = ::EVP_get_cipherbyname(pcchCipherName);
	if (__cm_psCipher == nullptr)
	{
		throw(std::invalid_argument("不支持此算法"));
	}
}

void
Openssl_evp::CCipher::Init()
{
	::EVP_CIPHER_CTX_init(&__cm_sCtx);
	if (!::EVP_CipherInit_ex(&__cm_sCtx, __cm_psCipher, __cm_psImpl,
		__cm_pcuchKey, __cm_pcuchInitVec, __cm_nIsEncry))
	{
		__cm_nError = ::ERR_get_error();
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw (std::runtime_error(__cm_pchErrorInfo));
	}
}


int 
Openssl_evp::CCipher::Update(IN const unsigned char* pcuchInput, 
							 IN int nLenOfInput, OUT unsigned char* puchOutput)
{
	int nLength = 0;
	if (!::EVP_CipherUpdate(&__cm_sCtx, puchOutput, &nLength, 
							pcuchInput, nLenOfInput))
	{
		__cm_nError = 0;
		__cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw (std::runtime_error(__cm_pchErrorInfo));
	}
	return nLength;
} 

int 
Openssl_evp::CCipher::Final(OUT unsigned char* puchOutput)
{
	int nLength = 0;
	if (!::EVP_CipherFinal_ex(&__cm_sCtx, puchOutput, &nLength))
	{
		 __cm_nError = ::ERR_get_error();
		::bzero(__cm_pchErrorInfo,1024);
		::ERR_error_string(__cm_nError, __cm_pchErrorInfo);
		throw (std::runtime_error(__cm_pchErrorInfo));
	}
	return nLength;
}

void
Openssl_evp::CCipher::Change(IN const char* pcchCipherName, 
		                     IN const unsigned char* pcuchKey, 
							 IN const unsigned char* pcuchInitVec, 
							 IN int nIsEncry /*=1*/, IN ENGINE* psImpl /*=nullptr*/)
{
	if (pcchCipherName != nullptr)
	{
		GetEVP_CIPHER(pcchCipherName);
	}
	if (pcuchKey != nullptr)
	{
		__cm_pcuchKey = pcuchKey;
	}
	if (pcuchInitVec != nullptr)
	{
		__cm_pcuchInitVec = pcuchInitVec;
	}
	__cm_nIsEncry = nIsEncry;
	if (psImpl != nullptr)
	{
		__cm_psImpl = psImpl;
	}
	Init();
}


//CDigestAndHmac
Openssl_evp::CDigestAndHmac::CDigestAndHmac(IN const char* pcchDigestName,
							  IN ENGINE* psImpl /* = nullptr*/,
		                      IN const unsigned char* pcuchKey /*=nullptr*/,
							  IN int nLenOfKey/*=0*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_nLenOfKey(nLenOfKey)
{
	GetEVP_MD(pcchDigestName);
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
Openssl_evp::CDigestAndHmac::GetEVP_MD(IN const char* pcchDigestName)
{
	__cm_psMD = ::EVP_get_digestbyname(pcchDigestName);
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
Openssl_evp::CDigestAndHmac::Change(IN const char* pcchDigestName /*=nullptr*/,
		                     IN ENGINE* psImpl /*= nullptr*/,
							 IN const unsigned char* pcuchKey /*= nullpt*/, 
							 IN int nLenOfKey /*= 0*/)
{
	if (pcchDigestName!= nullptr)
	{
		 GetEVP_MD(pcchDigestName);
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
	}
	return nLength;
}


string
Openssl_evp::CConversion::DataToHexStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char hex[17]="0123456789abcdef";
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		__cm_strResult.push_back(hex[pcuchInput[i] >> 4 & 0xf]);
		__cm_strResult.push_back(hex[pcuchInput[i]  & 0xf]);
	}
	return __cm_strResult;
}

string
Openssl_evp::CConversion::DataToDecStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		if (pcuchInput[i] < 10)
		{
			__cm_strResult.append("00");
			__cm_strResult.append(std::to_string(pcuchInput[i]));
		}
		else if (pcuchInput[i] < 99)
		{
			__cm_strResult.append("0");
			__cm_strResult.append(std::to_string(pcuchInput[i]));
		}
		else
		{
			__cm_strResult.append(std::to_string(pcuchInput[i]));
		}
	}
	return __cm_strResult;
}

string
Openssl_evp::CConversion::DataToOctStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char oct[9]="01234567";
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		__cm_strResult.push_back(oct[pcuchInput[i] >> 6 & 0x3]);
		__cm_strResult.push_back(oct[pcuchInput[i] >> 3 & 0x7]);
		__cm_strResult.push_back(oct[pcuchInput[i]   & 0x7]);
	}
	return __cm_strResult;

}

string
Openssl_evp::CConversion::DataToBinStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char bin[3]="01";
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			__cm_strResult.push_back(bin[pcuchInput[i] >> (7-i) & 0x1]);
		}
	}
	return __cm_strResult;
}



vector<unsigned char> 
Openssl_evp::CConversion::HexStrToData(IN const  char* pcuchInput, IN int nLenOfInput)
{
	if ( nLenOfInput % 2 != 0 )
	{
		throw std::invalid_argument("十六进制文本长度不是2的倍数");
	}
	char temp[3] = {0};
	for (int i = 0; i < nLenOfInput; i += 2)
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		__cm_veData.push_back(std::stoi(temp, 0, 16));
	}
	return __cm_veData;
}


vector<unsigned char> 
Openssl_evp::CConversion::DecStrToData(IN const  char* pcuchInput, IN int nLenOfInput)
{
	char temp[4] = {0};
	if ( nLenOfInput % 3 != 0 )
	{
		throw std::invalid_argument("十进制文本长度不是3的倍数");
	}
	for (int i = 0; i < nLenOfInput; i += 3)
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		temp[2] = pcuchInput[i+2];
		__cm_veData.push_back(std::stoi(temp, 0, 10));
	}
	return __cm_veData;
}

vector<unsigned char> 
Openssl_evp::CConversion::OctStrToData(IN const  char* pcuchInput, IN int nLenOfInput)
{
	if ( nLenOfInput % 3 != 0 )
	{
		throw std::invalid_argument("八进制文本长度不是3的倍数");
	}
	char temp[4] = {0};
	for (int i = 0; i < nLenOfInput; i += 3)
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		temp[2] = pcuchInput[i+2];
		__cm_veData.push_back(std::stoi(temp, 0, 8));
	}
	return __cm_veData;

}


vector<unsigned char> 
Openssl_evp::CConversion::BinStrToData(IN const char* pcuchInput, IN int nLenOfInput)
{
	char temp[9] = {0};
	if ( nLenOfInput % 8 != 0 )
	{
		throw std::invalid_argument("二进制文本长度不是8的倍数");
	}
	for (int i = 0; i < nLenOfInput; i += 8)
	{
		for(int j = 0;j<8; j++)
		{
			temp[j]=pcuchInput[i+j];
		}
		__cm_veData.push_back(std::stoi(temp, 0, 2));
	}
	return __cm_veData;
}

string 
Openssl_evp::CConversion::DataToStr(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN int nBase)
{
	switch (nBase)
	{
		case 2: return DataToBinStr(pcuchInput, nLenOfInput);
		case 8: return DataToOctStr(pcuchInput, nLenOfInput);
		case 10: return DataToDecStr(pcuchInput, nLenOfInput);
		case 16: return DataToHexStr(pcuchInput, nLenOfInput);
		default:throw std::invalid_argument("输入的进制转换不支持");
	}
}
vector<unsigned char> 
Openssl_evp::CConversion::StrToData(IN const char* pcuchInput, IN int nLenOfInput, IN int nBase)
{
	switch (nBase)
	{
		case 2: return BinStrToData(pcuchInput, nLenOfInput);
		case 8: return OctStrToData(pcuchInput, nLenOfInput);
		case 10: return DecStrToData(pcuchInput, nLenOfInput);
		case 16: return HexStrToData(pcuchInput, nLenOfInput);
		default:throw std::invalid_argument("输入的进制转换不支持");
	}
}
