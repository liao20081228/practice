/*****************************************************************************80
  > File Name: getopt.cpp
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年08月02日 星期三 10时15分18秒
 *******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#include<getopt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"openssl_evp_c.h"
#include<openssl/evp.h>
#include<openssl/err.h>
#define MY_MAX_BUFFER_SIZE 24000
void 
ShowHelpInfo(void)
{
	printf("help info\n \
		-m/--mode 计算模式，包括 encrypt | decrypt | digest | hmac 这四种\n  \
		-a/--algorithom 算法名称，包括 RC4 | AES-128-CBC | AES-128-ECB | AES-256-CBC | AES-128-ECB | MD5 | SHA1 | SHA256 这些\n \
		-k/--key HEX(16进制)格式的密钥值，比如 0001020304050600708090A0B0C0D0E0F 表示一个16字节的密钥\n \
		-v/--iv HEX(16进制)格式的初始化向量\n \
		-i/--input 输入文件\n  \
		-o/--output 输出文件\n \
		-f/--format 输出/输入格式，包括 BINARY | HEX | BASE64 这三种，默认为BINARY\n \
		-h/--help 显示使用帮助\n \
		\n \
		使用示例1：对称加密（使用全0的密钥和全0的IV）\n \
		xxxxx -m encrypt -a AES-128-CBC -k 00000000000000000000000000000000 -v 00000000000000000000000000000000 -i in.txt -o out.b64 -f BASE64\n \
		\n \
		使用示例2：摘要计算\n \
		xxxxx -m digest -a SHA1 -i in.txt -o digest.hex -f HEX\n \
		\n \
		使用示例3：HMAC计算(使用一个5字节的KEY)\n \
		xxxxx -m hmac -a SHA1 -i in.txt -k 0000000000 -o hmac.hex -f BINARY\n");
}

int 
ReadAccordingFormat(IN int nFdIn, IN const char*format, OUT unsigned char* pchdata, IN int nLen)
{
	if (strlen(format) == 0 || strcmp(format, "BINARY") == 0)
	{
		return read(nFdIn, pchdata, nLen);
	}
	else if (strcmp(format, "HEX") == 0) 
	{
		unsigned char temp[MY_MAX_BUFFER_SIZE*2]={0};
		int nLenTemp = read(nFdIn, temp, nLen*2);
		if (!(nLenTemp > 0 ))
		{
			return nLenTemp; 
		}
		else 
		{
			int len = HexToBin(pchdata,nLen, temp, nLenTemp);
			return len;
		}
	}
	else if (strcmp(format, "BASE64") == 0)
	{
		unsigned char temp[MY_MAX_BUFFER_SIZE*2] = {0};
		
		int realLen = nLen % 3 == 0 ? nLen / 3 * 4 : nLen / 3 * 4 + 4;   
		
		int nLenTemp = read(nFdIn, temp, realLen);
		if (temp[nLenTemp-1] == '\n')
		{
			--nLenTemp;
		}
		if (!(nLenTemp > 0 ))
		{
			return nLenTemp; 
		}
		else 
		{
			int len = OpenSSL_BASE64_decode(pchdata,nLen,temp,nLenTemp);
			return len;
		}
	}
	return 0;
}



int 
WriteAccordingFormat(IN int nFdOut, IN const char*format, IN const unsigned char* pchdata, IN int nLen)
{
	if (strlen(format) == 0 || strcmp(format, "BINARY") == 0)
	{
		if (-1 == write(nFdOut, pchdata, nLen))
		{
			goto err;
		}

	}
	else if (strcmp(format, "HEX") == 0) 
	{
		unsigned char temp[MY_MAX_BUFFER_SIZE*2] = {0};
		int len = BinToHex(temp, MY_MAX_BUFFER_SIZE*2, pchdata, nLen);
		if(-1 == write(nFdOut, temp, len))
		{
			goto err;
		}
	}
	else if (strcmp(format, "BASE64") == 0)
	{
		unsigned char temp[MY_MAX_BUFFER_SIZE*2] = {0};
		int len = OpenSSL_BASE64_encode(temp, MY_MAX_BUFFER_SIZE*2, pchdata, nLen);
		if (-1 == write(nFdOut, temp, len))
		{
			goto err;
		}
	}
	return 0;

err:
	perror("output failed or occur error");
	return -1;
}

int 
ReadCommandArgument(IN int argc, IN char* argv[],  OUT char* pchMode, 
					OUT char* pchAlgorithom,  OUT unsigned  char* pchKey, 
					OUT unsigned char* pchInitVec,  OUT char* pchInputFile, 
					OUT char* pchOutputFile, OUT char* pchFormat)
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	int IsHelp = 0;
	char KeyTemp[EVP_MAX_KEY_LENGTH*2 + 1] = {0};
	char IVTemp[EVP_MAX_IV_LENGTH*2 + 1] = {0};
	static struct option long_options[] = /* 长选项定义*/
	{
		{"mode",       1,    0,   'm'},
		{"algorithom", 1,    0,   'a'},
		{"key",        1,    0,   'k'},
		{"iv",         1,    0,   'v'},
		{"input",      1,    0,   'i'},
		{"output",     1,    0,   'o'},
		{"format",     1,    0,   'f'},
		{"help",       0 ,   0,   'h'},
		{0, 0, 0, 0}
	};

	while ((chOption = getopt_long(argc, argv, "m:a:k:v:i:o:f:h", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'm' : strcpy(pchMode, optarg); break;
			case 'a' : strcpy(pchAlgorithom, optarg); break;
			case 'k' : strcpy(KeyTemp, optarg); break;
			case 'v' : strcpy(IVTemp, optarg); break;
			case 'i' : strcpy(pchInputFile, optarg); break;
			case 'o' : strcpy(pchOutputFile, optarg); break;
			case 'f' : strcpy(pchFormat, optarg); break;
			case 'h' : ShowHelpInfo(); IsHelp = 1; exit(-1);
			default  : printf("Unknown option:%c\n",chOption); ShowHelpInfo(); return -1;
		}
	}
	if (IsHelp == 0)
	{
		if (!(strlen(pchMode) && strlen(pchAlgorithom) && strlen(pchInputFile)))
		{
			goto err;
		}
		if(0 ==((strcmp(pchMode, "encrypt") == 0 || strcmp(pchMode, "decrypt") == 0 
				|| strcmp(pchMode, "digest") == 0 || strcmp(pchMode, "hmac") == 0)))
		{
			goto err;
		}
		if (strlen(pchFormat) != 0 && (0 == (strcmp(pchFormat, "BINARY") == 0 || strcmp(pchFormat, "HEX") == 0
			|| strcmp(pchFormat, "BASE64") == 0)))
		{
			goto err;
		}
		if ((0 == strcmp(pchMode, "encrypt") || 0 == strcmp(pchMode, "decrypt")) 
				&& ((strlen(KeyTemp) == 0 || strlen(IVTemp) == 0))  )
		{
				goto err;
		}
		if (0 == strcmp(pchMode, "hmac") && strlen(KeyTemp) == 0)
		{
				goto err;
		}

		for ( int i = 0; i <(int) strlen(KeyTemp); ++i)
		{
			if (0 == ((KeyTemp[i] >= '0' && KeyTemp[i] <= '9') || (KeyTemp[i] >= 'a' && KeyTemp[i] <= 'f')))
			{
				printf("请输入十六进制的密钥\n");
				goto err;
			}
		}
		for ( int i = 0; i <(int) strlen(IVTemp); ++i)
		{
			if (0 == ((IVTemp[i] >= '0' && IVTemp[i] <= '9') || (IVTemp[i] >= 'a' && IVTemp[i] <= 'f')))
			{
				printf("请输入十六进制的初始向量\n");
				goto err;
			}
		}

		char temp[3] = {0};
		for ( int i = 0, j = 0; i < (int)strlen(KeyTemp) && j < EVP_MAX_KEY_LENGTH ;)
		{
			if (i + 1 < (int)strlen(KeyTemp))
			{
				temp[0] = KeyTemp[i];
				temp[1] = KeyTemp[i+1];
				temp[2] = '\0';
				pchKey[j++] = (unsigned char) strtoul(temp,NULL, 16 );
				i += 2;
			}
			else if (i + 1 == (int) strlen(KeyTemp))
			{
				temp[0] = KeyTemp[i];
				temp[1] = '\0';
				pchKey[j++] = (unsigned char) strtoul(temp,NULL, 16 );
				break;
			}
		}
		for ( int i = 0, j = 0; i < (int)strlen(IVTemp) && j < EVP_MAX_KEY_LENGTH ;)
		{
			if (i + 1 < (int)strlen(IVTemp))
			{
				temp[0] = IVTemp[i];
				temp[1] = IVTemp[i+1];
				temp[2] = '\0';
				pchInitVec[j++] = (unsigned char) strtoul(temp,NULL, 16 );
				i += 2;
			}
			else if (i + 1 == (int) strlen(IVTemp))
			{
				temp[0] = IVTemp[i];
				temp[1] = '\0';
				pchInitVec[j++] = (unsigned char) strtoul(temp,NULL, 16 );
				break;
			}
		}

	}
	return 0;
err:
	return -1;
}


int
HandleCommandArgument(IN int argc, IN char* argv[])
{
	if (openssl_flag == 0)
	{
		OpenSSL_add_all_algorithms();
		ERR_load_crypto_strings();
		openssl_flag = 1;
	}
	char pchMode[10] = {'\0'},
		 pchAlgorithom[20] = {'\0'},
		 pchInputFile[256] = {'\0'},
	     pchOutputFile[256] = {'\0'},
	     pchFormat[10] = {'\0'};
	unsigned char  pchKey[EVP_MAX_KEY_LENGTH + 1] = {'\0'},
					pchInitVec[EVP_MAX_IV_LENGTH + 1] = {'\0'};

	int nFdIn = 0,
		nFdOut = STDOUT_FILENO;
	
	unsigned char puchInput[MY_MAX_BUFFER_SIZE],
				  puchOutput[MY_MAX_BUFFER_SIZE * 2];
	
	int nLenOfIn  = 0,
		nLenOfOut = 0;

	char ErrorInfo[MY_MAX_BUFFER_SIZE] = {0};
	int nErr = 0;
	
	if (0 != ReadCommandArgument(argc, argv, pchMode, pchAlgorithom,                                                                      
	   pchKey, pchInitVec,pchInputFile, pchOutputFile, pchFormat))
	{
		goto err0;
	} 
	if ((nFdIn = open(pchInputFile, O_RDONLY)) == -1)
	{
		perror("open input file failed");
		goto err0;
	}
	
	if (strlen(pchOutputFile) != 0)
	{
		if ((nFdOut = open(pchOutputFile, O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, 0666)) == -1) 
		{
			perror("open output file failed");
			goto err1;
		}
	}

	if (0 == strcmp(pchMode, "encrypt"))
	{
		
		const EVP_CIPHER *psCipher = EVP_get_cipherbyname(pchAlgorithom);  //获取算法对应的const EVP_CIPHER*
		if (NULL == psCipher)
		{
			printf("不支持算法:%s\n",pchAlgorithom);
			goto err2;
		}
		EVP_CIPHER_CTX sCtx;                     //加密使用的上下文
		EVP_CIPHER_CTX_init(&sCtx);            //初始化上下文
		
		int nFinalable = 0;
		int nIsCallFinal = 0;

		if (0 == EVP_CipherInit_ex(&sCtx, psCipher, NULL,(unsigned char*)pchKey, (unsigned char*)pchInitVec, 1))
		{
			EVP_CIPHER_CTX_cleanup(&sCtx);
			goto err3;
		}
		char _format[1]={'\0'};
		while ( (nLenOfIn = ReadAccordingFormat(nFdIn,_format, puchInput, MY_MAX_BUFFER_SIZE / 2 )) > 0)
		{
			if (!EVP_CipherUpdate(&sCtx, puchOutput, &nLenOfOut, puchInput, nLenOfIn))
			{
				EVP_CIPHER_CTX_cleanup(&sCtx);
				goto err3;
			}
			nFinalable = 1;
			if (nLenOfIn < MY_MAX_BUFFER_SIZE / 2 && nFinalable == 1)
			{
				int templen = 0;
				if (!EVP_CipherFinal_ex(&sCtx, puchOutput+nLenOfOut , &templen))
				{
					EVP_CIPHER_CTX_cleanup(&sCtx);
					goto err3;
				}
				nLenOfOut += templen;
				nIsCallFinal = 1;
			}
			if(0 != WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
			{
				EVP_CIPHER_CTX_cleanup(&sCtx);
				goto err2;
			}
		}
		memset(puchOutput, 0, MY_MAX_BUFFER_SIZE);
	
		if (nLenOfIn < MY_MAX_BUFFER_SIZE / 2 && nFinalable == 1 && nIsCallFinal == 0)
		{
			if (!EVP_CipherFinal_ex(&sCtx, puchOutput , &nLenOfOut))
			{
				EVP_CIPHER_CTX_cleanup(&sCtx);
				goto err3;
			}
			EVP_CIPHER_CTX_cleanup(&sCtx);
			if (nLenOfOut != 0)
			{
				if(0 != WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
				{
					goto err2;
				}
			}
		}
	}
	else if ( 0 == strcmp(pchMode, "decrypt"))
	{
		
		const EVP_CIPHER *psCipher = EVP_get_cipherbyname(pchAlgorithom);  //获取算法对应的const EVP_CIPHER*
		if (NULL == psCipher)
		{
			printf("不支持算法:%s\n",pchAlgorithom);
			goto err2;
		}
		EVP_CIPHER_CTX sCtx;                     //加密使用的上下文
		EVP_CIPHER_CTX_init(&sCtx);            //初始化上下文
		
		int nFinalable = 0;
		int nIsCallFinal = 0;

		if (0 == EVP_CipherInit_ex(&sCtx, psCipher, NULL,(unsigned char*)pchKey, (unsigned char*)pchInitVec, 0))
		{
			EVP_CIPHER_CTX_cleanup(&sCtx);
			goto err3;
		}
		char _format[1]={0};
		while ( (nLenOfIn = ReadAccordingFormat(nFdIn,pchFormat, puchInput, MY_MAX_BUFFER_SIZE)) > 0)
		{
			if (!EVP_CipherUpdate(&sCtx, puchOutput, &nLenOfOut, puchInput, nLenOfIn))
			{
				EVP_CIPHER_CTX_cleanup(&sCtx);
				goto err3;
			}
			nFinalable = 1;
			if (nLenOfIn < MY_MAX_BUFFER_SIZE / 2 && nFinalable == 1)
			{
				int templen = 0;
				if (!EVP_CipherFinal_ex(&sCtx, puchOutput+nLenOfOut , &templen))
				{
					EVP_CIPHER_CTX_cleanup(&sCtx);
					goto err3;
				}
				nLenOfOut += templen;
				nIsCallFinal = 1;
			}
			if(0 != WriteAccordingFormat(nFdOut, _format, puchOutput, nLenOfOut))
			{
				EVP_CIPHER_CTX_cleanup(&sCtx);
				goto err2;
			}
		}
		memset(puchOutput, 0, MY_MAX_BUFFER_SIZE);
	
		if (nLenOfIn < MY_MAX_BUFFER_SIZE / 2 && nFinalable == 1 && nIsCallFinal == 0)
		{
			if (!EVP_CipherFinal_ex(&sCtx, puchOutput , &nLenOfOut))
			{
				EVP_CIPHER_CTX_cleanup(&sCtx);
				goto err3;
			}
			EVP_CIPHER_CTX_cleanup(&sCtx);
			if (nLenOfOut != 0)
			{
				if(0 != WriteAccordingFormat(nFdOut, _format, puchOutput, nLenOfOut))
				{
					goto err2;
				}
			}
		}
	}
	else if (0 == strcmp(pchMode, "digest")) 
	{
		const EVP_MD* psMD = EVP_get_digestbyname(pchAlgorithom);
		if (psMD == NULL)
		{
			printf("不支持算法:%s\n",pchAlgorithom);
			goto err2;
		}
		EVP_MD_CTX ctx;
		EVP_MD_CTX_init(&ctx);
		if(EVP_DigestInit_ex(&ctx, psMD ,NULL) != 1)
		{
			EVP_MD_CTX_cleanup(&ctx);
			goto err3;
		}
		while ((nLenOfIn = read(nFdIn, puchInput, MY_MAX_BUFFER_SIZE)) > 0)
		{
			
			if (EVP_DigestUpdate(&ctx, puchInput, nLenOfIn) != 1)
			{
				EVP_MD_CTX_cleanup(&ctx);
				goto err3;
			}
		}
		if (EVP_DigestFinal_ex(&ctx, puchOutput, (unsigned int*)&nLenOfOut) != 1)
		{
			EVP_MD_CTX_cleanup(&ctx);
			goto err3;
		}
		EVP_MD_CTX_cleanup(&ctx);
		if (0 != WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
		{
			goto err2;
		}
	}
	else if (0 == strcmp(pchMode, "hmac")) 
	{
		const EVP_MD* psMD = EVP_get_digestbyname(pchAlgorithom);
		if (psMD == NULL)
		{
			printf("不支持算法:%s\n",pchAlgorithom);
			goto err2;
		}
		
		HMAC_CTX ctx;
		HMAC_CTX_init(&ctx);
	
		if (!HMAC_Init_ex(&ctx, pchKey, strlen((char*)pchKey), psMD, NULL))
		{
			HMAC_CTX_cleanup(&ctx);
			goto err3;
		}
		while(( nLenOfIn = read(nFdIn, puchInput, MY_MAX_BUFFER_SIZE)) > 0)
		{
			if (!HMAC_Update(&ctx, puchInput, nLenOfIn))
			{
				HMAC_CTX_cleanup(&ctx);
				goto err3;
			}
		}
		if (!HMAC_Final(&ctx, puchOutput, (unsigned int*)&nLenOfOut))
		{
			HMAC_CTX_cleanup(&ctx);
			goto err3;
		}
		HMAC_CTX_cleanup(&ctx);
		if (0 != WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
		{
			goto err2;
		}
	}
	close(nFdIn);
	if( nFdOut != STDOUT_FILENO)
	{
		close(nFdOut);
	}
	EVP_cleanup();
	ERR_free_strings();
	return 0;
err0: 
	return -1;
err1: 
	close(nFdIn);
	return -1;
err2: 
	close(nFdIn);
	if( nFdOut != STDOUT_FILENO)
	{
		close(nFdOut);
	}
	return -1;
err3:
	nErr = ERR_get_error();
	ERR_error_string_n(nErr, ErrorInfo, MY_MAX_BUFFER_SIZE-1);
	printf("function call failed:%s\n",ErrorInfo);
	goto err2;
}


int main(int argc, char *argv[])
{

	if (0 != HandleCommandArgument(argc, argv))
	{
		printf("failed\n");
		return -1;
	}
	else
	{
		printf("success\n");
		return 0;
	}
}
