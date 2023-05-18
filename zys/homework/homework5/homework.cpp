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
	Vector<int>v1;
	  for(int i=0;i<10;i++)
    {
    v1.insert(i+1);
    }
    for(int i=0;i<10;i++)
    {
    	printf("%d ",v1[i]);
    }cout<<"顺序"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v1.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v1[i]);}
    cout<<endl;cout<<"冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v1.InsertionSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v1[i]);}
    cout<<endl;cout<<"插排执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v1.selectionSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v1[i]);}
    cout<<endl;cout<<"选排执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v1[i]);}
    cout<<endl;cout<<"归并执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v1.partition(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v1[i]);}
    cout<<endl;cout<<"快排执行时间："<<time*1000<<"ms"<<endl;
    
    Vector<int>v2;
	  for(int i=0;i<10;i++)
    {
    v2.insert(12-i);
    }
    for(int i=0;i<10;i++)
    {
    	printf("%d ",v2[i]);
    }cout<<"逆序"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v2.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v2[i]);}
    cout<<endl;cout<<"冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v2.InsertionSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v2[i]);}
    cout<<endl;cout<<"插排执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v2.selectionSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v2[i]);}
    cout<<endl;cout<<"选排执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v2.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v2[i]);}
    cout<<endl;cout<<"归并执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v2.partition(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v2[i]);}
    cout<<endl;cout<<"快排执行时间："<<time*1000<<"ms"<<endl;
    
     Vector<int>v3;
	  for(int i=0;i<10;i++)
    {
    v3.insert(rand() % 200 / 10);
    }
    for(int i=0;i<10;i++)
    {
    	printf("%d ",v3[i]);
    }cout<<"随机序"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v3.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v3[i]);}
    cout<<endl;cout<<"冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v3.InsertionSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v3[i]);}
    cout<<endl;cout<<"插排执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v3.selectionSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v3[i]);}
    cout<<endl;cout<<"选排执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v3.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v3[i]);}
    cout<<endl;cout<<"归并执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  QueryPerformanceCounter(&nBeginTime);
    v3.partition(0,10); 
    QueryPerformanceCounter(&nEndTime);time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout << "排序后" <<endl;
    for(int i=0;i<10;i++)
    {printf("%d ",v3[i]);}
    cout<<endl;cout<<"快排执行时间："<<time*1000<<"ms"<<endl;
}

