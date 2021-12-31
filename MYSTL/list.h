#pragma once

#include"iterator.h"
#include"Allocator.h"
#include"trait.h"
#include"algorithm.h"

template<typename T>
class allocator;

namespace MYSTL
{

	template <typename T>
	struct list_node
	{
		list_node* prior = nullptr;
		list_node* next = nullptr;
		T element;
	};
	
	//iterator of the container "list"(cycle)
	template<typename T>
	class list_iterator :public iterator<T,bidirectional_iterator_tag>
	{
	public:
		list_node<T>* pnode;
	public:
		list_iterator(list_node<T>* point_to_assign) :pnode{ point_to_assign } {};//use "list_node" type
		list_iterator(const list_iterator& ref_to_copy) :pnode{ ref_to_copy.pnode } {};

		list_iterator& operator++() { pnode = pnode->next; return *this; }
		list_iterator operator++(int) { list_iterator temp = *this; pnode=pnode->next; return temp; };
		list_iterator& operator--() { pnode = pnode->prior; return *this; }
		list_iterator operator--(int) { list_iterator temp = *this; pnode = pnode->prior; return temp; };
		bool operator==(const list_iterator& other_iteratot_to_compare) const { return pnode == other_iteratot_to_compare.pnode; }
		bool operator!=(const list_iterator& other_iteratot_to_compare) const { return pnode != other_iteratot_to_compare.pnode; }
		T& operator*() const{ return pnode->element; }
		T* operator->() const{ return &(pnode->element); }//"const iterator" can change element value and can't change direction.
		operator T* ()const{return &(pnode->element); }//It's used to the function"~list()"and"deallocate()".
	};
	template<typename T>
	class const_list_iterator :public iterator<T, bidirectional_iterator_tag>
	{
	public:
		const list_node<T>* pnode;
	public:
		
		const_list_iterator(const list_node<T>* point_to_assign) :pnode{ point_to_assign } {};
		const_list_iterator(const list_iterator<T>& nonconst_iterator):pnode{nonconst_iterator}{}
		const_list_iterator(const const_list_iterator& ref_to_copy) :pnode{ ref_to_copy.pnode } {};

		const_list_iterator& operator++() { pnode = pnode->next; return *this; }
		const_list_iterator operator++(int) { const_list_iterator<T> temp = *this; pnode = pnode->next; return temp; };
		const_list_iterator& operator--() { pnode = pnode->prior; return *this; }
		const_list_iterator operator--(int) { const_list_iterator<T> temp = *this; pnode = pnode->prior; return temp; };
		bool operator==(const const_list_iterator& other_iteratot_to_compare) const { return pnode == other_iteratot_to_compare.pnode; }
		bool operator!=(const const_list_iterator& other_iteratot_to_compare) const { return pnode != other_iteratot_to_compare.pnode; }
		const T& operator*() const { return pnode->element; }
		const T* operator->() const { return &(pnode->element); }
		operator const T* ()const{return &(pnode->element); }//It's used to the function"~list()"and"deallocate()".
	};

	//container "list"
	template<typename T, typename Allocator_Type = allocator<list_node<T>>>
	class list
	{
	protected:
		list_node<T>* the_end_node;//it is returned by "end()". it's not used to store element.
	public:
		//I think these provide access to gain information of the list or gain some kind of iterator to use.
		using value_type				= T;
		using iterator					= list_iterator<T>;
		using const_iterator			= const_list_iterator<T>;//return by "begin()const"and so on.
		using alloc						= allocator<list_node<T> >;
		using reverse_iterator			= reverse_iterator<list_iterator<T> >;
		using const_reverse_iterator	= const_reverse_iterator<const_list_iterator<T> >;
	public:
		//constructor and destructor
		list();
		list(int num, const T& value);
		template<typename InputIterator>
		list(const InputIterator& first, const InputIterator& last);
		list(const list& copied_list);
		~list();
		list& operator=(const list& copied_list);

		iterator begin() { return the_end_node->next; }
		iterator end() { return the_end_node; }
		const_iterator cbegin()const { return the_end_node->next; }
		const_iterator cend()const { return the_end_node; }
		reverse_iterator rbegin() { return begin(); }
		reverse_iterator rend() { return end(); }
  		const_reverse_iterator crbegin() const{ return cbegin(); }
  		const_reverse_iterator crend()const { return cend(); }

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(size_t n, const value_type& val);
		T& back()const;
		T& front()const;
		void clear()noexcept;
		bool empty() const noexcept;
 		iterator erase(iterator position_iterator);
 		iterator erase(iterator first_iterator, iterator last_iterator);//remove a sequence of nodes.
// 
// 		template <class... Args>
// 		iterator emplace(const_iterator position, Args&&... args);
// 		template <class... Args>
// 		void emplace_back(Args&&... args);
// 		template <class... Args>
// 		void emplace_front(Args&&... args);

		void push_back(const T& value);
		void push_front(const T& value);

		size_t size() const noexcept; 
	
	};//end of class "list"

	
	template<typename T, typename Allocator_Type>
	list<T, Allocator_Type>::list():the_end_node{alloc::allocate()}//initialize "prior" and "next"
	{
		the_end_node->prior = the_end_node;
		the_end_node->next = the_end_node;
	}
	template<typename T, typename Allocator_Type>
	list<T, Allocator_Type>::list(int num, const T& value)
		:list<T, Allocator_Type>::list()
	{
		for (int i = 0; i < num; i++)
		{
			push_back(value);
		}
	}
	template<typename T, typename Allocator_Type>
	template<typename InputIterator>
	list<T, Allocator_Type>::list(const InputIterator& first, const InputIterator& last) 
		:list<T, Allocator_Type>::list()
	{
		InputIterator move_iterator = first;
		while (move_iterator != last)
		{
			push_back(*move_iterator);
		}
	}
	template<typename T, typename Allocator_Type>
	list<T,Allocator_Type>::list(const list& copied_list)
		:list<T, Allocator_Type>::list()
	{
		const_iterator move_iterator = copied_list.cbegin();
		while (move_iterator != copied_list.cend())
		{
			push_back(*move_iterator);
			move_iterator++;
		}
	}
	template<typename T, typename Allocator_Type>
	list<T, Allocator_Type>::~list()
	{
		for (iterator i = begin(); i != end(); ) {
			auto p = i;
			i++;
 			alloc::deallocate(p.pnode);
 		}
		alloc::deallocate(the_end_node);
	}
	template<typename T, typename Allocator_Type>
	list<T,Allocator_Type>& MYSTL::list<T, Allocator_Type>::operator=(const list& copied_list)//为何这不写const list<T>&
	{
		assign(copied_list.cbegin(),copied_list.cend());
		return *this;
	}

		
	template<typename T,typename Allocator_Type>
	template<typename InputIterator>
	void list<T, Allocator_Type>::assign(InputIterator first, InputIterator last)
	{
		erase(begin(), end());
		InputIterator move_iterator = first;
		while (move_iterator != last)
		{
			push_back(*move_iterator);
		}
	}
	template<typename T, typename Allocator_Type>
	void list<T, Allocator_Type>::assign(size_t n, const value_type& val)
	{
		erase(begin(), end());
		for (size_t i = 0; i < n; i++)
		{
			push_back(val);
		}
	}
	template<typename T, typename Allocator_Type>
	T& list<T, Allocator_Type>::back() const
	{
		return the_end_node->prior->element;
	}
	template<typename T, typename Allocator_Type>
	T& list<T, Allocator_Type>::front() const
	{
		return the_end_node->next->element;
	}
	template<typename T, typename Allocator_Type>
	void list<T, Allocator_Type>::clear()noexcept
	{
		erase(begin(), end());
	}
	template<typename T, typename Allocator_Type>
	bool list<T, Allocator_Type>::empty()const noexcept
	{
		return cbegin() == cend();
	}
	template<typename T,typename Allocator_Type>
	typename list<T,Allocator_Type>::iterator 
		list<T, Allocator_Type>::erase(typename list<T, Allocator_Type>::iterator position_iterator)//give a list iterator to delete appropriate node; can't input "reverse iterator"
	{
		list_node<T>* p = position_iterator.pnode;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		iterator return_next_node{ p->next };
		alloc::deallocate(p);
		return return_next_node;
	}
	template<typename T, typename Allocator_Type>
	typename list<T, Allocator_Type>::iterator
		list<T, Allocator_Type>::erase(typename list<T, Allocator_Type>::iterator first, typename list<T, Allocator_Type>::iterator last)
	{
		for (iterator move_iterator = first; move_iterator != last; move_iterator++)
		{
			erase(move_iterator);
		}
			return last;//?
	}

	template<typename T, typename Allocator_Type>
	void list<T, Allocator_Type>::push_back(const T& value)
	{
		list_node<T>* add=alloc::allocate();
		add->element = value;
		the_end_node->prior->next = add;
		add->next = the_end_node;
		add->prior = the_end_node->prior;
		the_end_node->prior = add;
	}
	template<typename T, typename Allocator_Type>
	void list<T, Allocator_Type>::push_front(const T& value)
	{
		list_node<T>* add = alloc::allocate();
 		add->element = value;
		add->next = the_end_node->next;
		the_end_node->next = add;
		the_end_node->next->next->prior = add;
		add->prior = the_end_node;
	}
	template<typename T, typename Allocator_Type>
	size_t list<T, Allocator_Type>::size()const noexcept
	{
		return distance(cbegin(), cend());
	}
}
