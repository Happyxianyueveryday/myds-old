#include <iostream>
#include "HashTable.h"

using namespace std;

int main(void)
{
	int data[] = {19,14,23,1,68,20,84,27,55,11,10,79};

	// 1. 测试线性探查法
	HashTable hashtable1(data, 12, 13, "linear");
	cout<<"使用线性探查法构建的哈希表: "+hashtable1.toString()<<endl;

	for(int i=0;i<12;i++)
		// 输出下标为-1表示该值在哈希表中不存在
		cout<<"哈希表中值 val = "<<data[i]<<"的下标为 index = "<<hashtable1.getindex(data[i])<<endl;

	if(hashtable1.remove(20))
		cout<<"删除值20后的哈希表为: "+hashtable1.toString()<<endl;
	else
		cout<<"删除值20失败"<<endl;

	if(hashtable1.remove(100))
		cout<<"删除值100后的哈希表为: "+hashtable1.toString()<<endl;
	else
		cout<<"删除值100失败"<<endl;

	for(int i=0;i<12;i++)
		// 输出下标为-1表示该值在哈希表中不存在
		cout<<"哈希表中值 val = "<<data[i]<<"的下标为 index = "<<hashtable1.getindex(data[i])<<endl;

		cout<<"--------------------------------------------------------"<<endl;


	// 2. 测试二次探查法
	HashTable hashtable2(data, 12, 13, "square");
	cout<<"使用二次探查法构建的哈希表: "+hashtable2.toString()<<endl;

	for(int i=0;i<12;i++)
		// 输出下标为-1表示该值在哈希表中不存在
		cout<<"哈希表中值 val = "<<data[i]<<"的下标为 index = "<<hashtable2.getindex(data[i])<<endl;

	if(hashtable2.remove(84))
		cout<<"删除值84后的哈希表为: "+hashtable2.toString()<<endl;
	else
		cout<<"删除值84失败"<<endl;

	if(hashtable2.remove(1))
		cout<<"删除值1后的哈希表为: "+hashtable2.toString()<<endl;
	else
		cout<<"删除值1失败"<<endl;

		cout<<"--------------------------------------------------------"<<endl;

	// 3. 测试再哈希法
	HashTable hashtable3(data, 12, 13, "rehash");
	cout<<"使用再哈希法构建的哈希表: "+hashtable3.toString()<<endl;

	for(int i=0;i<12;i++)
		// 输出下标为-1表示该值在哈希表中不存在
		cout<<"哈希表中值 val = "<<data[i]<<"的下标为 index = "<<hashtable3.getindex(data[i])<<endl;

	if(hashtable3.remove(84))
		cout<<"删除值84后的哈希表为: "+hashtable3.toString()<<endl;
	else
		cout<<"删除值84失败"<<endl;

	if(hashtable3.remove(1))
		cout<<"删除值1后的哈希表为: "+hashtable3.toString()<<endl;
	else
		cout<<"删除值1失败"<<endl;

		cout<<"--------------------------------------------------------"<<endl;
}
