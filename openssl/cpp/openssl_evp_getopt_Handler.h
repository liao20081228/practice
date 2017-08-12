/*!@file
********************************************************************************
Module Name    : OpenSSL_evp
File Name      : OpenSSL_evp_getopt_handler.h
Related Files  : no
File Function  : 处理命令行参数
Author         : liaoweizhi
Department     : 技术研发总部
Email          : liaowz@koal.com
Version        : 0.0
--------------------------------------------------------------------------------
Note           : 采用c++的方式
--------------------------------------------------------------------------------
Date:          : 2017/07/30
Version:       : 0.0
Modifier       : no
Department     : no
Email          : no
Changes        : create
*******************************************************************************/
#ifndef __MY_OPENSSL_EVP_HANDLER_H
#define __MY_OPENSSL_EVP_HANDLER_H
#ifndef IN
#define IN
#endif /* end of include guard: IN */
#ifndef OUT
#define OUT
#endif /* end of include guard: OUT */
#ifndef __MY_OPENSSL_ERROR
#define __MY_OPENSSL_ERROR
#endif /* end of include guard: __MY_OPENSSL_ERROR */

#include"openssl_evp_cipher.h"
#include"openssl_evp_digestandhmac.h"
#include"openssl_evp_getopt_cmdarg.h"
#include"openssl_evp_getopt_writor.h"
namespace Openssl_evp
{

class CHandler
{
	public:
		CHandler(IN int argc, IN char** ppArgv);

	public:
		void exe(void);
	private:
		array<string,7> __cm_arCmdArg;
		int __cm_nFdInput;
};

}
#endif /* end of include guard: __MY_OPENSSL_EVP_HANDLER_H */


Openssl_evp::CHandler::CHandler(IN int argc, IN char** ppArgv)
	:__cm_arCmdArg(CCommandArgument(argc, ppArgv).GetArg())
{
	__cm_nFdInput = ::open(__cm_arCmdArg[4].c_str(), O_RDONLY);
	if (__cm_nFdInput == -1)
	{

	}
}



