#include"./openssl_cmd.h"
void 
ShowHelpInfo(void)
{
	printf("help info\n \
			支持以下命令行参数 \n\
				-d/--digest 摘要算法（包括SHA1 | SHA256 | SHA512)，默认为SHA256\n \
				-k/--key 私钥文件（要求能自动适应PEM与DER格式）\n \
				-s/--input 输入文件 subject 输入证书请求的DN项\n\
				-o/--output 输出文件\n \
				-f/--format 输出输出格式，包括 DER | PEM 这2种，默认为PEM \n\
				-h/--help 显示使用帮助\n \
			使用示例：\n \
				xxxxx -d SHA256 -k signer.pem -i input.txt -format BASE64 -out sig.txt\n");
}


int 
WriteAccordingFormat(IN FILE * FpOut, IN const char*format, X509_REQ * pReq)
{
	if (strlen(format) == 0 || strcmp(format, "DER") == 0)
	{
		if ( i2d_X509_REQ_fp(FpOut, pReq) != 1 )
		{
			goto err;
		}

	}
	else if (strcmp(format, "PEM") == 0) 
	{
		if (1 != PEM_write_X509_REQ(FpOut, pReq))
		{
			goto err;
		}
	}
	return 0;
err:
	g_nErrorFlag = 1;
	OpenSSL_PrintErrorInformation();
	return -1;
}

int 
ReadCommandArgument(OUT char* pchDigetName, OUT char* pchKeyfile,
					OUT char* pchSubject, OUT char* pchOutputFile, 
					OUT char* pchFormat,IN int argc, IN char* argv[])
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	int IsHelp = 0;
	static struct option long_options[] = /* 长选项定义*/
	{
		{"digest",     1,    0,   'd'},
		{"key",        1,    0,   'k'},
		{"subject",    1,    0,   's'},
		{"output",     1,    0,   'o'},
		{"format",     1,    0,   'f'},
		{"help",       0 ,   0,   'h'},
		{0, 0, 0, 0}
	};

	while ((chOption = getopt_long(argc, argv, "d:k:s:o:f:h", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'd' : strcpy(pchDigetName, optarg); break;
			case 'k' : strcpy(pchKeyfile, optarg); break;
			case 's' : strcpy(pchSubject, optarg); break;
			case 'o' : strcpy(pchOutputFile, optarg); break;
			case 'f' : strcpy(pchFormat, optarg); break;
			case 'h' : ShowHelpInfo(); IsHelp = 1; exit(-1);
			default  : printf("Unknown option:%c\n",chOption); ShowHelpInfo(); return -1;
		}
	}
	if (IsHelp == 0)
	{
		if (!(strlen(pchKeyfile)))
		{
			sprintf(g_pchErrorInformation,"缺少秘钥文件");
			goto err;
		}
		if (strlen(pchFormat) != 0 && (0 == (strcmp(pchFormat, "PEM") == 0 || strcmp(pchFormat, "DER") == 0)))
		{
			sprintf(g_pchErrorInformation,"输入的格式不支持");
			goto err;
		}

		if (strlen(pchFormat) == 0 )
		{
			strncpy(pchFormat, "PEM", 3);
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
		 pchSubject[1024] = {'\0'},
	     pchOutputFile[256] = {'\0'},
	     pchFormat[20] = {'\0'},
		 pchKeyfile[255] = {'\0'};

	FILE* fpOut = stdout;
	
	/*unsigned char puchMD[__MY_MAX_BUFFER_SIZE];*/
	
	/*int nLenOfMD  = 0;*/

	EVP_PKEY* pKey = NULL;
	FILE* fpKey    = NULL;
	
	const EVP_MD* psMD = NULL;
	
	X509_REQ  *req = X509_REQ_new();
	X509_NAME *name = X509_NAME_new();
	char *p = pchSubject;
	

	if (0 != ReadCommandArgument(pchDigestName,pchKeyfile, 
				pchSubject, pchOutputFile, pchFormat, argc, argv))
	{
		sprintf(g_pchErrorInformation, "ReadCommandArgument failed");
		goto err3;
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
			fclose(fpKey);
			goto err3;
		}
	}
	fclose(fpKey);
	
	
	if (strlen(pchOutputFile) != 0)
	{
		if (( fpOut = fopen(pchOutputFile, "wb+")) == NULL) 
		{
			sprintf(g_pchErrorInformation, "open output file  failed");
			goto err0;
		}
	}
		
	for (char* token = strsep(&p,"/"); token != NULL; token = strsep(&p,"/"))
	{
		char* temp = strsep(&token,"=");
		if (0 == X509_NAME_add_entry_by_txt(name,temp,V_ASN1_UTF8STRING,(unsigned char*)token, strlen(token),0,-1))
		{
			goto err3;
		}
	}
	if (1 != X509_REQ_set_subject_name(req,name))
	{
		goto err3;
	}

		
	if (1 !=X509_REQ_set_version(req, 0L ))
	{
		goto err3;
	}
	if (1 != X509_REQ_set_pubkey(req,pKey))
	{
		goto err3;
	}

	if ((psMD = EVP_get_digestbyname(pchDigestName)) == NULL)
	{
		sprintf(g_pchErrorInformation, "不支持此摘要算法");
		goto err0;
	}
	if (0 == X509_REQ_sign(req, pKey, psMD))
	{
		goto err3;
	}
	if (0 != WriteAccordingFormat(fpOut , pchFormat, req))
	{
		sprintf(g_pchErrorInformation, "ReadCommandArgument failed");
		goto err3;
	}
	
	if( fpOut != stdout)
	{
		fclose(fpOut);
	}
	X509_REQ_free(req);
	X509_NAME_free(name);
	return 0;
err0:
	g_nErrorFlag = 0;
	goto err2;
err2:
	if( fpOut != stdout)
	{
		fclose(fpOut);
	}
	X509_REQ_free(req);
	X509_NAME_free(name);
	OpenSSL_PrintErrorInformation();
	return -1;

err3:
	g_nErrorFlag = 1;
	goto err2;
}
