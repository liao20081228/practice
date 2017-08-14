/*****************************************************************************80
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月08日 星期二 12时55分34秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/

#include"openssl_evp_base64.h"

int main()
{
	Openssl_evp::vector<unsigned char> in = {'a','b'};
	Openssl_evp::CBase64 base64;
	Openssl_evp::vector<unsigned char> out = base64.Encode(in,true,true);
	for(unsigned char e : out)
	{
		std::cout<<(char)e;
	}
	
	in.clear();
	std::cout<<std::endl;

	in = base64.Decode(out,true,true);
	for(unsigned char e : in)
	{
		std::cout<<(char)e;
	}
}
