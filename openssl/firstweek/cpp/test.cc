/*****************************************************************************80
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月08日 星期二 12时55分34秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/

#include"openssl_evp_digest.h"

int main()
{
	{
		unsigned char input[10240];
		unsigned char output[100]= {0};
		Openssl_evp::CDigest digest1("md5");

		int nfd = ::open("./cpp_zh_cn.docset.zip", O_RDONLY);
		
		int inlen = ::read(nfd, input, 10240); 
		if (inlen < 10240)
		{
			digest1.Digest(input, inlen, output, true, true);
			for ( int i = 0 ;i<16;++i )
			{
				if(output[i]<16)
				{
					printf("0");
					printf("%x",output[i]);
				}
				else
				{
					printf("%x",output[i]);
				}
			}
		}
		else
		{

			digest1.Digest(input, inlen, output, true, false);
		}

		while ((std::memset(input,0,10240), inlen =::read(nfd, input, 10240)) > 0)
		{
			if ( inlen < 10240 )
			{
			digest1.Digest(input, inlen, output, false, true);
			for ( int i = 0 ;i<16;++i )
			{
				if(output[i]<16)
				{
					printf("0");
					printf("%x",output[i]);
				}
				else
				{
					printf("%x",output[i]);
				}
			}

			}
			else
			{
				digest1.Digest(input, inlen, output, false, false);
			}
		}
		close(nfd);
	}
}

