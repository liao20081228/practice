/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 12时07分33秒
 ************************************************************************/
#include"ThreadPool.h"
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
using namespace MyNamespace;
class CTask : public ITask
{
	public:
		virtual void Execute(void) const;
};

inline /* virtual*/ void
CTask::Execute(void) const
{

	::srand(::time(nullptr));
	std::cout << "id:  " << ::pthread_self() <<"__: "<<rand()/static_cast<double>(RAND_MAX/100) << std::endl;
}


int main(void)
{
	CThreadPool cThreadPool(5,10);
	ITask *pcITask = new CTask;
	cThreadPool.Start();
	for (int i = 0; i < 20; ++i) 
	{
		cThreadPool.AddTask(pcITask);
	}
	/*cThreadPool.Stop();*/

	return 0;
}
