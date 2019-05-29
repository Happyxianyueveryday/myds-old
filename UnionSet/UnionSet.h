#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * TreeNode: 并查集中所使用的树的结点
 * note: 并查集中的树结点使用双亲表示，其中val字段存储本结点的值，parent字段存储当前结点的父结点在数组中的下标
 */
struct TreeNode
{
	TreeNode(int _val=0):val(_val), parent(-1)
	{
	}

	int val;     // 当前结点的值
	int parent;  // 若parent>=0，则表示当前结点的父结点在数组中的下标；若parent<0，则表示当前结点没有父结点，其绝对值为当前结点的子结点的个数
};

class UnionSet
{
	public:
	// 1. constructor
	UnionSet(int _data[], int _size);

	// 2. copy_controller
	UnionSet(const UnionSet &other);
	UnionSet & operator = (const UnionSet &other);

	// 3. methods
	bool merge(int root1, int root2);
	bool findroot(int val, int &rootval);
	void print();

	// 4. destructor
	~UnionSet();

	// 5. domains
	private:
	TreeNode *data;
	int size;
};

/**
 * UnionSet: 从数组初始化并查集，数组中的每个元素自成一个集合
 * param data: 输入的数组
 * param size: 输入的数组的元素个数
 */
UnionSet::UnionSet(int _data[], int _size)
{
	size=_size;
	data=new TreeNode [size];

	for(int i=0;i<size;i++)
	{
		data[i].val=_data[i];
		data[i].parent=-1;      // 初始情况下数组中的每一个元素单独作为一个集合存在
	}
}

/**
 * UnionSet: 拷贝构造函数
 */
UnionSet::UnionSet(const UnionSet &other)
{
	size=other.size;
	data=new TreeNode [size];

	for(int i=0;i<size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].parent=other.data[i].parent;
	}
}

/**
 * operator =: 拷贝赋值运算符
 */
UnionSet & UnionSet::operator = (const UnionSet &other)
{
	if(&other==this)
		return (*this);

	delete [] data;

	size=other.size;
	data=new TreeNode [size];

	for(int i=0;i<size;i++)
	{
		data[i].val=other.data[i].val;
		data[i].parent=other.data[i].parent;
	}

	return (*this);
}

/**
 * merge: 将并查集中根结点的值为root1的集合和根结点为root2的集合进行合并，将root2并入root1
 * param root1: 需要进行合并的集合1的根结点的值
 * param root2: 需要进行合并的集合2的根结点的值
 * return: 若合并成功，则返回true；若不存在相应的集合，而合并失败，则返回false
 * note: 并查集中两个集合合并的操作非常简单，将其中一个集合的根结点的父亲字段parent设置为指向另一个集合的根结点即可
 * warning: 输入的结点都必须是根结点
 */
bool UnionSet::merge(int root1, int root2)
{
	int index1=-1;    // 集合1的根结点在数组中的下标
	int index2=-1;    // 集合2的根结点在数组中的下标

	for(int i=0;i<size;i++)
	{
		if(data[i].val==root1)
			index1=i;
		else if(data[i].val==root2)
			index2=i;
	}

	if(index1!=-1&&index2!=-1&&data[index1].parent<0&&data[index2].parent<0)
	{
		data[index1].parent+=data[index2].parent; // 将root2加入root1后，root1的结点数需要重新计算
		data[index2].parent=index1;
		return true;
	}
	else
		return false;
}

/**
 * findroot: 查找给定值在并查集中所在的集合的根结点
 * param val: 要查找的给定值
 * param rootval: 若根结点存在，则该方法执行完成后，该参数为给定值所在的集合的根结点
 * return: 若给定值在并查集中存在则返回true，否则返回false
 * note: 查找某个结点所在的集合的根结点的操作较为简单，首先从结点数组中查找到该结点，然后沿着该结点一路向上查找到根结点（根结点的parent字段为-1）即可
 */
bool UnionSet::findroot(int val, int &rootval)
{
	int index=-1;

	for(int i=0;i<size;i++)
	{
		if(data[i].val==val)
		{
			index=i;
			break;
		}
	}

	if(index==-1)
		return false;
	else
	{
		while(data[index].parent>=0)   // 从该结点向上查找到该结点所在集合的根结点
		{
			index=data[index].parent;
		}
		rootval=data[index].val;

		return true;
	}
}

/**
 * print: 输出当前并查集中的所有集合
 */
void UnionSet::print()
{
	for(int i=0;i<size;i++)
	{
		if(i!=0)
			cout<<",";

		cout<<"["<<data[i].val<<" | "<<data[i].parent<<"]";
	}
	cout<<endl;
}

/**
 * ~UnionSet: 本类型的析构函数
 */
UnionSet::~UnionSet()
{
	delete [] data;
}

