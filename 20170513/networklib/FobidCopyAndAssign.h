/*************************************************************************
    > File Name: FobidCopyAndAssign.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 11时57分11秒
 ************************************************************************/
#ifndef MY_FORBID_COPY_AND_ASSIGN_H
#define MY_FORBID_COPY_AND_ASSIGN_H
namespace NetworkLibrary
{
	class CForbidCopyAndAssign
	{
		public:
			CForbidCopyAndAssign(void);
			~CForbidCopyAndAssign(void);
			CForbidCopyAndAssign(const CForbidCopyAndAssign& cLRef) = delete;
			CForbidCopyAndAssign& operator = ( const CForbidCopyAndAssign& cLRef) = delete;
		private:
			/*CForbidCopyAndAssign(IN const CForbidCopyAndAssign& cLRef);*/
			/*CForbidCopyAndAssign& operator =(IN const CForbidCopyAndAssign& cLRef);*/
			/*当显示提供了拷贝构造函数时，如果要使用其他构造函数，都必须显式提供，因为拷贝构造函数也是构造函数 */
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
#endif /* end of include guard: MY_FORBID_COPY_AND_ASSIGN_H */
