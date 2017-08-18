/*****************************************************************************80
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月18日 星期五 12时29分35秒
*******************************************************************************/
/*myhead_c.h is a headfile in “/usr/local/include”,include all headfiles*/
#include"openssl_cmd.h"
int main(int argc, char *argv[])
{
	OpensSSL_LoadAlgorithmAndErrorString();
	if (0 != HandleCommandArgument(argc, argv))
	{
		sprintf(g_pchErrorInformation,"HandleCommandArgument failed");
		goto err;
	}
	OpensSSL_UnLoadAlgorithmAndErrorString();
	return 0;
err:
	OpenSSL_PrintErrorInformation();
	OpensSSL_UnLoadAlgorithmAndErrorString();
	return -1;
}

