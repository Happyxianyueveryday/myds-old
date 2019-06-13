#include <iostream>
#include <string>

using namespace std;

class SharedStack
{
	public:
	// 1. constructor
	SharedStack(int _max_size);

	// 2. copy_controller
	SharedStack(const SharedStack &other);
	SharedStack & operator = (const SharedStack &other);

	// 3. methods
	bool right_push(int val);    // 向右侧的栈入栈一个元素
	bool right_pop(int &val);    // 从右侧的栈出栈一个元素
	bool right_top(int &val);    // 获取右侧栈的栈顶元素
	int right_size();            // 获取右侧栈的元素个数

	bool left_push(int val);     // 向左侧的栈入栈一个元素
	bool left_pop(int &val);     // 从左侧的栈出栈一个元素
	bool left_top(int &val);     // 获取左侧栈的栈顶元素
	int left_size();             // 获取左侧栈的元素个数

	void print();                // 输出当前栈的情况

	// 4. destructor
	~SharedStack();

	// 5. domains
	private:
	int *data;
	int max_size;
	int righttop;  // 指向右侧栈的栈顶元素的下标
	int lefttop;   // 指向左侧栈的栈顶元素的下标
};

/**
 * SharedStack: 创建指定大小的两个空栈
 */
SharedStack::SharedStack(int _max_size)
{
	max_size=_max_size;
	data=new int[max_size];
	righttop=max_size;
	lefttop=-1;
}

/**
 * SharedStack: 拷贝构造函数
 */
SharedStack::SharedStack(const SharedStack &other)
{
	max_size=other.max_size;
	righttop=other.righttop;
	lefttop=other.lefttop;
	data=new int [max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i]=other.data[i];
	}
}

/**
 * SharedStack: 拷贝赋值运算符
 */
SharedStack & SharedStack::operator = (const SharedStack &other)
{
	if(this==&other)
		return (*this);

	delete [] data;

	max_size=other.max_size;
	righttop=other.righttop;
	lefttop=other.lefttop;
	data=new int [max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i]=other.data[i];
	}

	return (*this);
}

/**
 * right_push: 向右侧栈中入栈元素
 * param val: 需要入栈的元素
 * return: 若入栈成功，则返回true；若入栈失败，则返回false
 */
bool SharedStack::right_push(int val)
{
	if(righttop-lefttop==1)   // 若righttop-lefttop的值等于1，则说明右侧栈已经满，因为righttop和lefttop分别指向左侧栈和右侧栈的栈顶结点，差值为1说明两个栈的当前栈顶结点已经相邻，因此没有多余的为止存放新元素
		return false;
	else    // 否则栈未满，这时首先将右侧栈顶结点下标指针减1，然后写入要入栈的元素，并返回true
	{
		righttop-=1;
		data[righttop]=val;

		return true;
	}
}

/**
 * right_pop: 从右侧栈中出栈栈顶元素
 * param val: 出栈的栈顶元素值
 * return: 若出栈成功，则返回true；若出栈失败，则返回false
 */
bool SharedStack::right_pop(int &val)
{
	if(righttop>=max_size)    // 若righttop==max_size，则说明右侧栈为空，这时无法弹出栈顶元素，返回false
		return false;
	else                      // 否则弹出栈顶元素，先记录当右侧栈的栈顶元素值，然后将右侧栈顶结点下标指针加1，并返回true
	{
		val=data[righttop];
		righttop+=1;

		return true;
	}
}

/**
 * right_top: 获取右侧栈的栈顶元素
 * param val: 右侧栈的栈顶元素
 * return: 若获取栈顶元素成功，则返回true；若获取栈顶元素失败，则返回false
 */
bool SharedStack::right_top(int &val)
{
	if(righttop>=max_size)    // 若righttop==max_size，则说明右侧栈为空，这时无法取得栈顶元素，返回false
		return false;
	else                      // 否则取出栈顶元素，并返回true
	{
		val=data[righttop];
		return true;
	}
}

/**
 * right_size: 计算右侧栈的元素个数
 * return: 右侧栈的元素个数
 */
int SharedStack::right_size()
{
	return (max_size-righttop);   // 右侧栈的元素个数就是(max_size-righttop)
}

/**
 * left_push: 向左侧栈中入栈元素
 * param val: 需要入栈的元素
 * return: 若入栈成功，则返回true；若入栈失败，则返回false
 */
bool SharedStack::left_push(int val)
{
	if(righttop-lefttop==1)    // 若右侧栈栈顶元素下标和左侧栈栈顶元素下标只相差1，则说明左侧栈和右侧栈栈顶元素相邻，没有空余位置进行入栈，入栈失败
		return false;
	else
	{
		lefttop+=1;
		data[lefttop]=val;

		return true;
	}
}

/**
 * left_pop: 从左侧栈中出栈元素
 * param val: 从左侧栈中出栈的元素
 * return: 若出栈成功，则返回true；否则返回false
 */
bool SharedStack::left_pop(int &val)
{
	if(lefttop<0)
		return false;
	else
	{
		val=data[lefttop];
		lefttop-=1;

		return true;
	}
}

/**
 * left_top: 获取左侧栈中的栈顶元素
 * param val: 获取到的左侧栈的栈顶元素
 * return: 若获取左侧栈的栈顶元素成功，则返回true；若获取失败，则返回false
 */
bool SharedStack::left_top(int &val)
{
	if(lefttop<0)
		return false;
	else
	{
		val=data[lefttop];
		return true;
	}
}

/**
 * left_size: 获取左侧栈的元素个数
 * return: 左侧栈的元素个数
 */
int SharedStack::left_size()
{
	return (lefttop+1);
}

/**
 * print: 输出当前共享栈的元素
 */
void SharedStack::print()
{
	for(int i=lefttop;i>=0;i--)
	{
		if(i==lefttop)
			cout<<data[i];
		else
			cout<<"->"<<data[i];
	}
	cout<<endl;

	for(int i=righttop;i<max_size;i++)
	{
		if(i==righttop)
			cout<<data[i];
		else
			cout<<"->"<<data[i];
	}
	cout<<endl;
}

/**
 * ~SharedStack: 当前类的析构函数
 */
SharedStack::~SharedStack()
{
	delete [] data;
}
