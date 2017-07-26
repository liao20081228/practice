/*************************************************************************
    > File Name: RC4.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月25日 星期二 12时49分35秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class CRC4
{
	public:
		CRC4(unsigned int nLenOfSbox);
		~CRC4(void);
	public:
		void crypto(const unsigned char* puchData, unsigned long lnLenOfData, const unsigned char* puchKey, unsigned int nLenOfKey, unsigned char* puchCiphertext);
		void init(const unsigned char* puchKey, unsigned int nLenOfKey);
	private:
		unsigned int __cm_nLenOfSbox;
		bool __cm_bKeyIsExist;
		vector<unsigned char> __cm_veNewKey;
		vector<unsigned char> __cm_veSbox;
};


inline
CRC4::CRC4(unsigned int nLenOfSbox)
	: __cm_nLenOfSbox(nLenOfSbox)
	, __cm_bKeyIsExist(false)
{
	__cm_veSbox.resize(__cm_nLenOfSbox,'\0');
	__cm_veNewKey.resize(__cm_nLenOfSbox,'\0');
}


inline
CRC4::~CRC4(void)
{
}


void
CRC4::init(const unsigned char* puchKey, unsigned int nLenOfKey)
{
	unsigned int i = 0;
	for (i = 0 ;i < __cm_nLenOfSbox; ++i)
	{
		__cm_veSbox[i] = i; //初始化sbox
		__cm_veNewKey[i] = puchKey[i % nLenOfKey]; //将密钥扩展到与sbox一样长度
	}
	
	unsigned int j = 0;
	for (i = 0; i < __cm_nLenOfSbox; ++i)
	{
		j = (j + __cm_veSbox[i] + __cm_veNewKey[i]) % __cm_nLenOfSbox;
		std::swap(__cm_veSbox[i], __cm_veSbox[j]); //用密钥将sbox扰乱
	}
	__cm_bKeyIsExist = true;
}


void
CRC4::crypto(const unsigned char* puchData, unsigned long lnLenOfData, const unsigned char* puchKey, unsigned int nLenOfKey, unsigned char* puchCiphertext)
{
	init(puchKey,nLenOfKey);
	assert(__cm_bKeyIsExist);
	unsigned int i = 0,
				 j = 0,
				 t = 0;
	unsigned long k = 0;
	for (k = 0; k < lnLenOfData; ++k)
	{
		i = (i + 1) % __cm_nLenOfSbox;
		j = (j + __cm_veSbox[i]) % __cm_nLenOfSbox;
		std::swap(__cm_veSbox[i], __cm_veSbox[j]);
		t = (__cm_veSbox[i] + __cm_veSbox[j]) % __cm_nLenOfSbox; //生成伪随机数序列,也就是流密钥
		puchCiphertext[k] = puchData[k] ^ __cm_veSbox[t]; //异或运算,两次异或就回到原来数据
	}
}


int main()
{
	char plaintext[100] = "the word is best beautiful in the earth , 我爱你";
	char ciphertext[100] = "";
	char Key[] = "youaresb";

	//encry
	CRC4 rc4(256);
	rc4.crypto(reinterpret_cast<unsigned char*>(plaintext), strlen(plaintext), reinterpret_cast<unsigned char*>(Key),static_cast<unsigned int>(std::strlen(Key)), reinterpret_cast<unsigned char*>(ciphertext));
	cout << ciphertext << endl;
	
	//decry
	rc4.crypto(reinterpret_cast<unsigned char*>(ciphertext), strlen(ciphertext), reinterpret_cast<unsigned char*>(Key),static_cast<unsigned int>(std::strlen(Key)), reinterpret_cast<unsigned char*>(plaintext));
	cout << plaintext << endl;
}
