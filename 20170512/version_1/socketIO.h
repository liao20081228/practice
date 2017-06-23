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
			CSocketIO(IN const CSocketFd& cSocketFd);
			CSocketIO(IN int nSocketFd);

			int SendFile(IN const char* pchFileName) const;
			int RecvFile(void) const ;
			
			int SendMessage(IN const char* pchBuf) const;
			int RecvMessage(OUT char* pchBuf) const;
		
		private:
			int SendnBytes(IN  const char* pchData, IN int nDataLength) const;
			int RecvnBytes(OUT char* pchData, IN int nDataLength) const;
		private:
			int  __cm_nSocketFd;
	};

	inline
	CSocketIO::CSocketIO(IN const CSocketFd& cSocketFd)
		:__cm_nSocketFd(cSocketFd.GetSocketFd())
	{
	}

	inline
	CSocketIO::CSocketIO(IN int nSocketFd)
		:__cm_nSocketFd(nSocketFd)
	{
	}

	int
	CSocketIO::RecvnBytes(OUT char* pchData, IN int nDataLength) const
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
			nTotal += nPosition;
		}
		return 0;
	}


	int 
	CSocketIO::SendnBytes(IN const char* pchData, IN int nDataLength) const
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
		SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		while(::bzero(&sDataBag, sizeof(sDataBag)), (sDataBag.Length = ::read(nFd, sDataBag.buf, sizeof(sDataBag.buf))) > 0)
		{
			SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		}
		sDataBag.Length = 0; /* 发送一个结束标志*/
		SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		::close(nFd);
		return 0;
	}

	int 
	CSocketIO::RecvFile(void) const 
	{
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(SDataBag));
		RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int)); /* 先接收数据长度*/
		if (sDataBag.Length > 0) /* 如果长度大于0*/
		{
			RecvnBytes(sDataBag.buf,sDataBag.Length); /* 接收文件名*/
			int nFd = ::open(sDataBag.buf,O_WRONLY|O_CREAT|O_TRUNC,0655);
			if (nFd == -1)
			{
				::perror("open failed");
				return -1;
			}
			while (1)
			{
				::bzero(&sDataBag, sizeof(SDataBag));
				RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int));/* 接收长度*/
				if(sDataBag.Length > 0)
				{
					RecvnBytes(sDataBag.buf,sDataBag.Length);/* 接收数据，写入数据*/
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

	int
	CSocketIO::SendMessage(IN const char* pchBuf) const
	{
		int nLength = std::strlen(pchBuf);
		if (nLength == 0)
		{
			return 0;
		}
		else
		{
			SDataBag sDataBag;
			istringstream iss(pchBuf, std::ios::in | std::ios::binary);
			while (::bzero(static_cast<void*>(&sDataBag), sizeof(SDataBag)), !(iss.eof()))
			{
				iss.read(sDataBag.buf, sizeof(sDataBag.buf));
				sDataBag.Length = std::strlen(sDataBag.buf);
				SendnBytes(reinterpret_cast<char*>(&sDataBag), sizeof(sDataBag.Length) + sDataBag.Length);
			}
			::bzero(static_cast<void*>(&sDataBag), sizeof(sDataBag));
			sDataBag.Length = 0;
			SendnBytes(reinterpret_cast<char*>(&sDataBag), sizeof(sDataBag.Length) + sDataBag.Length);
		}
		return 0;
	}

	int
	CSocketIO::RecvMessage(IN char* pchBuf) const
	{
		SDataBag sDataBag;
		ostringstream oss(std::ios::in | std::ios::binary); 
		while(std::memset(&sDataBag, 0, sizeof(sDataBag)), !RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(sDataBag.Length)))
		{
			if (sDataBag.Length == 0)
			{
				break;
			}
			else
			{
				RecvnBytes(sDataBag.buf, sDataBag.Length);
				oss.write(sDataBag.buf,sDataBag.Length);
			}
		}
		std::strcpy(pchBuf, oss.str().c_str());
		return 0;
	}
}

#endif /* end of include guard: MY_SOCKETIO_H */
