package com.pzh.edge;

public class Edge implements Comparable<Edge>
{ 
	// 1. domains
	public int node1;   // 边所连接的结点1
	public int node2;   // 边所连接的结点2
	public double length;  // 当前边的长度
	
	// 2. constructor
	public Edge(int _node1, int _node2, double _length)
	{
		this.node1=_node1;
		this.node2=_node2;
		this.length=_length;
	}
	
	// 3. methods
	@Override
	public int compareTo(Edge other)
	{
		if(this.length<other.length)
			return -1;
		else if(this.length>other.length)
			return 1;
		else
			return 0;
	}
}