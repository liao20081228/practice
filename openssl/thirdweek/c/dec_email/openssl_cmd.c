#include"./openssl_cmd.h"
void 
ShowHelpInfo(void)
{
	printf("help info\n \
			支持以下命令行参数 \n\
			-k/--key 解密使用的私钥文件 \n \
			-c/--cert 验证签名使用的证书文件（如果不指定，则不进行签名验证）\n \
			-i/--input 输入的加密邮件 \n \
			-o/--output 输出的明文邮件\n \
			-h/--help 显示使用帮助\n");
}

int 
ReadAccordingFormat(OUT unsigned char* pchdata, IN int nFdIn, IN const char*format,  IN int nLen)
{
	if (strlen(format) == 0 || strcmp(format, "BINARY") == 0)
	{
		return read(nFdIn, pchdata, nLen);
	}
	else if (strcmp(format, "HEX") == 0) 
	{
		unsigned char temp[__MY_MAX_BUFFER_SIZE*2]={0};
		int nLenTemp = read(nFdIn, temp, nLen*2);
		if (!(nLenTemp > 0 ))
		{
			return nLenTemp; 
		}
		else 
		{
			int len = OpenSSL_HexToBin(pchdata,nLen, temp, nLenTemp);
			return len;
		}
	}
	else if (strcmp(format, "BASE64") == 0)
	{
		unsigned char temp[__MY_MAX_BUFFER_SIZE*2] = {0};
		
		int realLen = nLen % 48 == 0 ? nLen / 48 * 65 : nLen / 48 * 65 + 65;   
		
		int nLenTemp = read(nFdIn, temp, realLen);
		if (temp[nLenTemp-1] == '\n')
		{
			--nLenTemp;
		}
		if (!(nLenTemp > 0 ))
		{
			return nLenTemp; 
		}
		else 
		{
			int len = OpenSSL_BASE64_decode(pchdata,nLen,temp,nLenTemp);
			return len;
		}
	}
	return 0;
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
ReadCommandArgument(OUT char* pchCertFile, OUT char* pchKeyFile,
				     OUT char* pchOutputFile, OUT char* pchInputFile,
					 IN int argc, IN char* argv[])
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	int IsHelp = 0;
	static struct option long_options[] = /* 长选项定义*/
	{
		{"cerm",     1,    0,   'c'},
		{"key",        1,    0,   'k'},
		{"input",    1,    0,   'i'},
		{"output",     1,    0,   'o'},
		{"help",       0 ,   0,   'h'},
		{0, 0, 0, 0}
	};

	while ((chOption = getopt_long(argc, argv, "c:k:i:o:h", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'c' : strcpy(pchCertFile, optarg); break;
			case 'k' : strcpy(pchKeyFile, optarg); break;
			case 'i' : strcpy(pchInputFile, optarg); break;
			case 'o' : strcpy(pchOutputFile, optarg); break;
			case 'h' : ShowHelpInfo(); IsHelp = 1; exit(-1);
			default  : printf("Unknown option:%c\n",chOption); ShowHelpInfo(); return -1;
		}
	}
	if (IsHelp == 0)
	{
		if (!(strlen(pchKeyFile)))
		{
			sprintf(g_pchErrorInformation,"缺少秘钥文件");
			goto err;
		}
		if (!(strlen(pchCertFile)))
		{
			sprintf(g_pchErrorInformation,"缺少证书文件");
			goto err;
		}
		if (!(strlen(pchInputFile)))
		{
			sprintf(g_pchErrorInformation,"缺少输入文件");
			goto err;
		}

	}
	return 0;
err:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
}

PKCS7* GetPkcs7FromSmime( IN const char*  pchInputFile)
{
	BIO* psInputBIO = BIO_new_file(pchInputFile, "rb");
	if (psInputBIO == NULL)
	{
		g_nErrorFlag = 0;
		sprintf(g_pchErrorInformation, "read s/mime file failed");
		OpenSSL_PrintErrorInformation();
		return NULL;
	}
	PKCS7* psPkcs7 = SMIME_read_PKCS7(psInputBIO, NULL);
	BIO_free(psInputBIO);
	return psPkcs7;
}

EVP_PKEY* GetPrivateKey(IN const  char* pchKeyFile)
{
	FILE* fpPriKey = fopen(pchKeyFile, "rb");
	EVP_PKEY* pPriKey = NULL;
	if (fpPriKey == NULL)
	{
		g_nErrorFlag = 0;
		sprintf(g_pchErrorInformation, "read private key  file failed");
		OpenSSL_PrintErrorInformation();
		return NULL;
	}
	if (NULL == PEM_read_PrivateKey(fpPriKey, &pPriKey, NULL, NULL) 
			&& NULL == d2i_PrivateKey_fp(fpPriKey, &pPriKey))
	{
	}
	fclose(fpPriKey);
	return pPriKey;
}

X509* GetCert(IN const char* pchCertFile)
{
	BIO* pBioCert = BIO_new_file(pchCertFile, "rb");
	if (pBioCert == NULL)
	{
		g_nErrorFlag = 0;
		sprintf(g_pchErrorInformation, "read  certificate  file failed");
		OpenSSL_PrintErrorInformation();
		return NULL;
	}
	X509* pCert = NULL;
	if (NULL == PEM_read_bio_X509(pBioCert, &pCert, NULL, NULL) 
		&& NULL == d2i_X509_bio(pBioCert, &pCert))
	{
	}
	BIO_free(pBioCert);
	return pCert;
}

int 
ParsePkcs7(IN PKCS7* pPkcs7, IN EVP_PKEY* pPriKey, IN X509* pCert, IN const char* pchOutputFile )
{
	unsigned char* buf[__MY_MAX_BUFFER_SIZE*10] = {0};
	BIO *pBioSign = NULL,
		*pBioOut = NULL;
	BIO *pBioTemp = BIO_new_mem_buf(buf, __MY_MAX_BUFFER_SIZE * 10);
	if (pBioTemp == NULL)
	{
		goto err;
	}
	if ( 1 != PKCS7_decrypt(pPkcs7, pPriKey, NULL, pBioTemp, 0))
	{
		goto err;
	}

	if (SMIME_read_PKCS7(pBioTemp, &pBioSign))
	{
		goto err;
	}

	pBioOut = BIO_new_file(pchOutputFile, "wb");
	if (pBioOut == NULL)
	{
		goto err;
	}
	
	if (1 != PKCS7_verify(pPkcs7,NULL, NULL,NULL, pBioOut, 0))
	{
		goto err;
	}

	BIO_free(pBioTemp);
	BIO_free(pBioSign);
	BIO_free(pBioOut);
err:
	if (pBioTemp)
	{
		BIO_free(pBioTemp);
	}
	
	if (pBioSign)
	{
		BIO_free(pBioSign);
	}
	g_nErrorFlag = 1;
	OpenSSL_PrintErrorInformation();
	return -1;
}


int
HandleCommandArgument(IN int argc, IN char* argv[])
{
	char pchCertFile[20] = {'\0'},
	     pchInputFile[256] = {'\0'},
	     pchOutputFile[256] = {'\0'},
		 pchKeyFile[256] = {'\0'};

	PKCS7* pPkcs7 = NULL;
	EVP_PKEY* pPriKey = NULL;
	X509* pCert = NULL;

	
	if (0 != ReadCommandArgument(pchCertFile,pchKeyFile, 
				pchOutputFile, pchInputFile, argc, argv))
	{
		sprintf(g_pchErrorInformation, "ReadCommandArgument failed");
		goto err0;
	}

	if ((pPkcs7 = GetPkcs7FromSmime(pchInputFile)) == NULL)
	{
		goto err1;
	}
	
	if ((pPriKey = GetPrivateKey(pchKeyFile)) == NULL)
	{
		goto err1;
	}

	if (strlen(pchCertFile) != 0 && (pCert = GetCert(pchCertFile ))  == NULL)
	{
		if (strlen(pchCertFile ) != 0)
		{
			goto err1;
		}
	}
	
	if (ParsePkcs7(pPkcs7, pPriKey, pCert, pchOutputFile) == -1)
	{
		sprintf(g_pchErrorInformation, "ParsePkcs7(  ) failed ");
		goto err0;
	}
	
	PKCS7_free(pPkcs7);
	EVP_PKEY_free(pPriKey);
	X509_free(pCert);
	return 0;
err:
	if (pPkcs7 != NULL)
	{
		PKCS7_free(pPkcs7);
	}
	if (pPriKey != NULL)
	{
		EVP_PKEY_free(pPriKey);
	}
	if (pCert != NULL)
	{
		X509_free(pCert);
	}
	return -1;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	goto err;
err1:
	g_nErrorFlag = 1;
	OpenSSL_PrintErrorInformation();
	goto err;
}
