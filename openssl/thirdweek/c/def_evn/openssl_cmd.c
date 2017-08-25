#include"./openssl_cmd.h"
void 
ShowHelpInfo(void)
{
	printf("help info\n \
	-e/--encrypt 数字信封加密（对称算法使用AES128-CBC）\n \
	-d/--decrypt 数字信封解密\n \
	-k/--key 公钥或私钥文件（在加密时使用公钥，解密时使用私钥）\n \
	-c/--cer 数字证书\n \
	-i/--input 输入文件\n \
	-o/--output 输出文件\n \
	-h/--help 显示使用帮助 \n");
}

int 
ReadAccordingFormat(OUT unsigned char* pchdata, IN const char*format,  
		             IN int nLen, IN const char* pchInputFile)
{
	FILE* fpIn = fopen(pchInputFile, "rb");
	int out_len = 0;
	if (fpIn == NULL)
	{
		sprintf(g_pchErrorInformation, "fopen（）： open input file failed");
		goto err0;
	}
	if (strlen(format) == 0 || strcmp(format, "BINARY") == 0)
	{
		out_len  = fread(pchdata, 1,nLen, fpIn);
		if (out_len  <= 0)
		{
			sprintf(g_pchErrorInformation, "input file has no data or read failed");
			goto err1;
		}
	}
	else if (strcmp(format, "HEX") == 0) 
	{
		unsigned char *temp = (unsigned char*)malloc(nLen * 2);
		int nLenTemp = fread(temp, 1, nLen*2, fpIn);
		if (!(nLenTemp > 0 ))
		{
			sprintf(g_pchErrorInformation, "input file has no data or read failed");
			free(temp);
			goto err1;
		}
		else 
		{
			int len = OpenSSL_HexToBin(pchdata,nLen, temp, nLenTemp);
			free(temp);
			fclose(fpIn);
			return len;
		}
	}
	else if (strcmp(format, "BASE64") == 0)
	{
		unsigned char *temp =(unsigned char*)malloc(nLen * 2);
		
		int realLen = nLen % 48 == 0 ? nLen / 48 * 65 : nLen / 48 * 65 + 65;   
		
		int nLenTemp = fread(temp, 1, realLen, fpIn);
		if (temp[nLenTemp-1] == '\n')
		{
			--nLenTemp;
		}
		if (!(nLenTemp > 0 ))
		{
			sprintf(g_pchErrorInformation, "input file has no data or read failed");
			free(temp);
			goto err;
		}
		else 
		{
			int len = OpenSSL_BASE64_decode(pchdata,nLen,temp,nLenTemp);
			free(temp);
			return len;
		}
	}
	return 0;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err1:
	fclose(fpIn);
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
}


int 
WriteAccordingFormat(IN const char* pchOutputFile, IN const char*format, unsigned char* pData,  int Length)
{
	FILE* fpOut = stdout;
	if (strlen(pchOutputFile) !=0 )
	{
		fpOut = fopen(pchOutputFile, "wb");
		if (fpOut == NULL)
		{
			sprintf(g_pchErrorInformation,"open pchOutputFile failed");
			goto err0;
		}
	}
	if (strlen(format) == 0 || strcmp(format, "BINARY") == 0)
	{
		fwrite(pData, 1,Length, fpOut);
	}
	else if (strcmp(format, "BASE64") == 0) 
	{
		unsigned char* temp =(unsigned char*) malloc(Length / 48 * 65 + 65 * 2);
		int len = OpenSSL_BASE64_encode(temp, Length / 48 * 65 + 65 * 2, pData, Length);
		fwrite(temp, 1,len, fpOut);
		free(temp);
	}
	else
	{
		unsigned char* temp = (unsigned char*)malloc(Length * 2);
		int len = OpenSSL_BinToHex(temp, Length * 2, pData, Length);
		fwrite(temp, 1, len, fpOut);
		free(temp);
	}
	if (fpOut != stdout)
	{
		fclose(fpOut);
	}
	return 0;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
}

int 
ReadCommandArgument(OUT int* pnIsEncrypt, OUT char* pchKeyFile,
					OUT char* pchInputFile, OUT char* pchOutputFile, 
					OUT char* pchFormat, OUT char* pchSenderCertFile ,
				    OUT char* pchReceiverCertFile,OUT char* pchCipherName, 
					OUT char* pchDigestName,IN int argc, IN char* argv[])
{
	char chOption = '\0';
	int nLongOptionIndex = 0;
	int IsHelp = 0;
	int nEncrypt = 0,
		nDecrypt = 0;
	static struct option long_options[] = /* 长选项定义*/
	{
		{"encrypt",     0,    0,   'e'},
		{"decrypt",     0,    0,   'd'},
		{"key",         1,    0,   'k'},
		{"input",       1,    0,   'i'},
		{"output",      1,    0,   'o'},
		{"help",        0,   0,    'h'},
		{"digest",      1,   0,    'm'},
		{"scer",        1,   0,    's'},
		{"rcer",        1,   0,    'r'},
		{"alogrithm",   1,   0,    'a'},
		{0, 0, 0, 0}
	};

	while ((chOption = getopt_long(argc, argv, "edk:i:o:f:ha:r:s:m:", long_options, &nLongOptionIndex)) != -1)
	{
		switch (chOption)
		{
			case 'e' : nEncrypt = 1; break;
			case 'd' : nDecrypt = 1; break;
			case 'k' : strcpy(pchKeyFile, optarg); break;
			case 'a' : strcpy(pchCipherName, optarg); break;
			case 'm' : strcpy(pchDigestName, optarg); break;
			case 's' : strcpy(pchSenderCertFile, optarg); break;
			case 'r' : strcpy(pchReceiverCertFile, optarg); break;
			case 'i' : strcpy(pchInputFile, optarg); break;
			case 'o' : strcpy(pchOutputFile, optarg); break;
			case 'f' : strcpy(pchFormat, optarg); break;
			case 'h' : ShowHelpInfo(); IsHelp = 1; exit(-1);
			default  : printf("Unknown option:%c\n",chOption); ShowHelpInfo(); return -1;
		}
	}
	if (IsHelp == 0)
	{
		if ( nEncrypt && !(strlen(pchReceiverCertFile)))
		{
			sprintf(g_pchErrorInformation,"缺少对方证书");
			goto err;
		}
		if (strlen(pchFormat) != 0 && (0 == (strcmp(pchFormat, "BASE64") == 0 || strcmp(pchFormat, "HEX") ||strcmp(pchFormat, "BINARY") == 0)))
		{
			sprintf(g_pchErrorInformation,"输入的格式不支持");
			goto err;
		}
		if (strlen(pchInputFile) == 0)
		{
			sprintf(g_pchErrorInformation,"没有输入文件");
			goto err;
		}
		if (strlen(pchFormat) == 0 )
		{
			strncpy(pchFormat, "BINARY", 6);
		}
		if (nEncrypt == 1 && nDecrypt == 1)
		{
			sprintf(g_pchErrorInformation,"不能既加密又解密");
			goto err;
		}
		*pnIsEncrypt = nEncrypt ? 1 : 0;
	    if (strlen(pchCipherName) == 0)
		{
			strncpy(pchCipherName, "aes-128-cbc", 14);
		}
		if (strlen(pchDigestName) == 0)
		{
			strncpy(pchDigestName, "sha1", 14);
		}
		if (nEncrypt)
		{
			if ((strlen(pchSenderCertFile) != 0 && strlen(pchKeyFile) == 0 ) ||
					( strlen(pchSenderCertFile) == 0 && strlen(pchKeyFile) != 0))
			{
				sprintf(g_pchErrorInformation,"如果要带签名则请提供私钥和证书");
				goto err;
			}
		}
	}
	return 0;
err:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
}

int
HandleCommandArgument(IN int argc, IN char* argv[])
{
	int nIsEncrypt = 0;
	char pchInputFile[256] = {'\0'},
	     pchOutputFile[256] = {'\0'},
	     pchFormat[20] = {'\0'},
		 pchPriKeyfile[255] = {'\0'},
		 pchSenderCertFile[255] = {'\0'},
		 pchReceiverCertFile[255] = {'\0'},
		 pchCipherName[20] = {'\0'},
		 pchDigestName[20] = {'\0'};
	
	if (0 != ReadCommandArgument(&nIsEncrypt,pchPriKeyfile, 
				pchInputFile, pchOutputFile, pchFormat, 
				pchSenderCertFile, pchReceiverCertFile,
				pchCipherName, pchDigestName,argc, argv))
	{
		sprintf(g_pchErrorInformation, "ReadCommandArgument failed");
		goto err0;
	}

	if (nIsEncrypt == 1)
	{	
		// get cipher key and iv
		unsigned char salt[8] = {0},
					  passwd[8] = {1};
		srand(time(NULL));
		for (int i = 0; i < 8; ++i)
		{
			salt[i] = rand() % 256;
			passwd[i] = rand() % 256;
		}
		const EVP_CIPHER* cipher = EVP_get_cipherbyname(pchCipherName);
		const EVP_MD* md = EVP_get_digestbyname(pchDigestName);
		if (cipher == NULL)
		{
			sprintf(g_pchErrorInformation, "not support cipher alogrithm");
			goto err0;
		}
		if (md == NULL)
		{
			sprintf(g_pchErrorInformation, "not support  digest algorithm");
			goto err0;
		}
		unsigned char key[EVP_MAX_KEY_LENGTH] = {'\0'};  
		unsigned char iv[EVP_MAX_IV_LENGTH] = {'\0'}; 
		memset(iv, 1 , EVP_MAX_IV_LENGTH);
		EVP_BytesToKey(EVP_get_cipherbyname(pchCipherName), EVP_get_digestbyname(pchDigestName), 
						salt, passwd, 8, 3, key, NULL);
		
		//get encrypt  data
		FILE* fpIn = fopen(pchInputFile, "rb");
		if (fpIn == NULL)
		{
			sprintf(g_pchErrorInformation, "fopen Cer file  failed");
			goto err0;
		}

		unsigned char DataIn[__MY_MAX_BUFFER_SIZE * 10] = {0};
		int inLen = fread(DataIn, 1 , __MY_MAX_BUFFER_SIZE * 10, fpIn);
		fclose(fpIn);

		unsigned char enc_Data[__MY_MAX_BUFFER_SIZE * 10 + EVP_MAX_BLOCK_LENGTH] = {0};
		int enc_Data_len  = OpenSSL_Cipher(enc_Data, __MY_MAX_BUFFER_SIZE* 10 + EVP_MAX_BLOCK_LENGTH,
		                                pchCipherName, key, NULL, iv, DataIn ,inLen, 1);
		
		//get  public key from   Certificate
		EVP_PKEY* pubKey = NULL;
		X509* pX509 = NULL;
		FILE* fpPubKey;
		if ((fpPubKey = fopen(pchReceiverCertFile, "rb")) == NULL)
		{
			sprintf(g_pchErrorInformation, "fopen keyfile  failed");
			goto err0;
		}
		if (NULL == PEM_read_X509(fpPubKey, &pX509, NULL ,NULL))
		{
			rewind(fpPubKey);
			if (NULL == d2i_X509_fp(fpPubKey,&pX509))
			{
				fclose(fpPubKey);
				goto err1;
			}
		}
		fclose(fpPubKey);
		if ((pubKey = X509_get_pubkey(pX509)) == NULL)
		{
			X509_free(pX509);
			goto err1;
		}

		// encrypt the key 
		EVP_PKEY_CTX* pkeyCtx = EVP_PKEY_CTX_new(pubKey, NULL);
		if (pkeyCtx == NULL )
		{
			EVP_PKEY_free(pubKey);
			goto err1;
		}
		if (EVP_PKEY_encrypt_init(pkeyCtx) != 1)
		{
			EVP_PKEY_CTX_free(pkeyCtx);
			EVP_PKEY_free(pubKey);
			goto err1;
		}
		unsigned char enc_key[EVP_MAX_KEY_LENGTH * 100] =  {0}; 
		int enc_key_len = 100* EVP_MAX_KEY_LENGTH;
		if (1 != EVP_PKEY_encrypt(pkeyCtx, enc_key, (size_t*)&enc_key_len, key, 
					EVP_get_cipherbyname(pchCipherName)->key_len))
		{
			EVP_PKEY_CTX_free(pkeyCtx);
			EVP_PKEY_free(pubKey);
			goto err1;
		}
		EVP_PKEY_CTX_free(pkeyCtx);
		EVP_PKEY_free(pubKey);
	
		// sign 
		if (strlen(pchSenderCertFile) != 0)
		{
			//get sender's Certificate
			unsigned char SenderCert[__MY_MAX_BUFFER_SIZE * 10] = {0};
			FILE* fpSenderCer = NULL; 
			if ((fpSenderCer = fopen(pchSenderCertFile, "rb")) == NULL)
			{
				sprintf(g_pchErrorInformation, "fopen Cer file  failed");
				goto err0;
			}
			int Cert_Len =  fread(SenderCert,1 , __MY_MAX_BUFFER_SIZE * 10, fpSenderCer);
			fclose(fpSenderCer);

			//get sign
			unsigned char tempbuf[__MY_MAX_BUFFER_SIZE*11];
			memcpy(tempbuf, enc_key, enc_key_len);
			memcpy(tempbuf + enc_key_len, enc_Data, enc_Data_len);
			unsigned char Signature[__MY_MAX_BUFFER_SIZE] = {'\0'};
			int Signature_Len = 0;
			EVP_MD_CTX* mdCtx = EVP_MD_CTX_create();
			EVP_MD_CTX_init(mdCtx);
			
			//get private key
			EVP_PKEY *pPriKey = NULL;
			FILE* fpPriKey  = NULL;
			
			fpPriKey = fopen(pchPriKeyfile,"rb");
			if (fpPriKey == NULL)
			{
				sprintf(g_pchErrorInformation, "fopen keyfile  failed");
				EVP_MD_CTX_destroy(mdCtx);
				goto err0;
			}
			if (NULL == PEM_read_PrivateKey(fpPriKey, &pPriKey, NULL ,NULL))
			{
				rewind(fpPriKey);
				if (NULL == d2i_PrivateKey_fp(fpPriKey,&pPriKey))
				{
					sprintf(g_pchErrorInformation, "read key file   failed");
					fclose(fpPriKey);
					goto err0;
				}
			}
			fclose(fpPriKey);


			if(EVP_SignInit_ex(mdCtx, md ,NULL) != 1)
			{
				EVP_MD_CTX_cleanup(mdCtx);
				EVP_MD_CTX_destroy(mdCtx);
				goto err1;
			}
			if (EVP_SignUpdate(mdCtx, tempbuf,enc_key_len + enc_Data_len) != 1)
			{
				EVP_MD_CTX_cleanup(mdCtx);
				EVP_MD_CTX_destroy(mdCtx);
				goto err1;
			}
			if (EVP_SignFinal(mdCtx, Signature, (unsigned int*)&Signature_Len, pPriKey) != 1)
			{
				EVP_MD_CTX_cleanup(mdCtx);
				EVP_MD_CTX_destroy(mdCtx);
				goto err1;
			}

			EVP_MD_CTX_cleanup(mdCtx);
			EVP_MD_CTX_destroy(mdCtx);
			
			int digest_alg_Len = strlen(pchDigestName);
			int cipher_alg_Len = strlen(pchCipherName);
			int total_length = enc_Data_len + Signature_Len + enc_key_len + 
								Cert_Len + digest_alg_Len + cipher_alg_Len + 24;
			unsigned char buf[__MY_MAX_BUFFER_SIZE*20];
			memcpy(buf + 0, &Cert_Len, 4);
			memcpy(buf + 4, &Signature_Len, 4);
			memcpy(buf + 8, &digest_alg_Len, 4);
			memcpy(buf + 12, &cipher_alg_Len, 4);
			memcpy(buf + 16, &enc_key_len, 4);
			memcpy(buf + 20, &enc_Data_len, 4);
			memcpy(buf + 24, SenderCert, Cert_Len);
			memcpy(buf + 24 + Cert_Len, Signature, Signature_Len);
			memcpy(buf + 24 + Cert_Len + Signature_Len, pchDigestName, digest_alg_Len);
			memcpy(buf + 24 + Cert_Len + Signature_Len + digest_alg_Len, pchCipherName, cipher_alg_Len);
			memcpy(buf + 24 + Cert_Len + Signature_Len + digest_alg_Len + cipher_alg_Len, enc_key, enc_key_len);
			memcpy(buf + 24 + Cert_Len + Signature_Len + digest_alg_Len + cipher_alg_Len + enc_key_len, enc_Data, enc_Data_len);
			if (0 != WriteAccordingFormat(pchOutputFile, pchFormat, buf, total_length))
			{
				sprintf(g_pchErrorInformation, "WriteAccordingFormat() failed");
				goto err0;
			}
		}
		else
		{
			int Signature_Len = 0;
			int Cert_Len = 0;
			int digest_alg_Len = strlen(pchDigestName);
			int cipher_alg_Len = strlen(pchCipherName);

			int total_length = enc_Data_len + Signature_Len + enc_key_len + 
								Cert_Len + digest_alg_Len + cipher_alg_Len + 24;
			unsigned char buf[__MY_MAX_BUFFER_SIZE*20];
			memcpy(buf + 0, &Cert_Len, 4);
			memcpy(buf + 4, &Signature_Len, 4);
			memcpy(buf + 8, &digest_alg_Len, 4);
			memcpy(buf + 12, &cipher_alg_Len, 4);
			memcpy(buf + 16, &enc_key_len, 4);
			memcpy(buf + 20, &enc_Data_len, 4);
			memcpy(buf + 24 + Cert_Len + Signature_Len, pchDigestName, digest_alg_Len);
			memcpy(buf + 24 + Cert_Len + Signature_Len + digest_alg_Len, pchCipherName, cipher_alg_Len);
			memcpy(buf + 24 + Cert_Len + Signature_Len + digest_alg_Len + cipher_alg_Len, enc_key, enc_key_len);
			memcpy(buf + 24 + Cert_Len + Signature_Len + digest_alg_Len + cipher_alg_Len + enc_key_len, enc_Data, enc_Data_len);
			
			if (0 != WriteAccordingFormat(pchOutputFile, pchFormat, buf, total_length))
			{
				sprintf(g_pchErrorInformation, "WriteAccordingFormat() failed");
				goto err0;
			}
		}
	}
	else //decrypt
	{
		unsigned char temp[__MY_MAX_BUFFER_SIZE * 50] = {0};
		int Length = ReadAccordingFormat(temp, pchFormat, __MY_MAX_BUFFER_SIZE * 50, pchInputFile);
		if (Length <= 0)
		{
			sprintf(g_pchErrorInformation,"ReadAccordingFormat() failed");
			goto err0;
		}
		int Cert_Len = 0,
			Signature_Len = 0,
			digest_alg_Len = 0,
			cipher_alg_Len = 0,
			enc_key_Len = 0,
			enc_Data_Len = 0;
		memcpy(&Cert_Len, temp + 0, 4);
		memcpy(&Signature_Len, temp + 4, 4);
		memcpy(&digest_alg_Len, temp + 8, 4);
		memcpy(&cipher_alg_Len, temp + 12, 4);
		memcpy(&enc_key_Len, temp + 16, 4);
		memcpy(&enc_Data_Len, temp + 20, 4);
		unsigned char* pSenderCert =temp + 24;
		unsigned char* pSignature  = temp + Cert_Len + 24;
		char*          pDigest_alg =(char*) (temp+ Cert_Len + Signature_Len) + 24;
		char*          pCipher_alg = (char*)(temp+ Cert_Len + Signature_Len + digest_alg_Len) + 24;
		unsigned char* pEnc_key    = temp+ Cert_Len + Signature_Len + digest_alg_Len + cipher_alg_Len + 24;
		unsigned char* pEnc_data   = temp+ Cert_Len + Signature_Len + digest_alg_Len + cipher_alg_Len + enc_key_Len + 24;

		
		if(Cert_Len != 0 && Signature_Len != 0)
		{
			X509* pX509 = NULL;
			BIO* pCert = BIO_new_mem_buf(pSenderCert, Cert_Len);
			if (PEM_read_bio_X509(pCert, &pX509, NULL, NULL ) == NULL)
			{
				if (d2i_X509_bio(pCert, &pX509) == NULL)
				{
					BIO_free(pCert);
					goto err1;
				}
			}
			EVP_PKEY* pPubKey = X509_get_pubkey(pX509);
			X509_free(pX509);
			BIO_free(pCert);

			// verify
			if (digest_alg_Len != 0)
			{
				memcpy(pchDigestName, pDigest_alg, digest_alg_Len);
			}
			EVP_MD_CTX *mdCtx = EVP_MD_CTX_create();
			EVP_MD_CTX_init(mdCtx);
			if (EVP_VerifyInit_ex(mdCtx, EVP_get_digestbyname(pchDigestName), NULL) != 1)
			{
				EVP_PKEY_free(pPubKey);
				EVP_MD_CTX_destroy(mdCtx);
				goto err1;
			}
			if (1 != EVP_VerifyUpdate(mdCtx , pEnc_key, enc_key_Len + enc_Data_Len ))
			{
				EVP_PKEY_free(pPubKey);
				EVP_MD_CTX_destroy(mdCtx);
				goto err1;
			}
			if (1 != EVP_VerifyFinal(mdCtx, pSignature, Signature_Len,pPubKey))
			{
				EVP_PKEY_free(pPubKey);
				EVP_MD_CTX_destroy(mdCtx);
				sprintf(g_pchErrorInformation, "data has be modified ");
				goto err0;
			}
			EVP_PKEY_free(pPubKey);
			EVP_MD_CTX_destroy(mdCtx);
		}
		unsigned char iv[EVP_MAX_IV_LENGTH] = {'\0'};
		memset(iv,1,EVP_MAX_IV_LENGTH);
		//get private key
		FILE* fpkey = fopen(pchPriKeyfile, "rb");
		if (fpkey == NULL)
		{
			sprintf(g_pchErrorInformation, "open private key file failed");
			goto err0;
		}
		EVP_PKEY* pPriKey = NULL;
		if (PEM_read_PrivateKey(fpkey,&pPriKey, NULL, NULL) == NULL)
		{
			if (d2i_PrivateKey_fp(fpkey, &pPriKey) == NULL)
			{
				fclose(fpkey);
				goto err1;
			}
		}
		fclose(fpkey);

		//decrypt the key
		EVP_PKEY_CTX* pkeyCtx = EVP_PKEY_CTX_new(pPriKey, NULL);
		if (pkeyCtx == NULL )
		{
			EVP_PKEY_free(pPriKey);
			goto err1;
		}
		if (EVP_PKEY_decrypt_init(pkeyCtx) != 1)
		{
			EVP_PKEY_CTX_free(pkeyCtx);
			EVP_PKEY_free(pPriKey);
			goto err1;
		}
		unsigned char key[EVP_MAX_KEY_LENGTH * 10] = {'\0'};
		int key_len =  EVP_MAX_KEY_LENGTH * 10;
		if (1 != EVP_PKEY_decrypt(pkeyCtx, key, (size_t*)&key_len, pEnc_key, enc_key_Len))
		{
			EVP_PKEY_CTX_free(pkeyCtx);
			EVP_PKEY_free(pPriKey);
			goto err1;
		}
		EVP_PKEY_CTX_free(pkeyCtx);
		EVP_PKEY_free(pPriKey);
		
		unsigned char Data[__MY_MAX_BUFFER_SIZE* 10] = {0};
		memcpy(pchCipherName,pCipher_alg,cipher_alg_Len);
		int Data_Len = OpenSSL_Cipher(Data,__MY_MAX_BUFFER_SIZE * 10,
									pchCipherName, key, NULL, iv, pEnc_data,enc_Data_Len, 0);
		memset(pchFormat,'\0', 20);
		WriteAccordingFormat(pchOutputFile, pchFormat, Data, Data_Len);
	}
	return 0;
err0:
	g_nErrorFlag = 0;
	OpenSSL_PrintErrorInformation();
	return -1;
err1:
	g_nErrorFlag = 1;
	OpenSSL_PrintErrorInformation();
	return -1;
}
