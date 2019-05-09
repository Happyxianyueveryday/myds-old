#include <iostream> 
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <cstdlib>

using namespace std;

// 整数四则运算表达式计算器 
// note: 关于逆波兰表达式的相关内容，本处不再赘述，请参阅网上的相关内容，例如普通表达式(2+5*10)*2的逆波兰表达式为: 2 5 10 * + 2 * 

/*
 * ExpConvert: 将普通表达式转化为逆波兰表达式 
 * param exp: 输入的普通表达式 
 * note: 将普通表达式转化为逆波兰表达式的方法同样是通过一个临时栈（该栈中只存放运算符）来进行实现: 
 *       创建一个临时栈后，顺序遍历整个原始表达式: 
 *       (1) 若遇到数字，则直接将其放入到逆波兰表达式结果中
 *       (2) 若遇到左括号，则直接将其放入到栈中
 *       (3) 若遇到右括号，则从栈中不断出栈栈顶运算符，直到遇到左括号为止，左括号出栈但是不输出到结果表达式中 
 *       (4) 若遇到非括号运算符（即+, -, *, /），则从栈中不断出栈栈顶运算符并输出到结果中，直到栈顶运算符的优先级小于（没有等于！）当前元素的优先级或者栈顶运算符为左括号为止，然后再将当前元素入栈 （如何得到这个算法，以表达式2*5+5模拟一遍即可） 
 *       遍历结束后，将栈中剩下的符号依次出栈并输出到结果表达式中 
*/
vector<string> ExpConvert(const vector<string> &exp)
{
	vector<string> res;	     // 结果逆波兰表达式
	
	map<string, int> rank;   // 优先级 
	rank["+"]=rank["-"]=0;
	rank["*"]=rank["/"]=1;
	
	// 0. 处理特殊情况 
	if(!exp.size()) 
	return res;
	
	// 1. 顺序遍历整个输入的普通表达式
	stack<string> sta;
	
	for(int i=0;i<exp.size();i++)
	{
		// 1.1 若遇到左括号，则直接将左括号入栈
		if(exp[i]=="(")	      
		sta.push(exp[i]);
		
		// 1.2 若遇到右括号，则从栈顶出栈元素并输出到结果表达式中，直到遇到一个左括号为止，左括号出栈但是不输出 
		else if(exp[i]==")")  
		{
			while(sta.size()&&sta.top()!="(")
			{
				res.push_back(sta.top());
				sta.pop();
			}
			sta.pop();   // 出栈左括号但是不输出到结果表达式中 
		}
		
		// 1.3 若遇到运算符，则不断出栈栈顶元素并输出到结果表达式中，直到遇到一个左括号或者栈顶元素的优先级小于当前元素时停止，再将当前元素入栈 
		else if(exp[i]=="+"||exp[i]=="-"||exp[i]=="*"||exp[i]=="/")  
		{
			while(sta.size()&&sta.top()!="("&&rank[sta.top()]>=rank[exp[i]])
			{
				res.push_back(sta.top());
				sta.pop();
			}
			sta.push(exp[i]);    // 将当前元素入栈 
		} 
		else
		res.push_back(exp[i]);           // 1.4 若遇到数字则直接输出到结果表达式中 
	}
	
	// 2. 遍历结束后，将栈中剩下的符号依次出栈并输出到结果表达式中 
	while(sta.size())
	{
		res.push_back(sta.top());
		sta.pop();
	}
	
	return res;
}


/*
 * ExpCal: 对逆波兰表达式求值
 * exp: 输入的逆波兰表达式
 * note: 根据给定的逆波兰表达式进行求值的算法如下: 
 *       顺序遍历给定的逆波兰表达式: 
 *       (1) 若当前元素为数字，则直接将当前元素入栈
 *       (2) 若当前元素为运算符，从栈中出栈两个元素，将两个元素作当前运算符所规定的运算得到结果后，再将结果入栈 
*/
double ExpCal(const vector<string> &exp) 
{
	// 0. 处理特殊情况 
	if(!exp.size())
	return 0;
	
	// 1. 遍历输入的逆波兰表达式
	stack<double> sta;
	
	for(int i=0;i<exp.size();i++) 
	{
		if(exp[i]=="+")
		{
			double right=sta.top();
			sta.pop();
			double left=sta.top();
			sta.pop();
			
			sta.push(left+right);
		}
		else if(exp[i]=="-")
		{
			double right=sta.top();
			sta.pop();
			double left=sta.top();
			sta.pop();
			
			sta.push(left-right);
		}
		else if(exp[i]=="*")
		{
			double right=sta.top();
			sta.pop();
			double left=sta.top();
			sta.pop();
			
			sta.push(left*right);
		}
		else if(exp[i]=="/")
		{
			double right=sta.top();
			sta.pop();
			double left=sta.top();
			sta.pop();
			
			sta.push(left/right);
		}
		else
		{
			double num=atof(exp[i].c_str());
			sta.push(num);
		}
	}
	
	// 2. 最后栈中剩下的唯一一个元素就是最终表达式求值的结果
	double res=sta.top();
	sta.pop();
	
	return res;
}

/*
 * print: 输出表达式 
*/
void print(string infor, const vector<string> &res)
{
	cout<<infor;
	for(int i=0;i<res.size();i++)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;
}

int main(void)
{
	// 1. 原始表达式 = (5+6*5)*8 = 280
	vector<string> input={"(", "5", "+", "6", "*", "5", ")", "*", "8"};
	vector<string> res=ExpConvert(input);
	print("普通表达式 = ", input);
	print("逆波兰表达式 = ", res);
	cout<<"表达式求值结果 = "<<ExpCal(res)<<endl;
	cout<<"---------------------------------------------"<<endl;
	
	// 2. 原始表达式 = ((2.5+3.75)*7+(3.75+2.25*8)/2)-(8-7) = 53.625
	vector<string> input1={"(", "(", "2.5", "+", "3.75", ")", "*", "7", "+", "(", "3.75", "+", "2.25", "*", "8", ")", "/", "2", ")", "-", "(", "8", "-", "7", ")"};
	vector<string> res1=ExpConvert(input1);
	print("普通表达式 = ", input1);
	print("逆波兰表达式 = ", res1);
	cout<<"表达式求值结果 = "<<ExpCal(res1)<<endl;
	cout<<"---------------------------------------------"<<endl;
}
