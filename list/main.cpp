#include "list.h"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
	typedef int T;
	List<T> obj;
	for (int i = 0; i < 5; i++)
	{
		obj.add_node(i);
	}
	obj.print();
	obj = obj.reverse();
	obj.add_node(20);
	obj.print();
	obj = obj.sort();
	obj.print();
}
