/*************************************************************************
    > File Name: observer.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月30日 星期二 22时17分17秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/

//由于Subject要使用obsever类，所以要前置声明
class IObsever;

//Subject抽象类，提供规范接口
class ISubject  
{
	public:
		ISubject(IN int state = -1); //构造函数
		virtual ~ISubject(void); //析构函数
		
		void Attach(IN IObsever* pIObsever); //添加观察者
		void Detach(IN IObsever* pIObsever); //删除观察者
		void Notify(void); //通知状态发生改变
		
		virtual void DoSetState(IN int nState) = 0; //设置状态
		virtual int DoGetState(void) const = 0; //获取状态
	protected:
		int __cm_nSubjectState;  //主题状态
		list <IObsever*> __cm_liObsever; //观察者集合
};


//Obsever 基类
class IObsever
{
	public:
		IObsever(IN int state = -1); //构造函数
		 virtual ~IObsever(void); //析构函数
		
		void Display(void);
		virtual void DoUpdate(IN const ISubject* pISubject) = 0; //更新观察者状态
	protected:
		int __cm_nObseverState;
};


//Subject
class  CSubject : public ISubject
{
	public:
		CSubject(IN int nState = -1); //构造函数
		virtual ~CSubject(void); //析构函数
		
		virtual void DoSetState(IN int nState = -1);
		virtual int DoGetState(void) const;
};


//Obsever
class CObsever : public IObsever
{
	public:
		CObsever(IN int nState = -1); //构造函数
		virtual ~CObsever(void); //析构函数
		virtual void DoUpdate(IN const ISubject* pISubject); //更新观察者状态
};


//ISubject 构造函数
inline
ISubject::ISubject(IN int nState /* = -1 */)
	:__cm_nSubjectState(nState)
{

}

//析构函数
inline
ISubject::~ISubject(void)
{
}


//添加观察者
inline void
ISubject::Attach(IN IObsever* pIObsever)
{
	__cm_liObsever.push_back(pIObsever);
}


//删除观察者
void
ISubject::Detach(IN IObsever* pIObsever)
{
	list <IObsever*>::iterator iter;
	iter = std::find(__cm_liObsever.begin(), __cm_liObsever.end(), pIObsever);
	if (__cm_liObsever.end() != iter)
	{
		__cm_liObsever.erase(iter);
	}
}


//通知每一观察者
void
ISubject::Notify(void) 
{
	for (IObsever* elem : __cm_liObsever) //不能加const，加了const表示指针所指内容无法更改
	{
		elem->DoUpdate(this);
	}
	/*
	 *list <IObsever*>::iterator iter,iterEnd;
	 *for(iter = __cm_liObsever.begin(), iterEnd = __cm_liObsever.end(); iter != iterEnd; ++iter)
	 *{
	 *    (*iter)->DoUpdate(this);
	 *}
	 */
}


//CSubject的构造函数
inline 
CSubject::CSubject(IN int nState /* = -1 */)
	:ISubject(nState)
{
}

//CSubject的析构函数
inline
CSubject::~CSubject(void)
{
}


//设置状态
inline  /* virtual */ void
CSubject::DoSetState(IN int nState)
{
	__cm_nSubjectState = nState;
	return;
}


//获取状态
inline /*virtual */ int
CSubject::DoGetState(void) const
{
	return __cm_nSubjectState;
}


//Iobsever构造函数
inline
IObsever::IObsever(IN int nState /* = -1 */)
	:__cm_nObseverState(nState)
{
}


//IObsever析构函数
inline
IObsever::~IObsever(void)
{
}


//
inline void
IObsever::Display(void)
{
	cout << __cm_nObseverState << endl;
	
}


//CObsever构造函数
inline
CObsever::CObsever(IN int nState /* = -1 */)
	:IObsever(nState)
{

}


//destructor of CObsever
inline
CObsever::~CObsever(void)
{
}


//update state of Obsever
inline /* virtual */ void
CObsever::DoUpdate(IN const ISubject* pISubject) 
{
	__cm_nObseverState = pISubject->DoGetState();
}


int main(void)
{
	//创建观察者和主题
	IObsever* pIObseverA = new CObsever;
	IObsever* pIObseverB = new CObsever;
	IObsever* pIObseverC = new CObsever;
	
	ISubject* pISubject = new CSubject;

	//display the state of every obsever
	pIObseverA->Display();
	pIObseverB->Display();
	pIObseverC->Display();
	
	//attach pIObseverA
	pISubject->Attach(pIObseverA);
	pISubject->Attach(pIObseverB);
	pISubject->Attach(pIObseverC);
	
	//after change state of Subjecc ,Notify every obsever
	pISubject->DoSetState(100);
	pISubject->Notify();
	
	pIObseverA->Display();
	pIObseverB->Display();
	pIObseverC->Display();
	return 0;
}
