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
			CSocketIO(IN CSocketFd cSocketFd);
			CSocketIO(IN int nSocketFd);

			int Send(IN  const char* pchData, IN int nDataLength) const;
			int Recv(OUT char* pchData, IN int nDataLength) const;
			int SendFile(IN const char* pchFileName) const;
			int RecvFile(void) const ;
		private:
			int  __cm_nSocketFd;
	};

	inline
	CSocketIO::CSocketIO(IN CSocketFd cSocketFd)
		:__cm_nSocketFd(cSocketFd.GetSocketFd())
	{
	}
	inline
	CSocketIO::CSocketIO(IN int nSocketFd)
		:__cm_nSocketFd(nSocketFd)
	{
	}

	int
	CSocketIO::Recv(OUT char* pchData, IN int nDataLength) const
	{
		int nTotal = 0,
			nPosition = 0;
		while (nTotal < nDataLength)
		{
			nPosition = ::recv(__cm_nSocketFd, pchData+nTotal, nDataLength-nTotal, 0); 
			if (nPosition == -1)
			{
				if(errno == EINTR)
				{
					continue;
				}
				::perror("recv faild");
				return -1;
			}
			else if (nPosition == 0) /* 对端关闭*/
			{
				break;
			}
		}
		return 0;
	}


	int 
	CSocketIO::Send(IN const char* pchData, IN int nDataLength) const
	{
		int nTotal = 0,
			nPosition = 0;
		while (nTotal < nDataLength)
		{
			nPosition = ::send(__cm_nSocketFd, pchData+nTotal, nDataLength-nTotal, 0);
			if (nPosition == -1)
			{
				if(errno == EINTR)  /* 重启发送操作*/
				{
					continue;
				}
				::perror("send faild");
				return -1;
			}
			else if (nPosition == 0)
			{
				break; //对端关闭
			}
			nTotal += nPosition;
		}
		return 0;
	}
	
	int
	CSocketIO::SendFile(IN const char* pchFileName) const
	{
		struct stat sFileState;
		::bzero(&sFileState,sizeof(sFileState));
		if (-1 == ::stat(pchFileName,&sFileState)) /* 读取文件信息*/
		{
			::perror("stat() failed");
			return -1;
		}
		if (S_ISDIR(sFileState.st_mode)) /* 如果是目录则不能发送*/
		{
			cout << "cani\'t send directory" << endl;
			return -1;
		}

		int nFd = ::open(pchFileName,O_RDONLY);/* 打开文件*/
		if (nFd == -1)
		{
			::perror("opend file failed");
			return -1;
		}
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(sDataBag));
		sDataBag.Length = std::strlen(pchFileName);  /* 首先发送文件名*/
		std::strcpy(sDataBag.buf, pchFileName);
		Send(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		while(::bzero(&sDataBag, sizeof(sDataBag)), (sDataBag.Length = ::read(nFd, sDataBag.buf, sizeof(sDataBag.buf))) > 0)
		{
			Send(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		}
		sDataBag.Length = 0; /* 发送一个结束标志*/
		Send(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		::close(nFd);
		return 0;
	}

	int 
	CSocketIO::RecvFile(void) const 
	{
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(SDataBag));
		Recv(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int)); /* 先接收数据长度*/
		if (sDataBag.Length > 0) /* 如果长度大于0*/
		{
			Recv(sDataBag.buf,sDataBag.Length); /* 接收文件名*/
			int nFd = ::open(sDataBag.buf,O_WRONLY|O_CREAT|O_TRUNC,0755);
			if (nFd == -1)
			{
				::perror("open failed");
				return -1;
			}
			while (1)
			{
				::bzero(&sDataBag, sizeof(SDataBag));
				Recv(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int));/* 接收长度*/
				if(sDataBag.Length > 0)
				{
					Recv(sDataBag.buf,sDataBag.Length);/* 接收数据，写入数据*/
					::write(nFd,sDataBag.buf,sDataBag.Length);
				}
				else
				{
					break;
				}
			}
			::close(nFd);
		}
		return 0;
	}
}

#endif /* end of include guard: MY_SOCKETIO_H */
