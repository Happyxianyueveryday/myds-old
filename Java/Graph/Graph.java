package com.pzh.graph;

import java.util.*;
import java.util.concurrent.ConcurrentLinkedQueue;
import com.pzh.edge.Edge;

class Graph implements Cloneable   // extends是java中的继承机制，implements是java中的接口机制，请详细学习core java中的第五章和第六章的内容
{
	// 1. domains
	private double [][] data;    // 当前图的邻接矩阵
	private int size;         // 当前图的结点个数，各个结点分别被命名为0,1,2,...,size-1
	private final double INF=Double.POSITIVE_INFINITY;
	
	// 2. constructor
	/**
	 * @Graph: 根据输入的邻接矩阵创建图
	 * @param _data: 输入的图的邻接矩阵，其中_data[i][k]表示结点i和k之前的距离，-1表示两点之间的距离为无穷大
	 */
	public Graph(double [][] _data)
	{
		this.size=_data.length;     
		
		this.data=new double [this.size][this.size];
		
		for(int i=0;i<this.size;i++)
		{
			for(int k=0;k<this.size;k++)
			{
				if(_data[i][k]==-1)
					this.data[i][k]=INF;
				else
					this.data[i][k]=_data[i][k];
			}
		}
	}
	
	// 3. methods
	/**
	 * @dfs: 对当前图进行深度优先遍历（dfs）
	 * @param start: 遍历的起始结点
	 * @return: 当前图的深度优先遍历序列
	 * @throws RuntimeException: 若起始结点下标不合法，该方法抛出一个RuntimeException异常
	 * @note: 深度优先遍历通常使用栈进行实现，基本步骤如下：（1）将起始结点入栈，（2）循环进行以下步骤直到栈为空为止：从栈中出栈栈顶元素，判断该结点是否已经访问过，若未访问过则依次标记输出该结点，标记该结点为已访问，最后将与该结点直接相连即相邻的所有未访问的结点入栈
	 */
	public int [] dfs(int start) throws RuntimeException
	{
		int [] res=new int [this.size];
		boolean [] dic=new boolean [this.size];    // 记录结点是否被访问过的标记数组：false表示未访问过，true表示已经访问过，java默认初始化boolean数组为false
		
		if(start<0||start>=this.size)
			throw new RuntimeException();
		
		Stack<Integer> sta=new Stack<Integer>();
		
		sta.push(start);
		int respos=0;
		
		while(!sta.empty())
		{
			int now=sta.pop();
			
			if(dic[now]==true)   // 若该结点已经访问过，则无需输出和进一步处理
				continue;
			
			res[respos]=now;     // 输出当前结点
			respos+=1;
			
			dic[now]=true;       // 标记当前结点为已访问
			
			for(int i=0;i<this.size;i++)  // 将当前结点所有相邻的且未访问的结点入栈
			{
				if(dic[i]==false&&this.data[now][i]!=INF)
					sta.push(i);
			}
		}
		
		return res;
	}
	
	/**
	 * @bfs: 当前图的广度优先遍历
	 * @param start: 广度优先遍历的起始结点
	 * @return: 当前图的广度优先遍历序列
	 * @throws RuntimeException: 若输入的起始结点下标不合法，则抛出一个RuntimeException异常
	 * @note: 深度优先遍历通常使用栈进行实现，基本步骤如下：（1）将起始结点入队，（2）循环进行如下步骤直到队列为空为止：从队首出队一个元素，若该结点未访问，则依次输出该结点，标记该结点为已访问，将与该结点相邻的未访问的结点入队
	 */
	public int [] bfs(int start) throws RuntimeException
	{
		int [] res=new int [this.size];
		boolean [] dic=new boolean [this.size];    // 记录结点是否被访问过的标记数组：false表示未访问过，true表示已经访问过，java默认初始化boolean数组为false
		
		if(start<0||start>=this.size)
			throw new RuntimeException();
		
		Queue<Integer> que=new ConcurrentLinkedQueue<Integer>();
		int respos=0;
		
		que.add(start);
		
		while(!que.isEmpty())
		{
			int now=que.poll();
			
			if(dic[now]==true)   // 若当前结点已访问，则无需输出和做进一步处理
				continue;
			
			res[respos]=now;    // 输出当前结点
			respos+=1;
			
			dic[now]=true;       // 标记当前结点为已访问
			
			for(int i=0;i<this.size;i++)  // 将当前结点的未访问的结点加入队列中
			{
				if(dic[i]==false&&this.data[now][i]!=INF)
					que.offer(i);
			}
		}
		
		return res;
	}
	
	/**
	 * @dijkstra: 计算某个结点到所有其他结点的最短距离（单源最短路径）
	 * @param start: 作为起点的结点
	 * @return: 起点到所有其他结点的距离
	 * @note: dijkstra算法的基本步骤为（1）将图中的所有结点分为两个集合N和S，集合S中初始包含起始结点，集合N中初始包含其他结点，
	 * 							   （2）初始化集合N中的每个结点i到起始结点的最短距离dist[i]，dist[i]的初始值就是结点i到起始结点的直接距离
	 * 							 （3）循环进行以下步骤直到集合N为空为止：（a）从集合N中选出到起点中距离dist[i]最短的结点k，（b）将结点k从集合N中删除并加入集合S，（c）更新集合N中剩下的结点i到起始结点的距离，由于集合S中增加结点k，因此新增一个从i到起始结点的方式，因此更新公式为：dist[i]=min(dist[i], data[i][k]+dist[k])
	 */
	public double [] dijkstra(int start) throws RuntimeException
	{
		if(start<0||start>=this.size)
			throw new RuntimeException();
		
		double [] dist=new double [this.size];    // 记录各个结点到起始结点的最短距离
		boolean [] visit=new boolean [this.size]; // 记录各个结点属于集合N还是集合S，false表示属于集合N，true属于集合S
		
		visit[start]=true;    // 将起始结点加入集合S
		int count=1;
		
		for(int i=0;i<this.size;i++)   // 初始化数组dist，初始化为各个结点到起始结点的直接距离
		{
			dist[i]=this.data[i][start];
		}
		
		while(count<this.size)
		{
			int minpos=-1;
			double minvalue=INF;
			
			for(int i=0;i<this.size;i++)   // 查找到集合N中起始结点当前距离最短的结点
			{
				if(visit[i]==false&&dist[i]<=minvalue)  // 注意此处需要使用<=
				{
					minpos=i;
					minvalue=dist[i];
				}
			}
			
			visit[minpos]=true;    // 将该节点从集合N中删除并加入集合S
			count+=1;
			
			for(int i=0;i<this.size;i++)
			{
				if(visit[i]==false)
					dist[i]=Math.min(dist[i], this.data[i][minpos]+dist[minpos]);
			}
		}
		
		return dist;
	}
	
	/**
	 * @floyd: 计算每个结点到所有其他结点的最短距离（多源最短路径）
	 * @return: 所有各个结点到所有其他结点的距离
	 * @note: floyd算法的基本步骤为：（1）初始化最短距离矩阵dist和data相等，（2） 先选择中间/中转结点k（必须先选择中间结点k！易错点），然后依次选择每一对起点i和终点j循环执行迭代公式：dist[i][j]=min(dist[i][j], data[i][k]+data[k][j])，其中k依次取0,1,...,this.size-1
	 */
	public double [][] floyd()
	{	
		double [][] dist=new double [this.size][this.size];
		
		for(int i=0;i<this.size;i++)   // 对邻接矩阵进行拷贝
		{
			for(int k=0;k<this.size;k++)
			{
				dist[i][k]=this.data[i][k];
			}
		}
		
		for(int k=0;k<this.size;k++)   // 选择是否中转结点k
		{
			for(int i=0;i<this.size;i++)  // 选择起点i
			{
				for(int j=0;j<this.size;j++)  // 选择终点j
				{
					dist[i][j]=Math.min(dist[i][j], dist[i][k]+dist[k][j]); 
				}
			}
		}
		
		return dist;
	}
	
	/**
	 * @prim: 生成最小生成树的prim算法
	 * @return: 生成的最小生成树的邻接矩阵
	 * @note: 生成最小生成树的prim算法的基本步骤是：（1）初始化两个集合S和N，集合S初始化为包含起始结点，集合N初始化为包含图中的所有其他结点
	 * 									  （2）初始化集合N中的结点i到集合S的最短距离dist[i]，初始化公式为：dist[i]=data[i][start]
	 * 									  （3） 循环进行以下步骤直到集合N为空为止：（a）从集合N中选取到集合S的距离最短的结点k，将结点k从集合N中删除并加入到集合S中，并把对应的边加入结果，（b）更新集合N中剩下的结点i到集合S的距离dist[i]，更新公式为：dist[i]=min(dist[i],data[i][k])
	 */
	public double [][] prim() 
	{
		double [][] res=new double [this.size][this.size];
		
		for(int i=0;i<this.size;i++)   // 将结果的路径长度全部初始化为-1，除了结点到自己本身的距离
		{
			for(int k=0;k<this.size;k++)
			{
				if(i==k)
					res[i][k]=0;
				else
					res[i][k]=-1;
			}
		}
		
		double dist[]=new double [this.size];    // 记录各个结点到集合S的距离
		int distnode[]=new int [this.size];      // 记录各个结点到集合S的距离取最短时，是到集合S中的那个结点时取到最小值
		boolean visit[]=new boolean [this.size]; // 记录结点是在集合S还是在集合N中
		int count=1; 
		
		visit[0]=true;   // 划分集合S和集合N
		
		for(int i=0;i<this.size;i++)   // 初始化集合N中各个点到集合S的距离
		{
			dist[i]=this.data[i][0];
			distnode[i]=0;
		}
		
		while(count<this.size)
		{
			int minpos=-1;
			double minvalue=Double.POSITIVE_INFINITY;
			
			for(int i=0;i<this.size;i++)    // 查找集合N中到集合S距离最近的结点
			{
				if(dist[i]<=minvalue&&visit[i]==false)
				{
					minvalue=dist[i];
					minpos=i;
				}
			}
			
			visit[minpos]=true;  // 将该结点从集合N中删除并加入到集合S中
			res[minpos][distnode[minpos]]=dist[minpos];  // 将对应的边加入结果中
			res[distnode[minpos]][minpos]=dist[minpos];
			count+=1;
			 
			for(int i=0;i<this.size;i++)  // 更新剩下的结点到集合S的距离
			{
				if(visit[i]==false)
				{
					if(this.data[i][minpos]<dist[i])
					{
						dist[i]=data[i][minpos];
						distnode[i]=minpos;
					}
				}
			}
		}
		
		return res;
	}
	
	/**
	 * @kruskkal: 求解当前图的最小生成树的kruskkal算法
	 * @return: 当前图的最小生成树
	 * @note: kruskkal算法的基本步骤是：（1）初始化集合N为空，集合N包含原图中所有的边，（2）循环进行以下步骤直到集合N中含有(this.size-1)条边为止：从集合N中选出最短的且加入集合S后不会产生任何环的边，将该边从集合N中删除并加入集合S中
	 */
	public double [][] kruskkal()
	{
		double res[][]=new double [this.size][this.size]; //集合S
		
		for(int i=0;i<this.size;i++)   // 将结果的路径长度全部初始化为INF，除了结点到自己本身的距离
		{
			for(int k=0;k<this.size;k++)
			{
				if(i==k)
					res[i][k]=0;
				else
					res[i][k]=-1;
			}
		}
		
		ArrayList<Edge> edge=new ArrayList<Edge> ();  // 集合N
		
		for(int i=0;i<this.size;i++)   // 初始化集合S和集合N，集合N中初始情况下包含原图中所有的边（注意不要添加重复边，也不要添加结点到自身的边）
		{
			for(int k=0;k<i;k++)
			{
				Edge temp=new Edge(i, k, this.data[i][k]);
				edge.add(temp);
			}
		}
		
		edge.sort(new Comparator<Edge>() {    // 将集合N中的边由小到大排序
			@Override
			public int compare(Edge e1, Edge e2) {
				return e1.compareTo(e2);
		}});
		
		int count=0;
		
		for(int i=0;i<edge.size();i++)
		{
			if(count==this.size-1)    // 若集合N中已经存在(this.size-1)条边，则循环结束
				break;
			else                      // 循环地将最短且加入后不产生环的边加入到集合N中
			{
				Edge now=edge.get(i);
				if(!this.hasCycle(res, now))
				{
					res[now.node1][now.node2]=now.length;
					res[now.node2][now.node1]=now.length;
					count+=1;
				}
			}
		}
		
		return res;
	}
	
	public boolean hasCycle(double [][] res, Edge e)
	{	
		res[e.node1][e.node2]=e.length;   // 将边首先加入图中
		res[e.node2][e.node1]=e.length;
		
		for(int start=0;start<this.size;start++)
		{
			Stack<Integer> sta=new Stack<Integer>();
			boolean [] dic=new boolean [this.size];    // 记录结点是否被访问过的标记数组：false表示未访问过，true表示已经访问过，java默认初始化boolean数组为false
			
			sta.push(start);  
			
			while(!sta.empty())
			{
				int now=sta.pop();
				
				if(dic[now]==true)   // 若该结点已经访问过，则说明存在环，直接返回true
				{
					res[e.node1][e.node2]=-1;   // 在返回前重新将该边从图中删除
					res[e.node2][e.node1]=-1;     
						
					return true;
				}
				
				dic[now]=true;       // 标记当前结点为已访问
				
				for(int i=0;i<this.size;i++)  // 将当前结点所有相邻的且未访问的结点入栈
				{
					if(dic[i]==false&&res[now][i]!=-1)
						sta.push(i);
				}
			}
		}
		
		res[e.node1][e.node2]=-1;   // 在返回前重新将该边从图中删除
		res[e.node2][e.node1]=-1;     
			
		return false;
	}
	
	public static void main(String [] args)
	{
		double data[][] = { {0,2,4,1,-1,-1,-1},
		       {2,0,-1,3,10,-1,-1},
		       {4,-1,0,2,-1,5,-1},
		       {1,3,2,0,7,8,4},
		       {-1,10,-1,7,0,-1,6},
		       {-1,-1,5,8,-1,0,1},
		       {-1,-1,-1,4,6,1,0}
			 };   // 距离为-1表示两结点之间距离为无穷大
		
		
		Graph graph1=new Graph(data);
		
		System.out.println(Arrays.toString(graph1.dfs(1)));
		
		System.out.println(Arrays.toString(graph1.bfs(1)));
		
		System.out.println(Arrays.toString(graph1.dijkstra(0)));
		
		double [][] dist=graph1.floyd();
		
		System.out.println("[");
		for(int i=0;i<dist.length;i++)
		{
			for(int k=0;k<dist[0].length;k++)
			{
				System.out.print(String.valueOf(dist[i][k])+" ");
			}
			System.out.println("");
		}
		System.out.println("]");
		
		double [][] dist2=graph1.prim();
		
		System.out.println("[");
		for(int i=0;i<dist2.length;i++)
		{
			for(int k=0;k<dist2[0].length;k++)
			{
				System.out.print(String.valueOf(dist2[i][k])+" ");
			}
			System.out.println("");
		}
		System.out.println("]");
		
		double [][] dist3=graph1.kruskkal();
		
		System.out.println("[");
		for(int i=0;i<dist3.length;i++)
		{
			for(int k=0;k<dist3[0].length;k++)
			{
				System.out.print(String.valueOf(dist3[i][k])+" ");
			}
			System.out.println("");
		}
		System.out.println("]");
	}
}