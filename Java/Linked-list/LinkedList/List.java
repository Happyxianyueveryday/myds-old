package LinkedList;
import ListNode.ListNode;

public class List implements Cloneable
{
	// 1. fields
	private ListNode head;
	private int size;
	
	
	// 2. constructors
	/**
	 * @List: 默认构造函数
	 */
	public List()
	{
		this.head=new ListNode(0);    // 初始化链表头部哑结点
		this.size=0;                  // 初始化链表结点个数
	}
	
	/**
	 * @List: 从输入数组构造链表
	 * @param lis: 输入的数组
	 * @param len: 输入数组的元素个数/长度
	 */
	public List(int [] lis, int len)
	{
		this.head=new ListNode(0);
		this.size=len;
		
		ListNode now=this.head;
		
		for(int i=0;i<len;i++)
		{
			now.next=new ListNode(lis[i]);
			now=now.next;
		}
	}
	
	
	// 3. copy_controller
	public Object clone() throws CloneNotSupportedException
	{
		List copy=new List();
		copy.head=new ListNode(0);
		copy.size=this.size;
		
		ListNode now=this.head.next;
		ListNode copynow=copy.head;
		
		while(now!=null)
		{
			copynow.next=new ListNode(now.val);
			now=now.next;
			copynow=copynow.next;
		}
		
		return copy;
	}
	
	
	// 4. methods
	/**
	 * @insert: 向链表中插入一个新的元素值 
	 * @param pos: 待插入的位置
	 * @param val: 待插入的元素值
	 * @return: 若插入成功返回true，插入失败（位置不合法）则返回false
	 */
	public boolean insert(int pos, int val)
	{
		if(pos>size||pos<0)
			return false;
		
		ListNode now=this.head;
		
		for(int i=0;i<pos;i++)
		{
			now=now.next;
		}
		
		
		ListNode newnode=new ListNode(val);
		newnode.next=now.next;
		now.next=newnode;
		
		size+=1;
		
		return true;
	}
	
	/**
	 * @delete: 删除链表中的给定位置的元素
	 * @param pos: 待删除的位置 
	 * @return: 若删除成功则返回true，删除失败（位置不合法）则返回false
	 */
	public boolean delete(int pos)
	{
		if(pos>=size||pos<0)
			return false;
		
		ListNode now=this.head;
		
		for(int i=0;i<pos;i++)
		{
			now=now.next;
		}
		
		now.next=now.next.next;
		
		size-=1;
		
		return true;
	}
	
	/**
	 * @isvalid: 判断给定的下标位置在链表中是否合法
	 * @param pos: 需要检验合法性的下标
	 * @return: 若下标合法，返回 true；若下标不合法，返回false
	 */
	public boolean isvalid(int pos)
	{
		if(pos>=size||pos<0)
			return false;
		else
			return true;
	}
	
	/**
	 * @getval: getval
	 * @param pos: 需要获取值的下标位置
	 * @return: 链表中对应下标的值
	 * @warning: 在获取一个下标位置之前，首先应该使用isvalid成员方法检验下标是否合法
	 */
	public int getval(int pos)
	{
		if(pos>=size||pos<0)
			return Integer.MIN_VALUE;
		
		ListNode now=this.head.next;
		
		for(int i=0;i<pos;i++)
		{
			now=now.next;
		}
		
		return now.val;
	}
	
	
	/**
	 * @length: 输出链表的长度
	 * @return: 当前链表的长度
	 */
	public int length()
	{
		return size;
	}
	
	/**
	 * @toString: 将链表字符串化以便输出
	 */
	@Override
	public String toString()
	{
		ListNode now=this.head.next;
		String output = new String("");
		
		while(now!=null)
		{
			output=output+((now!=this.head.next)? "->": "")+String.valueOf(now.val);
			now=now.next;
		}
		
		return output;
	}
}