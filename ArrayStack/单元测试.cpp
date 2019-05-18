#include "ArrayStack.h"
#include <iostream>

using namespace std;

int main(void)
{
	// 1. 测试构造函数 
	ArrayStack sta1(100);           // 默认构造函数 
	cout<<"栈sta1为空，sta1 = "<<endl;
	sta1.print();
	
	vector<int> data0={};
	ArrayStack sta0(100, data0);           // 由数组构造的构造函数
	sta0=sta0=sta0;
	cout<<"栈sta0为空，sta0 = "<<endl;
	sta0.print();
	
	vector<int> data={1,2,3,4,5,6};
	ArrayStack sta2(100, data);     // 由数组构造的构造函数 
	cout<<"由数组{1,2,3,4,5,6}构造的栈sta2为 sta2 = "<<endl;
	sta2.print();
	cout<<"栈sta2的大小为 length = "<<sta2.length()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	// 2. 测试拷贝控制函数 
	ArrayStack sta3(sta2);     //  拷贝构造函数 
	cout<<"令sta3 = sta2，现在栈 sta3 = "<<endl;
	sta3.print();
	cout<<"栈sta3的大小为 length = "<<sta3.length()<<endl;
	
	vector<int> data2={1,2,3,4,5,6,7,8};
	sta3=ArrayStack(100, data2);    // 拷贝赋值运算符
	cout<<"用数组{1,2,3,4,5,6,7,8}重新构造栈sta3，现在sta3 = "<<endl;
	sta3.print();
	cout<<"栈sta3的大小为 length = "<<sta3.length()<<endl;
	
	cout<<"--------------------------------------------"<<endl;
	
	// 3. 测试入栈函数 
	cout<<"在测试入栈功能之前，栈 sta3 = "<<endl;
	sta3.print();
	
	sta3.push(9);
	cout<<"入栈元素9后，栈 sta3 = "<<endl;
	sta3.print();
	cout<<"栈sta3的大小为 length = "<<sta3.length()<<endl;
	
	sta3.push(10);
	cout<<"入栈元素10后，栈 sta3 = "<<endl;
	sta3.print();
	cout<<"栈sta3的大小为 length = "<<sta3.length()<<endl;
	
	// 4. 测试出栈函数
	cout<<"在测试出栈功能之前，栈 sta3 = "<<endl;
	sta3.print(); 
	cout<<"下面依次出栈元素直到栈为空为止"<<endl;
	
	int val;
	while(sta3.pop(val))
	{
		cout<<"出栈的栈顶元素值为 val = "<<val<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	// 5. 测试清空函数
	cout<<"在测试清空栈功能之前，栈 sta2 = "<<endl;
	sta2.print();
	sta2.clear();
	cout<<"清空栈sta2后，栈sta2 = "<<endl;
	sta2.print();
}
