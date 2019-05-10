#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Stack
{
	public:
	Stack();
	
	int top();
	int pop();
	void push(int val);
	int size();
	
	private:
	queue<int> que1;
};

Stack::Stack()
{
}

int Stack::top()
{
	queue<int> que2;
	int res;
	
	while(que1.size())
	{
		res=que1.front();
		que2.push(res);
		que1.pop();
	}
	
	while(que2.size())
	{
		que1.push(que2.front());
		que2.pop();
	}
	
	return res;
}

int Stack::pop()
{
	queue<int> que2;
	
	while(que1.size()>1)
	{
		que2.push(que1.front());
		que1.pop();
	}
	
	int res=que1.front();
	que1.pop();
	
	while(que2.size())
	{
		que1.push(que2.front());
		que2.pop();
	}
	
	return res;
}

void Stack::push(int val)
{
	que1.push(val);
}

int Stack::size()
{
	queue<int> que2;
	int count=0;
	
	while(que1.size())
	{
		que2.push(que1.front());
		que1.pop();
		count+=1;
	}
	
	while(que2.size())
	{
		que1.push(que2.front());
		que2.pop();
	}
	
	return count;
}


int main(void)
{
	Stack stack;
	
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	stack.push(6);
	
	cout<<stack.top()<<endl;
	cout<<stack.pop()<<endl; 
	
	cout<<stack.top()<<endl;
	cout<<stack.pop()<<endl;
	
	while(stack.size())
	{
		cout<<stack.pop()<<" ";
	}
	cout<<endl;
}
