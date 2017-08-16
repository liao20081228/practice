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
#ifndef __MY_OPENSSL_EVP_C_H
#define __MY_OPENSSL_EVP_C_H

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#include<openssl/evp.h>
#include<openssl/err.h>
#include<openssl/hmac.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
/*! @function
********************************************************************************
Function Name  : OpenSSL_Cipher
Function       : 对称加/解密
Parameters     : IN pcchCipherName:加密算法名字
				 IN pcuchKey:密钥
				 IN pcuchInitVec: 初始向量
				 IN pcuchInput:输入数据
				 OUT puchOutput：输出数据
				 IN ulnLenOfInput：输入数据长度
				 OUT pulnLenOfOutput：输出数据长度
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
int openssl_flag = 0;
	
int
OpenSSL_Cipher(IN const char* pcchCipherName, IN ENGINE* impl,IN const unsigned char* pcuchKey, 
		       IN const unsigned char* pcuchInitVec, IN const unsigned char* pcuchInput,
	           IN int nLenOfInput, OUT unsigned char* puchOutput,
			   OUT int* pnLenOfOutput, IN int nIsEncry) 
{
	*pnLenOfOutput = 0;
	int nRetVal = 0,          
		nTempLen = 0,        
		nRet = 0;           
	char pchErrorInfo[1024] = {'\0'};      
	if (openssl_flag == 0)
	{
		OpenSSL_add_all_algorithms();     
		ERR_load_crypto_strings();
		openssl_flag = 1;
	}
	EVP_CIPHER_CTX sCtx;                 
	EVP_CIPHER_CTX_init(&sCtx);         
	
	const EVP_CIPHER *psCipher = EVP_get_cipherbyname(pcchCipherName);
	if (NULL == psCipher)
	{
		printf("不支持算法:%s\n",pcchCipherName);
		goto err;
	}
	if (!EVP_CipherInit_ex(&sCtx, psCipher, impl, pcuchKey, pcuchInitVec, nIsEncry))
	{
		nRet = ERR_get_error();
		ERR_error_string(nRet, pchErrorInfo);
		printf("EVP_CipherInit_ex failed:%s\n",pchErrorInfo);
		nRetVal = -3;
		goto err;
	}

		if (!EVP_CipherUpdate(&sCtx, puchOutput, pnLenOfOutput, pcuchInput, nLenOfInput))
		{
			nRet = ERR_get_error();
			ERR_error_string(nRet, pchErrorInfo);
			printf("EVP_CipherUpdate failed:%s\n",pchErrorInfo);
			nRetVal = -4;
			goto err;
		}
	if (!EVP_CipherFinal_ex(&sCtx, puchOutput + *pnLenOfOutput, &nTempLen))
	{
		nRet = ERR_get_error();
		ERR_error_string(nRet, pchErrorInfo);
		printf("EVP_CipherFinal_ex failed:%s\n",pchErrorInfo);
		nRetVal = -5;
		goto err;
	}
	*pnLenOfOutput += nTempLen;
	return 0;
err:
	EVP_CIPHER_CTX_cleanup(&sCtx);
	return nRetVal;
}

/*!@function
********************************************************************************
Function Name  : OpenSSL_Digest
Function       : 计算摘要
Parameters     : IN pcchDigestName:摘要算法名字
				 IN pcuchInput:输入数据
				 OUT puchOutput：输出数据
				 IN ulnLenOfInput：输入数据长度
				 OUT pulnLenOfOutput：输出数据长度
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
	           IN int nLenOfInput, OUT unsigned char* puchOutput,
			   OUT int* pnLenOfOutput)
{
	int nRetVal = 0,                         // the return Value of this function
		nRet = 0;                            // return value of system calling 
	char pchErrorInfo[1024] = {'\0'};        //Error Information
	
	if (openssl_flag == 0)
	{
		OpenSSL_add_all_algorithms();          //load globle configuration
		ERR_load_crypto_strings();
		openssl_flag = 1;
	}
	EVP_MD_CTX sCtx;                         //digest context 
	EVP_MD_CTX_init(&sCtx);                //initialize context
	const EVP_MD *psDigest = EVP_get_digestbyname(pcchDigestName);  //算法对应的const EVP_MD*
	if (NULL == psDigest)
	{
		printf("不支持算法:%s\n",pcchDigestName);
		nRetVal = -1;
		goto err;
	}
	if (!EVP_DigestInit_ex(&sCtx, psDigest, impl))
	{
		nRet = ERR_get_error();
		ERR_error_string(nRet, pchErrorInfo);
		printf("EVP_CipherInit_ex failed:%s\n",pchErrorInfo);
		nRetVal = -3;
		goto err;
	}
	*pnLenOfOutput = 0; 
	
	if (!EVP_DigestUpdate(&sCtx,  pcuchInput, nLenOfInput))
	{
		nRet = ERR_get_error();
		ERR_error_string(nRet, pchErrorInfo);
		printf("EVP_CipherUpdate failed:%s\n",pchErrorInfo);
		nRetVal = -4;
		goto err;
	}
	if (!EVP_DigestFinal_ex(&sCtx, puchOutput , (unsigned int*)pnLenOfOutput))
	{
		nRet = ERR_get_error();
		ERR_error_string(nRet, pchErrorInfo);
		printf("EVP_CipherFinal_ex failed:%s\n",pchErrorInfo);
		nRetVal = -5;
		goto err;
	}
	return 0;
err:
	EVP_MD_CTX_cleanup(&sCtx);
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
				 OUT pcuchOutput：输出数据
				 IN nLenOfInput：输入数据长度
				 OUT punLenOfOutput：输出数据长度
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
			 OUT unsigned char* puchOutput, OUT unsigned int* punLenOfOutput)

{
	if (openssl_flag == 0)
	{
		OpenSSL_add_all_algorithms();          //load globle configuration
		ERR_load_crypto_strings();
		openssl_flag = 1;
	}
	*punLenOfOutput = 0;
	int nRetVal = 0,                        //return value of this function
		nERR = 0;                             // return value of error
	char pchErrorInfo[1024] = {'\0'};
	const EVP_MD *pcsMD = EVP_get_digestbyname(pcsDigestName); //get the struct EVP_MD
	
	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);
	
	if (NULL == pcsMD)
	{
		printf("不支持该摘要算法\n");
		nRetVal = -1;
		goto err;
	}
	
	if (!HMAC_Init_ex(&ctx, pcuchKey, nLenOfKey, pcsMD,  pstEngine))
	{
		nERR = ERR_get_error();
		ERR_error_string(nERR, pchErrorInfo);
		printf("HMAC_Init_ex failed%s\n", pchErrorInfo);
		nRetVal = -2;
		goto err;
	}

	if (!HMAC_Update(&ctx, pcuchInput, nLenOfInput))
	{
		nERR = ERR_get_error();
		ERR_error_string(nERR, pchErrorInfo);
		printf("HMAC_Update failed%s\n",pchErrorInfo);
		nRetVal = -3;
		goto err;
	}

	if (!HMAC_Final(&ctx, puchOutput, punLenOfOutput))
	{
		nERR = ERR_get_error();
		ERR_error_string(nERR, pchErrorInfo);
		printf("HMAC_Final failed%s\n",pchErrorInfo);
		nRetVal = -4;
		goto err;
	}
	return 0;
err:
	HMAC_CTX_cleanup(&ctx);
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
int 
BinToHex(OUT unsigned char *puchOutput, OUT int nLenOfOutput, IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	if (nLenOfOutput < nLenOfInput * 2)
	{
		printf("BinToHex输出缓冲区过小\n");
		return -1;
	}
	const char hex[17] = "0123456789abcdef";
	int i = 0,
		j = 0;
	for (i = 0,j = 0; i < nLenOfInput ; ++i)
	{
		puchOutput[j++] = hex[pcuchInput[i] >> 4 & 0xf];
		puchOutput[j++] = hex[pcuchInput[i] & 0xf];
	}
	return j;
}

int 
HexToBin(OUT unsigned char *puchOutput, OUT int nLenOfOutput, IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	if (nLenOfInput % 2 != 0)
	{
		printf("HexToBex 输入的十六进制数据有误\n");
	}
	if (nLenOfOutput < nLenOfInput / 2)
	{
		printf("HexToBex输出缓冲区过小");
		return -1;
	}
	char temp[3] =  {0};
	int i = 0,
		j = 0;
	for (i = 0, j = 0; i < nLenOfInput ; i+=2 )
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		puchOutput[j++] = strtoul(temp, NULL, 16);
	}
	return j;
}


/*!@function
********************************************************************************
Function Name  : OpenSSL_BASE64_encode
Function       : encode or decode data with base64
Parameters     : IN pcuchInput: input data
				 IN nLenOfInput: input data length
				 OUT puchOutput: output data
				 OUT pnLenOfOutput: output data length
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

int  
OpenSSL_BASE64_encode( OUT unsigned char* puchOutput,  IN int nLenOfOutput,
						IN const unsigned char* pcuchInput, IN int nLenOfInput )
{
	int len = nLenOfInput % 3 == 0 ? nLenOfInput / 3  * 4  : nLenOfInput / 3  * 4 + 4 ;
	if (nLenOfOutput < len)
	{
		printf("OpenSSL_BASE64_encode输出缓冲区过小\n");
		return -1;
	}
	if (openssl_flag == 0)
	{
		OpenSSL_add_all_algorithms();        
		ERR_load_crypto_strings();
		openssl_flag = 1;
	}

	int nTempLen = 0;
	int nLenOut = 0;
	EVP_ENCODE_CTX ctx;
	EVP_EncodeInit(&ctx);
	EVP_EncodeUpdate(&ctx, puchOutput, &nLenOut, pcuchInput, nLenOfInput);
	EVP_EncodeFinal(&ctx, puchOutput + nLenOut, &nTempLen);
	nLenOut += nTempLen;
	return nLenOut - 1;
}

/*!@function
********************************************************************************
Function Name  : OPenssl_BASE64_decode
Function       : encode or decode data with base64
Parameters     : IN pcuchInput: input data
				 IN nLenOfInput: input data length
				 OUT puchOutput: output data
				 OUT pnLenOfOutput: output data length
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
OpenSSL_BASE64_decode( OUT unsigned char* puchOutput, IN int nLenOfOutput,
		IN const unsigned char* pcuchInput, IN int nLenOfInput )
{
	int nLenOut = 0;
	int nTempLen = 0;
	EVP_ENCODE_CTX ctx;
	if (nLenOfOutput < nLenOfInput / 4 * 3)
	{
		printf("OpenSSL_BASE64_decode输出缓冲区过小\n");
		goto err;
	}
	if ( nLenOfInput % 4 != 0 )
	{
		printf("输入的BASE64数据有误\n");
		goto err;
	}
	if (openssl_flag == 0)
	{
		OpenSSL_add_all_algorithms();    
		ERR_load_crypto_strings();
		openssl_flag = 1;
	}
	
	EVP_DecodeInit(&ctx);
	
	if(-1 == EVP_DecodeUpdate(&ctx, puchOutput, &nLenOut, pcuchInput, nLenOfInput))
	{
		printf( "EVP_DecodeUpdate failed" );
		goto err;
	}
	if ( -1 ==EVP_DecodeFinal(&ctx, puchOutput + nLenOut, &nTempLen) )
	{
		printf("EVP_DecodeFinal failed");
		goto err;
	}
	nLenOut += nTempLen;
	return nLenOut;
err:
	return -1;
}



#endif /* end of include guard: __MY_OPENSSL_EVP_H */
