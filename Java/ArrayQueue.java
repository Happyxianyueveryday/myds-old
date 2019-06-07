package com.pzh.arrayqueue;

/**
 * @ArrayQueue: 用循环数组实现的队列
 */
public class ArrayQueue 
{
	// 1. domains
	private int [] data;   // 实际存储的底层数组
  	private int front;     // 队首元素下标
	private int rear;       // 队尾元素的后继元素的下标，始终为指向队尾元素的下一个位置的下标
	private int max_size;  // 底层存储数组的最大大小
	
	// 2. methods
	/**
	 * @ArrayQueue: 构造指定大小的，空的静态队列
	 * @param _max_size: 队列的最大大小
	 */
	ArrayQueue(int _max_size)
	{
		this.max_size=_max_size+1;    
		this.front=0;
		this.rear=0;
		this.data=new int [this.max_size];
	}
	
	/**
	 * @push: 向队尾新增一个元素
	 * @param val: 需要新增的元素的值
	 * @return: 若队列未满，入队成功则返回true；若队列已满，入队失败则返回false
	 * @note: 在我们的实现方法中，空出队列中的一个单元不使用，从而区分队空和队满的情况
	 */
	public boolean push(int val)
	{
		if((this.rear+1)%this.max_size==this.front)    // 队列为满的重要标准判断条件：若(rear+1)%max_size==front，则表示队列已经满
			return false;
		else
		{
			this.data[this.rear]=val;
			this.rear=(this.rear+1)%this.max_size;
			return true;
		}
	}
	
	/**
	 * @pop: 从队首出队一个元素
	 * @return: 若队列非空，则出队成功，返回true；否则出队失败，则返回false
	 */
	public boolean pop()
	{ 
		if(this.rear==this.front)          // 队列为空的重要标准判断条件：若rear==front，则表示队列为空
			return false;
		else
		{
			this.front=(this.front+1)%this.max_size;
			return true;
		}
	}
	
	/**
	 * @front: 获取队首元素
	 * @return: 当前队列的队首元素
	 * @warning: 仅有在确定队列为空时，调用该方法才能获得正确的队首元素，否则获取的元素值不正确
	 */
	public int front()
	{
		return this.data[this.front];
	}
	
	/**
	 * @empty: 判断队列是否为空
	 * @return: 若队列为空，则返回true；否则返回false
	 * @note: 静态队列的核心难点就在于判定队空和队满的条件，这里通常使用的方法是空出一个单元不使用来区分队空和队满的条件
	 * @note: 静态队列的队空的判断条件是：rear==front
	 */
	public boolean empty()
	{
		if(this.rear==this.front)
			return true;
		else
			return false;
	}
	
	/**
	 * @full: 判断队列是否为满
	 * @return: 若队列为满，则返回true，否则返回false
	 * @note: 静态队列的队满的判断条件是：(rear+1)%max_size==front
	 */
	public boolean full()
	{
		if((this.rear+1)%this.max_size==this.front)
			return true;
		else
			return false;
	}
	
	/**
	 * @length: 计算队列中的元素个数
	 * @return: 当前静态队列中的元素个数
	 * @note: 对于静态队列而言，计算元素个数的公式是：(rear-front+_max_size)%max_size，该公式只需要多举出几个示例就能够推导得出，但是需要特别注意，这里的max_size是队列中能够存储的最大元素的个数加1
	 */
	public int length()
	{
		return (this.rear-this.front+this.max_size)%this.max_size;
	}
	
	/**
	 * @main: 基础单元测试
	 */
	public static void main(String [] args)
	{
		ArrayQueue que=new ArrayQueue(6);     
		
		// 1. 首先向队列中依次入队元素：1，2，3，4，5，6
		for(int i=1;i<=10;i++)
		{
			if(que.push(i))
				System.out.println("值"+String.valueOf(i)+"入队成功" );
			else
				System.out.println("入队失败，队列已经满");
		}
		
		// 2. 再从队首依次出队元素：1，2，3，这时队列中仅剩下元素：4，5，6
		for(int i=0;i<3;i++)
		{
			int temp=que.front();
			if(que.pop())
				System.out.println("值"+String.valueOf(temp)+"出队成功" );
			else
				System.out.println("出队失败，队列已经空");
		}
		
		 // 3. 再向队列中依次入队元素：7，8，9，10，11，其中只有7，8，9能够入队成功，入队10以及后续元素时，队列已经满
		for(int i=7;i<=11;i++)
		{
			if(que.push(i))
				System.out.println("值"+String.valueOf(i)+"入队成功" );
			else
				System.out.println("入队失败，队列已经满");
		}
		
		// 4. 查看当前的队首元素
		int temp=que.front();
		System.out.println("当前的队首元素为： "+String.valueOf(temp));
		
		System.out.println("当前队列中的元素个数为： "+String.valueOf(que.length()));
		
		
		// 5. 将队列出队至剩下1个元素
		while(que.length()>1)
		{
			temp=que.front();
			if(que.pop())
				System.out.println("值"+String.valueOf(temp)+"出队成功" );
			else
				System.out.println("出队失败，队列已经空");
		}
		
		// 6. 现在队列中只剩下一个元素9，再依次入队：10，11，12，...，直到队列中有4个元素为止，上述元素中仅有10，11，12能够入队成功
		int k=10;
		while(que.length()<4)
		{
			if(que.push(k))
				System.out.println("值"+String.valueOf(k)+"入队成功" );
			else
				System.out.println("入队失败，队列已经满");
			
			k+=1;
		}
		
		// 7. 再入队若干元素
		while(que.length()<9&&k<=17)
		{
			if(que.push(k))
				System.out.println("值"+String.valueOf(k)+"入队成功" );
			else
				System.out.println("入队失败，队列已经满");
			
			k+=1;
		}
		
		// 8. 出队直到队列为空为止
		while(que.length()>0)
		{
			temp=que.front();
			if(que.pop())
				System.out.println("值"+String.valueOf(temp)+"出队成功" );
			else
				System.out.println("出队失败，队列已经空");
		}
	}
}
