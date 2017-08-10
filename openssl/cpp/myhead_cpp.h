#ifndef MY_CPP_AND_C_ALL_HEADER
#define MY_CPP_AND_C_ALL_HEADER

/*linux c*/
#include<sys/stat.h>
#include<unistd.h> 
#include<sys/stat.h> 
#include<sys/types.h> 
#include<dirent.h> 
#include<pwd.h>
#include<grp.h>
#include<fcntl.h> 
#include<sys/select.h>
#include<syslog.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/ipc.h> 
#include<sys/shm.h> 
#include<sys/sem.h>
#include<sys/time.h>
#include<pthread.h>
#include<malloc.h>
#include<semaphore.h>
#include<arpa/inet.h>
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/uio.h>
#include<sys/epoll.h>
#include<poll.h>
#include<strings.h>
#include<sched.h>
#include<sys/timerfd.h>
#include<sys/eventfd.h>

/*standard C++11*/
/*工具库*/
#include<cstdlib> /*通用实用程序：程序控制，动态内存分配，随机数，排序和搜索*/
#include<csignal> /*用于信号量（Signal）管理的函数及宏常量*/
#include<csetjmp> /*包含用来跳转到执行上下文（Execution context）的宏或函数*/
#include<cstdarg> /*可变长参数列表的处理*/
#include<typeinfo> /*运行时类型信息*/
#include<typeindex>/* std::type_index*/
#include<type_traits> /*C++11 编译时类型信息*/
#include<bitset> /*std::bitset 类模板，提供位集操作*/
#include<functional> /*提供被设计用来支持标准算法的函数对象*/
#include<utility> /*大量实用程序组件*/
#include<ctime> /*C型时间/日期实用程序*/
#include<chrono> /*C++11 C++时间实用程序*/
#include<cstddef> /*定义（typedef）了一些类型，比如：std::size_t、NULL及其它*/
#include<initializer_list> /*C++11 std::initializer_list 类模板*/
#include<tuple> /*C++11 std::tuple 类模板，使C++程序支持多元组*/
/*动态内存管理*/
#include<new> /*底层内存管理*/
#include<memory> /*用于上层内存管理，包含智能指针、内存分配器、哈希（Hash）、类型转换等。*/
#include<scoped_allocator> /*C++11 支持可嵌套的内存分配器（Allocator）*/
/* 数值限制*/
#include<climits> /*整数类型的限制*/
#include<cfloat> /*浮点数类型的限制*/
#include<cstdint> /*一些字节大小固定（Fixed-size）的类型及其它类型的限制*/
#include<cinttypes> /*格式化相关的宏*/
#include<limits>/* 提供了查询基础类型属性的标准方法*/
/* 错误诊断处理*/
#include<exception> /*异常处理*/
#include<stdexcept> /*提供了一些标准异常对象*/
#include<cassert> /*提供了用于断言的宏*/
#include<cerrno> /*提供了一个保存了最近错误号的宏*/
#include<system_error> /*C++11 定义了 std::error_code ，用来依赖于平台的（Platform-dependent）错误码*/
/*字符串库*/
#include<cctype> /*用来判断字符数据类型的函数，比如：std::isdigit、std::isspace、std::islower*/
#include<cwctype> /*用来判断宽字符数据类型的函数，比如：std::iswdigit、std::iswspace、std::iswlower*/
#include<cstring> /*大量窄字符字符串处理函数*/
#include<cwchar> /*大量宽字符及多字符字符串处理函数*/
// #include<cuchar> /*C++11 C型Unicode字符转换函数,linux中没有提供*/
#include<string> /*std::basic_string 类模板*/
/*容器库*/
#include<array> /*C++11 std::array 容器*/
#include<vector> /*std::vector 容器*/
#include<deque> /*std::deque 容器*/
#include<list> /*std::list 容器*/
#include<forward_list> /*C++11 std::forward_list 容器*/
#include<set> /*std::set 及 std::multiset 关联容器*/
#include<map> /*std::map 及 std::multimap 关联容器*/
#include<unordered_set> /*C++11 std::unordered_set 及 std::unordered_multiset 无序关联容器*/
#include<unordered_map> /*C++11 std::unordered_map 及 std::unordered_multimap 无序关联容器*/
#include<queue> /*std::queue 及 std::priority_queue 容器适配器*/
#include<stack> /*std::stack 容器适配器*/
/*算法库*/
#include<algorithm> /*用于操作容器的算法*/
/*迭代器库*/
#include<iterator> /*容器迭代器*/
/*数学库*/
#include<cmath> /*普通的数学函数*/
#include<complex> /*复数类型*/
#include<valarray> /*包含用来表示及操作值的数组的类，比如获得一个数组中所有值的和、最大值、最小值等*/
#include<random>/* 随机数生成器与随机数分布*/
#include<numeric> /*对容器中的值进行数值操作*/
#include<ratio> /*C++11 编译时有理数运算*/
/*输入/输出库*/
#include<iosfwd> /*前置声明所有输入/输出库中的类*/
#include<ios> /*std::ios_base 及 std::basic_ios 类模板*/
#include<istream> /*std::basic_istream 类模板*/
#include<ostream> /*std::basic_ostream 类模板*/
#include<iostream> /*std::basic_iostream 类模板*/
#include<fstream> /*std::basic_fstream、std::basic_ifstream、std::basic_ofstream 类模板*/
#include<sstream> /*std::basic_stringstream、std::basic_istringstream、std::basic_ostringstream 类模板*/
#include<iomanip> /*控制输入及输出格式的输助函数*/
#include<streambuf> /*std::basic_streambuf 类模板*/
#include<cstdio> /*C型输入/输出函数*/
/*本地化库*/
#include<locale> /*本地化相关，包括对国际字符分类的的支持，对字符串排序规则的支持等*/
#include<clocale> /*C型本地化相关*/
#include<codecvt> /*C++11 Unicode转换机制*/
/*正则表达式库*/
 #include<regex> /*C++11 提供了支持处理正则表达式的类、算法及迭代器*/
/*原子操作库*/
#include<atomic> /*C++11 原子操作相关*/
/*线程支持库*/
#include<thread> /*C++11 std::thread 类及一些用来创建或管理线程的线程支持函数*/
#include<mutex> /*C++11 互斥原语*/
#include<future> /*C++11 提供支持异步执行的原语*/
#include<condition_variable> /*C++11 线程等待条件*/
/*空的c 头文件*/
#include<ctgmath> /*C++11 简单的包含头文件<ccomplex>及<cmath>*/
#include<ccomplex>
/* 无意义c头文件，在c中定义的宏已经成为c++的关键字*/
// #include<ciso646> 
// #include<cstdalign> 
// #include<cstdbool> 
#define IN  /* 表示输入参数*/
#define OUT /* 表示输出参数*/
//input/output
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istream;
using std::ostream;
using std::iostream;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
//container
using std::iterator;
using std::array;
using std::deque;
using std::vector;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::stack;
using std::queue;
using std::priority_queue;
//pointer manerger
using std::auto_ptr;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
#endif
