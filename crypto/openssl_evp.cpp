/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp.cpp
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
#include<openssl.h>
#include<myhead_cpp.h>


/*! @function
********************************************************************************
Function Name  : OpenSSL_Cipher
Function       : 对称加/解密
Parameters     : IN pcchCipherName:加密算法名字
				 IN pcuchKey:密钥
				 IN pcuchInitVec: 初始向量
				 IN pcuchInput:输入数据
				 IN OUT puchOutput：输出数据
				 IN ulnLenOfInput：输入数据长度
				 IN OUT pulnLenOfOutput：输出数据长度
				 IN nIsEncry :加密标志位，为false 为解密
Return Value   : 成功返回0，失败返回错误值
Throw exception: no exception
--------------------------------------------------------------------------------
Note           : puchOutput，应该有足够的长度，请注意char与unsigned char的区别
Typical usage  : no
--------------------------------------------------------------------------------
Date:          : 2017/07/30
Version:       : 0.0
Author         : liaoweizhi
Department     : 技术研发总部
Modifier       : liaoweizhi
Department     : 技术研发总部
Changes        : create
*******************************************************************************/
int
OpenSSL_Cipher(IN const char* pcchCipherName, IN ENGINE* impl,IN const unsigned char* pcuchKey, 
		       IN const unsigned char* pcuchInitVec, IN const unsigned char* pcuchInput,
	           IN int nLenOfInput, IN OUT unsigned char* puchOutput,
			   IN int* pnLenOfOutput, IN int nIsEncry = true)
{
	int nRetVal = 0,                         // the return Value of this function
		nTempLen = 0,                        // last block with padding
		nRet = 0,                            // return value of system calling 
		nBlockSize = 0;                      // 块大小
	char pchErrorInfo[1024] = {'\0'};        //Error Information
	
	EVP_CIPHER_CTX sCtx;              //加密使用的上下文
	::EVP_CIPHER_CTX_init(&sCtx);     //初始化上下文
	const EVP_CIPHER *psCipher = nullptr;   //算法对应的const EVP_CIPHER*
	psCipher = ::EVP_get_cipherbyname(pcchCipherName);
	if (nullptr == psCipher)
	{
		cout << "不支持加密算法:" << pcchCipherName << endl;
		nRetVal = -1;
		goto err;
	}
	nBlockSize = ::EVP_CIPHER_block_size(psCipher); //获取算法对应的块大小
	/*
	 * 初始化：设置对称算法的密钥，IV，以及加解密标志位
	 * 如果使用Engine，此时会调用其实现的EVP_CIPHER->init回调函数
	 */
	if (::EVP_CipherInit_ex(&sCtx, psCipher, impl, pcuchKey, pcuchInitVec, nIsEncry))
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
	*pnLenOfOutput = 0; //置为0
	do 
	{
		if (*pnLenOfOutput + nBlockSize >= nLenOfInput)
		{
			break;
		}
		if (::EVP_CipherUpdate(&sCtx, puchOutput + *pnLenOfOutput, &nTempLen, pcuchInput, nLenOfInput))
		{
			nRet = ::ERR_get_error();
			::ERR_error_string(nRet, pchErrorInfo);
			cout << "EVP_CipherUpdate failed:"<<pchErrorInfo << endl;
			nRetVal = -4;
			goto err;
		}
		*pnLenOfOutput += nBlockSize;
	} while(1);
	/*
	 *输出最后一块数据结果（块加密时，数据将被padding到block长度的整数倍，因此会产生额外的最后一段数据）
	 *注意：如果使用Engine，此时会触发其实现的EVP_CIPHER->do_cipher，而不是EVP_CIPHER->cleanup
	 *这点上与EVP_DigestFinal/EVP_SignFinal/EVP_VerifyFinal是完全不同的
	 */
	
	if (::EVP_CipherFinal_ex(&sCtx, puchOutput + *pnLenOfOutput, &nTempLen))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherFinal_ex failed:"<<pchErrorInfo << endl;
		nRetVal = -5;
		goto err;
	}
	*pnLenOfOutput += nTempLen;
err:
	::EVP_CIPHER_CTX_cleanup(&sCtx);
	return nRetVal;
}





int
OpenSSL_Digest(IN const char* pcchDigestName, IN ENGINE *impl, IN const unsigned char* pcuchInput,
	           IN int nLenOfInput, IN OUT unsigned char* puchOutput,
			   IN int* pnLenOfOutput)
{
	int nRetVal = 0,                         // the return Value of this function
		nTempLen = 0,                        // last block with padding
		nRet = 0,                            // return value of system calling 
		nBlockSize = 0;                      // 块大小
	char pchErrorInfo[1024] = {'\0'};        //Error Information
	
	EVP_MD_CTX sCtx;              //加密使用的上下文
	::EVP_MD_CTX_init(&sCtx);     //初始化上下文
	const EVP_MD *psDigest = nullptr;   //算法对应的const EVP_MD*
	psDigest = ::EVP_get_digestbyname(pcchDigestName);
	if (nullptr == psDigest)
	{
		cout << "不支持摘要算法:" << pcchDigestName << endl;
		nRetVal = -1;
		goto err;
	}
	nBlockSize = ::EVP_MD_block_size(psDigest); //获取算法对应的块大小
	/*
	 * 初始化,如果使用Engine，此时会调用其实现的EVP_MD->init回调函数
	 */
	if (::EVP_DigestInit_ex(&sCtx, psDigest, impl))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_DigestInit_ex failed:" << pchErrorInfo << endl;
		nRetVal = -3;
		goto err;
	}

	/*
	 *对数据进行加/解密运算（如果使用Engine，此时会调用其实现的EVP_DIGEST->do_cipher回调函数）
	 *对于连续数据流，CipherUpdate一般会被调用多次
	 */
	*pnLenOfOutput = 0; //置为0
	do 
	{
		if (*pnLenOfOutput + nBlockSize >= nLenOfInput)
		{
			break;
		}
		if (::EVP_DigestUpdate(&sCtx,  pcuchInput, nLenOfInput))
		{
			nRet = ::ERR_get_error();
			::ERR_error_string(nRet, pchErrorInfo);
			cout << "EVP_CipherUpdate failed:"<<pchErrorInfo << endl;
			nRetVal = -4;
			goto err;
		}
		*pnLenOfOutput += nBlockSize;
	} while(1);
	/*
	 *输出最后一块数据结果（块加密时，数据将被padding到block长度的整数倍，因此会产生额外的最后一段数据）
	 *注意：如果使用Engine，此时会触发其实现的EVP_DIGEST->do_cipher，而不是EVP_DIGEST->cleanup
	 *这点上与EVP_DigestFinal/EVP_SignFinal/EVP_VerifyFinal是完全不同的
	 */
	
	if (::EVP_DigestFinal_ex(&sCtx, puchOutput , reinterpret_cast<unsigned int*>(pnLenOfOutput)))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherFinal_ex failed:"<<pchErrorInfo << endl;
		nRetVal = -5;
		goto err;
	}
	*pnLenOfOutput += nTempLen;
err:
	::EVP_MD_CTX_cleanup(&sCtx);
	return nRetVal;
}
















int main()
{
	/*::OpenSSL_add_all_algorithms();*/
	char pchCipherName[] = "aes-128-dbc";
	unsigned char puchKey[EVP_MAX_KEY_LENGTH] = "asdasdasdasdfasdfsaf";
	unsigned char puchIV[] = "asdasdasdadasdasd";
	unsigned char puchPlainText[1024] ="i love you see is the weorad asdad";
	unsigned char puchCipherText[1024] ="";
	int nOutLen = 0;
	OpenSSL_Cipher(pchCipherName, nullptr, puchKey, puchIV, 
					puchPlainText, std::strlen(reinterpret_cast<char*>(puchPlainText)),
					puchCipherText,&nOutLen,1);

	cout << (char*)puchCipherText << endl;
	cout << nOutLen  << endl;
	return 0;
}
