/*************************************************************************
    > File Name: ScoketIO.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 21时51分42秒
 ************************************************************************/
#ifndef MY_SOCKET_IO_H
#define MY_SOCKET_IO_H
#include<myhead>
namespace NetworkLibrary
{

	struct SDataBag
	{
		size_t nLength;
		char chBuf[1024];
	};
	class CSocketIO
	{
		public:
			CSocketIO(IN int nNewSocketFd);
			
			void SendMessage(IN const string& strBuf) const;
			void RecvMessage(OUT  string& strBuf) const;
			void SendFile(IN const string& cstrFileName) const;
			void RecvFile(void);
		private:
			size_t SendnBytes(IN const void* buf, IN size_t nLen) const;
			size_t RecvnBytes(OUT void* buf, IN size_t nLen) const;
		private:
			int __cm_nNewSocketFd;
	};

	void 
	CSocketIO::SendFile(IN const string& cstrFileName) const
	{
		struct stat sFilestat;
		::bzero(&sFilestat, sizeof(sFilestat));
		if (cstrFileName.size() == 0)
		{
			return;
		}
		if (-1 == ::stat(cstrFileName.c_str(), &sFilestat))
		{
			std::perror("stat() failed or occur error");
			std::exit(-1);
		}
		if (S_ISDIR(sFilestat.st_mode))
		{
			cout << "can\'t send directory " << endl;
			return;
		}
		int fd = ::open(cstrFileName.c_str(), O_RDONLY);
		if (fd == -1)
		{
			std::perror("open() failed or occur error");
			std::exit(-1);
		}
		SDataBag sDataBag;
		::bzero(&sDataBag, sizeof(sDataBag));
		sDataBag.nLength = cstrFileName.size();
		std::strcpy(sDataBag.chBuf, cstrFileName.c_str());
		int nRet = SendnBytes(&sDataBag, sizeof(sDataBag.nLength) + sDataBag.nLength);
		if (nRet != 0)
		{
			cout << "传输出错或对端关闭" << endl;
			::close(fd);
			std::exit(-1);
		}
		while(::bzero(&sDataBag, sizeof(sDataBag)), (sDataBag.nLength = ::read(fd, sDataBag.chBuf, sizeof(sDataBag.chBuf)) > 0))
		{
			nRet = SendnBytes(&sDataBag, sizeof(sDataBag.nLength) + sDataBag.nLength);
			if (nRet != 0)
			{
				cout << "传输出错或对端关闭" << endl;
				::close(fd);
				std::exit(-1);
			}
		}
		sDataBag.nLength = 0;
		nRet = SendnBytes(&sDataBag, sizeof(sDataBag.nLength) + sDataBag.nLength);
		if (nRet != 0)
		{
			cout << "传输出错或对端关闭" << endl;
			::close(fd);
			std::exit(-1);
		}
		::close(fd);
	}

	void 
	CSocketIO::RecvFile(void)
	{
		SDataBag  sDataBag;
		::bzero(&sDataBag, sizeof(sDataBag));
		int nRet = RecvnBytes(&sDataBag.nLength, sizeof(sDataBag.nLength));
		if (nRet != 0)
		{
			cout << "传输出错或对端关闭" << endl;
			std::exit(-1);
		}
		if (sDataBag.nLength > 0)
		{
			nRet = RecvnBytes(sDataBag.chBuf, sDataBag.nLength);
			if (nRet != 0)
			{
				cout << "传输出错或对端关闭" << endl;
				std::exit(-1);
			}
			int fd = ::open(sDataBag.chBuf, O_WRONLY | O_CREAT | O_TRUNC);
			if (fd == -1)
			{
				std::perror("open() failed or occur error");
				std::exit(-1);
			}
			while(1)
			{
				::bzero(&sDataBag, sizeof(sDataBag));
				nRet = RecvnBytes(&sDataBag.nLength, sizeof(sDataBag.nLength));
				if (nRet != 0)
				{
					cout << "传输出错或对端关闭" << endl;
					::close(fd);
					std::exit(-1);
				}
				if (sDataBag.nLength == 0)
				{
					break;
				}
				if (sDataBag.nLength > 0)
				{
					nRet = RecvnBytes(&sDataBag.nLength, sDataBag.nLength);
					if (nRet != 0)
					{
						cout << "传输出错或对端关闭" << endl;
						::close(fd);
						std::exit(-1);
					}
					if (::write(fd, sDataBag.chBuf, sDataBag.nLength) != static_cast<ssize_t>(sDataBag.nLength))
					{
						cout << "写入文件出错" << endl;
						::close(fd);
						std::exit(-1);
					}
				}
				::close(fd);
			}
		}
	}
	
	void 
	CSocketIO::SendMessage(IN const string& strBuf) const
	{
		size_t nLen = strBuf.size();
		if (nLen == 0)
		{
		}
		else
		{
			SDataBag sDataBag;
			::bzero(&sDataBag, sizeof(sDataBag));
			istringstream iss(strBuf, std::ios::in | std::ios::binary);
			while(::bzero(&sDataBag, sizeof(SDataBag)), !iss.eof())
			{
				iss.read(sDataBag.chBuf, strlen(sDataBag.chBuf));
				sDataBag.nLength = strlen(sDataBag.chBuf);
				if (SendnBytes(&sDataBag, sizeof(sDataBag.nLength)+sDataBag.nLength) != 0)
				{
					cout << "传输出错或对端关闭" << endl;
					std::exit(-1);
				}
			}
			sDataBag.nLength = 0;
			if (SendnBytes(&sDataBag, sizeof(sDataBag.nLength)+sDataBag.nLength) != 0)
			{
				cout << "传输出错或对端关闭" << endl;
				std::exit(-1);
			}
		}
	}
	void 
	CSocketIO::RecvMessage(OUT  string& strBuf) const
	{
		SDataBag sDataBag;
		size_t nRet = 0;
		strBuf.clear();
		while(1)
		{
			std::memset(&sDataBag, 0, sizeof(sDataBag));
			nRet = RecvnBytes(&sDataBag.nLength, sizeof(sDataBag.nLength));
			if (nRet != 0)
			{
				cout << "接收消息出错" << endl;
				std::exit(-1);
			}
			else if (sDataBag.nLength == 0) 
			{
				break;
			}
			else if (sDataBag.nLength > 0)
			{
				nRet = RecvnBytes(sDataBag.chBuf, sDataBag.nLength);
				if (nRet != 0)
				{
					cout << "接收消息出错" << endl;
					std::exit(-1);
				}
				strBuf.append(sDataBag.chBuf);
			}
		}
	}

	inline
	CSocketIO::CSocketIO(IN int nNewSocketFd)
		:__cm_nNewSocketFd(nNewSocketFd)
	{
		assert(__cm_nNewSocketFd >= 0);
	}

	
	size_t
	CSocketIO::SendnBytes(IN const void* buf, IN size_t nLen) const
	{
		size_t nTotal = 0;
		int nPos = 0;
		while(nTotal < nLen)
		{
			nPos = ::send(__cm_nNewSocketFd, static_cast<const char*>(buf) + nTotal, nLen - nTotal, 0);
			if (nPos == -1)
			{
				if (errno == EINTR | errno == EAGAIN )
				{
					continue;
				}
				std::perror("recv() failed or occur error");
				std::exit(-1);
			}
			else if (nPos == 0) 
			{
				break;
			}
			nTotal += nPos;
		}
		return nLen - nTotal;
	}
	
	size_t
	CSocketIO::RecvnBytes(IN void* buf, IN size_t nLen) const
	{
		size_t nTotal = 0;
		int nPos = 0;
		while(nTotal < nLen)
		{
			nPos = ::recv(__cm_nNewSocketFd, static_cast<char*>(buf) + nTotal, nLen - nTotal, 0);
			if (nPos == -1)
			{
				if (errno == EINTR | errno == EAGAIN )
				{
					continue;
				}
				std::perror("recv() failed or occur error");
				std::exit(-1);
			}
			else if (nPos == 0) 
			{
				break;
			}
			nTotal += nPos;
		}
		return nLen - nTotal;
	}
}
#endif /* end of include guard: MY_SOCKET_IO_H */
