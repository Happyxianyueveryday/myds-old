package com.pzh.aoe;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 * @AOE: AOE网的类实现，AOE网指的是用边表示活动的网络
 * @note: 需要特别注意，在AOE网中，有如下的基本规定：
 *       （1）每个结点代表一个事件，每条结点之间的有向边来代表一个活动，在某个事件的基础上执行一个活动，就可以引发另一个事件（相当于从一个结点沿着一个有向边到另一个结点）
 *       （2）每条边代表从一个结点（事件）到另一个结点（事件）的过程所需要耗费的时间
 *       （3）每个结点（代表一个事件）必须等到当前结点的所有前驱结点全部发生后才能发生（核心规定，务必非常熟悉）
 */
public class AOE
{
	// 1. domains
	private double [][] data;    // AOE网的邻接矩阵
	private int size;            // AOE网的结点个数 
	private int begin;           // AOE网中的起始结点/起始事件
	private int end;             // AOE网中的终止结点/终止事件
	
	private static double INF=Double.POSITIVE_INFINITY;
	
	// 2. constructor
	/**
	 * @AOE: AOE网的私有构造函数
	 * @param _data: AOE网的邻接矩阵
	 * @param _size: AOE网中的结点个数
	 * @param _begin: AOE网中的起始结点/起始事件
	 * @param _end: AOE网中的终止结点/终止事件
	 */
	private AOE(double [][] _data, int _size, int _begin, int _end)
	{
		this.size=_size;
		this.begin=_begin;
		this.end=_end;
		this.data=new double [this.size][this.size];
		
		for(int i=0;i<this.size;i++)
		{
			for(int k=0;k<this.size;k++)
			{
				if(_data[i][k]!=-1)
					this.data[i][k]=_data[i][k];
				else
					this.data[i][k]=AOE.INF;
			}
		}
	}
	
	// 3. methods
	/**
	 * @build: 生产AOE类对象的静态工厂函数
	 * @param _data: AOE网的邻接矩阵
	 * @param _size: AOE网的结点个数
	 * @return: 若输入的AOE网的邻接矩阵符合AOE网的基本定义和要求，则返回新创建的AOE网对象，否则返回null
	 * @note: AOE网的邻接矩阵必须满足要求: AOE网中有且仅有一个起始结点/起始事件和终止结点/终止事件，其中起始结点的入度为0，终止结点的出度为0，这是AOE网的基本定义要求
	 */
	public static AOE build(double [][] _data, int _size)
	{
		int begin_count=0;    // 计算起始结点的数量
		int end_count=0;      // 计算终止结点的数量
		int begin=-1;         // 记录起始结点
		int end=-1;           // 记录终止结点
		
		for(int i=0;i<_size;i++)
		{
			int begin_flag=0;
			int end_flag=0;
			for(int k=0;k<_size;k++)
			{
				if(_data[k][i]!=-1)
					begin_flag=1;
				if(_data[i][k]!=-1)
					end_flag=1;
			}
			if(begin_flag==0)
			{
				begin=i;
				begin_count+=1;
			}
			if(end_flag==0)
			{
				end=i;
				end_count+=1;
			}
		}
		
		if(begin_count==1&&end_count==1)
			return new AOE(_data, _size, begin, end);
		else
			return null;
	}
	
	/**
	 * @early_happen_time: 计算AOE网中各个结点/事件的最早发生时间，最早发生时间是指当起始结点发生后，最早在哪个时刻当前结点代表的事件能够发生
	 * @return: 各个结点的最早发生时间组成的数组
	 * @note 1: 因为当前结点i只有在其各个前驱结点k所代表的事件全部发生后才能发生，因此当前结点i的最早发生时间的计算公式为: res[i]=max{res[i], res[k]+data[k][i]}，其中k为结点i的各个前驱结点
	 * @note 2: 在具体的实现上，由于每个结点的最早发生时间需要根据该结点的前驱结点进行计算，因此具体的步骤为：
	 *          （1）对原AOE网中的结点进行拓扑排序
	 *          （2）依次按照拓扑排序中得到的阶段顺序，对每一个结点使用公式：res[now]=max{res[now], res[i]+data[i][now]}，其中i取当前结点now的所有前驱结点 
	 */
	public double [] early_happen_time()
	{
		ArrayList<Integer> topo=new ArrayList<Integer>();
		double [] res=new double [this.size];
		
		this.topoSort1(topo);
		
		for(int now=0;now<topo.size();now++)
		{
			for(int i=0;i<this.size;i++)
			{
				if(this.data[i][now]!=INF)
					res[now]=Math.max(res[now], res[i]+data[i][now]);
			}
		}
		
		return res;
	}
	
	/**
	 * @late_happen_time: 计算AOE网中各个结点/事件的最晚发生时间，AOE网中的结点的最晚发生时间是指为了让当前结点所指向的后继结点在其最早发生时间发生，当前结点发生不迟于的最晚时间
	 * @return: 各个结点的最晚发生时间组成的数组
	 * @note 1: 因为当前结点i的所有后继结点k都必须在其最早时刻发生，因此当前结点i的最晚发生时间的计算公式为：res[i]=min{res[i], res[k]-data[i][k]}
	 * @note 2: 在具体的实现上，由于每个结点的最早发生时间需要根据该结点的后驱结点进行计算，因此具体的步骤为：
	 *          （1）对原AOE网中的顶点进行拓扑排序
	 *          （2）依次反向按照拓扑排序中得到的结点顺序，对每一个结点使用公式：res[now]=min{res[now], res[i]-data[now][i]}，其中i取当前结点now的所有后继结点
	 */
	public double [] late_happen_time()
	{
		ArrayList<Integer> topo=new ArrayList<Integer>();
		double [] early=this.early_happen_time();
		double [] res=new double [this.size];
		
		for(int i=0;i<this.size;i++)
		{
			if(i==this.end)
				res[i]=early[this.end];
			else
				res[i]=Double.POSITIVE_INFINITY;
		}
		
		this.topoSort1(topo);
		
		for(int now=topo.size()-1;now>=0;now--)
		{
			for(int i=0;i<this.size;i++)
			{
				if(this.data[now][i]!=INF)
					res[now]=Math.min(res[now], res[i]-data[now][i]);
			}
		}
		
		return res;
	}
	
	/**
	 * @early_activate_time: 计算AOE网中各个边/活动的最早开始时间 
	 * @return: 由各个边的最早开始时间组成的矩阵
	 * @note 1: 对于AOE网中的一个边，其最早开始时间就是该边起点的最早发生时间。因为一旦起点发生，则从起点到终点的活动就可以立即开始执行
	 * @note 2: 在具体的实现上，思想较为简单，只需要首先得到各个结点/事件的最早发生时间，那么对于AOE网中的每一条边/活动，其最早开始时间就是该边的起点的最早发生时间
	 */
	public double [][] early_activate_time()
	{
		double [][] res=new double [this.size][this.size];
		double [] node_early_time=this.early_happen_time();
		
		for(int i=0;i<this.size;i++)
		{
			for(int k=0;k<this.size;k++)
			{
				if(this.data[i][k]!=INF)
					res[i][k]=node_early_time[i];
				else
					res[i][k]=INF;
			}
		}
		
		return res;
	}
	
	/**
	 * @late_activate_time: 计算AOE网中各个边/活动的最晚开始时间 
	 * @return: 由各个边的最晚开始时间组成的矩阵
	 * @note 1: 对于AOE网中的一个边，其最晚开始时间就是该边的终点的最晚发生时间减去该边的长度。因为只有在这种情况下，该边的终点才能够如期按时在最晚开始时间运行
	 * @note 2: 在具体的实现上，思想较为简单，只需要首先得到各个结点/事件的最晚发生时间，那么对于AOE网中的每一条边/活动，其最晚开始时间就是该边终点的最晚发生时间减去该边的长度
	 */
	public double [][] late_activate_time()
	{
		double [][] res=new double [this.size][this.size];
		double [] node_late_time=this.late_happen_time();
		
		for(int i=0;i<this.size;i++)
		{
			for(int k=0;k<this.size;k++)
			{
				if(this.data[i][k]!=INF)
					res[i][k]=node_late_time[k]-this.data[i][k];
				else
					res[i][k]=INF;
			}
		}
		
		return res;
	}
	
	/**
	 * @getKeyPath: 计算得到当前AOE网中的关键路径
	 * @return: 返回值是一个bool矩阵，若AOE网中的一个路径为关键路径，则返回的结果矩阵中的对应位置的值为true，否则值为false
	 * @note 1: AOE网中的关键路径是从AOE网中的边中选择的，关键路径的长度之和是完成整个AOE网所代表的工程的最短时间，关键路径的具体定义是：若AOE网中的一条边的最晚开始时间减去最早开始时间等于0，则该边就是关键路径
	 * @note: 在具体实现上，只需要依次检查AOE网中的每条边，若边的最晚开始时间减去最早开始时间等于0，则该边就是关键路径，将该边对应的位置标记为true 
	 */
	public boolean [][] getKeyPath()
	{
		boolean [][] res=new boolean [this.size][this.size];
		double [][] early_activate_mat=this.early_activate_time();
		double [][] late_activate_mat=this.late_activate_time();
		
		for(int i=0;i<this.size;i++)
		{
			for(int k=0;k<this.size;k++)
			{
				if(this.data[i][k]!=INF&&late_activate_mat[i][k]==early_activate_mat[i][k])
					res[i][k]=true;
				else
					res[i][k]=false;
			}
		}
		
		return res;
	}
	
	/** 
	 * @topoSort2: 对当前的DAG使用dfs进行拓扑排序
	 * @param res: 拓扑排序结果存放的数组
	 * @return: 若原有向图中有环，则拓扑排序失败，返回false；否则，拓扑排序成功，返回true
	 * @note: 使用dfs实现拓扑排序的基本思想是：因为拓扑排序要求若存在从结点a到结点b的边，则在拓扑排序序列中结点a排在结点b之前，因此使用递归的深度遍历时，在访问完了当前结点的子结点后，将当前结点加入排序结果中，则恰好得到了反向的拓扑排序序列
	 * @note: dfs实现拓扑排序的基本步骤为：使用递归的dfs进行，在访问完当前结点所指向的所有结点后，将当前结点加入排序结果中即可得到逆置的拓扑排序序列，最终再将该序列进行反转即可得到拓扑排序序列
	 */
	public boolean topoSort1(ArrayList<Integer> res)
	{
		boolean [] visit=new boolean [this.size];
		
		this.dfs(res, visit, 0);
		
		Collections.reverse(res);
		
		if(res.size()==this.size)
			return true;
		else
			return false;
	}
	
	/**
	 * @dfs: 拓扑排序过程中所使用的深度遍历实现
	 * @param res: 拓扑排序结果数组
	 * @param visit: 标记结点是否已经被访问的标记数组
	 * @param now: 当前访问结点的下标
	 */
	private void dfs(ArrayList<Integer> res, boolean [] visit, int now)
	{
		if(visit[now]==false) 
		{
			visit[now]=true;
			
			for(int i=0;i<this.size;i++)
			{
				if(data[now][i]!=INF&&visit[i]==false)
					dfs(res, visit, i);
			}
			
			res.add(now); 
		}
	}
	
	/**
	 * @main: 单元测试函数
	 */
	public static void main(String [] args)
	{
		double [][] data= {{-1,3,2,-1,-1,-1},
				           {-1,-1,-1,2,3,-1},
				           {-1,-1,-1,4,-1,3},
				           {-1,-1,-1,-1,-1,2},
				           {-1,-1,-1,-1,-1,1},
				           {-1,-1,-1,-1,-1,-1}};
		
		AOE aoe=AOE.build(data, 6);
		
		if(aoe!=null)
		{
			System.out.println("创建AOE网成功");
		}
		else
		{
			System.out.println("创建AOE网失败，输入的邻接矩阵不符合AOE网的要求");
		}
		
		System.out.println("AOE网中各个结点/事件的最早发生时间  = ");
		System.out.println(Arrays.toString(aoe.early_happen_time()));
		
		System.out.println("AOE网中各个结点/事件的最晚发生时间  = ");
		System.out.println(Arrays.toString(aoe.late_happen_time()));
		
		System.out.println("AOE网中各个边/活动的最早开始时间  = ");
		double [][] res=aoe.early_activate_time();
		for(int i=0;i<res.length;i++)
		{
			System.out.println(Arrays.toString(res[i]));
		}
		
		System.out.println("AOE网中各个边/活动的最晚开始时间  = ");
		double [][] res2=aoe.late_activate_time();
		for(int i=0;i<res2.length;i++)
		{
			System.out.println(Arrays.toString(res2[i]));
		}
		
		System.out.println("AOE网中的关键路径矩阵 = ");
		boolean [][] res3=aoe.getKeyPath();
		for(int i=0;i<res3.length;i++)
		{
			System.out.println(Arrays.toString(res3[i]));
		}
	}
}
