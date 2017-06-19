/*************************************************************************
    > File Name: forbid.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 22时12分02秒
 ************************************************************************/
#ifndef MY_FORBID_H
#define MY_FORBID_H

namespace MyNamespace
{
	class CForbidCopyAndAssign
	{
		public:
			CForbidCopyAndAssign(void);
			~CForbidCopyAndAssign();
			CForbidCopyAndAssign(const CForbidCopyAndAssign& lref) =delete;
			CForbidCopyAndAssign& operator = (const CForbidCopyAndAssign& lref) = delete;
	};

	inline
	CForbidCopyAndAssign::CForbidCopyAndAssign(void)
	{
	}

	inline
	CForbidCopyAndAssign::~CForbidCopyAndAssign(void)
	{
	}
}

#endif /* end of include guard: MY_FORBID_H */
