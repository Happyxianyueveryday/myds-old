#include <iostream>
#include <string>
#include <cstdlib>
#include "ListNode.h"

using namespace std;

class ZigHashTable
{
	public:
	// 1. constructor
	ZigHashTable(int _max_size);
	ZigHashTable(int _data[], int _size, int max_size);

	// 2. copy controller
	ZigHashTable(const ZigHashTable &other);
	ZigHashTable & operator = (const ZigHashTable &other);

	// 3. methods
	void insert(int key);
	bool remove(int key);
	bool exist(int key);
	string toString();

	// 4. destructor
	~ZigHashTable();

	// 5. domains
	private:
	ListNode **data;
	int max_size;

	int hash(int key);
};


/**
 * ZigHashTable: 创建一个空的哈希表
 */
ZigHashTable::ZigHashTable(int _max_size)
{
	max_size=_max_size;
	data=new ListNode* [max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i]=new ListNode(0);
	}
}

/**
 * ZigHashTable: 根据数组创建哈希表
 */
ZigHashTable::ZigHashTable(int _data[], int _size, int _max_size)
{
	max_size=_max_size;
	data=new ListNode* [max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i]=new ListNode(0);
	}

	for(int i=0;i<_size;i++)
	{
		this->insert(_data[i]);
	}
}

/**
 * ZigHashTable: 拷贝构造函数
 */
ZigHashTable::ZigHashTable(const ZigHashTable &other)
{
	max_size=other.max_size;
	data=new ListNode* [max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i]=new ListNode(0);
	}

	for(int i=0;i<max_size;i++)
	{
		ListNode *now=data[i];
		ListNode *othernow=other.data[i]->next;

		while(othernow)
		{
			now->next=new ListNode(othernow->val);
			othernow=othernow->next;
			now=now->next;
		}
	}
}

/**
 * operator =: 拷贝赋值运算符
 */
ZigHashTable &ZigHashTable::operator =(const ZigHashTable &other)
{
	if(&other==this)
		return (*this);

	for(int i=0;i<max_size;i++)
	{
		ListNode *now=data[i];
		while(now)
		{
			ListNode *temp=now;
			now=now->next;
			delete temp;
		}
	}

	delete [] data;

	max_size=other.max_size;
	data=new ListNode* [max_size];

	for(int i=0;i<max_size;i++)
	{
		data[i]=new ListNode(0);
	}

	for(int i=0;i<max_size;i++)
	{
		ListNode *now=data[i];
		ListNode *othernow=other.data[i]->next;

		while(othernow)
		{
			now->next=new ListNode(othernow->val);
			othernow=othernow->next;
			now=now->next;
		}
	}

	return (*this);
}

/**
 * hash: 本哈希表所选用的哈希函数
 * param key: 输入的原始值
 * return: 输入值的对应密钥
 */
int ZigHashTable::hash(int key)
{
	return key%max_size;
}


/**
 * insert: 向哈希表中插入一个值
 * param key: 要插入的值
 */
void ZigHashTable::insert(int key)
{
	int index=this->hash(key);

	ListNode *now=data[index]->next;
	ListNode *nowprev=data[index];

	while(now)
	{
		if(now->val>=key)
			break;
		else
		{
			nowprev=now;
			now=now->next;
		}
	}

	if(!now||now->val>key)
	{
		ListNode *newnode=new ListNode(key);
		nowprev->next=newnode;
		newnode->next=now;
	}

	return;
}

/**
 * remove: 从哈希表中删除给定的值
 * param key: 要删除的值
 * return: 若成功找到该值并删除则返回true，否则返回false
 */
bool ZigHashTable::remove(int key)
{
	int index=this->hash(key);

	ListNode *now=data[index]->next;
	ListNode *nowprev=data[index];

	while(now)
	{
		if(now->val==key)
		{
			nowprev->next=now->next;
			delete now;
			return true;
		}
		else
		{
			nowprev=now;
			now=now->next;
		}
	}

	return false;
}

/**
 * exist: 判断给定值是否在哈希表中存在
 * param key: 要判断是否存在的值
 * return: 若该值在哈希表中存在则返回true，否则返回false
 */
bool ZigHashTable::exist(int key)
{
	int index=this->hash(key);

	ListNode *now=data[index]->next;

	while(now)
	{
		if(now->val==key)
			return true;
		else
			now=now->next;
	}

	return false;
}

/**
 * toString: 将哈希表格式化为字符串输出
 * return: 输出的格式化字符串
 */
string ZigHashTable::toString()
{
	string res;

	for(int i=0;i<max_size;i++)
	{
		res+="#";
		ListNode *now=data[i]->next;

		while(now)
		{
			char tempstr[100];
			itoa(now->val, tempstr, 10);
			res=res+"->"+string(tempstr);
			now=now->next;
		}

		res+="\n";
	}

	return res;
}

/**
 * ~ZigHashTable: 类的析构函数
 */
ZigHashTable::~ZigHashTable()
{
	for(int i=0;i<max_size;i++)
	{
		ListNode *now=data[i];

		while(now)
		{
			ListNode *temp=now;
			now=now->next;
			delete temp;
		}
	}

	delete [] data;
}


