#include <iostream>
#include "ZigHashTable.h"

using namespace std;

int main(void)
{
	int data[]= {19,23,1,68,20,84,27,14,55,11,10,79,14};

	ZigHashTable zighashtable(data, 13, 13);
	cout<<zighashtable.toString()<<endl;

	cout<<"------------------------------------"<<endl;

	cout<<zighashtable.exist(0)<<endl;
	cout<<zighashtable.exist(27)<<endl;
	cout<<zighashtable.exist(23)<<endl;

	cout<<"------------------------------------"<<endl;

	for(int i=6;i<13;i++)
	{
		zighashtable.remove(data[i]);
	}

	cout<<zighashtable.toString()<<endl;

	cout<<"------------------------------------"<<endl;

	ZigHashTable zighashtable2=ZigHashTable(zighashtable);
	cout<<zighashtable2.toString()<<endl;

	cout<<"------------------------------------"<<endl;

	ZigHashTable zighashtable3=zighashtable2=zighashtable2;
	cout<<zighashtable3.toString()<<endl;

	cout<<"------------------------------------"<<endl;

}
