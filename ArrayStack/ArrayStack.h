#include <iostream> 
#include <vector>

using namespace std;

class ArrayStack
{
	public: 
	// 1. 构造函数 
	ArrayStack(int max_size);
	ArrayStack(int max_size, const vector<int> &lis);
	
	// 2. 拷贝控制
	ArrayStack(const ArrayStack &other);
	ArrayStack & operator = (const ArrayStack &other);
	
	// 3. 功能函数 
	bool push(int val);         // 新元素入栈 
	bool pop(int &val);         // 栈顶元素出栈 
	bool top(int &val) const;   // 获取栈顶的元素
	void clear();               // 清空栈 
	int length() const;         // 获取栈中的元素个数 
	void print() const;         // 输出栈中的数据 
	
	// 4. 析构函数
	~ArrayStack();              // 类的析构函数 
	
	private:
	int *data;                  // 栈数据实际存储的数组
	int pos;                    // 栈顶元素在数组中的下标 
	int MAX_SIZE;               // 数组的最大大小，即栈中最多允许的元素个数 
};

/*
 * ArrayStack: 默认构造函数 
*/
ArrayStack::ArrayStack(int max_size)
{
	data=new int [max_size];
	pos=-1;
	MAX_SIZE=max_size;
}

/*
 * ArrayStack: 从数组构造栈 
*/
ArrayStack::ArrayStack(int max_size, const vector<int> &lis)
{
	if(lis.size()>max_size)   // 若输入不合法，则默认构造一个空的栈，栈的最大大小为100 
	{
		data=new int [100];
		pos=-1;
		MAX_SIZE=100;
		return; 
	}
	
	data=new int [max_size];
	pos=lis.size()-1;
	MAX_SIZE=max_size;
	
	for(int i=0;i<lis.size();i++)
	{
		data[i]=lis[i];
	}
	
	return;
}

/*
 * ArrayStack: 拷贝构造函数 
*/
ArrayStack::ArrayStack(const ArrayStack &other)
{
	data=new int[other.MAX_SIZE];
	MAX_SIZE=other.MAX_SIZE;
	pos=other.pos;
	
	for(int i=0;i<=pos;i++)
	{
		data[i]=other.data[i];
	}
}

/*
 * ArrayStack: 拷贝赋值运算符 
*/
ArrayStack & ArrayStack::operator = (const ArrayStack &other)
{
	if(&other==this) 
	return (*this);
	
	delete [] data;
	
	data=new int[other.MAX_SIZE];
	MAX_SIZE=other.MAX_SIZE;
	pos=other.pos;
	
	for(int i=0;i<=pos;i++)
	{
		data[i]=other.data[i];
	}
} 

/*
 * push: 将元素入栈 
 * note: 在数组表示的栈中，首先要判断栈是否已满，若栈已满，则入栈失败，返回false；若栈未满，只需要首先将栈顶元素的下标加1，然后再写入该元素即可，最后返回true 
*/
bool ArrayStack::push(int val)
{
	if(pos==MAX_SIZE-1)
	return false;
	else
	{
		pos+=1;
		data[pos]=val;
		return true;
	}
}

/*
 * pop: 将栈顶元素出栈
 * note: 出栈的算法也较为简单，首先判断栈中是否存在元素，若栈为空，则出栈失败，返回false；若栈未空，则首先记录当前栈顶元素的值，然后直接将栈顶元素的下标减1，即出栈完成，返回true 
*/
bool ArrayStack::pop(int &val)
{
	if(pos==-1)
	return false;
	else
	{
		val=data[pos];
		pos-=1;
		return true;
	}
}

/*
 * top: 返回栈顶元素 
 * note: 返回栈顶元素的算法和出栈过程大致相同，本处不再重复介绍 
*/
bool ArrayStack::top(int &val) const
{
	if(pos==-1)
	return false;
	else
	{
		val=data[pos];
		return true;
	}
}

/*
 * clear: 清空栈中元素 
*/
void ArrayStack::clear()
{
	pos=-1;
}
	
/*
 * length: 返回栈中的元素数量 
*/
int ArrayStack::length() const
{
	return (pos+1);
}

/*
 * print: 输出栈
*/ 
void ArrayStack::print() const
{
	string res;
	
	for(int i=0;i<=pos;i++)
	{
		if(i==0)
		res=to_string(data[i])+res;
		else
		res=to_string(data[i])+"<-"+res;
	}
	
	cout<<res<<endl;
}

/*
 * ~ArrayStack: 析构函数  
*/ 
ArrayStack::~ArrayStack()
{
	delete [] data;
}


