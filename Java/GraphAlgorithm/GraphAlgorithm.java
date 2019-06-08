package com.pzh.graphalgorithm;

import java.util.*;

public class GraphAlgorithm 
{
	// 1. domains
	public static double INF=Double.POSITIVE_INFINITY;
	
	// 2. methods
	// 2.1 无向图中环的存在性
	/**
	 * @hasCycle: 判断给定的无向图是否存在环
	 * @param graph: 输入的无向图的邻接矩阵
	 * @param size: 输入的无向图的结点个数
	 * @note: 无向图是否存在环的最简单的判断方法就是直接使用dfs，从每一个结点开始进行一次dfs，若在dfs遍历过程中遇到已经访问过的结点，则说明原图中存在环，否则不存在环
	 */
	public static boolean hasCycle(double [][] graph, int size)
	{
		for(int i=0;i<size;i++)
		{
			Stack<Integer> sta=new Stack<Integer> ();
			boolean [] visit=new boolean [size];
			
			sta.push(i);
			
			while(!sta.empty())
			{
				int now=sta.pop();
				
				if(visit[now]==true)
					return true;
				
				visit[now]=true;
				
				for(int k=0;k<size;k++)
				{
					if(graph[now][k]!=INF)    // 这里无需判断是否已经访问过，否则对环的判断有影响
						sta.push(k);
				}
			}
		}
		return false;
	}
	
	// 2.2 有向图中环的存在性
	/**
	 * @diHasCycle: 判断给定的有向图是否存在环
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @note: 判断有向图是否存在环的方法同样不唯一，常见的一种方法是使用拓扑排序：若对给定的有向图进行拓扑排序后得到完整的拓扑排序序列，则说明原图中不存在环
	 */
	public static boolean diHasCycle(double [][] digraph, int size)
	{
		Stack<Integer> sta=new Stack<Integer> ();
		ArrayList<Integer> res=new ArrayList<Integer> ();
		boolean [] visit=new boolean [size];
		
		int [] degree=new int [size];   // 记录图中各个结点的入度
		for(int i=0;i<size;i++)
		{
			int count=0;
			for(int k=0;k<size;k++)
			{
				if(digraph[k][i]!=INF)
					count+=1;
			}
			degree[i]=count;
		}
		
		for(int i=0;i<size;i++)
		{
			if(degree[i]==0)
				sta.push(i);
		}
		
		while(!sta.empty())
		{
			int now=sta.pop();
			
			if(visit[now]==true)
				continue;
			
			visit[now]=true;
			res.add(now);
			
			for(int i=0;i<size;i++)
			{
				if(digraph[now][i]!=INF)
					degree[i]-=1;
				if(degree[i]==0&&visit[i]==false)
					sta.push(i);
			}
		}
		
		if(res.size()!=size)
			return true;
		else
			return false;
	}
	
	// 2.3 有向图的连通性
	/**
	 * @isConnect: 判断给定的无向图是否连通
	 * @param graph: 输入的无向图的邻接矩阵
	 * @param size: 输入的无向图的结点个数
	 * @return: 若输入的无向图为连通的，则返回true；否则返回false
	 * @note: 判断无向图的连通性只需要进行一次dfs或者bfs即可，若一次遍历后所遍历的结点数量等于图中总的结点数量，则给定的无向图是连通的，否则不是连通的
	 */
	public static boolean isConnect(double [][] graph, int size)
	{
		int count=0;
		
		Stack<Integer> sta=new Stack<Integer> ();
		boolean [] visit=new boolean [size];
		
		sta.push(0);
		
		while(!sta.empty())
		{
			int now=sta.pop();
			
			if(visit[now]==true)
				continue;
			
			count+=1;
			visit[now]=true;
			
			for(int i=0;i<size;i++)
			{
				if(graph[now][i]!=INF)   // 这里也可以加上条件&&visit[i]==false来进行进一步优化，减少执行时间，但是不加也可以正常进行dfs
					sta.push(i);
			}
		}
		
		if(count==size)
			return true;
		else
			return false;
	}
	
	// 2.4 有向图的三类连通性：弱连通性，单向连通性，强连通性
	/**
	 * @diWeakConnect: 判断给定的有向图是否为弱连通的
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 若输入的有向图为弱连通的，则返回true；否则返回false
	 * @note 1: 有向图的强连通性的标准定义是：将有向图中的有向边换成无向边后，得到的无向图是连通的，则这时称该有向图是弱连通的
	 * @note 2: 因此根据有向图的弱连通性的定义，具体的算法步骤为：将原图中的有向边转化无向边后，直接调用无向图的连通性判断方法进行判断
	 */
	public static boolean diWeakConnect(double [][] digraph, int size)
	{
		double [][] data=new double [size][size];
		for(int i=0;i<size;i++)
		{
			for(int k=0;k<size;k++)
			{
				if(digraph[i][k]!=INF)
					data[i][k]=data[k][i]=digraph[i][k];
			}
		}
		
		return GraphAlgorithm.isConnect(data, size);
	}
	
	/**
	 * @diSingleConnect: 判断给定的有向图是否为单向连通的
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 若输入的有向图为单向连通的，则返回true；否则返回false
	 */
	public static boolean diSingleConnect(double [][] digraph, int size)
	{
		
	}
	
	/**
	 * @diStrongConnect: 判断给定的有向图是否为强连通的
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 若输入的有向图为强连通的，则返回true；否则返回false
	 */
	public static boolean isStrongConnect(double [][] digraph, int size)
	{
		
	}
	
	// 2.5 有向图的强连通分量
	/**
	 * @getStrongWeight: 获取输入的有向图的强连通分量
	 * @param digraph: 输入的有向图的邻接矩阵
	 * @param size: 输入的有向图的结点个数
	 * @return: 给定有向图的强连通分量组成的矩阵
	 */
	public double [][] getStrongWeight(double [][] digraph, int size)
	{
		
	}
	
	
	// 2.6 无向图的双连通性和割点
	/**
	 * @isBiConnect: 判断给定的无向图是否为双连通的
	 * @param graph: 输入的无向图的邻接矩阵
	 * @param size: 输入的无向图的结点个数
	 * @return: 若输入的无向图为双连通的，则返回true；否则返回false
	 */
	public static boolean isBiConnect(double [][] graph, int size)
	{
		
	}
	
	/**
	 * @findDividedPoint: 查找无向图的割点
	 * @param graph: 输入的无向图的邻接矩阵
	 * @param size: 输入的无向图的结点个数
	 * @return: 给定无向图的结果点列表
	 */
	public static ArrayList<Integer> findDividedPoint(double [][] graph, int size)
	{
		
	}
	
	/**
	 * @main: 单元测试方法
	 */
	public static void main(String [] args)
	{
		double INF=Double.POSITIVE_INFINITY;        // 两个结点之间若无边，则设置为正无穷
		
		// 1. 测试无向图中环存在性的判断
		System.out.println("测试无向图中环存在性的判断：");
		double data1[][] = {{0,2,4,1,INF,INF,INF},
			       {2,0,INF,3,10,INF,INF},
			       {4,INF,0,2,INF,5,INF},
			       {1,3,2,0,7,8,4},
			       {INF,10,INF,7,0,INF,6},
			       {INF,INF,5,8,INF,0,1},
			       {INF,INF,INF,4,6,1,0}};   
		int size1=7;
		
		System.out.println(GraphAlgorithm.hasCycle(data1, size1));
		
	    // 2. 测试有向图中环存在性的判断
		System.out.println("测试有向图中环存在性的判断：");
		double [][] data2= {{INF,1,INF,1,INF},      // 测试用有向图1，参见王道数据结构，p216
				   {INF,INF,1,1,INF},
				   {INF,INF,INF,INF,1},
				   {INF,INF,1,INF,1},
				   {INF,INF,INF,INF,INF}};

		double [][] data3= {{INF,3,2,INF,INF,INF},   // 测试用有向图2，参见王道数据结构，p219
				   {INF,INF,INF,2,3,INF},
				   {INF,INF,INF,4,INF,3},
				   {INF,INF,INF,INF,INF,2},
				   {INF,INF,INF,INF,INF,1},
				   {INF,INF,INF,INF,INF,INF}};
		
		double [][] data4= {{INF,1,INF,1,INF,INF,INF,INF,INF,INF},   // 测试用有向图3，参见数据结构与算法分析，p248
				            {INF,INF,1,INF,INF,1,INF,INF,INF,INF},
				            {1,INF,INF,1,1,INF,INF,INF,INF,INF},
				            {INF,INF,INF,INF,1,INF,INF,INF,INF,INF},
				            {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
				            {INF,INF,1,INF,INF,INF,INF,INF,INF,INF},
				            {INF,INF,INF,INF,INF,1,INF,1,INF,INF},
				            {INF,INF,INF,INF,INF,1,INF,INF,INF,1},
				            {INF,INF,INF,INF,INF,INF,INF,1,INF,INF},
				            {INF,INF,INF,INF,INF,INF,INF,INF,1,INF}};
		
		double [][] data5= {{INF,1,INF},{INF,INF,1},{1,INF,INF}};     // 测试用有向图4，三角形有向有环图
		
		int size2=5;
		int size3=6;
		int size4=10;
		int size5=3;
		
		System.out.println(GraphAlgorithm.diHasCycle(data2, size2));
		System.out.println(GraphAlgorithm.diHasCycle(data3, size3));
		System.out.println(GraphAlgorithm.diHasCycle(data4, size4));
		System.out.println(GraphAlgorithm.diHasCycle(data5, size5));
		
		// 3. 测试无向图的连通性判断
		System.out.println("测试无向图中连通性的判断：");
		double [][] data6= {{INF,1,INF},{1,INF,INF},{INF,INF,INF}};      // 测试用无向图2，不连通       
		int size6=3;
		
		System.out.println(GraphAlgorithm.isConnect(data1, size1));
		System.out.println(GraphAlgorithm.isConnect(data6, size6));
		
		// 4. 测试有向图的弱连通性，单向连通性和强连通性判断
		System.out.println("测试有向图中弱连通性的判断：");
		System.out.println(GraphAlgorithm.diWeakConnect(data2, size2));
		System.out.println(GraphAlgorithm.diWeakConnect(data3, size3));
		System.out.println(GraphAlgorithm.diWeakConnect(data4, size4));
		System.out.println(GraphAlgorithm.diWeakConnect(data5, size5));
	}
}
