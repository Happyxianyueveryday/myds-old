package com.pzh.dag;

import java.util.*;

class DAG implements Cloneable
{
	// 1. domains
	double [][] data;
	int size;
	static double INF=Double.POSITIVE_INFINITY;
	
	// 2. constructor
	/**
	 * @DAG: DAG的构造函数
	 * @param _data: DAG的邻接矩阵，使用-1表示两个结点之间没有有向边（包括自己到自己的边，若不存在该种有向边，则初始化值为-1）
	 * @param size: DAG中的结点个数
	 */
	public DAG(double [][] _data, int _size)
	{
		this.size=_size;
		this.data=new double [this.size][this.size];
		
		for(int i=0;i<size;i++)
		{
			for(int k=0;k<size;k++)
			{
				if(_data[i][k]!=-1)
					this.data[i][k]=_data[i][k];
				else
					this.data[i][k]=INF;
			}
		}
	}
	
	// 3. methods
	/**
	 * @topoSort1: 对当前的DAG使用去点法进行拓扑排序
	 * @param res: 拓扑排序结果存放的数组
	 * @return: 若原有向图中有环，则拓扑排序失败，返回false；否则，拓扑排序成功，返回true
	 * @note: 使用去点法实现拓扑排序的基本思想是：因为拓扑排序要求若存在从结点a到结点b的边，则在拓扑排序序列中结点a排在结点b之前，因此每次都选择一个图中入度为0的结点，则该图中没有排在该结点之前的结点，在将该结点加入结果后，从原图中删除该结点和从该结点出发的边，循环进行上述步骤直到所有结点都加入排序结果中为止
	 * @note: 去点法实现拓扑排序的基本步骤为：（1）创建一个栈，将原图中所有的入度为0的结点入栈
	 *                              （2）循环进行以下步骤直到栈为空时停止：（a）出栈栈顶结点，（b）将当前结点加入排序结果，（3）将当前结点以及从当前结点出发的边从原图中删除，判断删除前由当前结点指向的结点的入度是否为0，将其中入度为0的结点入栈
	 *                              （3）上述步骤结束后，若结果中存在图中所有的结点，则拓扑排序成功；否则原图中存在环，不是DAG，拓扑排序失败
	 */
	public boolean topoSort1(ArrayList<Integer> res)   // java传基本类型参数相当于cpp的值传递，传自定义类型和高级类型以及数组相当于cpp的引用传递
	{
		double [][] _data=new double[this.size][this.size];
		
		for(int i=0;i<this.size;i++)
		{
			for(int k=0;k<this.size;k++)
			{
				_data[i][k]=this.data[i][k];
			}
		}
		
		Stack<Integer> sta=new Stack<Integer> ();
		boolean [] visit=new boolean[this.size];     // 记录结点是否访问过的数组
		
		for(int i=0;i<this.size;i++)
		{
			int flag=0;
			for(int k=0;k<this.size;k++)
			{
				if(_data[k][i]!=INF)
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
				sta.push(i);
		}
		
		while(!sta.empty())
		{
			int now=sta.pop();
			
			res.add(now);
			visit[now]=true;
			
			for(int i=0;i<this.size;i++)
			{
				if(visit[i]==false)
				{
					_data[now][i]=INF;
					
					int flag=0;
					for(int k=0;k<this.size;k++)
					{
						if(_data[k][i]!=INF)
						{
							flag=1;
							break;
						}
					}
					if(flag==0)
						sta.push(i);
				}
			}
		}
		
		if(res.size()==this.size)
			return true;
		else
			return false;
	}
	
	/**
	 * @topoSort2: 对当前的DAG使用dfs进行拓扑排序
	 * @param res: 拓扑排序结果存放的数组
	 * @return: 若原有向图中有环，则拓扑排序失败，返回false；否则，拓扑排序成功，返回true
	 * @note: 使用dfs实现拓扑排序的基本思想是：因为拓扑排序要求若存在从结点a到结点b的边，则在拓扑排序序列中结点a排在结点b之前，因此使用递归的深度遍历时，在访问完了当前结点的子结点后，将当前结点加入排序结果中，则恰好得到了反向的拓扑排序序列
	 * @note: dfs实现拓扑排序的基本步骤为：使用递归的dfs进行，在访问完当前结点所指向的所有结点后，将当前结点加入排序结果中即可得到逆置的拓扑排序序列，最终再将该序列进行反转即可得到拓扑排序序列
	 */
	public boolean topoSort2(ArrayList<Integer> res)
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
	
	@ Override
	public Object clone()
	{
		DAG res=new DAG(this.data, this.size);
		return res;
	}
	
	/**
	 * main: 简单单元测试
	 */
	public static void main(String [] args)
	{
		double [][] data= {{-1,1,-1,1,-1},
						   {-1,-1,1,1,-1},
						   {-1,-1,-1,-1,1},
						   {-1,-1,1,-1,1},
						   {-1,-1,-1,-1,-1}};
		
		DAG dag=new DAG(data, 5);
		
		ArrayList<Integer> res=new ArrayList<Integer> ();
		if(dag.topoSort1(res))
		{
			for(int i=0;i<res.size();i++)
			{
				System.out.print(String.valueOf(res.get(i))+" ");
			}
			System.out.print("\n");
		}
		else
			System.out.println("原图不是DAG，拓扑排序失败！");
		
		DAG dag2=(DAG)dag.clone();
		ArrayList<Integer> res2=new ArrayList<Integer> ();
		if(dag2.topoSort2(res2))
		{
			for(int i=0;i<res2.size();i++)
			{
				System.out.print(String.valueOf(res2.get(i))+" ");
			}
			System.out.print("\n");
		}
		else
			System.out.println("原图不是DAG，拓扑排序失败！");
	}
}