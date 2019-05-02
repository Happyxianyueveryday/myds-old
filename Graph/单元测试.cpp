#include <iostream>
#include "graph-dev.h"

using namespace std;

int main(void)
{
	// 1. 测试构造函数 
	Graph graph1;   // 默认构造函数
	graph1.print();
	
	vector<vector<int> > lis={{0,1,-1,-1,1},{1,0,1,1,1},{-1,1,0,1,-1},{-1,1,1,0,1},{1,1,-1,1,0}};   // 距离为-1表示两结点之间距离为无穷大 
	Graph graph2(lis);  // 由数组构造的构造函数 
	graph2.print();
	
	// 2. 测试拷贝控制函数
	Graph graph3(graph2);    // 拷贝构造函数 
	graph3.print();
	
	Graph graph4=Graph();
	graph4=graph4=graph1=graph3; // 拷贝构造运算符 
	graph1.print();
	graph3.print();
	graph4.print();
	
	// 3. 测试广度优先遍历和深度优先遍历
	cout<<"graph2的深度优先搜索 dfs = "<<endl; 
	vector<int> res=graph2.dfs(1);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;
	
	cout<<"graph2的广度优先搜索 bfs = "<<endl; 
	res=graph2.bfs(1);
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;
	
	// 4. 测试最短距离路径的dijkstra算法和floyd算法 
	cout<<"graph2中结点1到其他结点的最短距离 dijkstra = "<<endl; 
	res=graph2.dijkstra(0);
	for(int i=0;i<res.size();i++)
	{
		cout<<"结点0到结点"<<i<<"的最短距离 dist = "<<res[i]<<" "<<endl;
	}
	cout<<endl;
	
	
}
