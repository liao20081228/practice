/*****************************************************************************80
  > File Name: getopt.cpp
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年08月02日 星期三 10时15分18秒
 *******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#include"openssl_evp_c.h"
#include<getopt.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<assert.h>
using std::cout;
using std::cin;
using std::endl;

void 
ShowHelpInfo(void)
{
	cout << "help info" << endl
		<< "-m/--mode 计算模式，包括 encrypt | decrypt | digest | hmac 这四种"<< endl
		<< "-a/--algorithom 算法名称，包括 RC4 | AES-128-CBC | AES-128-ECB | AES-256-CBC | AES-128-ECB | MD5 | SHA1 | SHA256 这些" << endl
		<< "-k/--key HEX(16进制)格式的密钥值，比如 0001020304050600708090A0B0C0D0E0F 表示一个16字节的密钥" << endl
		<< "-v/--iv HEX(16进制)格式的初始化向量" << endl
		<< "-i/--input 输入文件 " << endl
		<< "-o/--output 输出文件" << endl
		<< "-f/--format 输出/输入格式，包括 BINARY | HEX | BASE64 这三种，默认为BINARY" << endl
		<< "-h/--help 显示使用帮助" << endl
		<< endl
		<< "使用示例1：对称加密（使用全0的密钥和全0的IV）" << endl
		<< "xxxxx -m encrypt -a AES-128-CBC -k 00000000000000000000000000000000 -v 00000000000000000000000000000000 -i in.txt -o out.b64 -f BASE64" << endl

		<< "使用示例2：摘要计算" << endl
		<< "xxxxx -m digest -a SHA1 -i in.txt -o digest.hex -f HEX" << endl
		<< endl
		<< "使用示例3：HMAC计算(使用一个5字节的KEY)" << endl
		<< "xxxxx -m hmac -a SHA1 -i in.txt -k 0000000000 -o hmac.hex -f BINARY" << endl;
}

int 
WriteAccordingFormat(IN int nFdOut, IN const char*format, IN const unsigned char* pchdata, IN int nLen)
{
	if (std::strcmp(format, "BINARY") == 0)
	{
		if (-1 == ::write(nFdOut, pchdata, nLen))
		{
			std::perror("write() failed or occur error");
			return -1;
		}
	}
	else if (std::strcmp(format, "HEX") == 0) 
	{
		for (int i = 0; i < nLen; ++i) 
		{
			if (pchdata[i] < 16)
			{
				dprintf(nFdOut, "0");
				dprintf(nFdOut,"%x",pchdata[i]);
			}
			else
			{
				dprintf(nFdOut,"%x",pchdata[i]);
			}
		}
	}
	else if (std::strcmp(format, "BASE64") == 0)
	{
		unsigned char Output[1024*4] = {0};
		int nLenofOut = 0;
		::OpenSSL_BASE64_encode(pchdata, nLen, Output, &nLenofOut);
		if (-1 == ::write(nFdOut, Output, nLenofOut))
		{
			std::perror("write() failed or occur error");
			return -1;
		}
	}
	return 0;
}

int 
ReadCommandArgument(IN int argc, IN char* argv[],  OUT char* pchMode, 
					OUT char* pchAlgorithom,  OUT char* pchKey, 
					OUT char* pchInitVec,  OUT char* pchInputFile, 
					OUT char* pchOutputFile, OUT char* pchFormat)
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	int IsHelp = 0;
	static struct option long_options[] = /* 长选项定义*/
	{
		{"mode",       1,    0,   'm'},
		{"algorithom", 1,    0,   'a'},
		{"key",        1,    0,   'k'},
		{"iv",         1,    0,   'v'},
		{"input",      1,    0,   'i'},
		{"output",     2,    0,   'o'},
		{"format",     1,    0,   'f'},
		{"help",       0 ,   0,   'h'},
		{0, 0, 0, 0}
	};

	while ((chOption = ::getopt_long(argc, argv, "m:a:k:v:i:o::f:h", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'm' : std::strcpy(pchMode, optarg); break;
			case 'a' : std::strcpy(pchAlgorithom, optarg); break;
			case 'k' : std::strcpy(pchKey, optarg); break;
			case 'v' : std::strcpy(pchInitVec, optarg); break;
			case 'i' : std::strcpy(pchInputFile, optarg); break;
			case 'o' : std::strcpy(pchOutputFile, optarg); break;
			case 'f' : std::strcpy(pchFormat, optarg); break;
			case 'h' : ShowHelpInfo(); IsHelp = 1; std::exit(-1);
			default  : cout << "Unknown option:" << chOption << endl; ShowHelpInfo(); return -1;
		}
	}
	if (IsHelp == 0)
	{
		assert(std::strlen(pchMode) && std::strlen(pchAlgorithom) 
				&& std::strlen(pchInputFile) && std::strlen(pchFormat));
		assert(std::strcmp(pchMode, "encrypt") == 0 || std::strcmp(pchMode, "decrypt") == 0 
				|| std::strcmp(pchMode, "digest") == 0 || std::strcmp(pchMode, "hmac") == 0); 
		assert(std::strcmp(pchFormat, "BINARY") == 0 || std::strcmp(pchFormat, "HEX") == 0 
				|| std::strcmp(pchFormat, "BASE64") == 0);
	}
	return 0;
}


int
HandleCommandArgument(IN int argc, IN char* argv[])
{
	::OpenSSL_add_all_algorithms();
	::ERR_load_crypto_strings();
	char pchMode[10] = {'\0'};
	char pchAlgorithom[20] = {'\0'};
	char pchKey[EVP_MAX_KEY_LENGTH + 1] = {'\0'};
	char pchInitVec[EVP_MAX_IV_LENGTH + 1] = {'\0'};
	char pchInputFile[256] = {'\0'};
	char pchOutputFile[256] = {'\0'};
	char pchFormat[10] = {'\0'};

	if (0 != ReadCommandArgument(argc, argv, pchMode, pchAlgorithom, 
			pchKey, pchInitVec,pchInputFile, pchOutputFile, pchFormat))
	{
		return -1;
	}
		
	int nFdIn = ::open(pchInputFile, O_RDONLY);
	if (nFdIn == -1)
	{
		std::perror("open() failed or occur error");
		return -1;
	}

	int nFdOut = STDOUT_FILENO;
	if (std::strlen(pchOutputFile) != 0)
	{
		nFdOut = ::open(pchOutputFile, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, 0755);
		if (nFdOut == -1)
		{
			std::perror("open() failed or occur error");
			::close(nFdIn);
			return -1;
		}
	}


	unsigned char puchInput[10240];
	unsigned char puchOutput[10240 * 2];
	int nLenOfIn  = 0;
	int nLenOfOut = 0;


	if (0 == std::strcmp(pchMode, "encrypt") || 0 == std::strcmp(pchMode, "decrypt"))
	{
		int IsEncry = 1;
		if (0 == std::strcmp(pchMode, "decrypt"))
		{
			IsEncry = 0;
		}
		if (std::strlen(pchKey) != 0 && std::strlen(pchInitVec) != 0)
		{
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
		
		while ((::bzero(puchInput,sizeof(puchInput)), ::bzero(puchOutput,sizeof(puchOutput)),
				nLenOfIn = ::read(nFdIn, puchInput, 10240)) > 0)
		{
			if (0 != ::OpenSSL_Cipher(pchAlgorithom, nullptr, reinterpret_cast<unsigned char*>(pchKey), 
							reinterpret_cast<unsigned char*>(pchInitVec), puchInput, nLenOfIn, 
							puchOutput, &nLenOfOut, IsEncry))
			{
				::close(nFdIn);
				if( nFdOut != STDOUT_FILENO)
				{
					::close(nFdOut);
				}
				return -1;
			}
			if(0 != ::WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
			{
				::close(nFdIn);
				if( nFdOut != STDOUT_FILENO)
				{
					::close(nFdOut);
				}
				return -1;
			}
		}
	}
	else if (0 == std::strcmp(pchMode, "digest")) 
	{
		char ErrorInfo[1024] = {0};
		int nErr = 0;
		const EVP_MD* psMD = ::EVP_get_digestbyname(pchAlgorithom);
		if (psMD == nullptr)
		{
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}

		int nLenOfIn  = 0;
		int nLenOfOut = 0;
		
		EVP_MD_CTX ctx;
		::EVP_MD_CTX_init(&ctx);
		if(::EVP_DigestInit_ex(&ctx, psMD ,nullptr) != 1)
		{
			nErr = ::ERR_get_error();
			::ERR_error_string(nErr, ErrorInfo);
			cout << "EVP_DigestInit_ex failed" << endl;
			::EVP_MD_CTX_cleanup(&ctx);
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
		while ((::bzero(puchInput,sizeof(puchInput)), nLenOfIn = ::read(nFdIn, puchInput, 10240)) > 0)
		{
			
			if (::EVP_DigestUpdate(&ctx, puchInput, nLenOfIn) != 1)
			{
				nErr = ::ERR_get_error();
				::ERR_error_string(nErr, ErrorInfo);
				cout << "EVP_DigestUpdate failed" << endl;
				::EVP_MD_CTX_cleanup(&ctx);
				::close(nFdIn);
				if( nFdOut != STDOUT_FILENO)
				{
					::close(nFdOut);
				}
				return -1;
			}
		}
		if (::EVP_DigestFinal_ex(&ctx, puchOutput, reinterpret_cast<unsigned int*>(&nLenOfOut)) != 1)
		{
			nErr = ::ERR_get_error();
			::ERR_error_string(nErr, ErrorInfo);
			cout << "EVP_DigestUpdate failed" << endl;
			::EVP_MD_CTX_cleanup(&ctx);
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
		::EVP_MD_CTX_cleanup(&ctx);
		if (0 != ::WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
		{
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
	}
	else if (0 == std::strcmp(pchMode, "hmac")) 
	{
		char ErrorInfo[1024] = {0};
		int nErr = 0;
		const EVP_MD* psMD = ::EVP_get_digestbyname(pchAlgorithom);

		if (std::strlen(pchKey) != 0 && nullptr != psMD)
		{
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
		
		HMAC_CTX ctx;
		::HMAC_CTX_init(&ctx);
	
		if (!::HMAC_Init_ex(&ctx, pchKey, std::strlen(pchKey), psMD, nullptr))
		{
			nErr = ::ERR_get_error();
			::ERR_error_string(nErr, ErrorInfo);
			cout << "HMAC_Init_ex failed" << ErrorInfo << endl;
			::HMAC_CTX_cleanup(&ctx);
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
		while((::bzero(puchInput,sizeof(puchInput)), nLenOfIn = ::read(nFdIn, puchInput, 10240)) > 0)
		{
			if (!::HMAC_Update(&ctx, puchInput, nLenOfIn))
			{
				nErr = ::ERR_get_error();
				::ERR_error_string(nErr, ErrorInfo);
				cout << "HMAC_Update failed" << ErrorInfo << endl;
				::HMAC_CTX_cleanup(&ctx);
				::close(nFdIn);
				if( nFdOut != STDOUT_FILENO)
				{
					::close(nFdOut);
				}
				return -1;
			}
		}
		if (!::HMAC_Final(&ctx, puchOutput, reinterpret_cast<unsigned int*>(&nLenOfOut)))
		{
			nErr = ::ERR_get_error();
			::ERR_error_string(nErr, ErrorInfo);
			cout << "HMAC_Final failed" << ErrorInfo << endl;
			::HMAC_CTX_cleanup(&ctx);
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
		::HMAC_CTX_cleanup(&ctx);
		if (0 != ::WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
		{
			::close(nFdIn);
			if( nFdOut != STDOUT_FILENO)
			{
				::close(nFdOut);
			}
			return -1;
		}
	}
	::close(nFdIn);
	if( nFdOut != STDOUT_FILENO)
	{
		::close(nFdOut);
	}
	::EVP_cleanup();
	::ERR_free_strings();
	return 0;
}


int main(int argc, char *argv[])
{

	if (0 != HandleCommandArgument(argc, argv))
	{
		cout << "failed" << endl;
		return -1;
	}
	return 0;
}
