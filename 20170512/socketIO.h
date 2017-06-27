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

	CSocketIO::CSocketIO(IN int nSocketFd)
		:__cm_nSocketFd(nSocketFd)
	{
		if (__cm_nSocketFd == -1)
		{
			cout << "传入的新套接字错误" << endl;
			std::exit(-1);
		}
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
				if(errno == EINTR || errno == EAGAIN)
				{
					continue;
				}
				std::perror("recv faild");
				std::exit(-1);
			}
			else if (nPosition == 0) /* 对端关闭*/
			{
				break;
			}
			nTotal += nPosition;
		}
		return nDataLength - nTotal;
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
				if(errno == EINTR || errno ==  EAGAIN)  /* 重启发送操作*/
				{
					continue;
				}
				std::perror("send faild");
				std::exit(-1);
			}
			else if (nPosition == 0)
			{
				break; //对端关闭
			}
			nTotal += nPosition;
		}
		return nDataLength - nTotal;
	}
	
	void
	CSocketIO::SendFile(IN const string& strFileName) const
	{
		struct stat sFileState;
		::bzero(&sFileState,sizeof(sFileState));
		if (-1 == ::stat(strFileName.c_str(),&sFileState)) /* 读取文件信息*/
		{
			::perror("stat() failed");
			std::exit(-1);
		}
		if (S_ISDIR(sFileState.st_mode)) /* 如果是目录则不能发送*/
		{
			cout << "cann\'t send directory" << endl;
			std::exit(-1);
		}

		int nFd = ::open(strFileName.c_str(),O_RDONLY);/* 打开文件*/
		if (nFd == -1)
		{
			std::perror("opend file failed");
			std::exit(-1);
		}
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(sDataBag));
		sDataBag.Length = strFileName.size();  /* 首先发送文件名*/
		std::strcpy(sDataBag.buf, strFileName.c_str());
		int nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		if (nRet != 0)
		{
			::close(nFd);
			std::exit(-1);
		}
		//当到大文件末尾时候，read返回0
		while(::bzero(&sDataBag, sizeof(sDataBag)), (sDataBag.Length = ::read(nFd, sDataBag.buf, sizeof(sDataBag.buf))) > 0)
		{
			nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
			if (nRet != 0)
			{
				::close(nFd);
				std::exit(-1);
			}
		}
		sDataBag.Length = 0;
		nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sDataBag.Length + sizeof(int));
		if (nRet != 0 )
		{
			::close(nFd);
			std::exit(-1);
		}
		::close(nFd);
	}

	void 
	CSocketIO::RecvFile(void) const 
	{
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(SDataBag));
		int nRet = RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int)); /* 先接收数据长度*/
		if (nRet != 0)
		{
			cout << "接收文件出错" << endl;
			std::exit(-1);
		}
		if (sDataBag.Length > 0) /* 如果长度大于0*/
		{
			nRet = RecvnBytes(sDataBag.buf,sDataBag.Length); /* 接收文件名*/
			if (nRet != 0)
			{
				cout << "接收文件出错" << endl;
				std::exit(-1);
			}
			int nFd = ::open(sDataBag.buf,O_WRONLY|O_CREAT|O_TRUNC,0655);
			if (nFd == -1)
			{
				std::perror("open failed");
				std::exit(-1);
			}
			while (1)
			{
				::bzero(&sDataBag, sizeof(SDataBag));
				nRet = RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(int));/* 接收长度*/
				if (nRet != 0)
				{
					::close(nFd);
					cout << "接收文件出错" << endl;
					std::exit(-1);
				}
				if(sDataBag.Length > 0)
				{
					nRet = RecvnBytes(sDataBag.buf,sDataBag.Length);/* 接收数据，写入数据*/
					if (nRet != 0)
					{
						::close(nFd);
						cout << "接收文件出错" << endl;
						std::exit(-1);
					}
					if (::write(nFd,sDataBag.buf,sDataBag.Length)!= sDataBag.Length)
					{
						::close(nFd);
						cout << "写入文件出错" << endl;
						std::exit(-1);
					}
				}
				else
				{
					break;
				}
			}
			::close(nFd);
		}
	}

	void
	CSocketIO::SendMessage(IN const string&  strBuf) const
	{
		int nLength = strBuf.size();
		int nRet = 0;
		if (nLength == 0)
		{
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
				if (nRet != 0 )
				{
					cout << "发送消息出错" << endl;
					std::exit(-1);
				}
			}
			::bzero(static_cast<void*>(&sDataBag), sizeof(sDataBag));
			sDataBag.Length = 0;
			nRet = SendnBytes(reinterpret_cast<char*>(&sDataBag), sizeof(sDataBag.Length) + sDataBag.Length);
			if (nRet != 0 )
			{
				cout << "发送消息出错" << endl;
				std::exit(-1);
			}
		}
	}

	void
	CSocketIO::RecvMessage(IN string& strBuf) const
	{
		SDataBag sDataBag;
		int nRet;
		strBuf.clear();
		while(1)
		{
			std::memset(&sDataBag, 0, sizeof(sDataBag)); 
			nRet = RecvnBytes(reinterpret_cast<char*>(&sDataBag.Length), sizeof(sDataBag.Length));
			if (nRet != 0 )
			{
				cout << "接收消息出错" << endl;
				std::exit(-1);
			}
			if (sDataBag.Length == 0)
			{
				break;
			}
			else
			{
				nRet = RecvnBytes(sDataBag.buf, sDataBag.Length);
				if (nRet != 0 )
				{
					cout << "接收消息出错" << endl;
					std::exit(-1);
				}
				strBuf.append(sDataBag.buf);
			}
		}
	}
}

#endif /* end of include guard: MY_SOCKETIO_H */
