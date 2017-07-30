/*************************************************************************
    > File Name: socketIO.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 19时30分59秒
 ************************************************************************/
#ifndef MY_SOCKETIO_H
#define MY_SOCKETIO_H
#include"socketFd.h"
namespace MyNamespace
{
	struct SDataBag
	{
		int Length;
		char buf[1024];
	};
	
	class CSocketIO
	{
		public:
			CSocketIO(IN int nSocketFd);

			void SendFile(IN const string& strFileName) const;
			void RecvFile(void) const ;
			
			void SendMessage(IN const string& strBuf) const;
			void RecvMessage(OUT string& strBuf) const;
		
		private:
			int SendnBytes(IN  const char* pchData, IN int nDataLength) const;
			int RecvnBytes(OUT char* pchData, IN int nDataLength) const;
		private:
			int  __cm_nSocketFd;
	};

}

#endif /* end of include guard: MY_SOCKETIO_H */
