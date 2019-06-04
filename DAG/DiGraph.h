#include <iostream>
#include <vector>
#include <stack>
#include <cfloat>
#include <memory>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

/**
 * DiGraph: 使用邻接矩阵存储的有向无环图
 */
class DiGraph
{
	public:
	// 1. constructor
	DiGraph(double data[], int size);

	// 2. copy controller
	DiGraph(const DiGraph &other);
	DiGraph & operator= (const DiGraph &other);

	// 3. methods
	bool topoSort1(vector<int> &res);      // 对当前无向图进行拓扑排序：实现方法1——去点法
	bool topoSort2(vector<int> &res);      // 对当前无向图进行拓扑排序：实现方法2——利用基于递归的dfs进行拓扑排序

	// 4. destructor
	~DiGraph();

	private:
	// 5. domains
	double **data;               // 当前有向图的邻接矩阵
	int size;                    // 当前有向图中的结点个数

	// 6. private methods
	void __dfs(vector<int> &res, bool visit[], int now);    // 有向图的递归深度遍历
};

/**
 * DiGraph: 从邻接矩阵创建无向图
 * param _data: 一维化的邻接矩阵，大小应为size*size
 * param _size: 无向图中的结点个数
 */
DiGraph::DiGraph(double _data[], int _size)
{
	size=_size;

	data=new double* [size];
	for(int i=0;i<size;i++)
	{
		data[i]=new double [size];
	}

	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			if(_data[i*size+k]!=-1)
				data[i][k]=_data[i*size+k];
			else
				data[i][k]=DBL_MAX;
		}
	}
}

/**
 * DiGraph: 拷贝构造函数
 * param other: 拷贝源对象
 */
DiGraph::DiGraph(const DiGraph &other)
{
	size=other.size;

	data=new double* [size];
	for(int i=0;i<size;i++)
	{
		data[i]=new double [size];
	}

	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			data[i][k]=other.data[i][k];
		}
	}
}

/**
 * operator =: 拷贝赋值运算符
 * param other: 拷贝源
 */
DiGraph & DiGraph::operator= (const DiGraph &other)
{
	for(int i=0;i<size;i++)
	{
		delete [] data[i];
	}
	delete [] data;

	size=other.size;

	data=new double* [size];
	for(int i=0;i<size;i++)
	{
		data[i]=new double [size];
	}

	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			data[i][k]=other.data[i][k];
		}
	}

	return (*this);
}

/**
 * topoSort1: 对当前有向图进行拓扑排序，同时判断有向图中是否存在环
 * param res: 若当前有向图有环，则拓扑排序的结果将放入该参数中
 * return: 拓扑排序仅能在有向图无环的时候得到排序结果，若当前有向图有环，则返回false；若无环，则返回true，且参数res中包含拓扑排序的结果
 * note 1: 因为拓扑排序要求若存在从结点a到结点b的边，在b必须放在a后，因此入度为0的结点始终是首先要输出的，因此一种拓扑排序算法的基本思想是：每次从有向图中取出一个入度为0的结点，将该结点以及从该结点出发的边从图中删除，循环进行上述步骤直到图中没有剩下结点为止，若过程中发现图中不存在入度为0的结点，则说明图中存在环
 * note 2: 上述算法在实际实现中，基于去点法拓扑排序的核心步骤是：
 * 	                 （1）创建一个栈，遍历原图中所有的结点，将原图中所有入度为0的结点依次入栈
 * 		      （2）循环进行以下步骤直到栈为空为止：（a）从栈顶出栈一个结点，（b）依次查找从当前结点出发的边所指向的结点，判断在删除从当前结点出发的边后是否入度为0，若入度为0则将该结点入栈
 */
bool DiGraph::topoSort1(vector<int> &res)
{
	double _data[size][size];     // 从原始图中拷贝邻接矩阵

	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			_data[i][k]=data[i][k];
		}
	}

	stack<int> sta;

	for(int i=0;i<size;i++)    // 将原图中所有入度为0的边入栈
	{
		int flag=0;
		for(int k=0;k<size;k++)
		{
			if(_data[k][i]!=DBL_MAX&&k!=i)   // 注意自己到自己的边不计算在内
			{
				flag=1;
				break;
			}
		}

		if(!flag)
			sta.push(i);
	}

	while(sta.size())           // 循环进行以下步骤直到栈为空为止
	{
		int now=sta.top();      // 从栈中出栈栈顶结点
		sta.pop();

		res.push_back(now);     // 输出栈顶结点

		for(int i=0;i<size;i++)   // 从图中删除栈顶结点和从栈顶结点出发的边，并判断当前结点所指向的结点在删除后入度是否为0，将其中入度为0的结点入栈
		{
			if(_data[now][i]!=DBL_MAX&&now!=i)
			{
				_data[now][i]=DBL_MAX;

				int flag=0;
				for(int k=0;k<size;k++)
				{
					if(_data[k][i]!=DBL_MAX&&k!=i)   // 注意条件k!=i
					{
						flag=1;
						break;
					}
				}

				if(!flag)
					sta.push(i);
			}
		}
	}

	if(res.size()==size)   // 若栈为空后结果中包含所有结点，则说明有向图中无环，返回true
		return true;
	else				   // 否则，有向图中存在环，返回false
		return false;
}


/**
 * topoSort2: 对当前无向图进行拓扑排序：实现方法2
 * param res: 若当前有向图有环，则拓扑排序的结果将放入该参数中
 * return: 拓扑排序仅能在有向图无环的时候得到排序结果，若当前有向图有环，则返回false；若无环，则返回true，且参数res中包含拓扑排序的结果
 * note 1: 因为拓扑排序要求若存在从结点a到结点b的边，在b必须放在a后，因此入度为0的结点始终是首先要输出的。因此在深度优先遍历中，只需要在访问完当前结点所指向的所有结点后，再将当前结点加入结果中，即可得到拓扑排序的倒序表示
 * note 2: 上述算法在实际实现中，基于dfs的拓扑排序的核心步骤是：
 * 		      （1）从某个结点开始递归地进行dfs
 * 		      （2）在dfs的递归过程中，首先检查当前结点是否已访问，若已访问，则直接返回；若未访问，则首先递归地访问该结点所指向的所有结点，访问结束后，再将当前结点加入结果中
 * 		      （3）上述dfs过程完成后，将dfs结果进行反转即可得到最终的拓扑排序结果
 */
bool DiGraph::topoSort2(vector<int> &res)
{
	bool visit[size];
	memset(visit, 0, size*sizeof(bool));

	__dfs(res, visit, 0);

	reverse(res.begin(), res.end());

	if(res.size()==size)
		return true;
	else
		return false;
}

void DiGraph::__dfs(vector<int> &res, bool visit[], int now)
{
	if(!visit[now])
	{
		visit[now]=true;
		for(int i=0;i<size;i++)
		{
			if(data[now][i]!=DBL_MAX&&i!=now)
				__dfs(res, visit, i);
		}
		res.push_back(now);    // 因为这里始终是在访问完当前结点所直接指向的结点后，再访问当前结点，因此最终得到的是拓扑排序的逆序（拓扑排序要求若a指向b，则排序结果中a在b之前）
	}
}

/**
 * DiGraph: 本类的析构函数
 */
DiGraph::~DiGraph()
{
	for(int i=0;i<size;i++)
	{
		delete [] data[i];
	}
	delete [] data;
}

