/*************************************************************************
    > File Name: Task.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月28日 星期三 21时21分39秒
 ************************************************************************/
#ifndef MY_TASK_H
#define MY_TASK_H

namespace MyNamespace
{
	//抽象任务类，由其派生类决定具体任务
	class ITask
	{
		public:
			virtual ~ITask(void);
			virtual void Execute(void) const = 0;
	};
}
namespace MyNamespace
{
	inline /*virtual */
	ITask::~ITask(void)
	{
	}
}

#endif /* end of include guard: MY_TASK_H */
