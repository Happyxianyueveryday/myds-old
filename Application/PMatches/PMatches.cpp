#include <iostream> 
#include <string>
#include <stack>

using namespace std;

/*
 * PMatches: 判断给定的表达式中的括号是否匹配 
 * param exp: 给定输入的表达式 
 * note: 利用栈判断给定表达式中的括号是否匹配的方法较为简单，直接遍历整个表达式中的每个字符，若遇到左括号则将其入栈，若遇到右括号则从栈顶出栈一个元素，判断出栈的元素和当前遇到遇到右括号是否匹配，若匹配则继续进行循环，否则表达式错误；遍历结束后，判断栈是否为空，若栈不为空，则表达式错误，若栈为空，则表达式正确 
*/
bool PMatches(string exp)
{
	if(exp=="")
	return true;
	
	stack<char> sta;
	
	for(int i=0;i<exp.size();i++)
	{
		if(exp[i]=='['||exp[i]=='{'||exp[i]=='(')   // 遇到左括号，则直接入栈 
		sta.push(exp[i]);
		else if(exp[i]==']'||exp[i]=='}'||exp[i]==')')   // 遇到右括号，从栈顶出栈栈顶元素，判断栈顶元素和当前遇到的右括号是否匹配 
		{
			if(sta.size())    
			{
				// 获取并出栈栈顶元素 
				char temp=sta.top();   
				sta.pop();   
				
				if(exp[i]==']'&&temp=='['||exp[i]=='}'&&temp=='{'||exp[i]==')'&&temp=='(')
				continue;
				else
				return false;
			}
			else     // 若遇到右括号时栈为空，则表达式错误 
			return false;
		}
	}
	
	if(sta.size())
	return false;
	else
	return true;
}

int main(void)
{
	string lis[5]={"{(abc)}", "[{abc}{a(bc)]", "[{}", "", "[{abc(abcd(abcd))}]"};
	
	for(int i=0;i<5;i++)
	{
		if(PMatches(lis[i]))
		cout<<"表达式 exp = "<<lis[i]<<" 合法"<<endl;
		else
		cout<<"表达式 exp = "<<lis[i]<<" 不合法"<<endl;
	}
}
