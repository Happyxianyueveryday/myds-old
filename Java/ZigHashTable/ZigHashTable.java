package zighashtable;

import zighashtable.ListNode;

class ZigHashTable
{
	// 1. domains
	ListNode [] data;
	int max_size;
	
	// 2. constructors
	/**
	 * @ZigHashTable: 初始化哈希表
	 * @param _max_size: 哈希表的存储数组大小
	 */
	public ZigHashTable(int _max_size)
	{
		this.max_size=_max_size;
		this.data=new ListNode [this.max_size];    // 在java中，创建一个自定义对象的数组，首先需要创建一个引用数组，然后分别为各个引用创建对象
		
		for(int i=0;i<this.max_size;i++)
		{
			this.data[i]=new ListNode(0);          // 为每一个数组位置创建头部哑结点
		}
	}
	
	/**
	 * @ZigHashTable: 
	 * @param _data: 
	 * @param size: 
	 * @param _max_size: 
	 */
	public ZigHashTable(int [] _data, int size, int _max_size)
	{
		this.max_size=_max_size;
		this.data=new ListNode [this.max_size];    // 在java中，创建一个自定义对象的数组，首先需要创建一个引用数组，然后分别为各个引用创建对象
		
		for(int i=0;i<this.max_size;i++)
		{
			this.data[i]=new ListNode(0);          // 为每一个数组位置创建头部哑结点
		}
		
		for(int i=0;i<size;i++)
		{
			this.insert(_data[i]); 
		}
	}
	
	/**
	 * @insert: 向哈希表中插入给定值
	 * @param key: 要插入的值
	 */
	public void insert(int key)
	{
		// 1. 计算给定值应当插入到哪一个下标位置的链表中
		int index=this.hash(key);     
		
		ListNode now=this.data[index].next;   
		ListNode nowprev=this.data[index];
		
		// 2. 将给定值插入到对应链表中的合理位置，并保证链表的有序性
		while(now!=null)
		{
			if(now.val>=key)    // 查找到第一个大于等于key的链表结点，并将目标值插入到该结点之前
				break;
			else
			{
				nowprev=now;
				now=now.next;
			}
		}
		
		if(now!=null&&now.val==key)  // 当链表中已经存在重复结点时无需进行插入
			return;
		else
		{
			ListNode newnode=new ListNode(key);
			newnode.next=now;
			nowprev.next=newnode;
			
			return;
		}
	}
	
	/**
	 * @delete: 从哈希表中删除给定值
	 * @param key: 要删除的值
	 * @return: 若删除成功则返回true，若哈希表中不存在该值，则返回false，表示删除失败
	 */
	public boolean delete(int key)
	{
		int index=this.hash(key);
		
		ListNode now=this.data[index].next;
		ListNode nowprev=this.data[index];
		
		while(now!=null)
		{
			if(now.val==key)
				break;
			else
			{
				nowprev=now;
				now=now.next;
			}
		}
		
		if(now!=null)
		{
			nowprev.next=now.next;
			return true;
		}
		else
			return false;
	}
	
	/**
	 * @exist: 判断哈希表中是否存在给定值
	 * @param key: 要判断是否存在的值
	 * @return: 若存在该值则返回true，若不存在该值则返回false
	 */
	public boolean exist(int key)
	{
		int index=this.hash(key);
		
		ListNode now=this.data[index].next;
		
		while(now!=null)
		{
			if(now.val==key)
				return true;
			else
				now=now.next;
		}
		
		return false;
	}
	
	/**
	 * @hash: 本哈希表中所使用的哈希表
	 * @param key: 输入值
	 * @return: 输入值的哈希值
	 */
	private int hash(int key)
	{
		return key%this.max_size;
	}
	
	/**
	 * @toString: 将哈希表转化为字符串输出
	 */
	public String toString()
	{
		String res=new String("");
		
		for(int i=0;i<this.max_size;i++)
		{
			res+="#";
			ListNode now=this.data[i].next;
			
			while(now!=null)
			{
				res=res+"->"+String.valueOf(now.val);
				now=now.next;
			}
			
			res+="\n";
		}
		
		return res;
	}
	
	/**
	 * @main: 本类的单元测试
	 */
	public static void main(String [] args)
	{
		int [] data= {19,23,1,68,20,84,27,14,55,11,10,79,14};   
		
		ZigHashTable zighashtable=new ZigHashTable(data, 13, 13);
		
		System.out.println(zighashtable.toString());
		
		System.out.println(zighashtable.exist(0));  
		System.out.println(zighashtable.exist(27));
		System.out.println(zighashtable.exist(23));
		
		for(int i=6;i<13;i++)
		{
			zighashtable.delete(data[i]);
		}
		
		System.out.println(zighashtable.toString());
	}
}