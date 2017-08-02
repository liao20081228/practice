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
#include<openssl/evp.h>
#include<openssl/err.h>
#include<openssl/hmac.h>
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
	::bzero(puchOutput, *pnLenOfOutput);
	*pnLenOfOutput =0;
	int nRetVal = 0,                         // the return Value of this function
		nTempLen = 0,                        // last block with padding
		nRet = 0;                            // return value of system calling 
	char pchErrorInfo[1024] = {'\0'};        //Error Information buffer
	::OpenSSL_add_all_algorithms();          //load globle configuration
	
	EVP_CIPHER_CTX sCtx;                     //加密使用的上下文
	::EVP_CIPHER_CTX_init(&sCtx);            //初始化上下文
	
	const EVP_CIPHER *psCipher = ::EVP_get_cipherbyname(pcchCipherName);   //获取算法对应的const EVP_CIPHER*
	if (nullptr == psCipher)
	{
		cout << "不支持算法:" << pcchCipherName << endl;
		goto err;
	}
	/*
	 * 初始化：设置对称算法的密钥，IV，以及加解密标志位
	 * 如果使用Engine，此时会调用其实现的EVP_CIPHER->init回调函数
	 */
	if (!::EVP_CipherInit_ex(&sCtx, psCipher, impl, pcuchKey, pcuchInitVec, nIsEncry))
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

		if (!::EVP_CipherUpdate(&sCtx, puchOutput + *pnLenOfOutput, pnLenOfOutput, pcuchInput, nLenOfInput))
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
	if (!::EVP_CipherFinal_ex(&sCtx, puchOutput + *pnLenOfOutput, &nTempLen))
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
	::EVP_CIPHER_CTX_cleanup(&sCtx);
	return nRetVal;
}

/*!@function
********************************************************************************
Function Name  : OpenSSL_Digest
Function       : 计算摘要
Parameters     : IN pcchDigestName:摘要算法名字
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
OpenSSL_Digest(IN const char* pcchDigestName, IN ENGINE *impl, IN const unsigned char* pcuchInput,
	           IN int nLenOfInput, IN OUT unsigned char* puchOutput,
			   IN OUT int* pnLenOfOutput)
{
	::bzero(puchOutput, *pnLenOfOutput);
	*pnLenOfOutput = 0;
	
	int nRetVal = 0,                         // the return Value of this function
		nRet = 0;                            // return value of system calling 
	char pchErrorInfo[1024] = {'\0'};        //Error Information
	::OpenSSL_add_all_algorithms();          //load globle algorithm configuration
	EVP_MD_CTX sCtx;                         //digest context 
	::EVP_MD_CTX_init(&sCtx);                //initialize context
	const EVP_MD *psDigest = ::EVP_get_digestbyname(pcchDigestName);  //算法对应的const EVP_MD*
	if (nullptr == psDigest)
	{
		cout << "不支持摘要算法:" << pcchDigestName << endl;
		nRetVal = -1;
		goto err;
	}
	/*
	 * 初始化,如果使用Engine，此时会调用其实现的EVP_MD->init回调函数
	 */
	if (!::EVP_DigestInit_ex(&sCtx, psDigest, impl))
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
		if (!::EVP_DigestUpdate(&sCtx,  pcuchInput, nLenOfInput))
		{
			nRet = ::ERR_get_error();
			::ERR_error_string(nRet, pchErrorInfo);
			cout << "EVP_CipherUpdate failed:"<<pchErrorInfo << endl;
			nRetVal = -4;
			goto err;
		}
	/*
	 *输出最后一块数据结果（块加密时，数据将被padding到block长度的整数倍，因此会产生额外的最后一段数据）
	 *注意：如果使用Engine，此时会触发其实现的EVP_DIGEST->do_cipher，而不是EVP_DIGEST->cleanup
	 *这点上与EVP_DigestFinal/EVP_SignFinal/EVP_VerifyFinal是完全不同的
	 */
	
	if (!::EVP_DigestFinal_ex(&sCtx, puchOutput , reinterpret_cast<unsigned int*>(pnLenOfOutput)))
	{
		nRet = ::ERR_get_error();
		::ERR_error_string(nRet, pchErrorInfo);
		cout << "EVP_CipherFinal_ex failed:"<<pchErrorInfo << endl;
		nRetVal = -5;
		goto err;
	}
	return 0;
err:
	::EVP_MD_CTX_cleanup(&sCtx);
	return nRetVal;
}

/*! @function
********************************************************************************
Function Name  : OpenSSL_HMAC
Function       : 对称加/解密
Parameters     : IN pcsDigestName:摘要算法算法名字
				 IN pcuchKey:密钥
				 IN pstEngine: 引擎
				 IN nLenOfKey: 密钥长度
				 IN pcuchInput:输入数据
				 IN OUT pcuchOutput：输出数据
				 IN nLenOfInput：输入数据长度
				 IN OUT punLenOfOutput：输出数据长度
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
OpenSSL_HMAC(IN const char* pcsDigestName, IN ENGINE *pstEngine, IN const unsigned char* pcuchKey,
		     IN int nLenOfKey, IN const unsigned char* pcuchInput, IN int nLenOfInput,
			 IN OUT unsigned char* puchOutput, IN OUT unsigned int* punLenOfOutput)

{
	::bzero(puchOutput, *punLenOfOutput);
	*punLenOfOutput = 0;
	int nRetVal = 0,                        //return value of this function
		nERR = 0;                             // return value of error
	char pchErrorInfo[1024] = {'\0'};
	const EVP_MD *pcsMD = ::EVP_get_digestbyname(pcsDigestName); //get the struct EVP_MD
	
	HMAC_CTX ctx;
	::HMAC_CTX_init(&ctx);
	
	if (nullptr == pcsMD)
	{
		cout << "不支持该摘要算法" << endl;
		nRetVal = -1;
		goto err;
	}
	
	if (!::HMAC_Init_ex(&ctx, pcuchKey, nLenOfKey, pcsMD,  pstEngine))
	{
		nERR = ::ERR_get_error();
		::ERR_error_string(nERR, pchErrorInfo);
		cout << "HMAC_Init_ex failed" << pchErrorInfo << endl;
		nRetVal = -2;
		goto err;
	}

	if (!::HMAC_Update(&ctx, pcuchInput, nLenOfInput))
	{
		nERR = ::ERR_get_error();
		::ERR_error_string(nERR, pchErrorInfo);
		cout << "HMAC_Update failed" << pchErrorInfo << endl;
		nRetVal = -3;
		goto err;
	}

	if (!::HMAC_Final(&ctx, puchOutput, punLenOfOutput))
	{
		nERR = ::ERR_get_error();
		::ERR_error_string(nERR, pchErrorInfo);
		cout << "HMAC_Final failed" << pchErrorInfo << endl;
		nRetVal = -4;
		goto err;
	}
	return 0;
err:
	::HMAC_CTX_cleanup(&ctx);
	return nRetVal;
}

/*!@function
********************************************************************************
Function Name  : Output_HEX
Function       : output result with hexadecimal
Parameters     : IN pcuchdata: date about to ouput
                 IN nLenOfData: length of data
				 IN pFileName: file name
Return Value   : no return value
Throw exception: no
--------------------------------------------------------------------------------
Note           : the differnce between char and unsigned char
Typical usage  :  no
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

void Output_HEX(IN const unsigned char* pcuchdata, IN unsigned int nLenOfData, const char* pFileName = nullptr)
{
	int nFd = 1;
	if (pFileName)
	{
		nFd = ::open(pFileName, O_WRONLY|O_CLOEXEC|O_CREAT|O_TRUNC, 0755);
		if (nFd == -1)
		{
			std::perror("open() failed or occur error");
			exit(-1);
		}
	}
	for (unsigned int i = 0; i < nLenOfData; ++i) 
	{
		if (pcuchdata[i] < 16)
		{
			::dprintf(nFd, "%x", 0);
			::dprintf(nFd, "%x", pcuchdata[i]);
		}
		else
		{
			::dprintf(nFd, "%x", pcuchdata[i]);
		}
		
	}
	if (nFd != 1)
	{
		::close(nFd);
	}
}


/*!@function
********************************************************************************
Function Name  : OpenSSL_BASE64_encode
Function       : encode or decode data with base64
Parameters     : IN pcuchInput: input data
				 IN nLenOfInput: input data length
				 IN OUT puchOutput: output data
				 IN OUT pnLenOfOutput: output data length
Return Value   : void
Throw exception: no
--------------------------------------------------------------------------------
Note           : no
Typical usage  : no 
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

void 
OpenSSL_BASE64_encode(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
					  IN OUT unsigned char* puchOutput, IN OUT int* pnLenOfOutput)
{
	::bzero(puchOutput, *pnLenOfOutput);
	*pnLenOfOutput = 0;

	int nTempLen = 0;
	EVP_ENCODE_CTX ctx;
	::EVP_EncodeInit(&ctx);
	
	::EVP_EncodeUpdate(&ctx, puchOutput, pnLenOfOutput, pcuchInput, nLenOfInput);

	::EVP_EncodeFinal(&ctx, puchOutput + *pnLenOfOutput, &nTempLen);

	*pnLenOfOutput += nTempLen;
}

/*!@function
********************************************************************************
Function Name  : OPenssl_BASE64_decode
Function       : encode or decode data with base64
Parameters     : IN pcuchInput: input data
				 IN nLenOfInput: input data length
				 IN OUT puchOutput: output data
				 IN OUT pnLenOfOutput: output data length
Return Value   : 0 sucess and no zero is error
Throw exception: no
--------------------------------------------------------------------------------
Note           : no
Typical usage  : no 
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

int
OpenSSL_BASE64_decode(IN const unsigned char* pcuchInput, IN int nLenOfInput, 
					  IN OUT unsigned char* puchOutput, IN OUT int* pnLenOfOutput)
{
	::bzero(puchOutput, *pnLenOfOutput);
	*pnLenOfOutput = 0;

	int nTempLen = 0;
	EVP_ENCODE_CTX ctx;
	::EVP_DecodeInit(&ctx);
	
	if(-1 == ::EVP_DecodeUpdate(&ctx, puchOutput, pnLenOfOutput, pcuchInput, nLenOfInput))
	{
		cout << "EVP_DecodeUpdate failed" << endl;
		return -1;
	}
	if ( -1 ==::EVP_DecodeFinal(&ctx, puchOutput + *pnLenOfOutput, &nTempLen) )
	{
		cout << "EVP_DecodeFinal failed" << endl;
		return -1;
	}
	*pnLenOfOutput += nTempLen;
	return 0;
}

