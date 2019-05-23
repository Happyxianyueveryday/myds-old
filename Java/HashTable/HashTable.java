package hashtable;

import java.util.Random;

// HashTable: 基于开放寻址法的哈希表实现

class HashTable
{
	// 1. domain
	int [] data;       // 哈希表底层存储
	boolean [] dic;    // 记录哈希表的底层存储数组单元是否已经被使用
	int max_size;      // 哈希表最大容量
	String method;     // 选择哈希表冲突探查方式，基于开放寻址法存在两种冲突解决算法——线性探查法，二次探查法和再散列法
	
	// 2. constructor
	/**
	 * @HashTable: 构造空的哈希表
	 * @param _max_size: 哈希表的最大容量
	 * @param _method: 指定哈希表解决冲突具体使用的开放寻址法，"linear"指定线性探查法，"square"指定平方探查法，"rehash"指定再散列法，其他不合法输入则默认指定为线性探查法
	 */
	public HashTable(int _max_size, String _method)
	{
		this.max_size=_max_size;
		
		if(_method=="linear"||_method=="square"||_method=="rehash")
			this.method=_method;
		else
			this.method="linear";
		
		this.data=new int [this.max_size];
		this.dic=new boolean [this.max_size];
	}
	
	/**
	 * @HashTable: 由键的数组构造哈希表
	 * @param _data: 原始输入数组
	 * @param _size: 原始输入数组的大小
	 * @param _max_size: 哈希表的最大容量
	 * @param _method: 指定哈希表解决冲突具体使用的开放寻址法，"linear"指定线性探查法，"square"指定平方探查法，其他不合法输入则默认指定为线性探查法
	 */
	public HashTable(int [] _data, int _size, int _max_size, String _method)
	{
		this.max_size=_max_size;
		
		if(_method=="linear"||_method=="square"||_method=="rehash")
			this.method=_method;
		else
			this.method="linear";
		
		this.data=new int [this.max_size];
		this.dic=new boolean [this.max_size];
		
		for(int i=0;i<_size;i++)
		{
			this.insert(_data[i]);
		}
	}
	
	// 3. methods
	/**
	 * @insert: 向哈希表中插入一个新值
	 * @param key: 待插入的新值
	 * @return: 若插入成功则返回true，若插入失败则返回false
	 */
	public boolean insert(int key)
	{
		// 1. 首先根据值，使用哈希函数计算出该值在内存中存储的地址（即数组下标）addr=hash(key)
		int index=this.hash(key);
		
		// 2. 检查该位置的值是否已经被使用，若未被使用，则将数据存储于此
		if(this.dic[index]==false)      
		{
			// 2.1 该位置未被使用，直接将待插入的值插入到这个位置
			this.data[index]=key;
			this.dic[index]=true;
			return true;
		}
		
		// 3. 若已经被使用，则使用线性探查法或者二次探查法进行探查
		else 
		{
			if(this.method=="linear")
			{
				// 3.2 该位置已经被使用，这时使用线性探查法，线性探查法依次探查数组下标pos=(index+1)%max_size, (index+2)%max_size, ..., (index+(max.size-1))%max_size，若遇到未被使用的单元，则将要插入的数据存入该单元，返回true；否则，返回false表示无法进行插入
				// note: 线性探查法的优点在于最多max_size-1次就可以探查到整个哈希表中的所有单元，即当哈希表中有空闲单元时，一定能查找到该空闲单元并将待插入元素插入到该空闲单元；缺点在于可能产生堆积现象，即原来要放到下标i的元素因冲突被放到i+1，下一个原来要放到i+1位置的元素被放置到i+2，从而大幅影响查找时间
				for(int i=1;i<this.max_size;i++)
				{
					int pos=(index+i)%this.max_size;
					
					if(this.dic[pos]==false)
					{
						this.data[pos]=key;
						this.dic[pos]=true;
						return true;
					}
				}
				return false;
			}
			else if(this.method=="square")
			{
				// 3.2 该位置已经被使用，这时使用二次探查法，二次探查法依次探查数组下标pos=(index+1^2)%max_size, (index+2^2)%max_size, (index+3^2)%max_size, ... ,(index+(max_size/2)^2)%max_size，若遇到未被使用的单元，则将要插入的数据存入该单元，返回true；否则，返回false表示无法进行插入
				// note: 二次探查法的主要优点在于可以避免堆积现象，缺点在于即使用max_size/2次探查也不能探查到整个哈希表中的所有单元，但是至少能探查到一半的单元，因此即使存在空闲单元，也可能会出现元素的插入失败 
				for(int i=1;i<=this.max_size/2;i++)
				{
					int pos=(index+i^2)%this.max_size;
					
					if(this.dic[pos]==false)
					{
						this.data[pos]=key;
						this.dic[pos]=true;
						return true;
					}
				}
				return false;
			}
			else
			{
				// 3.3 该位置已经被使用，这时使用再哈希法，再哈希法使用另外一个与原哈希函数不同的哈希函数，依次探查数组下标pos=(index+i*hash(index))%max_size，其中i为当前探查的次数
				// note 1: 再哈希法最多经过max_size-1次探查就能够遍历整个哈希表中的所有位置，因此可以探查到整个哈希表中的所有单元，是实际应用中最常见的解决冲突的开放定址法
				for(int i=1;i<this.max_size;i++)
				{
					int pos=(index+i*this.rehash(index))%this.max_size;
					
					if(this.dic[pos]==false)
					{
						this.data[pos]=key;
						this.dic[pos]=true;
						return true;
					}
				}
				return false;
			}
		}
	}
	
	/**
	 * @delete: 删除哈希表中的指定值
	 * @param key: 待删除的值
	 * @return: 若删除成功则返回true，若删除失败则返回false
	 */
	public boolean delete(int key)
	{
		int index=this.getindex(key);
		
		if(index==-1)    // 哈希表中没有该值，删除失败
			return false;
		else             // 哈希表中存在该值，进行删除
		{
			this.dic[index]=false;
			return true;
		}
	}
	
	/**
	 * @getindex: 获取指定值在哈希表中的存储位置（数组下标）
	 * @param key: 待获取下标的值
	 * @return: 对应的下标，若哈希表中不存在该值，则返回-1
	 * @note: 哈希表的查找过程和插入过程在基本上类似
	 */
	public int getindex(int key)
	{
		// 1. 首先根据值，使用哈希函数计算出该值在内存中存储的地址（即数组下标）addr=hash(key)
		int index=this.hash(key);
		
		// 2. 判断该位置的值是否等于目标值，若是则直接返回该位置的下标
		if(this.data[index]==key)
			return index;
		
		// 3. 若该位置的值不等于目标值，则按照所使用的避免冲突的具体算法来进行进一步查找，这里的查找过程和哈希表的插入过程基本类似
		else
		{
			if(this.method=="linear")
			{
				for(int i=1;i<this.max_size;i++)
				{
					int pos=(index+i)%this.max_size;
					if(this.dic[pos]==true&&this.data[pos]==key)
						return pos;
				}
			}
			else if(this.method=="square")
			{
				for(int i=1;i<=this.max_size/2;i++)
				{
					int pos=(index+i^2)%this.max_size;
					if(this.dic[pos]==true&&this.data[pos]==key)
						return pos;
				}
			}
			else
			{
				for(int i=1;i<this.max_size;i++)
				{
					int pos=(index+i*this.rehash(key))%this.max_size;
					if(this.dic[pos]==true&&this.data[pos]==key)
						return pos;
				}
			}
			
			return -1;
		}
	}
	
	/**
	 * @toString: 将哈希表格式化为字符串输出
	 * @return: 输出字符串
	 */
	public String toString()
	{
		String res=new String("");
		
		for(int i=0;i<this.max_size;i++)
		{
			if(this.dic[i]==true)
				res=res+String.valueOf(this.data[i])+" ";
			else
				res=res+"#"+" ";
		}
		
		return res;
	}
	
	/**
	 * @hash: 哈希函数是将要存储的键映射到对应的存储地址（在本哈希表简单实现中是映射到所存储的数组下标），哈希函数的选择非常多，且需要根据实际情况进行选取，这里仅选择最基础的取模哈希函数作为示例
	 * @param key: 要存储的键
	 * @return: 该键在内存中的存储地址（即数组下标）
	 */
	private int hash(int key)
	{
		return key%this.max_size; 
	}
	
	/**
	 * @rehash: 再哈希法中选取的另一个哈希函数，该哈希函数存在多种选择方案，本处所使用的方案和原哈希函数相同
	 * @param key: 要存储的键
	 * @return: 该键在内存中的存储地址（即数组下标）
	 */
	private int rehash(int key)
	{
		return key%this.max_size;      
	}
	
	/**
	 * @main: HashTable类的单元测试
	 */
	public static void main(String [] args)
	{
		int [] data= {19,14,23,1,68,20,84,27,55,11,10,79};
		
		// 1. 测试线性探查法
		HashTable hashtable1=new HashTable(data, 12, 13, "linear");
		System.out.println("使用线性探查法构建的哈希表: "+hashtable1.toString());
		
		for(int i=0;i<12;i++)
			// 输出下标为-1表示该值在哈希表中不存在
			System.out.println("哈希表中值 val = "+String.valueOf(data[i])+"的下标为 index = "+String.valueOf(hashtable1.getindex(data[i])));
		
		if(hashtable1.delete(20))
			System.out.println("删除值20后的哈希表为: "+hashtable1.toString());
		else
			System.out.println("删除值20失败");
			
		if(hashtable1.delete(100))
			System.out.println("删除值100后的哈希表为: "+hashtable1.toString());
		else
			System.out.println("删除值100失败");
		
		System.out.println("--------------------------------------------------------");
	
		
		// 2. 测试二次探查法
		HashTable hashtable2=new HashTable(data, 12, 13, "square");
		System.out.println("使用二次探查法构建的哈希表: "+hashtable2.toString());
		
		for(int i=0;i<12;i++)
			// 输出下标为-1表示该值在哈希表中不存在
			System.out.println("哈希表中值 val = "+String.valueOf(data[i])+"的下标为 index = "+String.valueOf(hashtable2.getindex(data[i])));
		
		if(hashtable2.delete(84))
			System.out.println("删除值84后的哈希表为: "+hashtable2.toString());
		else
			System.out.println("删除值84失败");
			
		if(hashtable2.delete(1))
			System.out.println("删除值1后的哈希表为: "+hashtable2.toString());
		else
			System.out.println("删除值1失败");
		
		System.out.println("--------------------------------------------------------");
		
		// 3. 测试再哈希法
		HashTable hashtable3=new HashTable(data, 12, 13, "rehash");
		System.out.println("使用再哈希法构建的哈希表: "+hashtable3.toString());
		
		for(int i=0;i<12;i++)
			// 输出下标为-1表示该值在哈希表中不存在
			System.out.println("哈希表中值 val = "+String.valueOf(data[i])+"的下标为 index = "+String.valueOf(hashtable3.getindex(data[i])));
		
		if(hashtable3.delete(84))
			System.out.println("删除值84后的哈希表为: "+hashtable3.toString());
		else
			System.out.println("删除值84失败");
			
		if(hashtable3.delete(1))
			System.out.println("删除值1后的哈希表为: "+hashtable3.toString());
		else
			System.out.println("删除值1失败");
		
		System.out.println("--------------------------------------------------------");
	}
}