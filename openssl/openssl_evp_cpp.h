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
#ifndef __MY_OPENSSL_EVP
#define __MY_OPENSSL_EVP

#include<openssl/err.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include<myhead_cpp.h>
namespace Openssl_evp
{
/*!@Class
********************************************************************************
Class Name     : CCipher
Function       : encry and decry according __cm_nIsEncry
Exception Class: no
--------------------------------------------------------------------------------
Note           : pnLenOfOutput must equal to the size of puchOutput
Typical Usage  : CCipher ciper("aes-128-cbc", nullptr, pKey,piv,1);
				 unsigned char* in = "dasda";
				 int inlen = 5;
				 unsigned char* out = inlen + EVP_MAX_BLOCK_LENGTH  
				 ciper.Cipher(in,inlen,out,outlen);
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
				IN const unsigned char* pcuchInitVec, IN int nIsEncry = 1, IN ENGINE* psImpl = nullptr);
		~CCipher(void);

		CCipher(IN const CCipher & lref) = delete;
		CCipher(IN CCipher && rref) = delete;
		CCipher& operator = (IN const CCipher & lref) = delete;
		CCipher& operator = (IN CCipher && rref) = delete;
	public:
		int Cipher(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN OUT unsigned char* puchOutput, 
			  IN OUT int* pnLenOfOutput);
	private:
		EVP_CIPHER_CTX       __cm_sCtx;
		IN ENGINE*           __cm_psImpl;
		const unsigned char* __cm_pcuchKey;
		const unsigned char* __cm_pcuchInitVec;
		const EVP_CIPHER*    __cm_psCipher;
		int                  __cm_nIsEncry;
};


/*!@Class
********************************************************************************
Class Name     : CDigest
Function       : calculate message digest value
Exception Class: no
--------------------------------------------------------------------------------
Note           : pnLenOfOutput must equal to the size of puchOutput
Typical Usage  : CDigest digest("md5", nullptr, pKey,piv,1);
				 unsigned char* in = "dasda";
				 int inlen = 5;
				 unsigned char* out = inlen + EVP_MAX_BLOCK_LENGTH  
				 ciper.Cipher(in,inlen,out,outlen);
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
		CDigest(IN const char* pcchDigestName,IN ENGINE* psImpl = nullptr,
				IN const unsigned char* pcuchKey = nullptr,IN int nLenOfKey = 0);
		~CDigest(void);

		CDigest(IN const CDigest & lref) = delete;
		CDigest(IN CDigest && rref) = delete;
		CDigest& operator = (IN const CDigest & lref) = delete;
		CDigest& operator = (IN CDigest && rref) = delete;
	public:
		int Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				   IN OUT unsigned char* puchOutput, IN OUT unsigned  int* punLenOfOutput);
		int HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
				IN OUT unsigned char* puchOutput, IN OUT unsigned int* punLenOfOutput);

	private:
		EVP_MD_CTX           __cm_sMdCtx;
		ENGINE*              __cm_psImpl;
		const EVP_MD*        __cm_psMD;
		HMAC_CTX             __cm_sHmacCtx;
		const unsigned char* __cm_pcuchKey;
		int					 __cm_nLenOfKey;
};


}
#endif /* end of include guard: __MY_OPENSSL_EVP */
/*****************************************************************************80
    > File Name: openssl_evp_cpp.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月01日 星期二 15时04分46秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/

inline
Openssl_evp::CCipher::CCipher(IN const char* pcchCipherName, IN const unsigned char* pcuchKey, 
				IN const unsigned char* pcuchInitVec, IN int nIsEncry /* =1 */
				                                    , IN ENGINE* psImpl /*=nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_pcuchInitVec(pcuchInitVec)
	, __cm_nIsEncry(nIsEncry)
{
	::OpenSSL_add_all_algorithms();          //load globle configuration
	::EVP_CIPHER_CTX_init(&__cm_sCtx);
	__cm_psCipher = ::EVP_get_cipherbyname(pcchCipherName);
	if (nullptr == __cm_psCipher)
	{
		cout << "不支持算法:" << pcchCipherName << endl;
		this->~CCipher();
		std::exit(-1);
	}

}

inline
Openssl_evp::CCipher::~CCipher(void)
{
	::EVP_CIPHER_CTX_cleanup(&__cm_sCtx);
}


inline int 
Openssl_evp::CCipher::Cipher(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN OUT unsigned char* puchOutput, 
			  IN OUT int* pnLenOfOutput)
{
	::bzero(puchOutput, *pnLenOfOutput);
	*pnLenOfOutput =0;
	int nRetVal = 0,                         // the return Value of this function
		nTempLen = 0,                        // last block with padding
		nRet = 0;                            // return value of system calling 
	char pchErrorInfo[1024] = {'\0'};        //Error Information buffer
	
		/*
	 * 初始化：设置对称算法的密钥，IV，以及加解密标志位
	 * 如果使用Engine，此时会调用其实现的EVP_CIPHER->init回调函数
	 */
	if (!::EVP_CipherInit_ex(&__cm_sCtx, __cm_psCipher, __cm_psImpl, __cm_pcuchKey, __cm_pcuchInitVec, __cm_nIsEncry))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherInit_ex failed:" << pchErrorInfo << endl;
		nRetVal = -3;
		goto err;
	}

	/*
	 *对数据进行加/解密运算（如果使用Engine，此时会调用其实现的EVP_CIPHER->do_cipher回调函数）
	 *对于连续数据流，CipherUpdate一般会被调用多次
	 */
	if (!::EVP_CipherUpdate(&__cm_sCtx, puchOutput + *pnLenOfOutput, pnLenOfOutput, pcuchInput, nLenOfInput))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherUpdate failed:"<<pchErrorInfo << endl;
		nRetVal = -4;
		goto err;
	}
	/*
	 *输出最后一块数据结果（块加密时，数据将被padding到block长度的整数倍，因此会产生额外的最后一段数据）
	 *注意：如果使用Engine，此时会触发其实现的EVP_CIPHER->do_cipher，而不是EVP_CIPHER->cleanup
	 *这点上与EVP_DigestFinal/EVP_SignFinal/EVP_VerifyFinal是完全不同的
	 */
	if (!::EVP_CipherFinal_ex(&__cm_sCtx, puchOutput + *pnLenOfOutput, &nTempLen))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherFinal_ex failed:"<<pchErrorInfo << endl;
		nRetVal = -5;
		goto err;
	}
	*pnLenOfOutput += nTempLen;
	return 0;
err:
	this->~CCipher();
	std::exit(nRetVal);
}






inline
Openssl_evp::CDigest::CDigest(IN const char* pcchDigestName,
							  IN ENGINE* psImpl /* = nullptr*/,
		                      IN const unsigned char* pcuchKey /*=nullptr*/,
							  IN int nLenOfKey/*=0*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_nLenOfKey(nLenOfKey)
{
	::OpenSSL_add_all_algorithms();          //load globle configuration
	
	::EVP_MD_CTX_init(&__cm_sMdCtx);
	::HMAC_CTX_init(&__cm_sHmacCtx);
	
	__cm_psMD = ::EVP_get_digestbyname(pcchDigestName);
	if (nullptr == __cm_psMD)
	{
		cout << "不支持算法:" << pcchDigestName << endl;
		this->~CDigest();
		std::exit(-1);
	}
}

inline
Openssl_evp::CDigest::~CDigest(void)

{
	::EVP_MD_CTX_cleanup(&__cm_sMdCtx);
	::HMAC_CTX_cleanup(&__cm_sHmacCtx);
}


inline int
Openssl_evp::CDigest::Digest(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN OUT unsigned char* puchOutput, 
			  IN OUT unsigned int* pnLenOfOutput)
{
	::bzero(puchOutput, *pnLenOfOutput);
	*pnLenOfOutput =0;
	int nRetVal = 0,                         // the return Value of this function
		nRet = 0;                            // return value of system calling 
	char pchErrorInfo[1024] = {'\0'};        //Error Information buffer
	
		/*
	 * 初始化：设置对称算法的密钥，IV，以及加解密标志位
	 * 如果使用Engine，此时会调用其实现的EVP_CIPHER->init回调函数
	 */
	if (!::EVP_DigestInit_ex(&__cm_sMdCtx, __cm_psMD, __cm_psImpl))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_DigestInit_ex failed:" << pchErrorInfo << endl;
		nRetVal = -3;
		goto err;
	}

	/*
	 *对数据进行加/解密运算（如果使用Engine，此时会调用其实现的EVP_CIPHER->do_cipher回调函数）
	 *对于连续数据流，CipherUpdate一般会被调用多次
	 */
    if (!::EVP_DigestUpdate(&__cm_sMdCtx, pcuchInput, nLenOfInput))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_DigestUpdate failed:"<<pchErrorInfo << endl;
		nRetVal = -4;
		goto err;
	}
	/*
	 *输出最后一块数据结果（块加密时，数据将被padding到block长度的整数倍，因此会产生额外的最后一段数据）
	 *注意：如果使用Engine，此时会触发其实现的EVP_CIPHER->do_cipher，而不是EVP_CIPHER->cleanup
	 *这点上与EVP_DigestFinal/EVP_SignFinal/EVP_VerifyFinal是完全不同的
	 */
	if (!::EVP_DigestFinal_ex(&__cm_sMdCtx, puchOutput, pnLenOfOutput))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherFinal_ex failed:"<<pchErrorInfo << endl;
		nRetVal = -5;
		goto err;
	}
	return 0;
err:
	this->~CDigest();
	std::exit(nRetVal);
}


inline int 
Openssl_evp::CDigest::HMAC(IN const unsigned char* pcuchInput, IN int nLenOfInput,
		IN OUT unsigned char* puchOutput, IN OUT unsigned int* punLenOfOutput)
{
	::bzero(puchOutput, *punLenOfOutput);
	*punLenOfOutput = 0;
	int nRetVal = 0,                        //return value of this function
		nERR = 0;                             // return value of error
	char pchErrorInfo[1024] = {'\0'};
	
	if (!::HMAC_Init_ex(&__cm_sHmacCtx, __cm_pcuchKey, __cm_nLenOfKey, __cm_psMD, __cm_psImpl))
	{
		nERR = ::ERR_get_error();
		::ERR_error_string(nERR, pchErrorInfo);
		cout << "HMAC_Init_ex failed" << pchErrorInfo << endl;
		nRetVal = -2;
		goto err;
	}

	if (!::HMAC_Update(&__cm_sHmacCtx, pcuchInput, nLenOfInput))
	{
		nERR = ::ERR_get_error();
		::ERR_error_string(nERR, pchErrorInfo);
		cout << "HMAC_Update failed" << pchErrorInfo << endl;
		nRetVal = -3;
		goto err;
	}

	if (!::HMAC_Final(&__cm_sHmacCtx, puchOutput, punLenOfOutput))
	{
		nERR = ::ERR_get_error();
		::ERR_error_string(nERR, pchErrorInfo);
		cout << "HMAC_Final failed" << pchErrorInfo << endl;
		nRetVal = -4;
		goto err;
	}
	return 0;
err:
	return nRetVal;
}

