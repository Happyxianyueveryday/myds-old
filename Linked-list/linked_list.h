#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ListNode
{
    ListNode(int ival=0):val(ival),next(NULL)
    {
    }

    int val;
    ListNode *next;
};

class List
{
    public:
    // 1. 构造函数
    List();                                            // 默认构造函数
    List(const vector<int> &lis);                      // 其他构造函数: 从数组构造链表

    // 2. 拷贝控制
    List(const List &other);                           // 拷贝构造函数
    List &operator = (const List &other);              // 拷贝构造运算符

    // 3. 功能函数
    bool insert(const int pos, const int val);         // 向链表中的指定位置插入值
    bool mydelete(const int pos, int &val);              // 从链表中删除指定位置的值
    bool getval(const int pos, int &val) const;        // 获取链表中指定位置的值  

    int length() const;                // 返回链表的元素个数/长度
    void print() const;                // 输出链表: 本函数仅方便测试使用，成员函数中应尽量减少cin和cout的直接使用

    // 4. 析构函数
    ~List();                           // 析构函数

    private:
    ListNode *head;                    // 链表头结点，本实现中使用头部哑结点来简化插入和删除过程
    int size;                          // 链表中的结点个数
};



/*
 * List: 默认构造函数
*/
List::List()
{
    size=0;                  // 初始化链表的元素个数
    head=new ListNode(0);    // 初始化链表头部哑结点
}


/* 
 * List: 其他构造函数，从数组构造链表
 * param lis: 原始数组
*/
List::List(const vector<int> &lis)  // 为什么lis参数使用const引用而不是值传递？因为大型数组的拷贝非常耗时和占用空间，因此使用引用，const防止本函数修改该数组
{
    head=new ListNode(0);    // 初始化链表头部哑结点
    ListNode *now=head;      // 用于遍历链表的游标指针

    for(int i=0;i<lis.size();i++)    
    {
        now->next=new ListNode(lis[i]);
        now=now->next;
    }

    size=lis.size();        // 初始化链表的元素个数，链表现在的元素个数和输入的数组参数的大小相等
}


// C++的拷贝控制相对复杂，主要学java不打算深入C++的话可以不看

/*
 * List: 拷贝构造函数
 * param other: 拷贝来源对象/源链表对象
*/
List::List(const List &other)
{
    // 拷贝构造函数仅在用一个同类的其他对象初始化当前对象时才被调用，这时尚未申请空间，因此无需对head进行delete

    head=new ListNode(0);      // 初始化当前链表的链表头部哑结点

    ListNode *now=head;                  // 遍历当前链表的游标指针
    ListNode *copynow=other.head->next;  // 从源链表的第一个元素开始遍历的游标指针
    
    while(copynow)
    {
        now->next=new ListNode(copynow->val);
        copynow=copynow->next;
        now=now->next;
    }

    size=other.size;           // 初始化完成后，当前链表长度和源链表长度相等
}


/* 
 * operator =: 拷贝赋值运算符
 * param other: 拷贝来源对象/源链表对象
*/
List & List::operator = (const List &other)
{
    // 拷贝赋值运算符和上面的拷贝构造函数不同，调用拷贝赋值运算符时，当前链表可能已经分配了内存，因此必须首先释放当前链表所占用的内存，防止内存泄漏

    // 0. 处理自我赋值的特殊情况，参见effective c++的详细说明
    if(this==&other)
    return (*this);

    // 1. 释放当前链表的内存
    if(head->next)   // head为方便插入操作的头部哑结点，head->next才是实际上的第一个结点
    {
        ListNode *now=head;
        
        while(now)
        {
            ListNode *temp=now;         // 先使用临时变量temp记录要删除的结点
            now=now->next;              // 调整游标指针指向下一个结点
            delete temp;                // 删除当前结点         
        }
    }

    // 2. 下面的步骤和拷贝构造函数就相同了，不必再花时间看，拷贝构造运算符和拷贝构造函数的唯一区别就是需要释放当前链表head的内存
    head=new ListNode(0);      // 初始化当前链表的链表头部哑结点

    ListNode *now=head;                  // 遍历当前链表的游标指针
    ListNode *copynow=other.head->next;  // 从源链表的第一个元素开始遍历的游标指针
    
    while(copynow)
    {
        now->next=new ListNode(copynow->val);
        copynow=copynow->next;
        now=now->next;
    }

    size=other.size;           // 初始化完成后，当前链表长度和源链表长度相等

    return (*this);
}


/*
 * insert: 向链表中插入一个指定值的结点
 * param pos: 需要插入的位置下标，下标从0开始
 * param val: 需要插入的结点的值
*/
bool List::insert(const int pos, const int val)
{
    // 1. 先判断插入位置是否合法
    if(pos<0||pos>size)   // 不合法位置直接返回false
    {
        return false;
    }

    // 2. 对合法的位置进行插入
    ListNode *now=head;      // 遍历当前链表的游标指针
    
    for(int i=0;i<pos;i++)  // 移动游标指针到要插入的位置的前驱结点上
    {
        now=now->next;
    }

	ListNode *temp=now->next;
    now->next=new ListNode(val);
    now->next->next=temp;

    // 3. 插入了一个新结点，因此增加链表的结点计数变量size
    size+=1;

    return true;
}

/*
 * delete: 向链表中插入一个指定值的结点
 * param pos: 需要删除的位置下标，下标从0开始
 * param val: 返回给用户所删除的结点的值
*/
bool List::mydelete(const int pos, int &val)
{
    // 1. 先判断删除位置是否合法
    if(pos<0||pos>=size)
    {
        return false;
    }

    // 2. 若删除位置合法，则删除对应位置的结点
    ListNode *now=head;      // 遍历当前链表的游标指针
    
    for(int i=0;i<pos;i++)  // 删除操作和插入操作使用相同方法，即移动游标指针到要删除结点的前驱结点上
    {
        now=now->next;
    }

    ListNode *temp=now->next;    // 先使用临时变量temp记录要删除的结点
    val=temp->val;               // 将删除的结点的值返回给用户
    now->next=now->next->next;   // 调整前驱结点的next指针指向待删除结点的下一个结点，使用两重next(->next->next)时必须极其谨慎，必须确保now->next!=NULL
    delete temp;                 // 删除待删除的目标结点

    // 3. 删除了一个结点，因此减小链表的结点计数变量size
    size-=1;

    return true;
}

/*
 * getval: 向链表中插入一个指定值的结点
 * param pos: 需要获取值的结点的下标
 * param val: 返回给用户结点的值
*/
bool List::getval(const int pos, int &val) const
{
    // 1. 先判断删除位置是否合法
    if(pos<0||pos>=size)
    {
        return false;
    }

    // 2. 若位置合法，则返回对应结点的值
    ListNode *now=head->next;     // 遍历当前链表的游标指针
    
    for(int i=0;i<pos;i++)        // 移动指针到目标结点上
    {
        now=now->next;
    }

    val=now->val;                 // 返回给用户目标结点的值

    return true;
}

/*
 * length: 返回链表的长度，也即链表中的结点数
*/
int List::length() const
{
    return size;
}

/*
 * print: 输出链表，输出链表中的元素
 * note: 本函数的目标只是方便单元测试，成员函数中应尽量减少cin和cout的直接使用
*/
void List::print() const
{
    ListNode *now=head->next;

    while(now)
    {
        if(now==head->next)
        cout<<now->val;
        else
        cout<<"->"<<now->val;

        now=now->next;
    }
    
    cout<<endl;
}

/*
 * ~List: 析构函数
*/
List::~List()
{
    // 1. List析构函数依次释放整个链表中的每个结点所占的内存，防止内存泄漏

    ListNode *now=head;
    while(now)
    {
        ListNode *temp=now;
        now=now->next;
        delete temp;    // 这个地方的错误找了10分钟！小心和谨慎！不能删除now，只能删除临时变量temp 
    }
}



