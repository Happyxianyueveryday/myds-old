#include <iostream> 
#include <vector>

using namespace std;

class CycleQueue
{
	public: 
	// 1. 构造函数 
	CycleQueue(int max_size);
	CycleQueue(int max_size, const vector<int> &lis);
	
	// 2. 拷贝控制
	CycleQueue(const CycleQueue &other);
	CycleQueue & operator = (const CycleQueue &other);
	
	// 3. 功能函数 
	bool push(int val);         // 新元素入队 
	bool pop(int &val);         // 队首元素出队 
	bool frontval(int &val) const; // 获取队首元素 
	void clear();               // 清空队列 
	int length() const;         // 获取队列中的元素个数 
	
	// 4. 析构函数
	~CycleQueue();              // 类的析构函数  
	
	private: 
	int *data;                  // 队列数据实际存储的数组
	int front;                  // 循环队列中游标front指向队首元素的下标 
	int back;                   // 循环队列中游标back指向队尾元素的下标，本实现中所使用的队空和队满的判断条件决定了队列中有一个元素的位置是不可用的 
	int MAX_SIZE;               // 数组的最大大小，即队列中最多允许的元素个数 
};

/*
 * CycleQueue: 默认构造函数 
*/
CycleQueue::CycleQueue(int max_size)
{
	data=new int [max_size];
	front=back=0;
	MAX_SIZE=max_size+1;
}

/*
 * CycleQueue: 从数组构造队列 
*/
CycleQueue::CycleQueue(int max_size, const vector<int> &lis)
{
	if(lis.size()>max_size)   // 若输入不合法，则默认构造一个空的队列，队列的最大大小为100 
	{
		data=new int [100];
		front=back=0;
		MAX_SIZE=100;
		return; 
	}
	
	data=new int [max_size];
	front=0;
	back=lis.size();
	MAX_SIZE=max_size;
	
	for(int i=0;i<lis.size();i++)
	{
		data[i]=lis[i];
	}
	
	return;
}

/*
 * CycleQueue: 拷贝构造函数 
*/
CycleQueue::CycleQueue(const CycleQueue &other)
{
	data=new int[other.MAX_SIZE];
	MAX_SIZE=other.MAX_SIZE;
	front=other.front;
	back=other.back;
	
	for(int i=front;i<back;i++)
	{
		data[i]=other.data[i];
	}
}

/*
 * CycleQueue: 拷贝赋值运算符 
*/
CycleQueue & CycleQueue::operator = (const CycleQueue &other)
{
	if(&other==this) 
	return (*this);
	
	delete [] data;
	
	data=new int[other.MAX_SIZE];
	MAX_SIZE=other.MAX_SIZE;
	front=other.front;
	back=other.back;
	
	for(int i=front;i<back;i++)
	{
		data[i]=other.data[i];
	}
} 

/*
 * push: 将元素入队列 
 * note: 循环队列中，在将元素入队之前，首先需要判断队列是否已经满，判断队列是否已满的重要条件为(back+1)%MAX_SIZE==front，即如果队列的尾后元素的位置紧邻着队首元素的位置，则队列已经满，这时返回false；多队列未满，这时将要入队的元素写入data[back]，然后将游标back加1后对MAX_SIZE取模，最后返回true 
*/
bool CycleQueue::push(int val)
{
	if((back+1)%MAX_SIZE==front)
	return false;
	else
	{
		data[back]=val;
		back=(back+1)%MAX_SIZE;
		return true;
	}
}

/*
 * pop: 将队首元素出队 
 * note: 循环队列中，在将元素出队之前，首先需要判断队列是否为空，判断队列是否为空的重要条件是front==end，即若队列的队尾的尾后元素等于队首元素下标，这时说明队列中没有元素返回false；否则，先记录队首元素，然后将队首游标增加1后取模，即front=(front+1)%MAX_SIZE，最后返回true 
*/
bool CycleQueue::pop(int &val)
{
	if(front==back)
	return false;
	else
	{
		val=data[front];
		front=(front+1)%MAX_SIZE;
		return true;
	}
}

/*
 * frontval: 返回队首元素 
 * note: 返回队首元素的算法和出队过程大致相同，本处不再重复介绍 
*/
bool CycleQueue::frontval(int &val) const
{
	if(front==back)
	return false;
	else
	{
		val=data[front];
		return true;
	}
}

/*
 * clear: 清空栈中元素 
*/
void CycleQueue::clear()
{
	front=back=0;
}
	
/*
 * length: 返回栈中的元素数量 
*/
int CycleQueue::length() const
{
	return (back-front+MAX_SIZE)%MAX_SIZE;    // 该公式需要使用几个简单的例子来进行推导，更简单的方法是直接记下来该公式 
}

/*
 * ~CycleQueue: 析构函数  
*/ 
CycleQueue::~CycleQueue()
{
	delete [] data;
}


