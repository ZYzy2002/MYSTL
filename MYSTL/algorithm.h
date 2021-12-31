#pragma once

#include<iostream>

//#include<c:\users\zy\source\repos\mystl\MYSTL\trait.h>

template<typename iterator_type>
class iterator_trait;//forward declare
namespace MYSTL
{

	// a functino to print all element, it's used to debug conviently;
	template<typename Container_Type>
	void debug_print_element(const Container_Type& container_to_print)
	{
        using const_iterator = typename Container_Type::const_iterator;
        const_iterator first = container_to_print.cbegin(), last = container_to_print.cend();
        for (; first != last; ++first)
        {
            std::cout << *first<<' ';
        }
        std::cout << "    These are all " << container_to_print.size() << "element(s)";
        std::cout << std::endl;
	}



    //a global function to calculate the distance between two bidirectional_interators.   //?不知道是否可以计算const interator的距离
    template<typename Type_forward_iterator>
    /*size_t*/typename iterator_trait<Type_forward_iterator>::difference_type
        distance(Type_forward_iterator First, Type_forward_iterator Last)
    {
        typename iterator_trait<Type_forward_iterator>::difference_type/*size_t*/ distance_between_two_iterator = 0;
        while (First != Last)
        {
            distance_between_two_iterator++;
            First++;
        }
        return distance_between_two_iterator;
    }






}