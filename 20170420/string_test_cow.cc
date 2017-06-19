/*************************************************************************
  > File Name: string_test_cow.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月22日 星期六 14时06分55秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int main(void)
{
	string s1 = "hello,world";
	string s2 = s1;
	string s3 = s2;
	const char * p1 = s1.c_str();
	const char * p2 = s2.c_str();
	const char * p3 = s3.c_str();

	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);
	printf("p3 = %p\n", p3);

	/*s3[0] = 'X';*/
	/*cout << "发生修改之后:" << endl;*/
	/*p1 = s1.c_str();*/
	/*p2 = s2.c_str();*/
	/*p3 = s3.c_str();*/

	/*cout << "s1 = " << s1 << endl;*/
	/*cout << "s2 = " << s2 << endl;*/
	/*cout << "s3 = " << s3 << endl;*/
	/*printf("p1 = %p\n", p1);*/
	/*printf("p2 = %p\n", p2);*/
	/*printf("p3 = %p\n", p3);*/

	/*cout << endl;*/
	/*cout << "读取s2[0]之后" << endl;*/
	/*cout << s2[0] << endl;*/
	/*p1 = s1.c_str();*/
	/*p2 = s2.c_str();*/
	/*p3 = s3.c_str();*/
	/*cout << "s1 = " << s1 << endl;*/
	/*cout << "s2 = " << s2 << endl;*/
	/*cout << "s3 = " << s3 << endl;*/
	/*printf("p1 = %p\n", p1);*/
	/*printf("p2 = %p\n", p2);*/
	/*printf("p3 = %p\n", p3);*/

	return 0;

}
