/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_conversion.h
Related Files  : no
File Function  : 将二进制以指定进制输出或者将字符数值转为二进制
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
#ifndef __MY_OPENSSL_EVP_CONVERSION_H
#define __MY_OPENSSL_EVP_CONVERSION_H

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<exception>
#include<vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
namespace Openssl_evp
{


class CConversion
{
	public:
		string DataToStr(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN int nBase);
		vector<unsigned char> StrToData(IN const  char* pcuchInput, IN int nLenOfInput, IN int nBase);

	private:
		 string DataToHexStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 string DataToDecStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 string DataToBinStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 string DataToOctStr(IN const unsigned char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  HexStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  DecStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  BinStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
		 vector<unsigned char>  OctStrToData(IN const  char* pcuchInput, IN int nLenOfInput);
	private:
		 string __cm_strResult;
		 vector<unsigned char> __cm_veData;
};

}



string
Openssl_evp::CConversion::DataToHexStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char hex[17]="0123456789abcdef";
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		__cm_strResult.push_back(hex[pcuchInput[i] >> 4 & 0xf]);
		__cm_strResult.push_back(hex[pcuchInput[i]  & 0xf]);
	}
	return __cm_strResult;
}

string
Openssl_evp::CConversion::DataToDecStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		if (pcuchInput[i] < 10)
		{
			__cm_strResult.append("00");
			__cm_strResult.append(std::to_string(pcuchInput[i]));
		}
		else if (pcuchInput[i] < 99)
		{
			__cm_strResult.append("0");
			__cm_strResult.append(std::to_string(pcuchInput[i]));
		}
		else
		{
			__cm_strResult.append(std::to_string(pcuchInput[i]));
		}
	}
	return __cm_strResult;
}

string
Openssl_evp::CConversion::DataToOctStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char oct[9]="01234567";
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		__cm_strResult.push_back(oct[pcuchInput[i] >> 6 & 0x3]);
		__cm_strResult.push_back(oct[pcuchInput[i] >> 3 & 0x7]);
		__cm_strResult.push_back(oct[pcuchInput[i]   & 0x7]);
	}
	return __cm_strResult;

}

string
Openssl_evp::CConversion::DataToBinStr(IN const unsigned char* pcuchInput, IN int nLenOfInput)
{
	const char bin[3]="01";
	__cm_strResult.clear();
	for(int i = 0; i < nLenOfInput; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			__cm_strResult.push_back(bin[pcuchInput[i] >> (7-i) & 0x1]);
		}
	}
	return __cm_strResult;
}



vector<unsigned char> 
Openssl_evp::CConversion::HexStrToData(IN const  char* pcuchInput, IN int nLenOfInput)
{
	if ( nLenOfInput % 2 != 0 )
	{
		throw std::invalid_argument("十六进制文本长度不是2的倍数");
	}
	char temp[3] = {0};
	for (int i = 0; i < nLenOfInput; i += 2)
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		__cm_veData.push_back(std::stoi(temp, 0, 16));
	}
	return __cm_veData;
}


vector<unsigned char> 
Openssl_evp::CConversion::DecStrToData(IN const  char* pcuchInput, IN int nLenOfInput)
{
	char temp[4] = {0};
	if ( nLenOfInput % 3 != 0 )
	{
		throw std::invalid_argument("十进制文本长度不是3的倍数");
	}
	for (int i = 0; i < nLenOfInput; i += 3)
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		temp[2] = pcuchInput[i+2];
		__cm_veData.push_back(std::stoi(temp, 0, 10));
	}
	return __cm_veData;
}

vector<unsigned char> 
Openssl_evp::CConversion::OctStrToData(IN const  char* pcuchInput, IN int nLenOfInput)
{
	if ( nLenOfInput % 3 != 0 )
	{
		throw std::invalid_argument("八进制文本长度不是3的倍数");
	}
	char temp[4] = {0};
	for (int i = 0; i < nLenOfInput; i += 3)
	{
		temp[0] = pcuchInput[i];
		temp[1] = pcuchInput[i+1];
		temp[2] = pcuchInput[i+2];
		__cm_veData.push_back(std::stoi(temp, 0, 8));
	}
	return __cm_veData;

}


vector<unsigned char> 
Openssl_evp::CConversion::BinStrToData(IN const char* pcuchInput, IN int nLenOfInput)
{
	char temp[9] = {0};
	if ( nLenOfInput % 8 != 0 )
	{
		throw std::invalid_argument("二进制文本长度不是8的倍数");
	}
	for (int i = 0; i < nLenOfInput; i += 8)
	{
		for(int j = 0;j<8; j++)
		{
			temp[j]=pcuchInput[i+j];
		}
		__cm_veData.push_back(std::stoi(temp, 0, 2));
	}
	return __cm_veData;
}

string 
Openssl_evp::CConversion::DataToStr(IN const unsigned char* pcuchInput, IN int nLenOfInput, IN int nBase)
{
	switch (nBase)
	{
		case 2: return DataToBinStr(pcuchInput, nLenOfInput);
		case 8: return DataToOctStr(pcuchInput, nLenOfInput);
		case 10: return DataToDecStr(pcuchInput, nLenOfInput);
		case 16: return DataToHexStr(pcuchInput, nLenOfInput);
		default:throw std::invalid_argument("输入的进制转换不支持");
	}
}
vector<unsigned char> 
Openssl_evp::CConversion::StrToData(IN const char* pcuchInput, IN int nLenOfInput, IN int nBase)
{
	switch (nBase)
	{
		case 2: return BinStrToData(pcuchInput, nLenOfInput);
		case 8: return OctStrToData(pcuchInput, nLenOfInput);
		case 10: return DecStrToData(pcuchInput, nLenOfInput);
		case 16: return HexStrToData(pcuchInput, nLenOfInput);
		default:throw std::invalid_argument("输入的进制转换不支持");
	}
}
#endif
