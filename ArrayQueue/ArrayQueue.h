#include <iostream> 
#include <vector>

using namespace std;

class ArrayQueue
{
	public: 
	// 1. 构造函数 
	ArrayQueue(int max_size);
	ArrayQueue(int max_size, const vector<int> &lis);
	
	// 2. 拷贝控制
	ArrayQueue(const ArrayQueue &other);
	ArrayQueue & operator = (const ArrayQueue &other);
	
	// 3. 功能函数 
	bool push(int val);         // 新元素入队 
	bool pop(int &val);         // 队首元素出队 
	bool frontval(int &val) const; // 获取队首元素 
	void clear();               // 清空队列 
	int length() const;         // 获取队列中的元素个数 
	void print() const;         // 输出队列中的数据 
	
	// 4. 析构函数
	~ArrayQueue();              // 类的析构函数 
	
	private:
	int *data;                  // 队列数据实际存储的数组
	int front;                  // 队首元素下标 
	int back;                   // 队尾元素下标加1的值，即队尾元素的尾后元素的下标  
	int MAX_SIZE;               // 数组的最大大小，即队列中最多允许的元素个数 
};

/*
 * ArrayQueue: 默认构造函数 
*/
ArrayQueue::ArrayQueue(int max_size)
{
	data=new int [max_size];
	front=back=0;
	MAX_SIZE=max_size;
}

/*
 * ArrayQueue: 从数组构造队列 
*/
ArrayQueue::ArrayQueue(int max_size, const vector<int> &lis)
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
 * ArrayQueue: 拷贝构造函数 
*/
ArrayQueue::ArrayQueue(const ArrayQueue &other)
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
 * ArrayQueue: 拷贝赋值运算符 
*/
ArrayQueue & ArrayQueue::operator = (const ArrayQueue &other)
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
 * note: 在数组表示的队列中，首先要判断队列是否已满，若队列已满，则入队失败，返回false；若栈未满，只需要将要入队的值写入data[back]，然后将back加1即可，最后返回true 
*/
bool ArrayQueue::push(int val)
{
	if(back==MAX_SIZE)
	return false;
	else
	{
		data[back]=val;
		back+=1;
		return true;
	}
}

/*
 * pop: 将队首元素出队 
 * note: 出栈的算法也较为简单，首先判断队列是否为空，若队列为空，则出队失败，返回false；若队列未空，则首先记录队首元素的值data[front]，然后将front加1，即出队完成，返回true 
*/
bool ArrayQueue::pop(int &val)
{
	if(front==back)	
	return false;
	else
	{
		val=data[front];
		front+=1;
		return true;
	}
}

/*
 * frontval: 返回队首元素 
 * note: 返回队首元素的算法和出队过程大致相同，本处不再重复介绍 
*/
bool ArrayQueue::frontval(int &val) const
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
void ArrayQueue::clear()
{
	front=back=0;
}
	
/*
 * length: 返回栈中的元素数量 
*/
int ArrayQueue::length() const
{
	return (back-front);
}

/*
 * print: 输出栈
*/ 
void ArrayQueue::print() const
{
	string res;
	
	for(int i=front;i<back;i++)
	{
		if(i==0)
		res=to_string(data[i])+res;
		else
		res=to_string(data[i])+"<-"+res;
	}
	
	cout<<res<<endl;
}

/*
 * ~ArrayQueue: 析构函数  
*/ 
ArrayQueue::~ArrayQueue()
{
	delete [] data;
}


