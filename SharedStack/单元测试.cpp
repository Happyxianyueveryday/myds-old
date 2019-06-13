#include "SharedStack.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	SharedStack sta(10);

	sta.left_push(1);
	sta.left_push(2);
	sta.left_push(3);
	sta.left_push(4);
	sta.left_push(5);

	sta.right_push(6);
	sta.right_push(7);
	sta.right_push(8);
	sta.right_push(9);
	sta.right_push(10);
	sta.right_push(11);

	sta.print();

	int val;
	sta.left_pop(val);
	sta.left_pop(val);
	sta.right_pop(val);
	sta.right_pop(val);

	sta.print();

	sta.right_push(9);
	sta.right_push(10);
	sta.right_push(11);
	sta.right_push(12);
	sta.left_push(4);
	sta.print();

	while(sta.left_size())
	{
		sta.left_pop(val);
		cout<<val<<endl;
	}

	cout<<sta.left_top(val)<<endl;

	sta.right_top(val);
	cout<<val<<endl;

	cout<<sta.right_size()<<endl;
}
