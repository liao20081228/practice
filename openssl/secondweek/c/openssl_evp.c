/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp.c
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
#include"openssl_evp.h"


int g_nOpenSSLoadFlag = 0;
int g_nErrorNumber = 0;
int g_nErrorFlag = 0;
char g_pchErrorInformation[__MY_ERR_BUFFER_SIZE] = {0};
void (*HandleRrror_cb)(void);



/*!@function
********************************************************************************
Function Name  : OpenSSL_PrintErrorInformation
Function       : print error Information
Parameters     : no parameter
Return Value   : void
Throw exception: no
--------------------------------------------------------------------------------
Note           : no
Typical usage  : no
--------------------------------------------------------------------------------
Date:          : 2017/08/16
Version:       : 0.0
Author         : liaowz
Department     : 技术研发部
Email          : liaowz
Modifier       : no
Department     : 技术研发部
Email          : liaowz@koal.com
Changes        : create
*******************************************************************************/
void 
OpenSSL_PrintErrorInformation(void)
{
	if (g_nErrorFlag == 0)
	{
		printf( "\nfailed Information: %s\n",g_pchErrorInformation);
	}
	else
	{
		g_nErrorNumber = ERR_get_error();
		ERR_error_string_n(g_nErrorNumber, g_pchErrorInformation, __MY_ERR_BUFFER_SIZE-1);
		printf( "\nfailed Information: %s\n",g_pchErrorInformation);
	}
}

void
OpensSSL_LoadAlgorithmAndErrorString(void)
{
	if (g_nOpenSSLoadFlag == 0)
	{
		OpenSSL_add_all_algorithms();     
		ERR_load_crypto_strings();
		g_nOpenSSLoadFlag = 1;
	}
}
void 
OpensSSL_UnLoadAlgorithmAndErrorString(void)
{
	if (g_nOpenSSLoadFlag == 1)
	{
		EVP_cleanup();
		ERR_free_strings();
		g_nOpenSSLoadFlag = 0;
	}
}








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
				 IN nLenOfOutput：输出缓冲区大小
				 IN nIsEncry :加密标志位，为false 为解密
Return Value   : 成功返回加密的长度，失败返回-1
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
OpenSSL_Cipher(OUT unsigned char* puchOutput, IN int nLenOfOutBuf, 
			   IN const char* pcchCipherName, IN const unsigned char* pcuchKey,
			   IN ENGINE* impl, IN const unsigned char* pcuchInitVec, 
			   IN const unsigned char* pcuchInput,IN int nLenOfInput,IN int nIsEncry)
{
	int nLenOfOutput = 0,
		nTempLen = 0;        
	EVP_CIPHER_CTX sCtx;                 
		
	const EVP_CIPHER *psCipher = EVP_get_cipherbyname(pcchCipherName);
	if (NULL == psCipher)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_Cipher:不支持算法:%s",pcchCipherName);
		goto err0;
	}
		
	if (nLenOfOutBuf < nLenOfInput)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_Cipher:输出缓冲区太小");
		goto err0;
	}


	EVP_CIPHER_CTX_init(&sCtx);         
	
	if (!EVP_CipherInit_ex(&sCtx, psCipher, impl, pcuchKey, pcuchInitVec, nIsEncry))
	{
		goto err1;
	}
	if (!EVP_CipherUpdate(&sCtx, puchOutput, &nLenOfOutput, pcuchInput, nLenOfInput))
	{
		goto err0;
	}
	if (!EVP_CipherFinal_ex(&sCtx, puchOutput + nLenOfOutput, &nTempLen))
	{
		goto err1;
	}
	nLenOfOutput += nTempLen;
	EVP_CIPHER_CTX_cleanup(&sCtx);
	return nLenOfOutput;

err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err1:
	g_nErrorFlag = 1;
	EVP_CIPHER_CTX_cleanup(&sCtx);
	OpenSSL_PrintErrorInformation();
	return -1;
}

/*!@function
********************************************************************************
Function Name  : OpenSSL_Digest
Function       : 计算摘要
Parameters     : IN pcchDigestName:摘要算法名字
				 IN pcuchInput:输入数据
				 OUT puchOutput：输出数据
				 IN ulnLenOfInput：输入数据长度
				 IN  nLenOfOutBuf：输出缓冲区大小
Return Value   : 成功返回摘要长度，失败返回-1
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
OpenSSL_Digest(OUT unsigned char* puchOutput, IN int nLenOfOutBuf,
				IN const char* pcchDigestName, IN ENGINE *impl, 
				IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	int nLenOfOutput = 0;

	const EVP_MD *psDigest = EVP_get_digestbyname(pcchDigestName);  
	if (NULL == psDigest)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_Digest:不支持算法:%s",pcchDigestName);
		goto err0;
	}
	
	if (nLenOfOutBuf < EVP_MD_size(psDigest))
	{
		sprintf(g_pchErrorInformation,"OpenSSL_Digest:输出缓冲区太小");
		goto err0;
	}

	EVP_MD_CTX sCtx;                       
	EVP_MD_CTX_init(&sCtx);               
	if (!EVP_DigestInit_ex(&sCtx, psDigest, impl))
	{
		goto err1;
	}
	
	if (!EVP_DigestUpdate(&sCtx,  pcuchInput, nLenOfInput))
	{
		goto err1;
	}
	if (!EVP_DigestFinal_ex(&sCtx, puchOutput , (unsigned int*)&nLenOfOutput))
	{
		goto err1;
	}
	EVP_MD_CTX_cleanup(&sCtx);
	return nLenOfOutput;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err1:
	g_nErrorFlag = 1;
	EVP_MD_CTX_cleanup(&sCtx);
	OpenSSL_PrintErrorInformation();
	return -1;
}

/*! @function
********************************************************************************
Function Name  : OpenSSL_HMAC
Function       : 消息验证码
Parameters     : IN pcsDigestName:摘要算法算法名字
				 IN pcuchKey:密钥
				 IN pstEngine: 引擎
				 IN nLenOfKey: 密钥长度
				 IN pcuchInput:输入数据
				 OUT pcuchOutput：输出数据
				 IN nLenOfInput：输入数据长度
				 IN nLenOfOutBuf：输出缓冲区大小
Return Value   : 成功返回验证码长度，失败返回-1
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
OpenSSL_HMAC(OUT unsigned char* puchOutput, IN int nLenOfOutBuf,
				IN const char* pcchDigestName, IN ENGINE *pstEngine, 
				IN const unsigned char* pcuchKey, IN int nLenOfKey, 
				IN const unsigned char* pcuchInput, IN int nLenOfInput)

{
	int nLenOfOutput = 0;

	const EVP_MD *psDigest = EVP_get_digestbyname(pcchDigestName);  
	if (NULL == psDigest)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_HMAC:不支持算法:%s",pcchDigestName);
		goto err0;
	}
	
	if (nLenOfOutBuf < EVP_MD_size(psDigest))
	{
		sprintf(g_pchErrorInformation,"OpenSSL_HMAC:输出缓冲区太小");
		goto err0;
	}
	
	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);
	
	if (!HMAC_Init_ex(&ctx, pcuchKey, nLenOfKey, psDigest,  pstEngine))
	{
		goto err1;
	}

	if (!HMAC_Update(&ctx, pcuchInput, nLenOfInput))
	{
		goto err1;
	}

	if (!HMAC_Final(&ctx, puchOutput, (unsigned int*)&nLenOfOutput))
	{
		goto err1;
	}
	HMAC_CTX_cleanup(&ctx);
	return nLenOfOutput;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err1:
	g_nErrorFlag = 1;
	HMAC_CTX_cleanup(&ctx);
	OpenSSL_PrintErrorInformation();
	return -1;
}

/*!@function
********************************************************************************
Function Name  : OpenSSL_BinToHex   OpenSSL_HexToBin
Function       : convert binary to hex or hex to binary
Parameters     : IN pcuchdata: date about to ouput
                 IN nLenOfOutBuf: length of output buffer 
                 IN nLenOfData: length of data
Return Value   : sucess return length affer conversion, failed return -1
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
OpenSSL_BinToHex(OUT unsigned char *puchOutput, OUT int nLenOfOutput, 
		IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char hex[17] = "0123456789abcdef";
	int i = 0,
		j = 0;
	if (nLenOfOutput < nLenOfInput * 2)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_BinToHex:输出缓冲区太小");
		goto err;
	}
	for (i = 0,j = 0; i < nLenOfInput ; ++i)
	{
		puchOutput[j++] = hex[pcuchInput[i] >> 4 & 0xf];
		puchOutput[j++] = hex[pcuchInput[i] & 0xf];
	}
	return j;
err:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
}

int 
OpenSSL_HexToBin(OUT unsigned char *puchOutput, OUT int nLenOfOutput, 
				IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	char temp[3] =  {0};
	int i = 0,
		j = 0;
	if (nLenOfInput % 2 != 0)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_HexToBin 输入的十六进制数据有误");
		goto err;
	}
	if (nLenOfOutput < nLenOfInput / 2)
	{
		sprintf(g_pchErrorInformation,"OpenSSL_HexToBinHex 输出缓冲区过小");
		return -1;
	}
	for (i = 0, j = 0; i < nLenOfInput ; i+=2 )
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		puchOutput[j++] = strtoul(temp, NULL, 16);
	}
	return j;
err:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
}


/*!@function
********************************************************************************
Function Name  : OpenSSL_BASE64_encode  OPenssl_BASE64_decode
Function       : encode or decode data with base64
Parameters     : IN pcuchInput: input data
				 IN nLenOfInput: input data length
				 OUT puchOutput: output data
				 IN  nLenOfOutput: output buffer size
Return Value   : sucess return length affer conversion ,failed return -1
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
	int len = nLenOfInput % 48 == 0 ? nLenOfInput / 48  * 65 + 1  : nLenOfInput / 48  * 65 + 66 ;
	int nTempLen = 0;
	int nLenOut = 0;
	EVP_ENCODE_CTX ctx;
	
	if (nLenOfOutput < len)
	{
		g_nErrorFlag = 0;
		sprintf(g_pchErrorInformation,"OpenSSL_BASE64_encode 输出缓冲区过小");
		goto err;
	}
	if (g_nOpenSSLoadFlag == 0)
	{
		OpenSSL_add_all_algorithms();        
		ERR_load_crypto_strings();
		g_nOpenSSLoadFlag = 1;
	}

	EVP_EncodeInit(&ctx);
	EVP_EncodeUpdate(&ctx, puchOutput, &nLenOut, pcuchInput, nLenOfInput);
	EVP_EncodeFinal(&ctx, puchOutput + nLenOut, &nTempLen);
	nLenOut += nTempLen;
	return nLenOut - 1;
err:
	OpenSSL_PrintErrorInformation();
	return  -1;
}

int
OpenSSL_BASE64_decode( OUT unsigned char* puchOutput, IN int nLenOfOutput,
		IN const unsigned char* pcuchInput, IN int nLenOfInput )
{
	int nLenOut = 0;
	int nTempLen = 0;
	EVP_ENCODE_CTX ctx;
	if (nLenOfOutput < nLenOfInput / 65 * 48 + 48)
	{
		g_nErrorFlag = 0;
		sprintf(g_pchErrorInformation,"OpenSSL_BASE64_decode 输出缓冲区过小");
		goto err;
	}
	if ( nLenOfInput % 4 != 0 )
	{
		g_nErrorFlag = 0;
		sprintf(g_pchErrorInformation, "输入的BASE64数据有误");
		goto err;
	}
	if (g_nOpenSSLoadFlag == 0)
	{
		OpenSSL_add_all_algorithms();    
		ERR_load_crypto_strings();
		g_nOpenSSLoadFlag = 1;
	}
	
	EVP_DecodeInit(&ctx);
	
	if(-1 == EVP_DecodeUpdate(&ctx, puchOutput, &nLenOut, pcuchInput, nLenOfInput))
	{
		g_nErrorFlag = 1;
		goto err;
	}
	if ( -1 ==EVP_DecodeFinal(&ctx, puchOutput + nLenOut, &nTempLen) )
	{
		g_nErrorFlag = 1;
		goto err;
	}
	nLenOut += nTempLen;
	return nLenOut;
err:
	OpenSSL_PrintErrorInformation();
	return  -1;
}



