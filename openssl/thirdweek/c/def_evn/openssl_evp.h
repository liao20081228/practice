/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp.h
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

#pragma once

#ifndef __MY_OPENSSL_EVP_C_H
#define __MY_OPENSSL_EVP_C_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include<openssl/evp.h>
#include<openssl/err.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef __MY_MAX_BUFFER_SIZE 
#define __MY_MAX_BUFFER_SIZE 12000
#endif

#ifndef __MY_ERR_BUFFER_SIZE
#define __MY_ERR_BUFFER_SIZE 1024
#endif


extern int g_nOpenSSLoadFlag;
extern int g_nErrorNumber;
extern int g_nErrorFlag;
extern char g_pchErrorInformation[]; 
extern void (*HandleRrror_cb)(void);


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
void OpenSSL_PrintErrorInformation(void);

void OpensSSL_LoadAlgorithmAndErrorString(void);
void OpensSSL_UnLoadAlgorithmAndErrorString(void);

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

int OpenSSL_Cipher(OUT unsigned char* puchOutput, IN int nLenOfOutBuf, 
			   IN const char* pcchCipherName, IN const unsigned char* pcuchKey,
			   IN ENGINE* impl, IN const unsigned char* pcuchInitVec, 
			   IN const unsigned char* pcuchInput,IN int nLenOfInput,IN int nIsEncry);

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

int OpenSSL_Digest(OUT unsigned char* puchOutput, IN int nLenOfOutBuf,
				IN const char* pcchDigestName, IN ENGINE *impl, 
				IN const unsigned char* pcuchInput, IN int nLenOfInput);

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

int OpenSSL_HMAC(OUT unsigned char* puchOutput, IN int nLenOfOutBuf,
				IN const char* pcchDigestName, IN ENGINE *pstEngine, 
				IN const unsigned char* pcuchKey, IN int nLenOfKey, 
				IN const unsigned char* pcuchInput, IN int nLenOfInput);

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
int OpenSSL_BinToHex(OUT unsigned char *puchOutput, OUT int nLenOfOutput, 
		IN const unsigned char* pcuchInput, IN int nLenOfInput);

int OpenSSL_HexToBin(OUT unsigned char *puchOutput, OUT int nLenOfOutput, 
				IN const unsigned char* pcuchInput, IN int nLenOfInput);

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

int  OpenSSL_BASE64_encode( OUT unsigned char* puchOutput,  IN int nLenOfOutput,
						IN const unsigned char* pcuchInput, IN int nLenOfInput );

int OpenSSL_BASE64_decode( OUT unsigned char* puchOutput, IN int nLenOfOutput,
		IN const unsigned char* pcuchInput, IN int nLenOfInput );

#endif /* end of include guard: __MY_OPENSSL_EVP_H */
