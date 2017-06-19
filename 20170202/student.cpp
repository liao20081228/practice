/*************************************************************************
    > File Name: student.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月04日 星期六 19时10分11秒
 ************************************************************************/

#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;

class stu
{
	private:
			int _id;
			char _sex;
			float _scorre;
			void setid(int id)
			{
				_id=id;
			}
			void setsex(char sex)
			{
				_sex=sex;
			}
			void setscore(int score)
			{
				_scorre=score;
			}	
	public:
			void setinfo(int id,char sex,float score)
			{
				setid(id);
				setsex(sex);
				setscore(score);
			}
			void print()
			{
				cout<<"id="<<_id<<"sex="<<_sex<<"score="<<_scorre<<endl;
			}
};

int main()
{
	stu xiaowang;
	xiaowang.setinfo(1000,'m',100);
	xiaowang.print();
	return 0;
	
}
