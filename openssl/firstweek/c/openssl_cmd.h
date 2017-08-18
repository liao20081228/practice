#pragma once

#ifndef __MY_OPENSSL_CMD_C_H
#define __MY_OPENSSL_CMD_C_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include<unistd.h>
#include<fcntl.h>
#include<getopt.h>

#include<openssl/evp.h>
#include<openssl/err.h>
#include<openssl/err.h>
#include<openssl/hmac.h>

#include"openssl_evp.h"


#ifndef __MY_MAX_BUFFER_SIZE 
#define __MY_MAX_BUFFER_SIZE 12000
#endif

void ShowHelpInfo(void);

int ReadAccordingFormat(OUT unsigned char* pchdata, IN int nFdIn, 
		IN const char*format,  IN int nLen);
int WriteAccordingFormat(IN int nFdOut, IN const char*format, 
		IN const unsigned char* pchdata, IN int nLen);

int ReadCommandArgument(OUT char* pchMode, OUT char* pchAlgorithom, 
					OUT unsigned  char* pchKey, OUT unsigned char* pchInitVec,  
					OUT char* pchInputFile, OUT char* pchOutputFile, 
					OUT char* pchFormat,
					IN int argc, IN char* argv[]);

int HandleCommandArgument(IN int argc, IN char* argv[]);


#endif /* end of include guard: __MY_OPENSSL_CMD_H */
