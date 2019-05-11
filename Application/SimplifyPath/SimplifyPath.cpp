#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std; 

/*
 * dividePath: 对输入路径进行分割
 * note: 本函数将给定的路径根据斜杠'/'进行分割，例如将原始路径字符串"/home//foo/"分割为{"home", "", "foo"}  
*/
vector<string> dividePath(string path)
{
	vector<string> res;
	
	string temp;     // 当前正在拼接的片段
	int flag=0;      // 标志变量
	 
	for(int i=0;i<path.size();i++)
	{
		if(flag==0&&path[i]!='/')
		{
			temp.push_back(path[i]);
			flag=1;
		}
		else if(flag==1&&path[i]!='/')
		{
			temp.push_back(path[i]);
		}
		else if(flag==1&&path[i]=='/')
		{
			flag=0;
			res.push_back(temp);
			temp="";
		}
	}
	
	res.push_back(temp);     // 注意由于输入的路径最后可能不以'/'结尾，因此需要最后再将剩下的字符串加入结果数组中 
	
	return res;
}

/*
 * simplifyPath: 对输入路径进行简化 
 * note: 首先对输入的路径字符串进行分割，分割为字符串数组，然后使用栈进行解题，基本步骤如下：
 *       (1) 遍历整个字符串数组，若遇到".."，则从栈中出栈一个元素（如果栈中不为空）；若遇到"."或""，则直接忽略，若遇到其他，则将其入栈 
 *       (2) 将栈中的元素依次出栈，并依次按照给定格式加上斜杠输出  
*/
string simplifyPath(string path) 
{
	stack<string> sta;
	vector<string> lis=dividePath(path);
	
	for(int i=0;i<lis.size();i++)
	{
		if(lis[i]=="..")
		{
			if(sta.size())
			sta.pop();
		}
		else if(lis[i]==".")
		continue;
		else if(lis[i]=="")    // 注意上述的dividePath方法的分割结果可能存在空格 
		continue;
		else
		sta.push(lis[i]);
	}
	
	string res;
	
	while(sta.size())
	{
		string temp=sta.top();
		sta.pop();
		
		res="/"+temp+res;
	}
	
	if(res=="")
	res="/"+res; 
	
	return res;
}


int main(void)
{
	string path;
	
	path="/home/";
	cout<<simplifyPath(path)<<endl;
	
	path="/../";
	cout<<simplifyPath(path)<<endl;
	
	path="/home//foo/";
	cout<<simplifyPath(path)<<endl;
	
	path="/a/./b/../../c/";
	cout<<simplifyPath(path)<<endl;
	
	path="/a/../../b/../c//.//";
	cout<<simplifyPath(path)<<endl;
	
	path="/a//b////c/d//././/..";
	cout<<simplifyPath(path)<<endl;
}
