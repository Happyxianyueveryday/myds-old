#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Queue
{
	public:
	Queue();
	
	void push(int val);
	int pop();
	int front();
	int size(); 
	
	private:
	stack<int> sta1;
};


Queue::Queue()
{
}

void Queue::push(int val)
{
	sta1.push(val);
}

int Queue::pop()
{
	stack<int> sta2;
	
	while(sta1.size())
	{
		sta2.push(sta1.top());
		sta1.pop();
	}
	
	int res=sta2.top();
	sta2.pop();
	
	while(sta2.size())
	{
		sta1.push(sta2.top());
		sta2.pop();
	}
	
	return res;
}

int Queue::front()
{
	stack<int> sta2;
	
	while(sta1.size())
	{
		sta2.push(sta1.top());
		sta1.pop();
	}
	
	int res=sta2.top();
	
	while(sta2.size())
	{
		sta1.push(sta2.top());
		sta2.pop();
	}
	
	return res;
}

int Queue::size()
{
	int count=0;
	stack<int> sta2;
	
	while(sta1.size())
	{
		sta2.push(sta1.top());
		sta1.pop();
		count+=1;
	}
	
	while(sta2.size())
	{
		sta1.push(sta2.top());
		sta2.pop();
	}
	
	return count;
}



int main(void)
{
	Queue queue;
	
	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.push(4);
	queue.push(5);
	queue.push(6);
	
	
	cout<<queue.front()<<endl;
	cout<<queue.pop()<<endl;
	
	while(queue.size())
	{
		cout<<queue.pop()<<" ";	
	}
	cout<<endl;
}

