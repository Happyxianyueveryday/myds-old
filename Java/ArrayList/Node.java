package com.pzh.arraylist;

public class Node 
{
	// 1. domains
	public int val;      // 当前结点的值
	public int next;     // 指向下一个结点的指针，若值为-1则表示当前结点不存在下一个结点
	
	// 2. constructor
	public Node()
	{
		this.val=0;
		this.next=-1;
	}
}
