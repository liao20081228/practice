/*************************************************************************
  > File Name: alloc.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月06日 星期六 15时08分19秒
 ************************************************************************/
#ifndef __SGI_STL_INTERNAL_ALLOC_H  /* 防止本文件被重复引入*/
#	define __SGI_STL_INTERNAL_ALLOC_H
/* 开启一级分配器*/
#	ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG   
#		define __USE_MALLOC
#	endif
/* 定义内存真的完全耗尽时，如何抛出异常*/
#	include <stdio.h>
#	include <stdlib.h>
#	define __THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1)
/* 引入头文件*/
#	include <stddef.h>   
#	include <stdlib.h>
#	include <string.h>
#	include <assert.h>
/*定义约束 */
#	ifndef __RESTRICT
#		define __RESTRICT
#	endif
template<int __inst>
class __malloc_alloc_template   /* 一级配置器*/
{
	private:
/* 指向oom异常发生时的处理函数，是一个静态函数指针,初始值为空*/
		static void (* __malloc_alloc_oom_handler)(); 
/*
 *allocate调用malloc申请空间失败后的处理函数，oom是内存耗尽的意思，out of memory
 *静态成员函数中只能调用静态成员 
 *该函数被调用时，说明malloc开空间失败，发生oom异常，因此首先应该调用oom处理函数，获取新空间后，
 *再开辟内存，但是处理oom异常时，是否获得了新的空间是未知的，要通过malloc开空间检来检测
 */ 
		static void* _S_oom_malloc(size_t __n)
		{
			void (*__my_malloc_handler)();/* 定义一个函数指针指向处理oom异常的函数*/
			void *__result;
			for(;;)
			{
				if((__my_malloc_handler=__malloc_alloc_oom_handler)==NULL) /* 如果没有oom异常的处理函数就抛出异常*/
				{
					__THROW_BAD_ALLOC;
				}
				(*__my_malloc_handler)();/* 否则就调用内存耗尽是的处理函数,获取空间，但不一定真的还有空间*/
				__result = malloc(__n); /* malloc开__n个空间，*/
				if (__result) /* 如果分配成功说明上面获取空间成功，否则说明内存真的耗尽*/
					return __result;
			}
		}

		/*reallocate调用realloc重新分配内存失败时的处理函数*/
		static void* _S_oom_realloc(void*__p, size_t __n)
		{
			void (*__my_malloc_handler)();
			void *__result;
			for(;;)
			{
				if((__my_malloc_handler=__malloc_alloc_oom_handler)==NULL)
				{
					__THROW_BAD_ALLOC;
				}
				(*__my_malloc_handler)();
				if((__result=realloc(__p,__n)))
					return __result; 
			}
		}
	
	public:
		static void* allocate(size_t __n)/* 分配空间_n*/
		{
			void* __result = malloc(__n);
			if (0 == __result)
				__result = _S_oom_malloc(__n);/* 如果申请堆空间失败交给 _S_oom_malloc处理*/
			return __result;
		}
		static void deallocate(void* __p, size_t /* __n */)  /* 释放空间*/
		{
			free(__p);
		}
		static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz)/* 重新分配空间*/
		{
			void* __result = realloc(__p, __new_sz);  
			if (0 == __result) 
				__result = _S_oom_realloc(__p, __new_sz);/* 如果重新分配空间失败，交给_S_oom_realloc处理*/
			return __result;
		}
		static void (* __set_malloc_handler(void (*__f)()))()/* 设置指向内存耗尽时的处理函数的指针__malloc_alloc_oom_handler为__f*/
		{
			void (* __old)() = __malloc_alloc_oom_handler;/* 保存原来的处理函数*/
			__malloc_alloc_oom_handler = __f;/* 设置新的处理函数*/
			return(__old);/* 返回原来的处理函数*/
		}
};
template <int __inst>
void (*__malloc_alloc_template<__inst>::__malloc_alloc_oom_handler)() = NULL;  /*c++11中只有 静态非常量成员必须在类外初始化*/

typedef __malloc_alloc_template<0> malloc_alloc; /* malloc 定义的对象获得的是一段内存的起始地址由malloc（0）分配，但并确切大小，也可以认为无限大*/

/* 基本简单的alloc*/
template<typename _Tp,typename _Alloc>  /* _TP是开辟空间的类型，而_alloc是__malloc_alloc_template*/
class simple_alloc
{
	public:
		static _Tp* allocate(size_t __n)  /* 分配__n个_TP类型的空间单元*/
		{ 
			return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof (_Tp));  
		}
		static _Tp* allocate(void)/* 分配1个_Tp类型的空间单元*/
		{ 
			return (_Tp*) _Alloc::allocate(sizeof (_Tp));  
		}
		static void deallocate(_Tp* __p, size_t __n) /* 释放__n个_TP类型的空间单元*/
		{ 
			if (0 != __n) _Alloc::deallocate(__p, __n * sizeof (_Tp));  
		}
		static void deallocate(_Tp* __p)  /* 释放1个_Tp类型的内存单元*/
		{ 
			_Alloc::deallocate(__p, sizeof (_Tp));  
		}
};

//debug版本的alloc
//模板参数_Alloc是__malloc_alloc_template
template<typename _Alloc>
class debug_alloc
{
	private:
		enum{_S_extra = 8}; /* 用来存放空间大小，8个字节*/
	public:
		static void* allocate(size_t __n)
		{
			char* __result = (char*)_Alloc::allocate(__n + (int) _S_extra);/* 开辟__n+8个空间*/
			*(size_t*)__result = __n;/* 前8个字节存放开辟的可用空间大小*/
			return __result + (int) _S_extra;/* 返回可用空间首地址*/
		}
		static void deallocate(void* __p, size_t __n) /* 释放__n+8个空间*/
		{
			char* __real_p = (char*)__p - (int) _S_extra;/*获得真实的应该释放的空间的首地址*/
			assert(*(size_t*)__real_p == __n);/*这是一个断言， 在不出异常的情况下，存放的字节数应该等于__n，否则就退出程序*/
			_Alloc::deallocate(__real_p, __n + (int) _S_extra);/* 释放真实分配的空间*/
		}
		static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz) /* 重新分配  __new_sz个空间*/
		{
			char* __real_p = (char*)__p - (int) _S_extra;/*获得真实的应该原来分配的空间的首地址*/
			assert(*(size_t*)__real_p == __old_sz);/*这是一个断言， 在不出异常的情况下，存放的字节数应该等于__n，否则就退出程序*/
			char* __result = (char*)_Alloc::reallocate(__real_p, __old_sz + (int) _S_extra,__new_sz + (int) _S_extra);/* 重新分配__new_sz+8个空间*/
			*(size_t*)__result = __new_sz;/* 保存新空间的可用大小*/
			return __result + (int) _S_extra;/* 返回重新分配的可用空间的首地址*/
		}
};

#ifdef __USE_MALLOC
typedef malloc_alloc alloc;  /* malloc_alloc,alloc,single_client_alloc 都是 __malloc_alloc_template<0>的别名*/
typedef malloc_alloc single_client_alloc;
#else
/*
 * 默认节点分配器，也就是第二级分配器。
 * 对合理的编译器来说，这应该与原始的STL类特定的分配器一样快，但是碎片更少。
 * Default_alloc_template参数是实验性的，未来可能会消失，用户现在应该只使用alloc。
 * 二级配置器维护了16个自由单链表，16个表头指针连续存放在128B内存中，第i个链表维护的节点指向大小为8*i的内存块
 * 分配空间时：
 *     如果大于128B,则由一级配置器处理，否则，由二级配置器从内存池中取。
 *     二级配置器 分配地址时， 先计算出要分配的内存块的大小（大于等于实际所需大小），
 *     方法是（__bytes+8-1）&（~（8-1）），同时又因为链表头指针顺序存储，可以计算出链表头指针。
 *     然后从链表中取下一个节点（指向一个8*i B的内存块）分配出去,然后将头指针执行指向第二个节点，
 *     使其成为第一个节点。如果维护的内存块不够，则向一级配置器求助。
 *回收空间时：
 *      把该空间的节点放回自由链表的吗末尾。
 *
 *第一个模板参数指定多个线程是否可以使用此分配器。从default_alloc的一个对象分配一些空间并将其分配给另一个对象是安全的。这有效地将其空间所有权转让给第二个。这可能对引用点产生不良影响。
 *第二个参数是未引用的，仅用于允许创建多个default_alloc实例。
 *基于不同分配器建立的容器具有不同的类型，限制了此方法的实用性。
 */

template <bool threads, int inst>
class __default_alloc_template 
{
	private:
		enum {_ALIGN = 8,_NFREELISTS = 16,_MAX_BYTES = 128};

		/* 首先设置16个自由链表*/
		union _Obj/* 定义自由链表结点*/ 
		{
			union _Obj* _M_free_list_link;  /* 链表指针*/
			char _M_client_data[1];    /* The client sees this*/
		};
		static _Obj*  _S_free_list[_NFREELISTS];/* 定义存放16个链表的头指针的指针数组*/ 

		/* 接着计算出要分配的内存快的大小和应该选择的自由链表的头结点的下标*/
		static size_t _S_round_up(size_t __bytes) /* 计算应该分配的内存块大小*/
		{
			return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); 
		}
		static  size_t _S_freelist_index(size_t __bytes)/* 计算应该分配空间的自由链表的头结点在数组中的下标*/ 
		{
			return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);          
		}

		static void* _S_refill(size_t __n);
		static char* _S_chunk_alloc(size_t __size, int& __nobjs);

		static char* _S_start_free;  /* 开始地址*/
		static char* _S_end_free;/* 结束地址*/
		static size_t _S_heap_size;/* 堆空间大小*/
	public:
		static void* allocate(size_t __n) /* __n必须大于0,如果申请的空间大于128B则交给一级配置器处理*/
		{
			void* __ret = 0;
			if (__n > (size_t) _MAX_BYTES) 
			{
				__ret = malloc_alloc::allocate(__n);  
			}
			else/*否则就自己从内存池中分配 */ 
			{
				_Obj** __my_free_list= _S_free_list + _S_freelist_index(__n);/* 找到应该分配内存块的自由链表的头结点的地址,这是一个二级指针*/
				_Obj* __result = *__my_free_list;  /*取二级指针的内容得到一级指针 */
				if (__result == 0) /* 如果指针为空*/
					__ret = _S_refill(_S_round_up(__n));
				else 
				{                                                     
					*__my_free_list = __result -> _M_free_list_link;
					__ret = __result;
				}                                                                         
			}
			return __ret;
		}
		static void deallocate(void* __p, size_t __n)
		{
			if (__n > (size_t) _MAX_BYTES)
				malloc_alloc::deallocate(__p, __n);
			else 
			{
				_Obj* *  __my_free_list= _S_free_list + _S_freelist_index(__n);
				_Obj* __q = (_Obj*)__p;
				__q -> _M_free_list_link = *__my_free_list;
				*__my_free_list = __q;
			}
		}
		static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);
};

typedef __default_alloc_template<true, 0> alloc;
typedef __default_alloc_template<false, 0> single_client_alloc;

template <bool __threads, int __inst>
inline bool operator==(const __default_alloc_template<__threads, __inst>&,const __default_alloc_template<__threads, __inst>&)
{
	return true;
}

# ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
	template <bool __threads, int __inst>
inline bool operator!=(const __default_alloc_template<__threads, __inst>&,
		const __default_alloc_template<__threads, __inst>&)
{
	return false;
}
# endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <bool __threads, int __inst>
char* __default_alloc_template<__threads, __inst>::_S_chunk_alloc(size_t __size,int& __nobjs)
{
	char* __result;
	size_t __total_bytes = __size * __nobjs;/*申请堆空间的大小 */
	size_t __bytes_left = _S_end_free - _S_start_free;/*剩余空间的大小 */
	if (__bytes_left >= __total_bytes)/*如果剩余空间大于要分配的空间 */ 
	{
		__result = _S_start_free;
		_S_start_free += __total_bytes;
		return(__result);
	} 
	else if (__bytes_left >= __size) 
	{
		__nobjs = (int)(__bytes_left/__size);
		__total_bytes = __size * __nobjs;
		__result = _S_start_free;
		_S_start_free += __total_bytes;
		return(__result);

	} 
	else 
	{
		size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
		if (__bytes_left > 0) 
		{
			_Obj** __my_free_list =_S_free_list + _S_freelist_index(__bytes_left);
			((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;
			*__my_free_list = (_Obj*)_S_start_free;
		}
		_S_start_free = (char*)malloc(__bytes_to_get);
		if (0 == _S_start_free) 
		{
			size_t __i;
			_Obj** __my_free_list;
			_Obj* __p;
			for (__i = __size;__i <= (size_t) _MAX_BYTES;__i += (size_t) _ALIGN) 
			{
				__my_free_list = _S_free_list + _S_freelist_index(__i);
				__p = *__my_free_list;
				if (0 != __p) 
				{
					*__my_free_list = __p -> _M_free_list_link;
					_S_start_free = (char*)__p;
					_S_end_free = _S_start_free + __i;
					return(_S_chunk_alloc(__size, __nobjs));
				}
			}
			_S_end_free = 0;	// In case of exception.
			_S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);
		}
		_S_heap_size += __bytes_to_get;
		_S_end_free = _S_start_free + __bytes_to_get;
		return(_S_chunk_alloc(__size, __nobjs));
	}
}




















#endif

