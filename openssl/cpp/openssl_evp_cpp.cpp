/*****************************************************************************80
    > File Name: openssl_evp_cpp.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月01日 星期二 15时04分46秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#include"openssl_evp_cpp.h"

Openssl_evp::CLoadConf* Openssl_evp::CLoadConf::__cm_pCLoadConf = Getinstance();
pthread_once_t Openssl_evp::CLoadConf::__cm_sOnce = PTHREAD_ONCE_INIT;

	/* static */ Openssl_evp::CLoadConf* 
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




Openssl_evp::CCipher::CCipher(IN const char* pcchCipherName, IN const unsigned char* pcuchKey, 
				IN const unsigned char* pcuchInitVec, IN int nIsEncry /* =1 */
				                                    , IN ENGINE* psImpl /*=nullptr*/)
	: __cm_psImpl(psImpl)
	, __cm_pcuchKey(pcuchKey)
	, __cm_pcuchInitVec(pcuchInitVec)
	, __cm_nIsEncry(nIsEncry)
{
	::EVP_CIPHER_CTX_init(&__cm_sCtx);
	if (g_IsLoa)
	{
		/*function_body*/
	}
	__cm_psCipher = ::EVP_get_cipherbyname(pcchCipherName);
	if (nullptr == __cm_psCipher)
	{
		throw(std::invalid_argument("不支持此算法"));
	}

}

inline
Openssl_evp::CCipher::~CCipher(void) noexcept
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

