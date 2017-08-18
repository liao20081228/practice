#include"./openssl_cmd.h"
void 
ShowHelpInfo(void)
{
	printf("help info\n \
			支持以下命令行参数 \n\
				-d/--digest 摘要算法（包括SHA1 | SHA256 | SHA512)，默认为SHA256\n \
				-k/--key 私钥文件（要求能自动适应PEM与DER格式）\n \
				-i/--input 输入文件 \n\
				-o/--output 输出文件\n \
				-f/--format 输出/输入格式，包括 BINARY | HEX | BASE64 这三种，默认为BINARY \n\
				-h/--help 显示使用帮助\n \
			使用示例：\n \
				xxxxx -d SHA256 -k signer.pem -i input.txt -format BASE64 -out sig.txt\n");
}


int 
WriteAccordingFormat(IN int nFdOut, IN const char*format, IN const unsigned char* pchdata, IN int nLen)
{
	if (strlen(format) == 0 || strcmp(format, "BINARY") == 0)
	{
		if (-1 == write(nFdOut, pchdata, nLen))
		{
			sprintf(g_pchErrorInformation,"write failed");
			goto err;
		}

	}
	else if (strcmp(format, "HEX") == 0) 
	{
		unsigned char temp[__MY_MAX_BUFFER_SIZE*2] = {0};
		int len = OpenSSL_BinToHex(temp, __MY_MAX_BUFFER_SIZE*2, pchdata, nLen);
		if(-1 == write(nFdOut, temp, len))
		{
			sprintf(g_pchErrorInformation,"write failed");
			goto err;
		}
	}
	else if (strcmp(format, "BASE64") == 0)
	{
		unsigned char temp[__MY_MAX_BUFFER_SIZE*2] = {0};
		int len = OpenSSL_BASE64_encode(temp, __MY_MAX_BUFFER_SIZE*2, pchdata, nLen);
		if (-1 == write(nFdOut, temp, len))
		{
			g_nErrorFlag = 0;
			sprintf(g_pchErrorInformation,"write failed");
			goto err;
		}
	}
	return 0;

err:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
}

int 
ReadCommandArgument(OUT char* pchDigetName, OUT char* pchKeyfile,
					OUT char* pchInputFile, OUT char* pchOutputFile, 
					OUT char* pchFormat,IN int argc, IN char* argv[])
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	int IsHelp = 0;
	static struct option long_options[] = /* 长选项定义*/
	{
		{"digest",     1,    0,   'd'},
		{"key",        1,    0,   'k'},
		{"input",      1,    0,   'i'},
		{"output",     1,    0,   'o'},
		{"format",     1,    0,   'f'},
		{"help",       0 ,   0,   'h'},
		{0, 0, 0, 0}
	};

	while ((chOption = getopt_long(argc, argv, "d:k:i:o:f:h", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'd' : strcpy(pchDigetName, optarg); break;
			case 'k' : strcpy(pchKeyfile, optarg); break;
			case 'i' : strcpy(pchInputFile, optarg); break;
			case 'o' : strcpy(pchOutputFile, optarg); break;
			case 'f' : strcpy(pchFormat, optarg); break;
			case 'h' : ShowHelpInfo(); IsHelp = 1; exit(-1);
			default  : printf("Unknown option:%c\n",chOption); ShowHelpInfo(); return -1;
		}
	}
	if (IsHelp == 0)
	{
		if (!(strlen(pchKeyfile)  && strlen(pchInputFile)))
		{
			sprintf(g_pchErrorInformation,"缺少 摘要算法或 输入文件");
			goto err;
		}
		if (strlen(pchFormat) != 0 && (0 == (strcmp(pchFormat, "BINARY") == 0 || strcmp(pchFormat, "HEX") == 0
			|| strcmp(pchFormat, "BASE64") == 0)))
		{
			sprintf(g_pchErrorInformation,"输入的格式不支持");
			goto err;
		}

		if (strlen(pchFormat) == 0 )
		{
			strncpy(pchFormat, "BINARY", 6);
		}

		if (strlen(pchDigetName) == 0)
		{
			strncpy(pchDigetName, "sha256", 6);
		}
	}
	return 0;
err:
	OpenSSL_PrintErrorInformation();
	return -1;
}


int
HandleCommandArgument(IN int argc, IN char* argv[])
{
	char pchDigestName[20] = {'\0'},
		 pchInputFile[256] = {'\0'},
	     pchOutputFile[256] = {'\0'},
	     pchFormat[10] = {'\0'},
		 pchKeyfile[255] = {'\0'};

	int nFdIn = 0,
		nFdOut = STDOUT_FILENO;
	
	unsigned char puchInput[__MY_MAX_BUFFER_SIZE],
				  puchOutput[__MY_MAX_BUFFER_SIZE * 2];
	
	int nLenOfIn  = 0,
		nLenOfOut = 0;
	
	EVP_PKEY *pKey;
	FILE* fpKey  = NULL;
	const EVP_MD* psMD = NULL;
	
	

	if (0 != ReadCommandArgument(pchDigestName,pchKeyfile, 
				pchInputFile, pchOutputFile, pchFormat, argc, argv))
	{
		sprintf(g_pchErrorInformation, "ReadCommandArgument failed");
		goto err0;
	}
	
	fpKey = fopen(pchKeyfile,"rb");
	if (fpKey == NULL)
	{
		sprintf(g_pchErrorInformation, "fopen keyfile  failed");
		goto err0;
	}
	
	if (NULL == PEM_read_PrivateKey(fpKey, &pKey, NULL ,NULL))
	{
		rewind(fpKey);
		if (NULL == d2i_PrivateKey_fp(fpKey,&pKey))
		{
			sprintf(g_pchErrorInformation, "read key file   failed");
			fclose(fpKey);
			goto err0;
		}
	}
	fclose(fpKey);

	if ((nFdIn = open(pchInputFile, O_RDONLY)) == -1)
	{
		sprintf(g_pchErrorInformation, "open input faile failed");
		goto err0;
	}
	if (strlen(pchOutputFile) != 0)
	{
		if ((nFdOut = open(pchOutputFile, O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, 0666)) == -1) 
		{
			sprintf(g_pchErrorInformation, "open output file  failed");
			goto err1;
		}
	}
		
	psMD = EVP_get_digestbyname(pchDigestName);
		
	if (psMD == NULL)
	{
		sprintf(g_pchErrorInformation,"不支持算法:%s",pchDigestName);
		goto err2;
	}
	EVP_MD_CTX ctx;
	EVP_MD_CTX_init(&ctx);
	if(EVP_SignInit_ex(&ctx, psMD ,NULL) != 1)
	{
		EVP_MD_CTX_cleanup(&ctx);
		goto err3;
	}
	while ((nLenOfIn = read(nFdIn, puchInput, __MY_MAX_BUFFER_SIZE)) > 0)
	{
		
		if (EVP_SignUpdate(&ctx, puchInput, nLenOfIn) != 1)
		{
			EVP_MD_CTX_cleanup(&ctx);
			goto err3;
		}
	}
	if (EVP_SignFinal(&ctx, puchOutput, (unsigned int*)&nLenOfOut, pKey) != 1)
	{
		EVP_MD_CTX_cleanup(&ctx);
		goto err3;
	}
	EVP_MD_CTX_cleanup(&ctx);
	if (0 != WriteAccordingFormat(nFdOut, pchFormat, puchOutput, nLenOfOut))
	{
		sprintf(g_pchErrorInformation,"WriteAccordingFormat failed");
		goto err2;
	}
	
	close(nFdIn);
	if( nFdOut != STDOUT_FILENO)
	{
		close(nFdOut);
	}
	return 0;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err1: 
	close(nFdIn);
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err2: 
	close(nFdIn);
	if( nFdOut != STDOUT_FILENO)
	{
		close(nFdOut);
	}
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err3:
	g_nErrorFlag = 1;
	if( nFdOut != STDOUT_FILENO)
	{
		close(nFdOut);
	}
	OpenSSL_PrintErrorInformation();
	return -1;
}

