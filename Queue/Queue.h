#include <iostream>
#include <string>

using namespace std;

struct ListNode
{
    ListNode(int ival=0):val(ival),next(NULL)
    {
    }

    int val;
    ListNode *next;
};


class Queue
{
	public:
	Queue();                                   // 默认构造函数 
	Queue(const Queue &other);                 // 拷贝构造函数
	Queue & operator = (const Queue &other);   // 拷贝构造运算符 
	~Queue();                                  // 析构函数 
	
	bool front(int &val);                      // 获取队首元素 
	bool pop(int &val);                        // 元素出队操作 
	void push(int val);                        // 元素入队操作 
	int length();                              // 获取队列中的元素个数 
	bool empty();                              // 判断队列是否为空 
		 
	private:
	ListNode *head;                            // 队首元素指针（链表包含一个头部哑结点） 
	ListNode *tail;                            // 队尾元素指针 
	int size;                                  // 队列中的元素数量 
};


/*
 * Queue: 默认构造函数 
*/
Queue::Queue()
{
	head=new ListNode(0);   // 初始化头部哑结点 
	tail=head;             
	size=0;
}


/*
 * Queue: 拷贝构造函数 
*/
Queue::Queue(const Queue &other)
{
	head=new ListNode(0);      // 初始化头结点 
	
	ListNode *now=head;
	ListNode *othernow=other.head->next;    // 注意从第一个真正的结点开始，不需要拷贝头部哑结点 
	
	while(othernow)
	{
		now->next=new ListNode(othernow->val);
		
		now=now->next;
		othernow=othernow->next;
	}
	
	tail=now;                // 初始化尾结点 
	size=other.size;         // 初始化元素个数 
}


/* 
 * operator = : 拷贝赋值运算符 
*/
Queue &Queue::operator = (const Queue &other)
{
	// 0. 处理自我赋值问题 
	if(this==&other)
	return (*this);
	
	// 1. 首先释放当前的内存
	ListNode *now=head;
	
	while(now) 
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
	
	// 2. 然后从拷贝源队列进行拷贝过程
	head=new ListNode(0);    // 重新创建头部哑结点
	
	now=head;
	ListNode *othernow=other.head;
	
	while(othernow)
	{
		now->next=new ListNode(othernow->val);
		
		now=now->next;
		othernow=othernow->next;
	}
	 
	tail=now;           // 初始化尾结点 
	size=other.size;    // 初始化元素个数 
}


/*
 * ~Queue: 析构函数 
*/
Queue::~Queue() 
{
	ListNode *now=head;
	
	while(now) 
	{
		ListNode *temp=now;
		now=now->next;
		delete temp;
	}
}


/*
 * front: 获取队首元素 
*/
bool Queue::front(int &val)
{
	if(!size)
	return false;
	else
	{
		val=head->next->val;
		return true;
	}
}


bool Queue::pop(int &val)
{
	if(!size)
	return false;
	else if(size==1)    // 易错点: 当队列中仅剩下一个元素时，由于使用了头部哑结点，因此必须重置tail指针    
	{
		ListNode *temp=head->next;
		val=temp->val;
		head->next=NULL;
		size=0;
		tail=head;
		delete temp;
		
		return true;
	}
	else                // 当队列中剩下多于一个元素时，这时无需调整tail指针 
	{
		ListNode *temp=head->next;
		head->next=head->next->next;
		
		val=temp->val;
		delete temp;
		size-=1;
		
		return true;
	}
}


void Queue::push(int val)
{
	tail->next=new ListNode(val);
	tail=tail->next;
	size+=1;
}


int Queue::length()
{
	return size;
}


bool Queue::empty()
{
	return size;
}

