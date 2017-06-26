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

			int SendFile(IN const string& strFileName) const;
			int RecvFile(void) const ;
			
			int SendMessage(IN const string& strBuf) const;
			int RecvMessage(OUT string& strBuf) const;
		
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
				if(errno == EINTR | errno == EAGAIN)
				{
					continue;
				}
				::perror("recv faild");
				return -1;
			}
			else if (nPosition == 0) /* 对端关闭*/
			{
				return -2;
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
				if(errno == EINTR | errno ==  EAGAIN)  /* 重启发送操作*/
				{
					continue;
				}
				::perror("send faild");
				return -1;
			}
			else if (nPosition == 0)
			{
				return -2; //对端关闭
			}
			nTotal += nPosition;
		}
		return 0;
	}
	
	int
	CSocketIO::SendFile(IN const string& strFileName) const
	{
		struct stat sFileState;
		::bzero(&sFileState,sizeof(sFileState));
		if (-1 == ::stat(strFileName.c_str(),&sFileState)) /* 读取文件信息*/
		{
			::perror("stat() failed");
			return -1;
		}
		if (S_ISDIR(sFileState.st_mode)) /* 如果是目录则不能发送*/
		{
			cout << "cani\'t send directory" << endl;
			return -1;
		}

		int nFd = ::open(strFileName.c_str(),O_RDONLY);/* 打开文件*/
		if (nFd == -1)
		{
			::perror("opend file failed");
			return -1;
		}
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(sDataBag));
		sDataBag.Length = strFileName.size();  /* 首先发送文件名*/
		std::strcpy(sDataBag.buf, strFileName.c_str());
		int nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		if (nRet == -1)
		{
			::close(nFd);
			return -1;
		}
		if (nRet == -2)
		{
			::close(nFd);
			return -2;
		}

		//当到大文件末尾时候，read返回0
		while(::bzero(&sDataBag, sizeof(sDataBag)), (sDataBag.Length = ::read(nFd, sDataBag.buf, sizeof(sDataBag.buf))) > 0)
		{
			nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
			if (nRet == -1)
			{
				::close(nFd);
				return -1;
			}
			if (nRet == -2)
			{
				::close(nFd);
				return -2;
			}
		}
		sDataBag.Length = 0;
		nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		if (nRet == -1)
		{
			::close(nFd);
			return -1;
		}
		if (nRet == -2)
		{
			::close(nFd);
			return -2;
		}
		::close(nFd);
		return 0;
	}

	int 
	CSocketIO::RecvFile(void) const 
	{
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(SDataBag));
		int nRet = RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int)); /* 先接收数据长度*/
		if (nRet == -1)
		{
			return -1;
		}
		if (nRet == -2)
		{
			return -2;
		}

		if (sDataBag.Length > 0) /* 如果长度大于0*/
		{
			nRet = RecvnBytes(sDataBag.buf,sDataBag.Length); /* 接收文件名*/
			if (nRet == -1)
			{
				return -1;
			}
			if (nRet == -2)
			{
				return -2;
			}
			int nFd = ::open(sDataBag.buf,O_WRONLY|O_CREAT|O_TRUNC,0655);
			if (nFd == -1)
			{
				::perror("open failed");
				return -1;
			}
			while (1)
			{
				::bzero(&sDataBag, sizeof(SDataBag));
				nRet = RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int));/* 接收长度*/
				if (nRet == -1)
				{
					::close(nFd);
					return -1;
				}
				if (nRet == -2)
				{
					::close(nFd);
					return -2;
				}
				if(sDataBag.Length > 0)
				{
					nRet = RecvnBytes(sDataBag.buf,sDataBag.Length);/* 接收数据，写入数据*/
					if (nRet == -1)
					{
						::close(nFd);
						return -1;
					}
					if (nRet == -2)
					{
						::close(nFd);
						return -2;
					}
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
	CSocketIO::SendMessage(IN const string&  strBuf) const
	{
		int nLength = strBuf.size();
		int nRet = 0;
		if (nLength == 0)
		{
			return 0;
		}
		else
		{
			SDataBag sDataBag;
			istringstream iss(strBuf, std::ios::in | std::ios::binary);
			while (::bzero(static_cast<void*>(&sDataBag), sizeof(SDataBag)), !(iss.eof()))
			{
				iss.read(sDataBag.buf, sizeof(sDataBag.buf));
				sDataBag.Length = std::strlen(sDataBag.buf);
				nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sizeof(sDataBag.Length) + sDataBag.Length);
				if (nRet == -1)
				{
					return -1;
				}
				if (nRet == -2)
				{
					return -2;
				}
			}
			::bzero(static_cast<void*>(&sDataBag), sizeof(sDataBag));
			sDataBag.Length = 0;
			nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sizeof(sDataBag.Length) + sDataBag.Length);
			if (nRet == -1)
			{
				return -1;
			}
			if (nRet == -2)
			{
				return -2;
			}
		}
		return 0;
	}

	int
	CSocketIO::RecvMessage(IN string& strBuf) const
	{
		SDataBag sDataBag;
		int nRet;
		strBuf.clear();
		while(1)
		{
			std::memset(&sDataBag, 0, sizeof(sDataBag)); 
			nRet = RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(sDataBag.Length));
			if (nRet == -1)
			{
				return -1;
			}
			if (nRet == -2)
			{
				return -2;
			}
			if (sDataBag.Length == 0)
			{
				break;
			}
			else
			{
				nRet = RecvnBytes(sDataBag.buf, sDataBag.Length);
				if (nRet == -1)
				{
					return -1;
				}
				if (nRet == -2)
				{
					return -2;
				}
				strBuf.append(sDataBag.buf);
			}
		}
		return 0;
	}
}

#endif /* end of include guard: MY_SOCKETIO_H */
