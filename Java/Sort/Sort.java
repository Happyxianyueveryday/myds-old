package sort;

import java.util.Arrays;

class Sort
{
	// 1. methods
	
	/**
	 * @bubble_sort: 对输入数组进行冒泡排序
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void bubble_sort(int [] lis, int size)
	{
		for(int i=size-1;i>=0;i--)
		{
			for(int k=0;k<i;k++)
			{
				if(lis[k]>lis[k+1])
				{
					int temp=lis[k];
					lis[k]=lis[k+1];
					lis[k+1]=temp;
				}
			}
		}
	}
	
	/**
	 * @insert_sort: 对输入数组进行插入排序
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void insert_sort(int [] lis, int size)
	{
		for(int i=0;i<size;i++)
		{
			int tar=lis[i];
			int k=i-1;
			
			for(k=i-1;k>=0;k--)
			{
				if(lis[k]<tar)
					break;
				else
					lis[k+1]=lis[k];
			}
			
			lis[k+1]=tar;
		}
	}
	
	/**
	 * @select_sort: 对输入数组进行选择排序 
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void select_sort(int [] lis, int size)
	{
		for(int i=0;i<size;i++)
		{
			int min=lis[i];
			int minpos=i;
			
			for(int k=i;k<size;k++)
			{
				if(lis[k]<min)
				{
					minpos=k;
					min=lis[k];
				}
			}
			
			int temp=lis[i];
			lis[i]=lis[minpos];
			lis[minpos]=temp;
		}
	}
	
	/**
	 * @shell_sort: 对输入数组进行希尔排序 
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void shell_sort(int [] lis, int size)
	{
		int step=size/2;
		
		while(step>=1)
		{
			for(int i=0;i<step;i++)
			{
				for(int k=i;k<size;k+=step)
				{
					int pos=k-step;
					int tar=lis[k];
					
					for(pos=k-step;pos>=0;pos-=step)
					{
						if(lis[pos]<tar)
							break;
						else
							lis[pos+step]=lis[pos];
					}
					
					lis[pos+step]=tar;
				}
			}
			
			step/=2;
		}
	}
	
	/**
	 * @merge_sort: 对输入数组进行归并排序
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void merge_sort(int [] lis, int size)
	{
		real_merge(lis, 0, size-1);
	}
	
	private static void real_merge(int [] lis, int begin, int end)
	{
		if(begin>=end)
			return;
		
		int mid=(begin+end)/2;
		
		real_merge(lis, begin, mid);
	    real_merge(lis, mid+1, end);
	    
	    int pos1=begin;
	    int pos2=mid+1;
	    int respos=0;
	    
	    int [] res=new int[end-begin+1];
	    
	    while(pos1<=mid&&pos2<=end)
	    {
	    	if(lis[pos1]<lis[pos2])
	    	{
	    		res[respos]=lis[pos1];
	    		respos+=1;
	    		pos1+=1;
	    	}
	    	else
	    	{
	    		res[respos]=lis[pos2];
	    		respos+=1;
	    		pos2+=1;
	    	}
	    }
	    
	    while(pos1<=mid)
	    {
	    	res[respos]=lis[pos1];
    		respos+=1;
    		pos1+=1;
	    }
	    
	    while(pos2<=end)
	    {
	    	res[respos]=lis[pos2];
    		respos+=1;
    		pos2+=1;
	    }
	    
	    int i=begin;
	    int j=0;
	    while(i<=end)
	    {
	    	lis[i]=res[j];
	    	i+=1;
	    	j+=1;
	    }
	}
	
	/**
	 * @quick_sort: 对输入数组进行快速排序 
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void quick_sort(int [] lis, int size)
	{
		real_quick(lis, 0, size-1);
	}
	
	private static void real_quick(int [] lis, int begin, int end)
	{
		if(begin>=end)
			return;
		
		// 1. partition 
		int pivot=lis[begin];
		int pos=begin;
		
		for(int i=begin+1;i<=end;i++)   // attention: i should begin with (begin+1), not begin.
		{
			if(lis[i]<=pivot)
			{
				pos+=1;
				
				int temp=lis[pos];
				lis[pos]=lis[i];
				lis[i]=temp;
			}
		}
		
		int temp=lis[pos];
		lis[pos]=lis[begin];
		lis[begin]=temp;
		
		// 2. recursion
		real_quick(lis, begin, pos-1);
		real_quick(lis, pos+1, end);
	}
	
	/**
	 * @param heap_sort: 对输入数组进行堆排序，这里使用最大堆
	 * @param lis: 输入的待排序数组
	 * @param size: 待排序数组的大小
	 */
	public static void heap_sort(int [] lis, int size)
	{
		for(int i=size/2-1;i>=0;i--)
		{
			adjust(lis, i, size-1);
		}
		
		for(int i=size-1;i>=1;i--)
		{
			int temp=lis[i];
			lis[i]=lis[0];
			lis[0]=temp;
			
			adjust(lis, 0, i-1);
		}
	}
	
	/**
	 * @adjust: 对输入的堆进行调整
	 * @param lis: 输入堆的数组
	 * @param begin: 输入的堆的根结点下标
	 * @param end: 输入的堆的最大下标限制
	 */
	private static void adjust(int [] lis, int begin, int end)
	{
		int pos=begin;
		
		while(true)
		{
			if(pos>=end)
				return;
			else
			{
				int left=(2*pos+1>end)?Integer.MIN_VALUE:lis[2*pos+1];
				int right=(2*pos+2>end)?Integer.MIN_VALUE:lis[2*pos+2];
				
				if(right>left&&right>lis[pos])
				{
					int temp=lis[pos];
					lis[pos]=lis[2*pos+2];
					lis[2*pos+2]=temp;
					pos=2*pos+2;
				}
				else if(left>right&&left>lis[pos])
				{
					int temp=lis[pos];
					lis[pos]=lis[2*pos+1];
					lis[2*pos+1]=temp;
					pos=2*pos+1;
				}
				else
					break;
			}
		}
	}
	
	/**
	 * @main: 单元测试
	 */
	public static void main(String [] args)
	{
		int [] lis= {9,6,5,8,7,4,1,2,3};
		Sort.bubble_sort(lis, 9);
		System.out.println(Arrays.toString(lis));
		
		int [] lis2= {9,6,5,8,7,4,1,2,3};
		Sort.insert_sort(lis2, 9);
		System.out.println(Arrays.toString(lis2));
		
		int [] lis3= {9,6,5,8,7,4,1,2,3};
		Sort.select_sort(lis3, 9);
		System.out.println(Arrays.toString(lis3));
		
		int [] lis4= {9,6,5,8,7,4,1,2,3};
		Sort.shell_sort(lis4, 9);
		System.out.println(Arrays.toString(lis4));
		
		int [] lis5= {9,6,3,2,5,8,7,4,1};
		Sort.merge_sort(lis5, 9);
		System.out.println(Arrays.toString(lis5));
		
		int [] lis6= {9,6,3,2,5,8,7,4,1};
		Sort.quick_sort(lis6, 9);
		System.out.println(Arrays.toString(lis6));
		
		int [] lis7= {9,3,2,8,7,1,4,5,6}; 
		Sort.heap_sort(lis7, 9);
		System.out.println(Arrays.toString(lis7));
	}
	
}