#include<iostream>
#include<cstdio>
#include<windows.h> 
#include<cstring>
#include<math.h>
#include"../../Vector/Vector.h"
#include"../../queue/queue.h"
#include"../../stack/stack.h"


double count(int *S,int n){//���ñ����㷨 
	Stack<double> opnd;
	double square,max;
	for(int i=0;i<n;i++){
		opnd.push(S[i]);
		int j;
		j=i;
		while(S[j]>=opnd.top()&&j<n){
				opnd.push(S[j]);
				j++;
			}//���Ѱ�� 
		
		square=(j-i)*S[i];
		if(square>max){
			max=square;
		}
		j=i;
		while(S[j]>=opnd.top()&&j<n){
				opnd.push(S[j]);
				j--;
			}//��ǰѰ�� 
		square=(i-j)*S[i];
		if(square>max){
			max=square;
		}
	}
	return max;
}


using namespace std;
int main(){
	int max;
	int n=10;
	int S[n]={2,1,5,6,2,3};
	cout<<"ʾ��"<<endl; 
	cout<<"2,1,5,6,2,3"<<endl;
	max=count(S,n);
	cout<<max<<endl;
	cout<<"�������"<<endl;
	cout<<"(1)"<<endl;
	for(int i=0;i<n;i++){
		S[i]=rand()%100+1;
		cout<<S[i]<<' ';
	}cout<<endl;
	max=count(S,n);
	cout<<max<<endl;
	cout<<"(2)"<<endl;
	for(int i=0;i<n;i++){
		S[i]=rand()%100+1;
		cout<<S[i]<<' ';
	}cout<<endl;
	max=count(S,n);
	cout<<max<<endl;
	cout<<"(3)"<<endl;
	for(int i=0;i<n;i++){
		S[i]=rand()%100+1;
		cout<<S[i]<<' ';
	}cout<<endl;
	max=count(S,n);
	cout<<max<<endl;
}
