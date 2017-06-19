/*************************************************************************
    > File Name: task.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 22时00分44秒
 ************************************************************************/
#ifndef MY_TASK_H
#define MY_TASK_H

#include"forbid.h"
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	class CTask : public CForbidCopyAndAssign
	{
		public:
			CTask(std::function<void()> cExecute);
			~CTask(void);
		public:
			void Execute(void) const;
		private:
			std::function<void()> __cm_cExecute;
	};

	inline
	CTask::CTask(std::function<void()> cExecute)
		:__cm_cExecute(cExecute)
	{
	}

	inline
	CTask::~CTask(void)
	{

	}

	inline void
	CTask
	::Execute(void) const
	{
		__cm_cExecute();
	}
}
#endif /* end of include guard: MY_TASK_H */
