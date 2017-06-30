/*************************************************************************
    > File Name: forbidcopyandassign.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月28日 星期三 21时04分47秒
 ************************************************************************/
#ifndef MY_FORBID_COPY_AND_ASSIGN_H
#define MY_FORBID_COPY_AND_ASSIGN_H
namespace MyNamespace
{
	//禁止拷贝
	class CForbidCopyAndAssign
	{
		public:
			CForbidCopyAndAssign(void);
			~CForbidCopyAndAssign(void);
			CForbidCopyAndAssign(const CForbidCopyAndAssign& lref) = delete;
			CForbidCopyAndAssign& operator = (const CForbidCopyAndAssign& lref) = delete;
	};
}
/*CForbidCopyAndAssign的实现*/
namespace MyNamespace
{
	inline
	CForbidCopyAndAssign::CForbidCopyAndAssign(void)
	{
	}

	inline 
	CForbidCopyAndAssign::~CForbidCopyAndAssign(void)
	{
	}
}
#endif /* end of include guard: MY_FORBID_COPY_AND_ASSIGN_H */
