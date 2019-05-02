#include <iostream>
#include <string>
#include <vector> 
#include <stack>
#include <queue>
#include <cstring> 

using namespace std;

/*
* Graph: 无向图类
*/
class Graph
{
    public:

    // 1. 构造函数
    Graph();                                      // 默认构造函数
    Graph(const vector<vector<int> > &lis);       // 从邻接矩阵数组(vector)构造图，图中的结点依次被命名为0,1,...,size-1

    // 2. 拷贝控制
    Graph(const Graph &gra);                      // 拷贝构造函数
    Graph & operator = (const Graph &other);      // 拷贝赋值运算符

    // 3. 基本操作与功能
    vector<int> bfs(int start);                   // 图的广度优先搜索
    vector<int> dfs(int start);                   // 图的深度优先搜索

    vector<int> dijkstra(int start);              // 计算某个结点到所有其他各个结点的最短路径长度: dijkstra算法
    vector<int> prim(int start);                  // 计算某个结点到所有其他各个结点的最短路径长度: floyd算法

    Graph prim();                                 // 产生最小生成树: prim算法
    Graph krustkal();                             // 产生最小生成树: krustkal算法

    void print();                                 // 输出图的邻接表 

    // 4. 析构函数
    ~Graph();                                     // 析构函数

    private:
    int **data;                                   // 图的邻接矩阵: 矩阵元素值为-1表示两个结点之间不相邻，之间的距离为无穷大 
    int size;                                     // 图的大小
};

/*
 * Graph: 默认构造函数
*/
Graph::Graph()
{
    data=NULL;
    size=0;
}

/*
 * Graph: 从邻接矩阵数组(vector)构造图
*/
Graph::Graph(const vector<vector<int> > &lis)
{
    // 0. 计算邻接表大小
    size=lis.size();

    // 1. 申请邻接表空间
    data=new int *[size];
    
    for(int i=0;i<size;i++)
    {
        data[i]=new int[size];
    }

    // 2. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
            data[i][k]=lis[i][k];
        }
    }
}

/*
 * Graph: 拷贝构造函数
*/
Graph::Graph(const Graph &other)
{
    // 1. 重新申请和拷贝源相同大小的邻接表内存
    size=other.size;
    data=new int*[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new int[size];
    }

    // 2. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
            data[i][k]=other.data[i][k];
        }
    }
}

/* 
 * operator = : 拷贝赋值运算符
*/
Graph & Graph::operator = (const Graph &other)
{
    // 0. 处理自我赋值的情况
    if(&other==this)
    return (*this);

    // 1. 释放当前邻接表内存
    for(int i=0;i<size;i++)
    {
        delete [] data[i];
    }
    delete [] data;

    // 2. 重新申请和拷贝源相同大小的邻接表内存
    size=other.size;
    data=new int*[size];

    for(int i=0;i<size;i++)
    {
        data[i]=new int[size];
    }

    // 3. 拷贝邻接表内容
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<size;k++)
        {
            data[i][k]=other.data[i][k];
        }
    }

    return (*this);
}

/*
 * print: 输出邻接表
*/ 
void Graph::print()
{
	for(int i=0;i<size;i++)	
	{
		for(int k=0;k<size;k++)
		{
			cout<<data[i][k]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

/*
 * bfs: 图的广度优先搜索
 * param start: 广度优先搜索的起始结点下标
 * note: 图的广度优先搜索和树的层次遍历使用的迭代算法类似，都是使用队列来辅助完成
*/
vector<int> Graph::bfs(int start)
{
    vector<int> res;    
    // 0. 处理特殊情况
    if(!size||start<0||start>=size)
    return res;

    // 1. 创建用于广度优先搜索的队列，并且将开始的结点放入队列，并且创建一个数组用于标记对应下标的结点是否已经访问过
    queue<int> que;      // 用于广度优先搜索的队列
    bool visit[size];    // 用于记录对应结点是否已经被访问过的数组
    memset(visit, 0, size*sizeof(bool));
    que.push(start);

    // 2. 循环进行如下的操作直到队列为空停止: 从队列中出队一个结点，若该结点未访问过，则输出该出队的结点并标记该结点已经访问过，然后将与该结点直接相连接的未访问过的邻居结点全部入队
    // 附注: 图的广度优先搜索和树的类似，但是需要特别注意，需要标记图中的每个结点是否已经访问过
    // 附注: 一定要注意使用两次访问检查，在输出前检查要输出的结点是否已经访问过，在结点入栈前检查要入队的结点是否已经访问过 
    while(que.size())
    {
        int temp=que.front();
        que.pop();
        
        // 2.1 若出队的结点已经访问过，直接忽略即可 
        if(visit[temp])
        continue; 
        
        // 2.2 若出队的结点没有被访问过，则输出该结点，并将该结点未访问过的邻居入队 
        else
        {
        	res.push_back(temp);
        	visit[temp]=true;

        	for(int i=0;i<size;i++)
        	{
            	if(data[temp][i]!=-1&&!visit[i])
            	que.push(i);
        	}
		}
    }

    // 3. 返回遍历结果
    return res;
}

/*
 * dfs: 图的深度优先搜索
 * param start: 深度优先搜索的起始结点下标
 * note: 图的深度优先搜索和树的前序遍历使用的迭代算法类似，都是使用栈来辅助完成
*/
vector<int> Graph::dfs(int start)
{
    vector<int> res;
    
    // 0. 处理特殊情况
    if(!size||start<0||start>=size)
    return res;

    // 1. 创建遍历所使用的栈，并将起始结点放入栈中，并且创建一个数组用于标记对应下标的结点是否已经访问过
    stack<int> sta;
    bool visit[size];    // 用于记录对应结点是否已经被访问过的数组
    memset(visit, 0, size*sizeof(bool));
    sta.push(start);

    // 2. 循环进行如下步骤直到栈为空停止: 从栈顶出栈一个结点，若该结点未访问过，则输出该结点并标记该结点为已经访问，然后将与该结点直接相连的所有未访问过的邻居结点依次加入栈中 
    // 附注: 一定要注意使用两次访问检查，在输出前检查要输出的结点是否已经访问过，在结点入栈前检查要入栈的结点是否已经访问过，定要注意，从栈中弹出的结点也有可能已经访问过，这是因为多个结点可能具有相同的邻居，从而将一个结点多次入栈 
    while(sta.size())
    {
        int temp=sta.top();
        sta.pop();
        
        // 2.1 若栈中弹出的结点已经访问过，则直接忽略即可
        if(visit[temp])   
        continue;
        
        // 2.2 若栈中弹出的结点未被访问过，则首先输出该结点，然后将该结点未访问过的邻居结点入栈 
        else
        {
        	res.push_back(temp);
        	visit[temp]=true;

        	for(int i=0;i<size;i++)
        	{
            	if(data[temp][i]!=-1&&!visit[i])
            	sta.push(i);
        	}
		}
    }

    // 3. 返回最终遍历结果
    return res;
}

/*
 * dijkstra: dijkstra算法求解 
*/
vector<int> Graph::dijkstra(int start)
{
	vector<int> res;
	
	// 0. 处理特殊情况和非法输入
	if(start<0||size==0||start>=size)
	return res;
	
	// 1. 初始化两个集合，用一个bool数组实现，值为true的结点属于集合S，值为false的结点输入集合N，初始化集合S包含结点start，集合N包含所有其他结点
	bool visit[size];
	memset(visit, 0, size*sizeof(bool));
	visit[start]=true;      // 设置起始结点的标记为1，即属于集合S，其他结点属于集合N 
	
	// 2. 初始化各个结点到起始结点start的距离，起始结点的邻居结点到start的距离就是直接距离，非邻居结点到start的距离设置为无穷大
	// 附注: 以下代码中，均使用-1表示无穷大距离 
	int dist[size];
	for(int i=0;i<size;i++)
	{
		dist[i]=data[start][i];
	}
	
	for(int i=0;i<size;i++)
	{
		cout<<dist[i]<<" ";
	}
	cout<<endl;
	
	// 3. 循环进行以下步骤直到集合N为空: 
	// (1). 从集合N中选择出到start距离dist[i]最小的结点m
	// (2). 将该结点m从集合N中删除，加入集合S中
	// (3). 然后更新集合N中的结点k到起始结点start的距离: dist[k]=min(dist[k], data[k][m]+dist[m])
	for(int i=0;i<size-1;i++)   // 上述循环只需进行size-1次结束，因为集合N中的结点数目为size-1 
	{
		// 3.1 	查找dist中最小的满足visit[m]==false的结点m 
		int m=0;
		int min=INT_MAX;
		
		for(int k=0;k<size;k++)
		{
			if(visit[k]==false&&dist[k]!=-1&&dist[k]<min)   // 注意-1表示不可达/无穷大 
			{
				min=dist[k];
				m=i;
			}
		}
		
		// 3.2 将结点m从集合N中删除并加入集合S中
		visit[m]=true;
		
		// 3.3 更新集合N中剩下的结点u到起始点start的距离: dist[u]=min(dist[u], data[u][m]+dist[m])
		for(int u=0;u<size;u++)
		{
			if(visit[u]==false)
			{
				// 需要特别注意data[u][m]==-1表示不可达，则这时(data[u][m]+dist[m])的结果仍然是不可达，结果同样为-1 
				// 之所以使用-1表示不可达，导致逻辑实现的复杂性，主要还是因为cpp没有内置类型能够很好地表示无穷大 
				int temp=(data[u][m]==-1)?-1:(data[u][m]+dist[m]);
				
				if(temp!=-1&&temp<dist[u])
				dist[u]=temp;
			}
		}
	}
	
	// 4. 将dist数组中的值依次装入vector类型的res，返回作为最终结果
	for(int i=0;i<size;i++) 
	{
		res.push_back(dist[i]);
	}
	
	return res;
}

/*
 * ~Graph: 析构函数
*/
Graph::~Graph()
{
    if(data!=NULL)
    {
        for(int i=0;i<size;i++)
        {
            delete [] data[i];
        }
        delete [] data;
    }
}



