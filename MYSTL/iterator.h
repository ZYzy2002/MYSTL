#pragma once
//#include"trait.h"
namespace MYSTL
{
	//iterator tag
	class input_iterator_tag {};
	class forward_iterator_tag :public input_iterator_tag {};
	class bidirectional_iterator_tag :public forward_iterator_tag {};
	class random_assess_iterator_tag :public bidirectional_iterator_tag {};
	class output_iterator_tag {};

	//base class of containers'iterators
	template<typename T,typename interator_tag>
	class iterator
	{
	public:
		using interator_category	= interator_tag;
		using difference_type		= ptrdiff_t;//WIN64 uses the type "int"
		using value_type			= T;
		using value_pointer			= T*;
		using value_reference		= T&;
	};
	
	template<typename iterator_type>
	class iterator_trait;
	//an adaptor of interator to realize reverse.
	template<typename original_iterator_type>
	class reverse_iterator
	{
	public:
		/*using */
	private:
		original_iterator_type the_iterator;
	public:
		reverse_iterator() :the_iterator{ nullptr } {}
		reverse_iterator(original_iterator_type container_iterator) :the_iterator{ container_iterator } {}
		//reverse_iterator(typename iterator_trait<original_iterator_type>::value_type the_node_pointer) :the_iterator{ the_node_pointer } {} //can't get "list node pointer"

		typename iterator_trait<original_iterator_type>::value_type& operator*() const { return *the_iterator; }
		typename iterator_trait<original_iterator_type>::value_type* operator->() const { return the_iterator.operator->(); }
		reverse_iterator& operator++() { ++the_iterator; return*this; }
		reverse_iterator operator++(int) { reverse_iterator temp = *this; the_iterator++; return temp; };
		reverse_iterator& operator--() { --the_iterator; return *this; }
		reverse_iterator operator--(int) { reverse_iterator temp = *this; the_iterator--; return temp; };
	};
	template<typename original_iterator_type>
	class const_reverse_iterator
	{
	public:
		using interator_category	=typename original_iterator_type::iterator_category;
		using difference_type		= ptrdiff_t;//WIN64 uses the type "int"
		using value_type			= typename original_iterator_type::value_type;
		using value_pointer			= typename original_iterator_type::value_pointer;
		using value_reference		= typename original_iterator_type::value_reference;
	private:
		original_iterator_type the_iterator;
	public:
		const_reverse_iterator() :the_iterator{ nullptr } {}
		const_reverse_iterator(original_iterator_type container_iterator) :the_iterator{ container_iterator } {}
		

		const typename iterator_trait<original_iterator_type>::value_type& operator*() const { return *the_iterator; }
		const typename iterator_trait<original_iterator_type>::value_type* operator->() const { return the_iterator.operator->(); }

		const_reverse_iterator& operator++() { ++the_iterator; return*this; }
		const_reverse_iterator operator++(int) { const_reverse_iterator temp = *this; the_iterator++; return temp; };
		const_reverse_iterator& operator--() { --the_iterator; return *this; }
		const_reverse_iterator operator--(int) { const_reverse_iterator temp = *this; the_iterator--; return temp; };
	};

	//a global function to calculate the distance between two bidirectional_interators.   //?不知道是否可以计算const interator的距离
// 	template<typename Type_forward_interator>
// 	inline  typename MYSTL::iterator_trait<Type_forward_interator>::difference_type
// 		distance(Type_forward_interator First, Type_forward_interator Last)
// 	{
// 		typename MYSTL::iterator_trait<Type_forward_interator>::difference_type distance = 0;
// 		while (First != Last)
// 		{
// 			distance++;
// 			First++;
// 		}
// 		return distance;
// 	}
}