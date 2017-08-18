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

