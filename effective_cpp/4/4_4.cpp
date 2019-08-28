#include<iostream>
#include<vector>
#include<typeinfo>
#include<boost/type_index.hpp>
struct widget
{
	int a;
	int b;
};

template<typename T>
void fun(const T& param)
{
	std::cout<< boost::typeindex::type_id_with_cvr<T>().pretty_name()<< std::endl;
	std::cout<< boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name()<< std::endl;
}


std::vector<widget> create_vec()
{
	std::vector<widget> vec={widget()};
	return vec;
}

int main(void)
{
	const auto vw=create_vec();
	fun(&vw[0]);
	return 0;
}
