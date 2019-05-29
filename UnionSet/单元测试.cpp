#include "UnionSet.h"
#include <iostream>

using namespace std;

int main(void)
{
	int data[]={0,1,2,3,4,5,6,7,8,9};

	UnionSet set(data, 10);

	set.print();

	// 在并查集中构建集合S1={0,6,7,8}，集合S1的根结点的值为0
	set.merge(0,6);    // 将根结点为6的集合并入根结点为0的集合
	set.merge(0,7);    // 将根结点为7的集合并入根结点为0的集合
	set.merge(0,8);    // 将根结点为8的集合并入根结点为0的集合

	// 在并查集中构建集合S2={1,4,9}，集合S2的根结点的值为1
	set.merge(1,4);    // 将根结点为4的集合并入根结点为1的集合
	set.merge(1,9);    // 将根结点为9的集合并入根结点为1的集合

	// 在并查集中构建集合S3={2,3,5}，集合S3的根结点的值为2
	set.merge(2,3);    // 将根结点为3的集合并入根结点为2的集合
	set.merge(2,5);    // 将根结点为5的集合并入根结点为2的集合

	set.print();

	// 查找结点3的根结点
	int rootpos=-1;
	set.findroot(3,rootpos);
	cout<<rootpos<<endl;

	// 查找结点9的根结点
	set.findroot(9,rootpos);
	cout<<rootpos<<endl;

	// 查找结点6的根结点
	set.findroot(6,rootpos);
	cout<<rootpos<<endl;

	// 将集合S2并入集合S1
	set.merge(0,1);

	set.print();

	// 查找结点1的根结点
	set.findroot(1,rootpos);
	cout<<rootpos<<endl;
}
