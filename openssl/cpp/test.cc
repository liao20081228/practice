/*****************************************************************************80
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月08日 星期二 12时55分34秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#include"openssl_evp_cpp.h"
int main(void)
{

	int nFdIn1= open("./openssl_evp_cpp.h",O_RDONLY);
	int nFdOut1=open("./test1", O_WRONLY|O_CREAT|O_TRUNC,0644);
	int nFdOut2=open("./test2", O_WRONLY|O_CREAT|O_TRUNC,0644);
	int nFdOut3=open("./test3", O_WRONLY|O_CREAT|O_TRUNC,0644);
	int nFdOut4=open("./test4", O_WRONLY|O_CREAT|O_TRUNC,0644);
	
	unsigned char bufferIn[1024];
	unsigned char bufferOut[1024*2];
	char name1[20]="des-cbc";
	char name2[20]="aes-128-cbc";
	char name3[20]="md5";
	char name4[20]="sha1";
	char key1[17]={0};
	char iv1[17] ={0};
	
	int inLen = 0;
	int outLen= 0;
	int outLen2 = 0;
try{
	Openssl_evp::CCipher cipher(name1, (unsigned char*)key1, (unsigned char*)iv1);
	Openssl_evp::CDigestAndHmac digest(name3);
	
	while((::bzero(bufferIn,1024), inLen = ::read(nFdIn1, bufferIn, 1024)) > 0)
	{
		bool flag = false;
		if ( inLen < 1024)
		{
			flag = true;
		}
		outLen = cipher.Cipher(bufferIn, inLen, bufferOut, flag);
		::write(nFdOut1,bufferOut, outLen);
		if ((outLen2 = digest.Digest(bufferIn,inLen,bufferOut,flag)) > 0)
		{
			for (int i = 0; i < outLen2;++i )
			{
				if(bufferOut[i]<16)
				{
					dprintf(nFdOut3, "0%x",bufferOut[i]);
				}
				else
				{
					dprintf(nFdOut3,"%x",bufferOut[i]);
				}
			}
		}
	}
	cipher.Change(name2,nullptr,nullptr,1,nullptr);
	digest.Change(name4,nullptr,nullptr,0);
	
	::lseek(nFdIn1,0,SEEK_SET);
	while((::bzero(bufferIn,1024), inLen = ::read(nFdIn1, bufferIn, 1024)) > 0)
	{
		bool flag = false;
		if ( inLen < 1024)
		{
			flag = true;
		}
		outLen = cipher.Cipher(bufferIn, inLen, bufferOut, flag);
		::write(nFdOut2,bufferOut, outLen);
		if ((outLen2 = digest.Digest(bufferIn,inLen,bufferOut,flag)) > 0)
		{
			for (int i = 0; i < outLen2;++i )
			{
				if(bufferOut[i]<16)
				{
					dprintf(nFdOut4, "0%x",bufferOut[i]);
				}
				else
				{
					dprintf(nFdOut4,"%x",bufferOut[i]);
				}
			}
		}
	}
}
catch(std::invalid_argument&a )
{
	cout<<a.what()<<endl;
}
catch(std::runtime_error&b)
{
	cout<<b.what()<<endl;
	
}
	close(nFdIn1);
	close(nFdOut1);
	close(nFdOut2);
	close(nFdOut3);
	close(nFdOut4);
	return 0;
}
