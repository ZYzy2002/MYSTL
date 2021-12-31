#include <iostream>
#include"list.h"
#include<list>
#include<iterator>

#include"algorithm.h"

using namespace MYSTL;

int main()
{
    MYSTL::list<int> mylist{};
    for (int i = 0; i < 10; i++)
    {
        mylist.push_back(i + 10);
    }
    mylist.erase(++mylist.begin());
    debug_print_element(mylist);
    
   
    list<int> mylist2 = mylist;
    //mylist2 = mylist;                  //"list::operator=()"is not exist now;
	for (int i = 0; i < 10; i++)
	{
        mylist2.push_front(9 - i);
	}
   
	
    debug_print_element(mylist2);
    std::cout<<"is empty:"<<mylist2.empty();
}

