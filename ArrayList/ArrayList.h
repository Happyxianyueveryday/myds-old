#include <iostream>
#include <string>

using namespace std;

struct Node
{
	Node(int _val=0):val(_val),next(-1)
	{
	}

	int val;
	int next;
};

/**
 * ArrayList: 静态链表类
 * note 1: 静态链表的每个结点Node使用val字段来存储数据，使用next字段来存储当前结点的下一个结点的下标
 * note 2: 静态链表中，将所有正在使用的链表结点链接起来组成工作链表，将所有未被使用（包括从未被使用或者被删除）的链表结点链接起来组成空闲链表
 * note 3: 当需要插入元素时，从空闲链表中取出一个空闲结点的下标，将该结点用于存储数据；当需要删除元素时，从工作链表中删除该结点，并将该结点重新放入空闲链表中
 */
class ArrayList
{
	public:
	// 1. constructor
	ArrayList(int _max_size);

	// 2. copy controller
	ArrayList(const ArrayList &other);
	ArrayList & operator = (const ArrayList &other);

	// 3. methods
	bool insert(int pos, int val);
	bool remove(int pos);
	void print();

	// 4. destructor
	~ArrayList();

	private:
	// 5. domains
	// 用于存放链表结点的数组：每个Node结点中的val字段存储该结点的值，next字段存储当前结点的下一个结点的下标
	Node *data;     // data[0]固定用于存储工作链表的头部哑结点，data[1]固定用于存储空闲链表的头部哑结点
	int max_size;   // 数组的最大大小，也即链表结点的最大数量
	int size;       // 当前链表中的结点个数

	int __malloc();   // 从空闲链表中取出（分配）一个空闲结点进行使用，返回该结点的下标
	bool __free(int index);    // 将工作链表中的指结点释放，即不再使用其中的数据，并将该结点转移到备用链表中
};

/**
 * ArrayList: 创建一个空的静态链表
 */
ArrayList::ArrayList(int _max_size)
{
	// 1. 初始化基本状态变量
	max_size=_max_size+2;    // 因为存在两个头部哑结点，因此需要多分配两个空间
	size=0;

	// 2. 初始化数组
	data=new Node [max_size];

	// 3. 初始化工作链表和空闲链表
	data[0].next=-1;         // 初始化工作链表为空

	data[1].next=2;          // 初始化空闲链表包含所有的链表单元
	for(int i=2;i<max_size-1;i++)
	{
		data[i].next=i+1;
	}
	data[max_size-1].next=-1;
}

/**
 * ArrayList: 拷贝构造函数
 */
ArrayList::ArrayList(const ArrayList &other)
{
	max_size=other.max_size;
	size=other.size;
	data=new Node[max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].next=other.data[i].next;
	}
}

/**
 * operator =: 拷贝赋值运算符
 */
ArrayList & ArrayList::operator = (const ArrayList &other)
{
	if(&other==this)
		return (*this);

	delete [] data;

	max_size=other.max_size;
	size=other.size;
	data=new Node[max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].next=other.data[i].next;
	}

	return (*this);
}

/**
 * insert: 向链表中插入一个结点
 * param pos: 需要插入结点的位置（该位置为链表中的逻辑位置，例如链表1->3->4->NULL,在pos=1处插入值2得到1->2->3->4->NULL）
 * param val: 需要插入的结点的值
 * return: 若插入成功则返回true，若插入失败则返回false
 */
bool ArrayList::insert(int pos, int val)
{
	// 1. 首先判断插入的逻辑位置是否合法
	if(pos<0||pos>size)
		return false;

	// 2. 若位置合法，首先使用__malloc方法尝试从空闲链表中分配一个空闲结点以供使用
	int index=this->__malloc();

	if(index==-1)     // 若__malloc方法返回-1，说明空闲链表中已经没有空闲结点以供使用了，插入失败
		return false;
	else              // 否则，进行插入操作
	{
		int now=data[0].next;
		int nowprev=0;

		for(int i=0;i<pos;i++)
		{
			nowprev=now;
			now=data[now].next;
		}

		data[index]=val;
		data[nowprev].next=index;
		data[index].next=now;

		size+=1;

		return true;
	}
}

/**
 * remove: 从链表中删除一个结点
 * param pos: 需要删除的结点的下标
 * return: 若给定的下标所对应的结点确实在工作链表中，则将其删除并返回true；否则返回false
 */
bool ArrayList::remove(int pos)
{
	// 1. 首先判断要删除的结点位置是否合法
	if(pos<0||pos>=size)
		return false;

	// 2. 若位置合法，则首先先查找到链表中的逻辑下标为pos的结点
	int now=0;

	for(int i=0;i<pos;i++)
	{
		now=data[now].next;
	}

	// 3. 从链表中删除该结点，并使用__free方法释放该结点的内存
	int index=data[now].next;
	data[now].next=data[data[now].next].next;
	this->__free(index);
	size-=1;

	return true;
}

/**
 * print: 输出当前链表
 */
void ArrayList::print()
{
	int now=data[0].next;

	while(now!=-1)
	{
		if(now!=data[0].next)
			cout<<"->"<<data[now].val;
		else
			cout<<data[now].val;

		now=data[now].next;
	}
	cout<<"->NULL"<<endl;
}

/**
 * __malloc: 从空闲链表中取出（分配）一个空闲结点进行使用，返回该结点的下标
 * return: 所释放的可供使用的空闲结点的在数组中的物理下标，若无空闲结点可用，返回值-1
 */
int ArrayList::__malloc()
{
	if(data[1].next==-1)
		return -1;

	int res=data[1].next;
	data[1].next=data[data[1].next].next;   // 从空闲链表中移出首结点，该首结点供调用者使用（将该结点加入工作链表的具体位置的工作由调用者进行）
	return res;
}

/**
 * __free: 将工作链表中的指定结点释放，即不再使用其中的数据，并将该结点转移到备用链表中
 * param index: 所需要释放的工作结点在数组中的物理下标
 * return: 若释放成功，则返回true，否则返回false
 */
bool ArrayList::__free(int index)
{
	// 1. 判断所需要释放的工作结点下标是否合法， 注意工作链表和空闲链表的头部哑结点均禁止释放
	if(index<2||index>=max_size)
		return false;

	// 2. 若下标合法，则进行释放，将该结点转移到备用链表中（从工作链表的对应位置删除该结点的操作由调用者进行）
	data[index].next=data[1].next;
	data[1].next=index;

	return false;
}

/**
 * ~ArrayList: 本类的析构函数
 */
ArrayList::~ArrayList()
{
	delete [] data;
}

