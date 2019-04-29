#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ListNode: 链表结点的实现
struct ListNode
{
    ListNode(int ival=0):val(ival),next(NULL)
    {
    }

    int val;
    ListNode *next;
};


// Stack: 基于链表的栈实现
class Stack
{
    public:
    // 1. 构造函数
    Stack();                                    // 默认构造函数
    Stack(const vector<int> &lis);              // 从数组构造栈 

    // 2. 拷贝控制
    Stack(const Stack &other);                  // 拷贝构造函数
    Stack & operator = (const Stack &other);    // 拷贝赋值运算符

    // 3. 基本功能
    void push(int val);           // 入栈操作
    bool pop(int &val);           // 出栈操作
    bool top(int &val) const;     // 获取栈中的元素数目 
    void clean();         		  // 清空栈操作
    int length() const;           // 获取栈的大小
    void print() const;           // 输出栈 

    // 4. 析构函数
    ~Stack();             // 析构函数
    
    private:
    ListNode *head;       // 栈顶结点的指针
    int size;             // 栈中的结点个数
};


/*
 * Stack: 默认构造函数，构造一个空的栈
*/
Stack::Stack()
{
    head=NULL;              // 这里的链表没有必要使用头部哑结点的方法
    size=0;                 // 初始化栈中的元素个数为0
}

/*
 * StacK: 从数组构造栈
*/ 
Stack::Stack(const vector<int> &lis)
{
	if(!lis.size())	
	{
		head=NULL;
		size=0;
	}
	else
	{
		head=new ListNode(lis[lis.size()-1]);	
		ListNode *now=head;
		
		for(int i=lis.size()-2;i>=0;i--)
		{
			now->next=new ListNode(lis[i]);
			now=now->next;
		}
		
		size=lis.size();
	}
}

/* 
 * Stack: 拷贝构造函数
*/
Stack::Stack(const Stack &other)
{
    head=new ListNode(0);   // 初始化链表头部哑结点 
    
    ListNode *now=head;
    ListNode *tempnow=other.head;

    while(tempnow)
    {
        now->next=new ListNode(tempnow->val);
        now=now->next;
        tempnow=tempnow->next;
    }
    
    ListNode *temp=head;
    head=head->next;
    delete temp;                          // 插入完成后，删除链表头部哑结点 

    size=other.size;                      // 初始化栈中的结点个数
}

/*
 * operator =: 拷贝赋值运算符
*/
Stack & Stack::operator = (const Stack &other)
{
	// 0. 处理自我赋值，存在深拷贝时，编写拷贝赋值运算符时，必须小心自我赋值的问题 
	if(this==&other)    // 若传入的拷贝源的地址和当前对象的地址(即this指针)相同，这时实际上就是自我赋值，无需进行赋值，直接返回(*this) 
	return (*this);
	
    // 1. 释放当前栈中链表的所有结点
    ListNode *now=head;
    
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }

    // 2. 从拷贝源拷贝所有栈的结点到当前栈中
    head=new ListNode(0);   // 初始化链表头部哑结点 
    
    now=head;
    ListNode *tempnow=other.head;

    while(tempnow)
    {
        now->next=new ListNode(tempnow->val);
        now=now->next;
        tempnow=tempnow->next;
    }
    
    ListNode *temp=head;
    head=head->next;
    delete temp;                          // 插入完成后，删除链表头部哑结点 

    size=other.size;                      // 初始化栈中的结点个数
    
    return (*this);
}

/*
 * push: 入栈操作
 * param val: 需要入栈的值
*/
void Stack::push(int val)
{
    ListNode *newnode=new ListNode(val);   // 创建新结点加入栈顶
    newnode->next=head;
    head=newnode;

    size+=1;                               // 栈中的结点计数增加1
}   

/*
 * pop: 出栈操作
 * param val: 出栈的元素值
*/
bool Stack::pop(int &val)
{
    if(!head)      // 若栈为空，这时出栈操作失败
    return false;

    ListNode *temp=head;
    val=temp->val;

    head=head->next;     // 删除栈顶结点
    delete temp;

    size-=1;             // 栈中的结点计数减小1
    
    return true;
}

/*
 * top: 获取栈顶元素操作
 * param val: 栈顶的元素值
*/
bool Stack::top(int &val) const
{
    if(!head)     // 若栈为空，这时获取栈顶元素操作失败
    return false;

    val=head->val;  // 获取栈顶元素值
    return true;
}

/*
 * clean: 清空栈
*/
void Stack::clean()
{
    ListNode *now=head;
    
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }

    head=NULL;
    size=0;
}

/*
 * length: 获取栈中的元素个数
*/
int Stack::length() const 
{
    return size;
}

/*
 * print: 输出栈
*/ 
void Stack::print() const
{
	ListNode *now=head;
	string res;
	
	while(now)
	{
		if(now==head)
		res=to_string(now->val)+res;
		else
		res=to_string(now->val)+"<-"+res;
		
		now=now->next;
	}
	
	cout<<res<<endl;
}

/* 
 * ~Stack: 析构函数
*/
Stack::~Stack()
{
    ListNode *now=head;
    
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;
    }
}




