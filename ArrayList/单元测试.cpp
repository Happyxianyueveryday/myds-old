#include <iostream>
#include "ArrayList.h"

using namespace std;

int main(void)
{
	ArrayList lis(10);

	if(!lis.insert(0,2))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(0,1))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(0,0))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(3,4))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(4,5))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(3,3))
		cout<<"插入失败，链表已经满！"<<endl;

	lis.print();

	if(!lis.remove(0))   // 删除逻辑位置为0的0
		cout<<"删除失败，逻辑位置不存在！"<<endl;
	if(!lis.remove(2))   // 删除逻辑位置为2的3
		cout<<"删除失败，逻辑位置不存在！"<<endl;

	lis.print();     // 这时链表中总共存在4个结点，应该还能够插入6个结点

	if(!lis.insert(2,12))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(5,6))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(6,7))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(7,8))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(8,9))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(9,10))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(10,11))
		cout<<"插入失败，链表已经满！"<<endl;

	lis.print();    // 这时链表中总共存在10个结点，链表已经满

	if(!lis.remove(11))   // 删除不合法的位置
		cout<<"删除失败，逻辑位置不存在！"<<endl;
	if(!lis.remove(-1))   // 删除不合法的位置
		cout<<"删除失败，逻辑位置不存在！"<<endl;
	if(!lis.remove(8))    // 删除位置8的元素
		cout<<"删除失败，逻辑位置不存在！"<<endl;
	if(!lis.remove(0))    // 删除位置0的元素
		cout<<"删除失败，逻辑位置不存在！"<<endl;

	lis.print();    // 这时链表中因为移出了两个元素从而留下了两个空位

	if(!lis.insert(0,1022)) // 再尝试插入三个元素，若实现正确则前两个插入可以成功进行，最后一个插入因为无空位而无法进行
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(0,1022))
		cout<<"插入失败，链表已经满！"<<endl;
	if(!lis.insert(0,1022))
		cout<<"插入失败，链表已经满！"<<endl;

	lis.print();

	ArrayList lis2=lis;
	ArrayList lis3=ArrayList(1);

	lis2.print();
	lis3.print();
}
