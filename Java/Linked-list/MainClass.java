import LinkedList.List;

public class MainClass
{
	public static void main(String [] args) throws CloneNotSupportedException
	{
		// 1. 
		List lis=new List();
		System.out.println("链表lis = "+lis.toString());
		
		int [] data= {1,2,3,4,5,6,7,8,9};
		List lis2=new List(data, 9);
		System.out.println("链表lis2 = "+lis2.toString());
		System.out.println("lis2的长度 = "+String.valueOf(lis2.length()));
		
		// 2. 
		List lis3=(List)lis2.clone();
		System.out.println("链表lis3 = "+lis3.toString());
		
	    lis3=(List)lis3.clone();
		System.out.println("链表lis3 = "+lis3.toString());
		
		// 3. 
		int val;
		if(lis3.delete(0))
		{
			System.out.println("链表lis3 = "+lis3.toString());
		}
		else
		{
			System.out.println("删除失败，给定的下标不合法！"); 
		}
		
		
		if(lis3.delete(4))
		{
			System.out.println("链表lis3 = "+lis3.toString());
		}
		else
		{
			System.out.println("删除失败，给定的下标不合法！"); 
		}
		
		if(lis3.delete(6))
		{
			System.out.println("链表lis3 = "+lis3.toString());
		}
		else
		{
			System.out.println("删除失败，给定的下标不合法！"); 
		}
		
		if(lis3.delete(-1))
		{
			System.out.println("链表lis3 = "+lis3.toString());
		}
		else
		{
			System.out.println("删除失败，给定的下标不合法！"); 
		}
		
		// 4.
		int data3[]= {};
		List lis4=new List(data3, 0);
		
		if(lis4.insert(0,1))
		{
			System.out.println("链表lis4 = "+lis4.toString());
		}
		else
		{
			System.out.println("插入失败，给定的下标不合法！"); 
		}
		
		if(lis4.insert(0,2))
		{
			System.out.println("链表lis4 = "+lis4.toString());
		}
		else
		{
			System.out.println("插入失败，给定的下标不合法！"); 
		}
		
		if(lis4.insert(0,3))
		{
			System.out.println("链表lis4 = "+lis4.toString());
		}
		else
		{
			System.out.println("插入失败，给定的下标不合法！"); 
		}
		
		if(lis4.insert(3,0))
		{
			System.out.println("链表lis4 = "+lis4.toString());
		}
		else
		{
			System.out.println("插入失败，给定的下标不合法！"); 
		}
		
		// 5. 
		if(lis4.isvalid(2))
		{
			System.out.println("指定下标的元素值为 = "+lis4.getval(2));
		}
		else
		{
			System.out.println("获取给定位置值失败，给定的下标不合法！"); 
		}
		
		if(lis4.isvalid(0))
		{
			System.out.println("指定下标的元素值为 = "+lis4.getval(0));
		}
		else
		{
			System.out.println("获取给定位置值失败，给定的下标不合法！"); 
		}
		
		if(lis4.isvalid(4))
		{
			System.out.println("指定下标的元素值为 = "+lis4.getval(4));
		}
		else
		{
			System.out.println("获取给定位置值失败，给定的下标不合法！"); 
		}
		
		if(lis4.isvalid(-1999))
		{
			System.out.println("指定下标的元素值为 = "+lis4.getval(-1999));
		}
		else
		{
			System.out.println("获取给定位置值失败，给定的下标不合法！"); 
		}
	}
}