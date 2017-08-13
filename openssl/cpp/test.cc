/*****************************************************************************80
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月08日 星期二 12时55分34秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include"openssl_evp_cipher.h"
#include"doctest.h"

TEST_SUITE_BEGIN("基础单元测试");

TEST_CASE("CCipher类测试")
{
	char ciphername1[20] = "aes-128-cbc";
	char ciphername2[20] = "des-cbc";
	char ciphername3[20] = "md5";
	unsigned char key1[16]= {0};
	unsigned char key2[16]= {1};
	unsigned char key3[16]= {2};
	unsigned char iv1[16]= {0};
	unsigned char iv2[16]= {1};
	unsigned char iv3[16]= {2};
	std::memset(key1, 0, 16);
	std::memset(key2, 1, 16);
	std::memset(key3, 2, 16);
	std::memset(iv1, 0, 16);
	std::memset(iv2, 1, 16);
	std::memset(iv3, 2, 16);
	Openssl_evp::CCipher  cipher1(ciphername1, key1, iv1);

}
TEST_SUITE_END();
