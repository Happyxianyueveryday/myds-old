#include "Sort.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	Sort sort; 
	
	int lis[]={9,6,3,2,5,8,7,4,1};
	int lis2[]={1};
	
	// 1. ≤‚ ‘√∞≈›≈≈–Ú 
	sort.bubble_sort(lis, 9);
	for(int i=0;i<9;i++)
	{
		cout<<lis[i]<<" ";
	}
	cout<<endl;
	
	sort.bubble_sort(lis2, 1);
	for(int i=0;i<1;i++)
	{
		cout<<lis2[i]<<" ";
	}
	cout<<endl;
	
	// 2. ≤‚ ‘≤Â»Î≈≈–Ú 
	int lis3[]={9,6,3,2,5,8,7,4,1};
	int lis4[]={1};
	
	sort.insert_sort(lis3, 9);
	for(int i=0;i<9;i++)
	{
		cout<<lis3[i]<<" ";
	}
	cout<<endl;
	
	sort.insert_sort(lis4, 1);
	for(int i=0;i<1;i++)
	{
		cout<<lis4[i]<<" ";
	}
	cout<<endl;
	
	 
}
