#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	Queue que;
	
	// 1. 测试入队功能
	que.push(1);
	que.push(2);
	que.push(3);
	
	cout<<"--------------------------------------------"<<endl;
	
	// 2. 测试获取队首元素功能
	int val; 
	if(que.front(val))
	{
		cout<<"队首元素为: val = "<<val<<endl;
	}
	else
	{
		cout<<"队列为空，无法获取队首元素"<<endl;
	}
	
	while(que.empty())
	{
		que.pop(val);
		cout<<"出队队首元素 val = "<<val<<endl;
	}
	
	if(que.front(val))
	{
		cout<<"队首元素为: val = "<<val<<endl;
	}
	else
	{
		cout<<"队列为空，无法获取队首元素"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;	
	
	// 3. 测试出队功能
	que.push(1);
	if(que.pop(val))
	cout<<"出队队首元素 val = "<<val<<endl;
	else
	cout<<"队列为空，出队失败"<<endl;
	
	que.push(1);
	que.push(2);
	que.push(3);
	que.push(4);
	que.push(5);
	que.push(6);
	
	while(que.length()>3)
	{
		if(que.pop(val))
		cout<<"出队队首元素 val = "<<val<<endl;
		else
		cout<<"队列为空，出队失败"<<endl;
	}
	
	if(que.front(val))
	{
		cout<<"现在队首元素为: val = "<<val<<endl;
	}
	else
	{
		cout<<"队列为空，无法获取队首元素"<<endl;
	}
	
	cout<<"--------------------------------------------"<<endl;
	
	// 3. 测试拷贝构造函数，拷贝构造运算符和析构函数
	Queue que2(que);
	Queue que3=que2=que2;
	 
	while(que2.length())
	{
		if(que2.pop(val))
		cout<<"出队队首元素 val = "<<val<<endl;
		else
		cout<<"队列为空，出队失败"<<endl;
	}
	
	while(que3.length())
	{
		if(que3.pop(val))
		cout<<"出队队首元素 val = "<<val<<endl;
		else
		cout<<"队列为空，出队失败"<<endl;
	}
	
}
