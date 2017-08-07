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

#include<openssl/err.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>
#include"myhead_cpp.h"
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
		CLoadConf(void) {};
		~CLoadConf(void) {};
	
	private:
		static CLoadConf *__cm_pCLoadConf;
		static pthread_once_t __cm_sOnce;
};




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
bool g_IsLoadGlobleConfig = false;
	
class CCipher
{
	public:
		CCipher(IN const char* pcchCipherName, IN const unsigned char* pcuchKey, 
				IN const unsigned char* pcuchInitVec, IN int nIsEncry = 1, IN ENGINE* psImpl = nullptr);
		~CCipher(void) noexcept;
		CCipher(IN const CCipher & lref) = delete; //不可拷贝
		CCipher(IN CCipher && rref) = delete; //不可赋值
		CCipher& operator = (IN const CCipher & lref) = delete; //不可移动拷贝
		CCipher& operator = (IN CCipher && rref) = delete; //不可移动赋值
	public:
		int Cipher(IN const unsigned char* pcuchInput, IN int nLenOfInput,
			       OUT unsigned char* puchOutput, IN OUT int* pnLenOfOutput);
		void ChangeKey(IN const unsigned char* pcuchKey);
		void ChangeIV(IN const unsigned char* pcuchInitVec);
		void changeMode(IN int nIsEncry = 0);
	private:
		void Init();
		void Final();
		void GetEVP_CIPHER(IN const char* pcchCipherName);
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

