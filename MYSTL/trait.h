#pragma once

#include"iterator.h"

namespace MYSTL
{
	//T is the type of container'interator
	template<typename iterator_type>
	class iterator_trait
	{
	public:
		using iterator_category = typename iterator_type::interator_category;
		using difference_type = typename iterator_type::difference_type;
		using value_type = typename iterator_type::value_type;
		using value_pointer = typename iterator_type::value_pointer;
		using value_reference = typename iterator_type::value_reference;
	};

	template<typename T>
	class iterator_trait<T*>
	{
	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using value_pointer = T*;
		using value_reference = T&;
	};
}
