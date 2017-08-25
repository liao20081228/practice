#pragma once

#ifndef __MY_OPENSSL_CMD_H
#define __MY_OPENSSL_CMD_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include<getopt.h>
#include<unistd.h>
#include<fcntl.h>

#include<openssl/evp.h>
#include<openssl/err.h>
#include<openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/bio.h>

#include"openssl_evp.h"

#ifndef ____MY_MAX_BUFFER_SIZE 
#define ____MY_MAX_BUFFER_SIZE 12000
#endif

void ShowHelpInfo(void);

int ReadCommandArgument(OUT char* pchDigetName, OUT char* pchKeyfile,
					OUT char* pchInputFile, OUT char* pchOutputFile, 
					OUT char* pchFormat,IN int argc, IN char* argv[]);

int HandleCommandArgument(IN int argc, IN char* argv[]);

int  WriteAccordingFormat(IN int nFdOut, IN const char*format, 
		IN const unsigned char* pchdata, IN int nLen);


#endif
