#include<iostream>
#include<cstdio>
#include<windows.h> 
#include<cstring>
#include<math.h>
#include"../../Vector/Vector.h"
#include"../../stack/stack.h"
using namespace std;
 #define N_OPTR 9 //���������
 typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
 //�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��
  const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
    /*              |-------------------- �� ǰ �� �� �� --------------------| */
    /*              +      -      *      /      ^      !      (      )      \0 */
    /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
    /* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
    /* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
    /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
    /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
 };
 

 
  void trim ( const char exp[], Rank& lo, Rank& hi ) { //ɾ��exp[lo, hi]�������ŵ��ǰ׺����׺
    while ( ( lo <= hi ) && ( exp[lo] != '(' ) && ( exp[lo] != ')' ) ) lo++; //���ҵ�һ����
    while ( ( lo <= hi ) && ( exp[hi] != '(' ) && ( exp[hi] != ')' ) ) hi--; //���һ������
 }
 
 Rank divide ( const char exp[], Rank lo, Rank hi ) { //�з�exp[lo, hi]��ʹexpƥ������ӱ��ʽƥ��
    int crc = 1; //crcΪ[lo, mi]��Χ������������Ŀ֮��
    while ( ( 0 < crc ) && ( ++lo < hi ) ) //��������ַ���ֱ������������Ŀ��ȣ�����Խ��
       if ( exp[lo] == '(' ) crc ++;
       else if ( exp[lo] == ')' ) crc --;
    return lo;
 }
 
 bool paren ( const char exp[], Rank lo, Rank hi ) { //�����ʽexp[lo, hi]�Ƿ�����ƥ�䣨�ݹ�棩
    trim ( exp, lo, hi ); if ( lo > hi ) return true; //����������ŵ�ǰ׺����׺
    if ( ( exp[lo] != '(' ) || ( exp[hi] != ')' ) ) return false; //�ס�ĩ�ַ����������ţ���ز�ƥ��
    Rank mi = divide ( exp, lo, hi ); //ȷ���ʵ����зֵ�
    return paren ( exp, lo + 1, mi - 1 ) && paren ( exp, mi + 1, hi ); //�ֱ��������ӱ��ʽ
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
    double evaluate ( char* S, char* RPN ) { //�ԣ����޳��׿ո�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽRPN
    Stack<double> opnd; Stack<char> optr; //������ջ�������ջ
    optr.push ( '\0' ); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
    while ( !optr.empty()) { //�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
//    cout<<flag<<endl;
       if ( isdigit ( *S ) ) { //����ǰ�ַ�Ϊ����������
          readNumber ( S, opnd ); append ( RPN, opnd.top() ); //��������������������RPNĩβ
       } else //����ǰ�ַ�Ϊ���������
          switch ( priority ( optr.top(), *S ) ) { //������ջ�������֮�����ȼ��ߵͷֱ���
             case '<': //ջ����������ȼ�����ʱ
                optr.push ( *S ); S++; //�����Ƴ٣���ǰ�������ջ
                break;
             case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
                optr.pop(); S++; //�����Ų�������һ���ַ�
                break;
             case '>': { //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
                char op = optr.pop(); append ( RPN, op ); //ջ���������ջ��������RPNĩβ
                if ( '!' == op ) //������һԪ�����
                   opnd.push ( calcu ( op, opnd.pop() ) ); //��ȡһ������������������ջ
                else { //������������Ԫ�������
                   double opnd2 = opnd.pop();
//                   cout<<opnd.top()<<endl;
                   if(opnd.empty()){
				   Flag=1;break;}
				   double opnd1 = opnd.pop(); //ȡ����ǰ������
                   opnd.push ( calcu ( opnd1, op, opnd2 ) ); //ʵʩ��Ԫ���㣬�����ջ
                }
                break;
             }
             default : exit ( -1 ); //���﷨���󣬲�������ֱ���˳�
          } 
    }//while
//    cout<<Flag<<endl;
    return opnd.pop();//�������������ļ�����
}
 void put(char *S){
 	int flag=0;double x=0;char RPN[20];
 	flag=paren(S,0,19);
	if(flag==1){
	x=evaluate(S,RPN);
		if(Flag==1)cout<<"������﷨����"<<endl;
	    else cout<<x<<endl;
}else{cout<<"�����﷨����"<<endl;}
//cout<<RPN<<endl;
 }
int main(){
	cout<<"�����������"<<endl;
	char S1[10]="1+2+7";
	cout<<S1<<endl;
	put(S1);
	char S2[10]="5!-(2+7)";
	cout<<S2<<endl;
	put(S2);
	char S3[19]="3^(4/(1+1))";
	cout<<S3<<endl;
	put(S3);
	cout<<"�﷨�������"<<endl;
	char S4[19]="2+(2+(2+2)";
	cout<<S4<<endl;
	put(S4);
	char S5[19]="1+2+";
	cout<<S5<<endl;
	put(S5);
	
	
	
	
	
	
	
}
