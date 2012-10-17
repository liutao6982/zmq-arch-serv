#ifndef _JJALLOC_
#define _JJALLOC_

#include <iostream>
#include <boost/pool/pool.hpp>

namespace CCTool
{

	template <class T1, class T2>
	inline void _construct(T1* p, const T2& value)
	{
		new(p) T1(value);
	}

	template <class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}

	template<class _Ty>
	struct _Allocator_base
	{	// base class for generic allocators
		typedef _Ty value_type;
	};

	// TEMPLATE CLASS _Allocator_base<const _Ty>
	template<class _Ty>
	struct _Allocator_base<const _Ty>
	{	// base class for generic allocators for const _Ty
		typedef _Ty value_type;
	};

	template <class T>
	class allocator
		: public _Allocator_base<T>
	{
	public:
		typedef _Allocator_base<T>				_Mybase;
		typedef typename _Mybase::value_type	value_type;
		typedef T*								pointer;
		typedef const T*						const_pointer;
		typedef T&								reference;
		typedef const T&						const_reference;
		typedef size_t							size_type;
		typedef ptrdiff_t						difference_type;

		//rebind allocator of type U
		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		allocator()
		{	// construct default allocator (do nothing)
		}

		allocator(const allocator<T>&)
		{	// construct by copying (do nothing)
		}

		template<class _Other>
		allocator(const allocator<_Other>&)
		{	// construct from a related allocator (do nothing)
		}

		template<class _Other>
		allocator<T>& operator=(const allocator<_Other>&)
		{	// assign from a related allocator (do nothing)
			return (*this);
		}

		template<class _Other>
		bool operator==(const allocator<_Other>&)
		{	// assign from a related allocator (do nothing)
			return true;
		}

		//hint used for locality.
		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}
		
		void deallocate(pointer p, size_type n) { _deallocate(p); }

		void construct(pointer p, const T& value)
		{
			_construct(p, value);
		}

		void destroy(pointer p) { _destroy(p); }

		pointer address(reference x) const 
		{ 
			return (pointer)&x; 
		}

		const_pointer const_address(const_reference x) const
		{
			return (const_pointer)&x;
		}

		size_type max_size() const
		{
			return size_type(UINT_MAX / sizeof(T));	
		}

		T* _allocate(ptrdiff_t size, T*)
		{
			T* tmp = (T*)mem_pool.ordered_malloc(size);
			if (tmp == 0)
			{
				std::cerr << "out of memory" << std::endl;
				exit(1);
			}
			return tmp;
		}

		void _deallocate(T* buffer)
		{
			mem_pool.free(buffer);
		}

	private:
		static boost::pool<> mem_pool;
	};

	template <class T>
	boost::pool<> allocator<T>::mem_pool(sizeof(T));

}//end of namespace JJ


#endif // _JJALLOC_