#include <iostream>
#include <string> 
#include <vector> 
#include <stack>
#include <queue>
#include <cstring>  
#include <algorithm>

using namespace std;

/*
* Graph: 无向图类
*/
class Graph
{
    public:

    // 1. 构造函数
    Graph();                                      // 默认构造函数
    Graph(int isize);                              // 初始化一个含有size个结点的图，图中默认没有任何的边 
    Graph(const vector<vector<int> > &lis);       // 从邻接矩阵数组(vector)构造图，图中的结点依次被命名为0,1,...,size-1
    Graph(const int *lis, int isize);             // 从邻接矩阵数组构造图

    // 2. 拷贝控制
    Graph(const Graph &gra);                      // 拷贝构造函数
    Graph & operator = (const Graph &other);      // 拷贝赋值运算符

    // 3. 基本操作与功能
    vector<int> bfs(int start);                   // 图的广度优先搜索
    vector<int> dfs(int start);                   // 图的深度优先搜索

    vector<int> dijkstra(int start);              // 计算某个结点到所有其他各个结点的最短路径长度: dijkstra算法
    vector<int> floyd(int start);                 // 计算某个结点到所有其他各个结点的最短路径长度: floyd算法

    Graph prim();                                 // 产生最小生成树: prim算法
    Graph kruskkal();                             // 产生最小生成树: krustkal算法

    void print();                                 // 输出图的邻接表 

    // 4. 析构函数
    ~Graph();                                     // 析构函数

    private:
    int **data;                                   // 图的邻接矩阵: 矩阵元素值为-1表示两个结点之间不相邻，之间的距离为无穷大 
    int size;                                     // 图的大小
    
    bool hasloop(Graph gra, int u, int v, int len);  // 判断给定的图增加一条边u,v后是否有环 
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
 * Graph: 构造固定大小的无边图 
*/
Graph::Graph(int isize)
{
	// 0. 计算邻接表大小
    size=isize;

    // 1. 申请邻接表空间
    data=new int *[size];
    
    for(int i=0;i<size;i++)
    {
        data[i]=new int[size];
    }
    
    // 2. 初始化邻接表为仅含结点而没有边的图
	for(int i=0;i<size;i++) 
	{
		for(int k=0;k<size;k++)
		{
			if(i==k)
			data[i][k]=0;
			else
			data[i][k]=-1;
		}
	}
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
 * Graph: 从邻接矩阵数组构造图 
*/
Graph::Graph(const int *lis, int isize)
{
	size=isize;
	
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
            // 这里仅使用一维数组指针lis来进行二维数组的传参，实际上lis指针指向二维数组的首元素，因为使用的是一维指针，因此必须使用lis[i*size+k]来代替lis[i][k] 
			data[i][k]=lis[i*size+k];
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
 * dijkstra: dijkstra算法求解结点间最小距离路径 
 * note: 因为C++语言中没有良好的内置机制来实现无穷大，因此必须使用很多技巧来保证实现无穷大机制 
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
	// 附注: 以下代码中，均使用INT_MAX替换-1表示无穷大距离 
	int dist[size];
	for(int i=0;i<size;i++)
	{
		if(data[start][i]==-1)
		dist[i]=INT_MAX;
		else
		dist[i]=data[start][i];
	}
	
	// 3. 循环进行以下步骤直到集合N为空: 
	// (1). 从集合N中选择出到start距离dist[i]最小的结点m
	// (2). 将该结点m从集合N中删除，加入集合S中
	// (3). 然后更新集合N中的结点k到起始结点start的距离: dist[k]=min(dist[k], data[k][m]+dist[m])
	for(int i=0;i<size-1;i++)   // 上述循环只需进行size-1次结束，因为集合N中的结点数目为size-1 
	{
		// 3.1 	查找dist中最小的满足visit[m]==false的结点m 
		int m=-1;
		int min=INT_MAX;
		
		for(int k=0;k<size;k++)
		{
			if(visit[k]==false&&dist[k]<=min) 
			{
				min=dist[k];
				m=k;
			}
		}
		
		// 3.2 将结点m从集合N中删除并加入集合S中
		visit[m]=true;
		
		// 3.3 更新集合N中剩下的结点u到起始点start的距离: dist[u]=min(dist[u], data[u][m]+dist[m])
		for(int u=0;u<size;u++)
		{ 
			if(visit[u]==false)
			{
				// 需要特别注意data[u][m]==INT_MAX表示不可达，则这时(data[u][m]+dist[m])的结果仍然是不可达，结果同样为INT_MAX
				// 特别地，INT_MAX不能参与数值运算，否则会导致溢出 
				int temp=(data[u][m]==-1)?INT_MAX:(data[u][m]+dist[m]);   // 注意data[u][m]中的无穷大又是用-1表示的，和 
				
				if(temp<dist[u]) 
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
 * floyd: floyd算法求解结点间最小距离路径 
 * note: dijkstra和floyd算法都是图中求解最短路径的核心算法，必须熟练掌握其原理 
*/
vector<int> Graph::floyd(int start)
{
	// floyd算法的总体思想非常简单，其核心公式表述是: data[i][j]=min(data[i][m]+data[m][j], data[i][j])，只需对每一个结点m应用上述公式并一直取最小值，最终即可求得结点i和结点j之间的最短距离 
	vector<int> res;
	int copy[size][size];
	
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(data[i][j]==-1)
			copy[i][j]=INT_MAX;
			else
			copy[i][j]=data[i][j];
		}
	}
	
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			for(int m=0;m<size;m++)
			{
				int temp=(copy[i][m]==INT_MAX||copy[m][j]==INT_MAX)?INT_MAX:(copy[i][m]+copy[m][j]);
				
				if(temp<copy[i][j])
				copy[i][j]=temp;
			}
		}
	}
	
	for(int i=0;i<size;i++)
	{
		res.push_back(copy[start][i]);
	}
	
	return res;
}

/*
 * prim: 生成最小生成树的prim算法 
 * note: prim算法的核心思路和dijkstra算法非常类似，如下所示:
 *	     1. 创建两个集合S和N，初始化S包含图中的任意一个结点u，初始化N包含图中的其他结点
 *	     2. 循环进行以下步骤直到集合为空为止，首先从集合N中选择一个到集合S距离最短的结点u，然后将该结点u和对应的边加入集合中，最后更新集合N中各个结点i到集合S的距离dist[i]，更新公式为: dist[i]=min(dist[i], data[i][u])
 * 		 附注: 结点u到集合S的最短距离定义为结点u到集合S中各个结点的距离的最小值
*/
Graph Graph::prim()
{	
	// 0. 处理特殊情况
	if(!size) 
	return (*this);
	
	// 1. 初始化结果图的邻接表
	int res[size][size];
	
	for(int i=0;i<size;i++)
	{
		for(int k=0;k<size;k++)
		{
			if(i==k)
			res[i][k]=0;
			else
			res[i][k]=-1;
		}
	}
	
	// 2. 初始化两个集合S和N，选择结点0放入集合S，其他结点放入集合N
	bool visit[size]; 
	memset(visit, 0, size*sizeof(bool));
	visit[0]=true;
	
	// 3. 初始化集合N中各个结点到集合S的最短距离 
	int dist[size];     // 记录集合N中各个结点到集合S的最短距离 
	int node[size];     // 记录集合N中各个结点取最短距离的S中的点 
	
	for(int i=0;i<size;i++)
	{
		if(data[i][0]==-1)
		{
			dist[i]=INT_MAX;
			node[i]=-1;
		}
		else
		{
			dist[i]=data[i][0];
			node[i]=0;
		}
	}
	
	// 4. 循环进行以下步骤直到集合N为空: 从集合N中选择一个到集合S的距离最近的结点u，将结点u从集合N中删除并加入集合S，并将相应的边加入最小生成树，最后，重新更新集合N中的各个结点到集合S的距离，并更新对应的取得最小距离的S中的结点 
	for(int i=0;i<size-1;i++)
	{
		int u, v;
		int min=INT_MAX;
		
		for(int k=0;k<size;k++)    // 从集合N中找出到集合S距离最近的结点 
		{
			if(!visit[k]&&dist[k]<=min)
			{
				min=dist[k];
				u=k;
				v=node[k];
			}
		}
		
		visit[u]=true;            // 将结点u从集合N中删除并加入集合S 
		
		res[u][v]=dist[u];        // 将边u-v加入结果邻接矩阵中
		res[v][u]=dist[u];        // 注意，还要将边v-u加入结果邻接矩阵中 (实际上就是同一条边) 
		
		for(int k=0;k<size;k++)   // 更新集合N中的各个结点k到集合S的距离dist[k]，以及对应的S中的结点node[k]，更新公式为: dist[k]=min(dist[k], data[k][u]), node[k]=(data[k][u]<dist[k])?u:node[k]
		{
			int temp=(data[k][u]==-1)?INT_MAX:data[k][u];   // 注意在邻接矩阵中是使用-1来表示无穷大的，与本算法中的规定有所区别 
			
			if(temp<dist[k])
			{
				dist[k]=temp;
				node[k]=u;
			}
		}
	}
	
	Graph result((const int *)res, size);
	return result;
}

/*
 * kruskkal: 生成最小生成树的kruskkal算法 
 * note: 在prim算法中核心步骤是: 集合S装有已经构成树的结点，然后将距离集合S最近的结点加入集合S，而kruskkal算法使用了另外一种思想: 在集合S中装构成树的边，每次将最短距离的一条边加入集合S，并且保证加入后集合S中不产生回路 
 *		 具体而言，kruskkal算法的步骤如下所示: 
 *       1. 创建两个集合S和N，初始化集合S装有原图中最短的一条边，初始化集合N具有原图中的其他边
 *       2. 循环进行以下步骤直到集合N为空时停止：从集合N中选出最短的且能保证加入集合S后不会产生环的边，将该边从集合N中删除并加入集合S
*/
Graph Graph::kruskkal()
{
	// 0. 定义表示图的边的自定义数据结构
	struct Edge
	{
		Edge(int ix, int iy, int ilen):x(ix), y(iy), len(ilen)
		{
		}
		
		int x;     // 端点1 
		int y;	   // 端点2 
		int len;   // 边长 
	};
	
	Graph res(size);   // 创建一个和当前图大小相同的图，该图即为最终的最小生成树 
	
	// 1. 初始化所有边的列表
	vector<Edge> edge;
	for(int i=0;i<size;i++)
	{
		for(int k=0;k<i+1;k++)    // 注意: k<i+1的目的是保证排除重复边，例如u-v和v-u是同一条边，只需要记录其中一个即可 
		{
			if(data[i][k]!=-1&&data[i][k]!=0)   // 排除结点自身的边长，排除不存在的边（不存在的边在邻接表中值为-1） 
			edge.push_back(Edge(i,k,data[i][k]));
		}
	}
	
	// 2. 按照边长从小到大对列表进行排序 
	sort(edge.begin(),edge.end(),[](const Edge &a, const Edge &b) -> bool { return a.len<b.len; });
	
	// 3. 初始化集合S和集合N，集合S初始情况下仅包含最短的边，集合N包含其他边
	bool visit[edge.size()];
	memset(visit, 0, edge.size()*sizeof(bool));
	
	visit[0]=true;     // 将最短的边加入集合S，其他的边加入集合N, visit[i]=true表明边edge[i]在集合S中，否则在集合N中 
	res.data[edge[0].x][edge[0].y]=edge[0].len;       // 将集合S中的边写入结果图中 
	res.data[edge[0].y][edge[0].x]=edge[0].len; 
	
	// 4. 循环进行以下步骤直到集合S加入了(n-1)条边时停止：从集合N中选出最短的且能保证加入集合S后不会产生环的边，将该边从集合N中删除并加入集合S
	int count=1;      // 集合S所包含的边数
	
	for(int i=1;i<edge.size();i++)
	{
		if(count==size-1)
		break;
		
		if(!hasloop(res, edge[i].x, edge[i].y, edge[i].len))   // 若将边edge[i]加入集合S中不会导致出现环，则将该边加入集合S 
		{
			count+=1;
			visit[i]=true;   // 将符合不出现环的边从集合N中删除，并加入集合S 
			
			res.data[edge[i].x][edge[i].y]=edge[i].len;       // 将新加入集合S的边写入结果图中 
			res.data[edge[i].y][edge[i].x]=edge[i].len; 
		}
	}
	
	return res;
}

/*
 * hasloop: 判断图中加入一条边后是否产生环 
 * note: 判断图中是否存在环的方法非常简单，只需要进行深度优先遍历，如果遍历过程中访问了已经访问过的结点，则该图中必定存在环 
*/
bool Graph::hasloop(Graph gra, int u, int v, int len)
{
	gra.data[u][v]=len;
	gra.data[v][u]=len;
	
	stack<int> sta;
    bool visit[gra.size];    // 用于记录对应结点是否已经被访问过的数组
    memset(visit, 0, (gra.size)*sizeof(bool));
    sta.push(0);
    
    while(sta.size())
    {
        int temp=sta.top();
        sta.pop();
        
        // 若栈中弹出的结点已经访问过，则说明图中存在环 
        if(visit[temp])   
        {
        	return true;
		}
        else
        {
        	visit[temp]=true;

        	for(int i=0;i<size;i++)
        	{
            	if(gra.data[temp][i]!=-1&&!visit[i])
            	sta.push(i);
        	}
		}
    }
    
    return false;	
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

 
