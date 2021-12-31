#pragma once



namespace MYSTL
{


	template<typename T>
	class allocator
	{
	public:
		using return_type = T*;

	public:

		static T* allocate();
		static T* allocate(size_t num);
		static void deallocate(T* p);
		static void deallocate(T* p, size_t num);
	};


	template<typename T>
	T* allocator<T>::allocate()
	{
		return new T;
	}
	template<typename T>
	T* allocator<T>::allocate(size_t num)
	{
		return new T[num];
	}

	template<typename T>
	void allocator<T>::deallocate(T* p)
	{
		delete p;
	}
	template<typename T>
	void allocator<T>::deallocate(T* p, size_t num)
	{
		delete[]p;
	}

}


