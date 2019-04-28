#include "linked_list.h"
#include <iostream>

using namespace std;

int main(void)
{
	// 1. 测试构造函数正确性 
	List lis;     // 测试默认构造函数
	lis.print();
	
	vector<int> data={1,2,3,4,5,6,7,8,9};
	List lis2(data);    // 测试从数组构造的构造函数的正确性
	cout<<"链表lis2 = "<<endl;
	lis2.print();
	cout<<"lis2的长度 = "<<lis2.length()<<endl<<endl;
	
	cout<<"------------------------------------------"<<endl;
	
	
	// 2. 测试拷贝控制函数的正确性 
	List lis3(lis2);   // 测试拷贝构造函数
	cout<<"链表lis3 = "<<endl;
	lis3.print();     
	cout<<"lis3的长度 = "<<lis3.length()<<endl<<endl;
	
	vector<int> data2={1,2,3,4,5,6};
	lis3=List(data2);  // 同时测试拷贝构造函数和拷贝构造运算符 
	cout<<"现在链表lis3 = "<<endl;
	lis3.print();     
	cout<<"lis3的长度 = "<<lis3.length()<<endl<<endl;
	
	cout<<"------------------------------------------"<<endl;
	
	// 3. 测试删除函数 
	cout<<"测试删除函数之前，初始情况下链表lis3 = "<<endl;
	lis3.print(); 
	
	int val;
	if(lis3.mydelete(0,val))
	{
		cout<<"删除下标为0的元素后，现在链表lis3 = "<<endl;  
		lis3.print(); 
		cout<<"删除的元素值为: val = "<<val<<endl;	
	}
	else
	{
		cout<<"删除失败，给定的下标不合法！"<<endl; 
	}
	
	
	if(lis3.mydelete(4,val))
	{
		cout<<"删除下标为4的元素后，现在链表lis3 = "<<endl;  // 测试删除 
		lis3.print(); 
		cout<<"删除的元素值为: val = "<<val<<endl;	
	}
	else
	{
		cout<<"删除失败，给定的下标不合法！"<<endl; 
	}
	
	if(lis3.mydelete(6,val))
	{
		cout<<"删除下标为6的元素后，现在链表lis3 = "<<endl;  // 测试删除 
		lis3.print(); 
		cout<<"删除的元素值为: val = "<<val<<endl;	
	}
	else
	{
		cout<<"删除失败，给定的下标6不合法！"<<endl; 
	}
	
	if(lis3.mydelete(-1,val))
	{
		cout<<"删除下标为-1的元素后，现在链表lis3 = "<<endl;  // 测试删除 
		lis3.print(); 
		cout<<"删除的元素值为: val = "<<val<<endl;	
	}
	else
	{
		cout<<"删除失败，给定的下标-1不合法！"<<endl; 
	}
	
	cout<<"------------------------------------------"<<endl;
	
	// 4. 测试插入函数
	vector<int> data3={};   // 特别注意测试数组为空的情况 
	List lis4(data3);
	cout<<"测试插入函数之前，初始情况下链表lis4为空"<<endl;
	lis4.print(); 
	if(lis4.insert(0,1))
	{
		cout<<"在下标为0的位置插入值1，现在链表lis4 = "<<endl;  
		lis4.print(); 
	}
	else
	{
		cout<<"插入失败，给定的下标0不合法！"<<endl; 
	}
	
	if(lis4.insert(0,2))
	{
		cout<<"在下标为0的位置插入值2，现在链表lis4 = "<<endl;  
		lis4.print(); 
	}
	else
	{
		cout<<"插入失败，给定的下标0不合法！"<<endl; 
	}
	
	if(lis4.insert(0,3))
	{
		cout<<"在下标为0的位置插入值3，现在链表lis4 = "<<endl;  
		lis4.print(); 
	}
	else
	{
		cout<<"插入失败，给定的下标0不合法！"<<endl; 
	}
	
	if(lis4.insert(3,0))
	{
		cout<<"在下标为3的位置插入值0，现在链表lis4 = "<<endl;  
		lis4.print(); 
	}
	else
	{
		cout<<"插入失败，给定的下标3不合法！"<<endl; 
	}
	
	cout<<"------------------------------------------"<<endl;
	
	// 5. 测试获取指定结点值的函数 
	cout<<"测试获取指定结点值的函数之前，初始情况下链表lis4 = "<<endl;
	lis4.print(); 
	if(lis4.getval(2,val))
	{
		cout<<"链表lis4下标为2的位置的值为val = "<<val<<endl;  
	}
	else
	{
		cout<<"获取值失败，给定的下标2不合法！"<<endl; 
	}
	
	if(lis4.getval(0,val))
	{
		cout<<"链表lis4下标为0的位置的值为val = "<<val<<endl;  
	}
	else
	{
		cout<<"获取值失败，给定的下标0不合法！"<<endl; 
	}
	
	if(lis4.getval(4,val))
	{
		cout<<"链表lis4下标为4的位置的值为val = "<<val<<endl;  
	}
	else
	{
		cout<<"获取值失败，给定的下标4不合法！"<<endl; 
	}
	
	if(lis4.getval(-1999,val))
	{
		cout<<"链表lis4下标为-1999的位置的值为val = "<<val<<endl;  
	}
	else
	{
		cout<<"获取值失败，给定的下标-1999不合法！"<<endl; 
	}
	
	cout<<"------------------------------------------"<<endl;
	
	// 6. 测试获取长度的函数
	cout<<"测试获取长度的函数之前，初始情况下链表lis3 = "<<endl;
	lis3.print(); 
	cout<<"链表lis3的长度为: length = "<<lis3.length()<<endl;
	
	// 7. 析构函数和输出函数上面已经隐式测试过了，这里不再重复测试 
	 
}
