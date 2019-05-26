package search;

public class Search
{
	// 1. constructor
	/**
	 * @Search: 默认构造器
	 */
	Search()
	{
	}
	
	// 2. methods
	/**
	 * @seq_search: 顺序搜索算法实现
	 * @param data: 输入的数组
	 * @param size: 输入数组的大小
	 * @param val: 待查找的值
	 * @return: 待查找的值在输入数组中的下标，若该值在数组中不存在，则返回-1
	 */
	public static int seq_search(int [] data, int size, int val)
	{
		for(int i=0;i<size;i++)
		{
			if(data[i]==val)
				return i;
		}
		
		return -1;
	}
	
	/**
	 * @binary_search: 顺序搜索算法实现
	 * @param data: 输入的数组
	 * @param size: 输入数组的大小
	 * @param val: 待查找的值
	 * @return: 待查找的值在输入数组中的下标，若该值在数组中不存在，则返回-1
	 */
	public static int binary_search(int [] data, int size, int val)
	{
		int begin=0;
		int end=size-1;
		
		while(begin<=end)
		{
			int mid=begin+(end-begin)/2;
			
			if(val>data[mid])
				begin=mid+1;
			else if(val<data[mid])
				end=mid-1;
			else
				return mid;
		}
		
		return -1;
	}
	
	/**
	 * @main: 单元测试方法
	 */
	public static void main(String [] args)
	{
		int lis1[]={1,2,3,4,5,6,7,8,9};
		int lis2[]={2,4,6,8,10};
		int lis3[]={};
		int lis4[]={1};
		int lis5[]={9,6,3,2,5,8,7,4,1};       
		
		int index;
		
		index=Search.binary_search(lis1,9,5);
		if(index!=-1)
			System.out.println("数组lis1 中元素5的下标为 index = "+String.valueOf(index));
		else
			System.out.println("数组lis1 中元素5不存在");
		
		index=Search.binary_search(lis1,9,9);
		if(index!=-1)
			System.out.println("数组lis1 中元素9的下标为 index = "+String.valueOf(index));
		else
			System.out.println("数组lis1 中元素9不存在");
		
		index=Search.binary_search(lis2,5,4);
		if(index!=-1)
			System.out.println("数组lis2 中元素4的下标为 index = "+String.valueOf(index));
		else
			System.out.println("数组lis2 中元素4不存在");
		
		index=Search.binary_search(lis3,0,1);
		if(index!=-1)
			System.out.println("数组lis3 中元素1的下标为 index = "+String.valueOf(index));
		else
			System.out.println("数组lis3 中元素1不存在");
		
		index=Search.binary_search(lis4,1,1);
		if(index!=-1)
			System.out.println("数组lis4 中元素1的下标为 index = "+String.valueOf(index));
		else
			System.out.println("数组lis4 中元素1不存在");
		
		index=Search.seq_search(lis5,9,4);
		if(index!=-1)
			System.out.println("数组lis5 中元素4的下标为 index = "+String.valueOf(index));
		else
			System.out.println("数组lis5 中元素4不存在");
	}
}