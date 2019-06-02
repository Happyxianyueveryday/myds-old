package com.pzh.threadnode;

public class ThreadNode 
{
	// 1. constructor
	public ThreadNode(int _val)
	{
		this.val=_val;
		this.left=null;
		this.right=null;
		this.lflag=0;
		this.rflag=0;
	}
	
	// 2. domains
	public int val;
	public ThreadNode left;
	public ThreadNode right;
	public int lflag;
	public int rflag;
}