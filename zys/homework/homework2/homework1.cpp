#include<iostream>
#include<cstdio>
#include<windows.h> 
#include<cstring>
#include<math.h>
#include"../../Vector/Vector.h"
#include"../../stack/stack.h"
using namespace std;
 #define N_OPTR 9 //运算符总数
 typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
 //加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符
  const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
    /*              |-------------------- 当 前 运 算 符 --------------------| */
    /*              +      -      *      /      ^      !      (      )      \0 */
    /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
    /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
    /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
    /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
    /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
 };
 

 
  void trim ( const char exp[], Rank& lo, Rank& hi ) { //删除exp[lo, hi]不含括号的最长前缀、后缀
    while ( ( lo <= hi ) && ( exp[lo] != '(' ) && ( exp[lo] != ')' ) ) lo++; //查找第一个和
    while ( ( lo <= hi ) && ( exp[hi] != '(' ) && ( exp[hi] != ')' ) ) hi--; //最后一个括号
 }
 
 Rank divide ( const char exp[], Rank lo, Rank hi ) { //切分exp[lo, hi]，使exp匹配仅当子表达式匹配
    int crc = 1; //crc为[lo, mi]范围内左、右括号数目之差
    while ( ( 0 < crc ) && ( ++lo < hi ) ) //逐个检查各字符，直到左、右括号数目相等，或者越界
       if ( exp[lo] == '(' ) crc ++;
       else if ( exp[lo] == ')' ) crc --;
    return lo;
 }
 
 bool paren ( const char exp[], Rank lo, Rank hi ) { //检查表达式exp[lo, hi]是否括号匹配（递归版）
    trim ( exp, lo, hi ); if ( lo > hi ) return true; //清除不含括号的前缀、后缀
    if ( ( exp[lo] != '(' ) || ( exp[hi] != ')' ) ) return false; //首、末字符非左、右括号，则必不匹配
    Rank mi = divide ( exp, lo, hi ); //确定适当的切分点
    return paren ( exp, lo + 1, mi - 1 ) && paren ( exp, mi + 1, hi ); //分别检查左、右子表达式
 }
 
 
 void readNumber(char *& p,Stack<double>& opnd){
    opnd.push((double)(*p - '0'));
    while(isdigit(*(++p)))
        opnd.push(opnd.pop()*10+(*p-'0'));
    if('.'!=(*p)) return ;
    double fraction=1;
    while(isdigit(*(++p)))
    opnd.push(opnd.pop()+(*p-'0')*(fraction/=10));
}
 
 void append(char* RPN,double top){
 	*RPN=*RPN+top;
 }
 int Turn(char str){
 	switch(str){
 		case'+':return 0;break;
 		case'-':return 1;break;
 		case'*':return 2;break;
 		case'/':return 3;break;
 		case'^':return 4;break;
 		case'!':return 5;break;
 		case'(':return 6;break;
 		case')':return 7;break;
 		case'\0':return 8;break;
	 }
 }
 char priority(char top,char s){
 	int x,y;
 	x=Turn(top);
 	y=Turn(s);
 	return pri[x][y];
 }
 
 double operator0(double opnd1,double opnd2){
 	return opnd1+opnd2;
 }
 double operator1(double opnd1,double opnd2){
 	return opnd1-opnd2;
 }
 double operator2(double opnd1,double opnd2){
 	return opnd1*opnd2;
 }
 double operator3(double opnd1,double opnd2){
 	return opnd1/opnd2;
 }
 double operator4(double opnd1,double opnd2){
 	return pow(opnd1,opnd2);
 }
 double operator5(double opnd){
 	int n=1,t=1;
 	while(n<=opnd){
 		t=t*n;
 		n++;
	 }return t;
 }
 
 
 double calcu(char op,double opnd){
 	switch(op){
 		case '!':
 		return operator5(opnd);
		 break;	
	 }
}
 
 double calcu(double opnd1,char op,double opnd2){
 	switch(op){
 		case '+':
 		return operator0(opnd1,opnd2);
		 break;	
		 case '-':
 		return operator1(opnd1,opnd2);
		 break;	
		 case '*':
 		return operator2(opnd1,opnd2);
		 break;	
		 case '/':
 		return operator3(opnd1,opnd2);
		 break;	
		 case '^':
 		return operator4(opnd1,opnd2);
		 break;	
	 }
 }
 
    int Flag=0;
    double evaluate ( char* S, char* RPN ) { //对（已剔除白空格的）表达式S求值，并转换为逆波兰式RPN
    Stack<double> opnd; Stack<char> optr; //运算数栈、运算符栈
    optr.push ( '\0' ); //尾哨兵'\0'也作为头哨兵首先入栈
    while ( !optr.empty()) { //在运算符栈非空之前，逐个处理表达式中各字符
//    cout<<flag<<endl;
       if ( isdigit ( *S ) ) { //若当前字符为操作数，则
          readNumber ( S, opnd ); append ( RPN, opnd.top() ); //读入操作数，并将其接至RPN末尾
       } else //若当前字符为运算符，则
          switch ( priority ( optr.top(), *S ) ) { //视其与栈顶运算符之间优先级高低分别处理
             case '<': //栈顶运算符优先级更低时
                optr.push ( *S ); S++; //计算推迟，当前运算符进栈
                break;
             case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                optr.pop(); S++; //脱括号并接收下一个字符
                break;
             case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
                char op = optr.pop(); append ( RPN, op ); //栈顶运算符出栈并续接至RPN末尾
                if ( '!' == op ) //若属于一元运算符
                   opnd.push ( calcu ( op, opnd.pop() ) ); //则取一个操作数，计算结果入栈
                else { //对于其它（二元）运算符
                   double opnd2 = opnd.pop();
//                   cout<<opnd.top()<<endl;
                   if(opnd.empty()){
				   Flag=1;break;}
				   double opnd1 = opnd.pop(); //取出后、前操作数
                   opnd.push ( calcu ( opnd1, op, opnd2 ) ); //实施二元计算，结果入栈
                }
                break;
             }
             default : exit ( -1 ); //逢语法错误，不做处理直接退出
          } 
    }//while
//    cout<<Flag<<endl;
    return opnd.pop();//弹出并返回最后的计算结果
}
 void put(char *S){
 	int flag=0;double x=0;char RPN[20];
 	flag=paren(S,0,19);
	if(flag==1){
	x=evaluate(S,RPN);
		if(Flag==1)cout<<"运算符语法错误"<<endl;
	    else cout<<x<<endl;
}else{cout<<"括号语法错误"<<endl;}
//cout<<RPN<<endl;
 }
int main(){
	cout<<"正常运算举例"<<endl;
	char S1[10]="1+2+7";
	cout<<S1<<endl;
	put(S1);
	char S2[10]="5!-(2+7)";
	cout<<S2<<endl;
	put(S2);
	char S3[19]="3^(4/(1+1))";
	cout<<S3<<endl;
	put(S3);
	cout<<"语法错误举例"<<endl;
	char S4[19]="2+(2+(2+2)";
	cout<<S4<<endl;
	put(S4);
	char S5[19]="1+2+";
	cout<<S5<<endl;
	put(S5);
	
	
	
	
	
	
	
}
