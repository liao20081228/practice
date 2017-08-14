/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_getopt_cmdarg.h
Related Files  : no
File Function  : base64编解码
Author         : liaoweizhi
Department     : 技术研发总部
Email          : liaowz@koal.com
Version        : 0.0
--------------------------------------------------------------------------------
Note           : 采用c++的方式
--------------------------------------------------------------------------------
Date:          : 2017/07/30
Version:       : 0.0
Modifier       : no
Department     : no
Email          : no
Changes        : create
*******************************************************************************/

#ifndef __MY_OPENSSL_EVP_GETOPT_CMDARG_H
#define __MY_OPENSSL_EVP_GETOPT_CMDARG_H

#ifndef IN
#define IN
#endif /* end of include guard: IN */

#ifndef OUT
#define OUT
#endif /* end of include guard: OUT */

#include<unistd.h>
#include<getopt.h>
#include<cassert>
#include<array>
#include<vector>
#include<iostream>
using std::array;
using std::vector;
using std::string;
using std::cout;
using std::endl;
namespace Openssl_evp
{

class CCommandArgument
{
	public:
		CCommandArgument(IN int argc, IN char* argv[]);
		array<string,7> GetArg(void);
	private:
		void ReadArgument(void);
		void ShowHelpInfo(void) const;
		void JudgeAagValid(void) const;
	private:
		int __cm_nArgc;
		char** __cm_ppArgv;

		array<string,7> __cm_arArgument;
		bool   __cm_bIsHelp;
		struct option long_options[9] = /* 长选项定义*/
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
};

}
#endif /* end of include guard: __MY_OPENSSL_EVP_GETOPT_CMDARG_H */

inline
Openssl_evp::CCommandArgument::CCommandArgument(IN int argc, IN char* argv[])
	: __cm_nArgc(argc)
	, __cm_ppArgv(argv)
	, __cm_bIsHelp(false)
{
	for (string& e:__cm_arArgument)
	{
		e.clear();
	}
}

void
Openssl_evp::CCommandArgument::ReadArgument(void)
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	while ((chOption = ::getopt_long(__cm_nArgc, __cm_ppArgv, "m:a:k:v:i:o::f:h", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'm' : __cm_arArgument[0].append(optarg);break;
			case 'a' : __cm_arArgument[1].append(optarg);break;
			case 'k' : __cm_arArgument[2].append(optarg);break;
			case 'v' : __cm_arArgument[3].append(optarg);break;
			case 'i' : __cm_arArgument[4].append(optarg);break;
			case 'o' : __cm_arArgument[5].append(optarg);break;
			case 'f' : __cm_arArgument[6].append(optarg);break;
			case 'h' : ShowHelpInfo(); __cm_bIsHelp = true; break;
			default  : cout << "Unknown option:" << chOption << endl; ShowHelpInfo();return; 
		}
	}
	JudgeAagValid();
}

void
Openssl_evp::CCommandArgument::ShowHelpInfo(void) const
{
	cout << "help info" << endl
		<< "-m/--mode 计算模式，包括 encrypt | decrypt | digest | hmac 这四种"<< endl
		<< "-a/--algorithom 算法名称，包括 RC4 | AES-128-CBC | AES-128-ECB | AES-256-CBC  \
		| AES-128-ECB | MD5 | SHA1 | SHA256 这些" << endl
		<< "-k/--key HEX(16进制)格式的密钥值，比如 0001020304050600708090A0B0C0D0E0F 表示一个16字节的密钥" << endl
		<< "-v/--iv HEX(16进制)格式的初始化向量" << endl
		<< "-i/--input 输入文件 " << endl
		<< "-o/--output 输出文件" << endl
		<< "-f/--format 输出/输入格式，包括 BINARY | HEX | BASE64 这三种，默认为BINARY" << endl
		<< "-h/--help 显示使用帮助" << endl
		<< endl
		<< "使用示例1：对称加密（使用全0的密钥和全0的IV）" << endl
		<< "xxxxx -m encrypt -a AES-128-CBC -k 00000000000000000000000000000000 -v \
		00000000000000000000000000000000 -i in.txt -o out.b64 -f BASE64" << endl

		<< "使用示例2：摘要计算" << endl
		<< "xxxxx -m digest -a SHA1 -i in.txt -o digest.hex -f HEX" << endl
		<< endl
		<< "使用示例3：HMAC计算(使用一个5字节的KEY)" << endl
		<< "xxxxx -m hmac -a SHA1 -i in.txt -k 0000000000 -o hmac.hex -f BINARY" << endl;
}


void
Openssl_evp::CCommandArgument::JudgeAagValid(void) const
{
	if (__cm_bIsHelp == false)
	{
		assert(!__cm_arArgument[0].empty() && !__cm_strAlgorithm[1].empty() 
				&& !__cm_arArgument[4].empty() && !__cm_arArgument[6].empty());

		assert(__cm_arArgument[0].compare("encrypt") == 0 || __cm_arArgument[0].compare("decrypt") == 0 
				|| __cm_arArgument[0].compare("digest") == 0 || __cm_arArgument[0].compare("hamc") == 0); 

		assert(__cm_arArgument[6].compare("BINARY") == 0 || __cm_arArgument[6].compare("HEX") == 0 
			||__cm_arArgument[6].compare("BASE64") == 0);
	}
	else
	{
		std::exit(0);
	}
}

array<string,7> 
Openssl_evp::CCommandArgument::GetArg(void)  
{
	ReadArgument();
	return __cm_arArgument;
}

