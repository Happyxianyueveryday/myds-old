#include "Search.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	Search search;
	
	int lis1[]={1,2,3,4,5,6,7,8,9};
	int lis2[]={2,4,6,8,10};
	int lis3[]={};
	int lis4[]={1};
	int lis5[]={9,6,3,2,5,8,7,4,1};      
	
	int index;
	
	index=search.binary_search(lis1,9,5);
	if(index!=-1)
	cout<<"数组lis1 中元素5的下标为 index = "<<index<<endl;
	else
	cout<<"数组lis1 中元素5不存在"<<endl;
	
	index=search.binary_search(lis1,9,9);
	if(index!=-1)
	cout<<"数组lis1 中元素9的下标为 index = "<<index<<endl;
	else
	cout<<"数组lis1 中元素9不存在"<<endl;
	
	index=search.binary_search(lis2,5,4);
	if(index!=-1)
	cout<<"数组lis2 中元素4的下标为 index = "<<index<<endl;
	else
	cout<<"数组lis2 中元素4不存在"<<endl;
	
	index=search.binary_search(lis3,0,1);
	if(index!=-1)
	cout<<"数组lis3 中元素1的下标为 index = "<<index<<endl;
	else
	cout<<"数组lis3 中元素1不存在"<<endl;
	
	index=search.binary_search(lis4,1,1);
	if(index!=-1)
	cout<<"数组lis4 中元素1的下标为 index = "<<index<<endl;
	else
	cout<<"数组lis4 中元素1不存在"<<endl;
	
	index=search.seq_search(lis5,9,4);
	if(index!=-1)
	cout<<"数组lis5 中元素4的下标为 index = "<<index<<endl;
	else
	cout<<"数组lis5 中元素4不存在"<<endl;
}
