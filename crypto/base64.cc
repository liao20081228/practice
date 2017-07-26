/*************************************************************************
    > File Name: base64.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月25日 星期二 14时28分03秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class CBase64
{
	public:
		CBase64(void);
	public:
		unsigned char* encoding(const unsigned char* pcuchScource, unsigned long lnLen, unsigned char* puchDestination);
		unsigned char* decoding(const unsigned char* pcuchScource, unsigned long lnLen, unsigned char* puchDestination);
	private:
		map<unsigned char,char> __cm_mpBase64LookTable;
		map<char, unsigned char> __cm_mpReverseLookTable;
};

CBase64::CBase64(void)
{
	for(unsigned char i = 0; i < 26; i++)
	{
		__cm_mpBase64LookTable.emplace(i, 65 + i);
		__cm_mpReverseLookTable.emplace(static_cast<char>(65 + i),i);
		__cm_mpBase64LookTable.emplace(i + 26,97 + i);
		__cm_mpReverseLookTable.emplace(static_cast<char>(97 + i),i + 26);
		if (i<10)
		{
			__cm_mpBase64LookTable.emplace(i + 52,48 + i);
			__cm_mpReverseLookTable.emplace(static_cast<char>(48 + i),i + 52);
		}
	}

	__cm_mpBase64LookTable.emplace(62, '+');
	__cm_mpBase64LookTable.emplace(63, '/');
	__cm_mpReverseLookTable.emplace('+', 62);
	__cm_mpReverseLookTable.emplace('/', 63);
}

unsigned char*
CBase64::encoding(const unsigned char* pcuchScource, unsigned long lnLen, unsigned char* puchDestination)
{
	for (unsigned long i = 0, j = 0; i < lnLen; i += 3, j += 4)
	{
		puchDestination[j] = __cm_mpBase64LookTable[pcuchScource[i] >> 2 & 0x3f];
		if (i+1 >= lnLen)
		{
			puchDestination[j+1] = __cm_mpBase64LookTable[(pcuchScource[i] << 4 & 0x30)]; 
			puchDestination[j+2] = '=';
			puchDestination[j+3] = '=';
			break;
		}
		puchDestination[j+1] = __cm_mpBase64LookTable[(pcuchScource[i] << 4 & 0x30) | (pcuchScource[i+1] >> 4 & 0x0f)];
		if (i+2 >= lnLen)
		{
			puchDestination[j+2] = __cm_mpBase64LookTable[(pcuchScource[i+1] << 2 & 0x3c)]; 
			puchDestination[j+3] = '=';
			break;
		}
		puchDestination[j+2] = __cm_mpBase64LookTable[(pcuchScource[i+1] << 2 & 0x3c) | (pcuchScource[i+2] >> 6 & 0x03)];
		puchDestination[j+3] = __cm_mpBase64LookTable[pcuchScource[i+2] & 0x3f];
	}
	return puchDestination;
}
unsigned char*
CBase64::decoding(const unsigned char* pcuchScource, unsigned long lnLen, unsigned char* puchDestination)
{
	for(unsigned long i = 0, j = 0; i < lnLen; i += 4,j += 3)
	{
		puchDestination[j] = (__cm_mpReverseLookTable[pcuchScource[i]] << 2 & 0xfc) | (__cm_mpReverseLookTable[pcuchScource[i + 1]] >> 4 & 0x03);
		if (pcuchScource[i + 2] == '=')
		{
			break;
		}
		puchDestination[j + 1] = (__cm_mpReverseLookTable[pcuchScource[i + 1]] << 4 & 0xf0) | (__cm_mpReverseLookTable[pcuchScource[i + 2]] >> 2 & 0x0f);
		if (pcuchScource[i + 3] == '=')
		{
			break;
		}
		puchDestination[ j + 2] = (__cm_mpReverseLookTable[pcuchScource[i + 2]] << 6 & 0xc0) | __cm_mpReverseLookTable[pcuchScource[i + 3]];
	}
	return puchDestination;
}


int main(void)
{
	char data[]="Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
	char rdata[500] = {'\0'};
	cout << "待编码数据:" << endl << data <<endl;
	cout << endl;
	
	CBase64 base64;
	base64.encoding(reinterpret_cast<unsigned char*>(data), strlen(data), reinterpret_cast<unsigned char*>(rdata));
	cout << "编码后数据：" << endl << rdata <<endl;
	cout << endl;
	
	::bzero(data, sizeof(data));
	base64.decoding(reinterpret_cast<unsigned char*>(rdata), strlen(rdata), reinterpret_cast<unsigned char*>(data));
	cout << "解码后数据：" << endl << data <<endl;
	cout << endl;
	return 0;
}
