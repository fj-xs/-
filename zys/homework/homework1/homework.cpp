//排序 
#include<windows.h> 
#include <ctime>
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex.h"
#include "../../vector/vector.h"
using namespace std;
int main()
{
	double time=0;  
    double counts=0;  
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime; 
	Complex A[10];
	Complex B[10];
	Complex C[10];
	cout << "（1）" <<endl; 
	for(int i=0;i<10;i++)
    {
    	C[i].m_real=i+1;
    	C[i].m_imag=i+1;
    	C[i].read_modulus();
        C[i].display();
	}
	cout<<endl;
	cout << "置乱" <<endl; 
	Vector<Complex>v2(C,10);
    v2.unsort (0,10);
    for(int i=0;i<10;i++)
    {
    v2[i].display();
    }
    cout<<endl;
    Complex t;
    t.m_real=4;
    t.m_imag=4;
    t.read_modulus();
    cout << "值与t相等的位置" <<endl; 
    int a;
	a = v2.find(t);
	cout<<a<<endl;
	v2.insert(a,t);
	cout << "插入" <<endl; 
	 for(int i=0;i<11;i++)
    {
    v2[i].display();
    }cout<<endl;
    v2.remove(6);
	cout << "删除第7个位置" <<endl; 
	 for(int i=0;i<10;i++)
    {
    v2[i].display();
    }cout<<endl;
	v2.deduplicate();
	cout << "唯一化" <<endl; 
	for(int i=0;i<9;i++)
    {
    v2[i].display();
    }cout<<endl;
	cout<<endl;
	cout << "（2）" <<endl; 
	
	cout << "随机生成复数" <<endl; 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();
    }
    cout << endl;
    for(int i=0;i<10;i++)
    {
    	B[i].m_real=A[i].m_real;
    	B[i].m_imag=A[i].m_imag;
    	B[i].m_modulus=A[i].m_modulus;
	}
    Vector<Complex>v(A, 10);
    Vector<Complex>v1(B, 10);
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for (int j = 0; j < 10; j++){
	   v[j].display();
    }
    cout<<endl;
    cout<<"乱序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
        cout<<"乱序归并执行时间："<<time*1000<<"ms"<<endl;
    
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"有序冒泡执行时间："<<time*1000<<"ms"<<endl;

    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"有序归并执行时间："<<time*1000<<"ms"<<endl;
    
	v.bubbleSort(-1,0,10);
    v1.bubbleSort(-1,0,10);
	 
    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"倒序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"倒序归并执行时间："<<time*1000<<"ms"<<endl;
    
    cout<<endl;
    cout << "（3）" <<endl; 
    
    
    Complex t2;
    t2.m_real=0;
    t2.m_imag=0;
    t2.read_modulus();
    v2.findem1m2(0,9,4,10);
    cout << "寻找模在4到10之间的数" <<endl; 
    int i=0;
	 while(v2[i]!=t2){
	 	v2[i].display();
	 	i++;
	 }
	
    
}
