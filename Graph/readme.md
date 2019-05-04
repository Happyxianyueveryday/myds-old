  # 图的经典算法

  ## 1. 图的深度优先遍历(dfs)
  图的深度优先遍历一般使用栈进行实现，其算法和树的前序遍历类似，但是需要额外标记各个结点是否已经访问过，因为图中可能存在环。
  
  图的深度优先遍历算法(dfs)的基本步骤如下：
  > 1. 创建一个临时栈，并选择一个遍历的开始结点加入栈中。
  > 2. 创建一个记录数组记录各个结点是否已经访问过，将开始结点标记为已经访问。
  > 3. 循环进行以下步骤直到栈为空为止：
  >> (1) 从栈顶出栈一个结点s  
  >> (2) 通过记录数组判断结点s是否已经访问过，若未访问过，则输出该结点，然后在记录数组中标记该结点为已访问；若已经访问过，则直接跳回循环开始处(continue语句)  
  >> (3) 将结点s的所有未访问过的邻居结点依次入栈  
  
  具体的代码实现示例如下，其中data为原图的邻接矩阵，邻接矩阵中的-1表示两点间不相邻。
  
  ```
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

  ```
  
  ## 2. 图的广度优先遍历(bfs)
  图的广度优先遍历一般使用队列进行实现，其算法和树的层次遍历类似，但是需要额外标记各个结点是否已经访问过，因为图中可能存在环。
  
  图的广度优先遍历算法(bfs)的基本步骤如下:
  > 1. 创建一个临时队列，将遍历的起始结点入队
  > 2. 创建一个记录数组记录各个结点是否已经访问过，将开始结点标记为已经访问。
  > 3. 循环进行以下步骤直到队列为空为止:
  >> (1) 从队首出队一个结点
  >> (2) 判断该结点是否已经访问过，若未访问过，则输出该结点，然后在记录数组中标记该结点为已访问；若已经访问过，则直接跳回循环开始处(continue语句)  
  >> (3) 将该结点的所有未访问过的邻居结点加入队列尾部
  
  
  具体的代码实现示例如下，其中data为原图的邻接矩阵，邻接矩阵中的-1表示两点间不相邻。
  
  ```
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
  ```
  
  ## 3. 图的结点间最短路径
  图的结点间最短路径问题，主要存在两种主要算法：dijkstra算法和floyd算法。
  
  ### 3.1 dijkstra算法
  
  dijkstra算法是一种贪心算法，主要实现步骤如下。
  
  > 1. 创建两个集合S和N，集合S初始时仅包含起点结点start，集合N则包含图中的所有其他结点。
  > 2. 初始化集合N中的每一个结点（记为结点i）通过集合S中的结点到达起点start的距离dist\[i]，若结点i是结点start的邻居结点，则dist\[i]就是结点i和结点start间的距离，否则初始化dist\[i]为无穷大。
  > 3. 循环进行以下步骤直到集合N为空为止: 
  >> (1) 从集合N中选取到起始结点start的距离dist最短的结点u  
  >> (2) 将结点u从集合N中删除，并加入集合S  
  >> (3) 由于这时多了一个结点u可供经过，因此更新集合N中剩下的各个结点v到起点start的距离dist\[v]，更新公式为: dist\[v]=min(dist\[v], c(v,u)+dist\[u])
  
   具体的代码实现示例如下，其中data为原图的邻接矩阵，邻接矩阵中的-1表示两点间不相邻。
  
  ```
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
  ```
  
  ## 3.2 floyd算法
  floyd算法相对于dijkstra算法实现起来更为简介，但是时间复杂度较高，为O(n^3)。
  
  floyd算法的核心思想可以用如下的公式进行表示：
