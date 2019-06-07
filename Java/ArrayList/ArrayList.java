package com.pzh.arraylist;

import com.pzh.arraylist.Node;

public class ArrayList 
{
	// 1. domains
	private Node [] data;     // 实际存储链表结点的数组，其中data[0]始终用于存储活动链表的头结点，而data[1]始终用于存储空闲链表的头结点
	private int size;         // 活动链表的结点数量
	private int max_size;     // 链表中结点的最大数量
	
	// 2. constructor
	/**
	 * @ArrayList: 创建一个指定大小的空的静态链表
	 * @param _max_size: 静态链表的最大结点数量
	 */
	public ArrayList(int _max_size)
	{
		this.max_size=_max_size+2;
		this.size=0;
		
		this.data=new Node[this.max_size];    // 易错点：需要特别注意，在java中创建自定义对象的数组时，先创建数组，然后再手动创建数组中的每一个对象  
		for(int i=0;i<this.max_size;i++)
		{
			this.data[i]=new Node();
		}
		
		this.data[0].next=-1;
		
		for(int i=1;i<this.max_size-1;i++)
		{
			this.data[i].next=i+1;
		}
	}
	
	/**
	 * @ArrayList: 从数组创建对应的静态链表
	 * @param _max_size: 静态链表的最大结点数量
	 * @param _data: 输入的源数组
	 * @param _size: 输入源数组的大小
	 */
	public ArrayList(int _max_size, int [] _data, int _size)
	{
		this.max_size=_max_size+2;
		this.size=0;
		
		this.data=new Node[this.max_size];
		this.data[0].next=-1;
		
		for(int i=1;i<this.max_size-1;i++)
		{
			this.data[i].next=i+1;
		}
		
		for(int i=_size-1;i>=0;i--)
		{
			this.insert(0, _data[i]);
		}
	}
	
	/**
	 * @malloc: 从空闲链表中分配一个可用结点的下标
	 * @return: 分配的可用结点的下标值，若分配失败则返回下标-1
	 * @note: malloc和free方法配套，用于管理空闲链表，而活动链表则由insert等方法管理
	 */
	private int malloc()
	{
		if(this.data[1].next==-1)    
			return -1;
		else
		{
			int res=this.data[1].next;
			this.data[1].next=this.data[res].next;
			
			return res;
		}
	}
	
	/**
	 * @free: 从活动链表中释放一个活动结点的下标
	 * @param pos: 需要释放的结点的下标
	 * @note: malloc和free方法配套，用于管理空闲链表，而活动链表则由insert等方法管理
	 */
	private void free(int pos)
	{
		int temp=this.data[1].next;
		this.data[1].next=pos;
		this.data[pos].next=temp;
	}
	
	/**
	 * @insert: 向链表中的逻辑下标为pos的位置插入一个元素 
	 * @param pos: 待插入结点的逻辑下标位置
	 * @param val: 需要进行插入的值
	 * @return: 若插入成功则返回true，否则返回false
	 */
	public boolean insert(int pos, int val)
	{
		if(pos<0||pos>this.size)
			return false;
		
		int index=this.malloc();
		
		if(index==-1)
			return false;
		
		int now=this.data[0].next;
		int nowprev=0;
		
		for(int i=0;i<pos;i++)
		{
			nowprev=now;
			now=this.data[now].next;
		}
		
		this.data[index].val=val;
		this.data[nowprev].next=index;
		this.data[index].next=now;
		
		this.size+=1;
		
		return true;
	}
	
	/**
	 * @delete: 从链表中删除指定逻辑位置的结点
	 * @param pos: 待删除结点的逻辑下标位置
	 * @return: 若删除成功则返回true，否则返回false
	 */
	public boolean delete(int pos)
	{
		if(pos<0||pos>=this.size)
			return false;
		
		int now=this.data[0].next;
		int nowprev=0;
		
		for(int i=0;i<pos;i++)
		{
			nowprev=now;
			now=this.data[now].next;
		}
		
		this.data[nowprev].next=this.data[now].next;
		this.free(now);     // 注意不是this.free(pos)，逻辑下标不等于物理下标
		
		this.size-=1;
		
		return true;
	}
	
	/**
	 * @toString: 输出当前静态链表
	 * @return: 当前静态链表的字符串输出
	 */
	public String toString()
	{
		String res=new String("");
		
		int now=this.data[0].next;
		
		while(now!=-1)
		{
			res=res+String.valueOf(this.data[now].val)+" ";
			now=this.data[now].next;
		}
		
		return res;
	}
	
	/**
	 * @main: 单元测试方法
	 */
	public static void main(String [] args)
	{
		ArrayList lis=new ArrayList(10);

		if(!lis.insert(0,2))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(0,1))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(0,0))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(3,4))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(4,5))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(3,3))
			System.out.println("插入失败，链表已经满！");

		System.out.println(lis.toString());
		

		if(!lis.delete(0))   // 删除逻辑位置为0的0
			System.out.println("删除失败，逻辑位置不存在！");
		if(!lis.delete(2))   // 删除逻辑位置为2的3
			System.out.println("删除失败，逻辑位置不存在！");

		System.out.println(lis.toString());   // 这时链表中总共存在4个结点，应该还能够插入6个结点
		

		if(!lis.insert(2,12))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(5,6))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(6,7))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(7,8))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(8,9))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(9,10))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(10,11))
			System.out.println("插入失败，链表已经满！");
		
		System.out.println(lis.toString());    // 这时链表中总共存在10个结点，链表已经满
		
		
		if(!lis.delete(11))   // 删除不合法的位置
			System.out.println("删除失败，逻辑位置不存在！");
		if(!lis.delete(-1))   // 删除不合法的位置
			System.out.println("删除失败，逻辑位置不存在！");
		if(!lis.delete(8))    // 删除位置8的元素
			System.out.println("删除失败，逻辑位置不存在！");
		if(!lis.delete(0))    // 删除位置0的元素
			System.out.println("删除失败，逻辑位置不存在！");

		System.out.println(lis.toString());    // 这时链表中因为移出了两个元素从而留下了两个空位
		
		
		if(!lis.insert(0,1022)) // 再尝试插入三个元素，若实现正确则前两个插入可以成功进行，最后一个插入因为无空位而无法进行
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(0,1022))
			System.out.println("插入失败，链表已经满！");
		if(!lis.insert(0,1022))
			System.out.println("插入失败，链表已经满！");

		System.out.println(lis.toString());
	}
}
