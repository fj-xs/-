#include"../stack/stack.h"
#ifndef VECTOR
#define VECTOR
typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）
#include<stdlib.h>
#include<iostream>
template <typename T> class Vector { //向量模板类
protected:
   Rank _size; int _capacity, clock;  T* _elem; //规模、容量、数据区
   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand(); //空间不足时扩容
   void shrink(); //装填因子过小时缩容 
   void heapSort ( Rank lo, Rank hi );
public:
// 构造函数
   void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
   void mergeSort ( Rank lo, Rank hi ); //归并排序算法 
   bool bubble ( Rank lo, Rank hi ); //扫描交换
   bool bubble ( Rank n, Rank lo, Rank hi);
   void bubbleSort ( Rank n, Rank lo, Rank hi);
   void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
   void selectionSort ( Rank lo, Rank hi );
   void quickSort ( Rank lo, Rank hi );
   void InsertionSort ( Rank lo, Rank hi);
   Rank partition ( Rank lo, Rank hi );
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) {
   //容量为c、规模为s、所有元素初始为v 
   _elem = new T[_capacity = c]; 
   for( _size = 0; _size < s; _elem[_size++] = v );} //s<=c
   Vector ( T const* A, Rank n ) 
  	    { copyFrom ( A, 0, n ); } //数组整体复制
   Vector ( T const* A, Rank lo, Rank hi )
    	{ copyFrom ( A, lo, hi ); } //区间
   Vector ( Vector<T> const& V )
    	{ copyFrom ( V._elem, 0, V._size ); } //向量整体复制
   Vector ( Vector<T> const& V, Rank lo, Rank hi )
   	    { copyFrom ( V._elem, lo, hi ); } //区间
// 析构函数
   ~Vector() { delete [] _elem; } //释放内部空间
// 只读访问接口
   Rank size() const { return _size; } //规模
   bool empty() const { return !_size; } //判空
   int disordered() const; //判断向量是否已排序
   Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
   Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找
   void findem1m2(Rank lo , Rank hi, double m1,double m2);
   Rank search ( T const& e ) const //有序向量整体查找
   { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
   Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
// 可写访问接口
   T& operator [] ( Rank r ) const; //重载下标操作符，可以类似于数组形式引用各元素
   Vector<T>& operator = ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
   T remove ( Rank r ); //删除秩为r的元素
   int remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
   Rank insert ( Rank r, T const& e ); //插入元素
   Rank insert ( T const& e ) 
   { return insert ( _size, e ); } //默认作为末元素插入
   void output ( Vector<T> & V );
   void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
   void unsort()
    { unsort ( 0, _size ); } //整体置乱
   int deduplicate(); //无序去重
   int uniquify(); //有序去重
   int check(Rank lo, Rank hi, double m1, double m2);
// 遍历
void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
}; //Vector
//——————————————————————————————————————————————————————// 
//copyfrom
template <typename T>
void Vector<T>::copyFrom(T const*A, Rank lo, Rank hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo<hi)
		_elem[_size++] = A[lo++];
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem) delete []_elem;
	copyFrom (V._elem,0,V.size());
	return *this;
}//=号重载,满足向量要求 

template <typename T>
T& Vector<T>::operator [] ( Rank  r) const {  //重载下标操作符
    return _elem[r];   //assert: 0 <= r < _size
}

template <typename T>
int Vector<T>::check(Rank lo, Rank hi, double m1, double m2)
{
	int count = 0;
	for(int i=lo;i<hi;i++)
	{
		if(_elem[i]>=m1&&_elem[i]<m2)
		{
			_elem[count]=_elem[i];
			count++;
		}
	}
	return count;
}
//扩容expand
template <typename T>
void Vector<T>::expand()
{
	if(_size < _capacity) return;//未满 不扩容 
	if(_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY; //保证不低于原来的容量 
	T *oldElem = _elem; _elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete []oldElem;//释放原空间 
}

//缩容shrink
template <typename T>
void Vector<T>::shrink()
{
	if(_capacity < DEFAULT_CAPACITY << 1)return;
	if(_size << 2 > _capacity)return;
	T* oldElem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete []oldElem;
}
//插入 
template <typename T>
Rank Vector<T>::insert ( Rank r, T const& e )
{
	expand();//有需要就先扩容 
	for(int i=_size; i>r; i--)
		_elem[i] = _elem[i-1];
	_elem[r] = e;
	_size++;
	return r;
}
//查找
template <typename T> 
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const
{
	while ((lo < hi--)&&(e != _elem[hi] ) );
	return hi;
}
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo,Rank hi)//二分查找 
{
	while(1<hi - lo)
	{
		Rank mi = (lo < hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;
	}
	return (e == A[lo]) ? lo : -1;
}

//置乱 
template <typename T>
void Vector<T>::unsort ( Rank lo, Rank hi )
{
	T* V = _elem + lo;
	for(Rank i = hi - lo;i > 0; i--)
		swap(V[i-1],V[rand() % i]);
} //对[lo, hi)置乱

//区间删除
template <typename T>
int Vector<T>::remove ( Rank lo, Rank hi )
{
	if( lo == hi)return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();//如需要 缩容 
	return hi - lo; 
 } 
 //单元素删除
template <typename T>
T Vector<T>::remove ( Rank r )
{
	T e = _elem[r];//备份被删除的元素 
	remove(r, r+1);
	return e;
}
//唯一化
template <typename T>
int Vector<T>::deduplicate() //无序去重
{
	int oldSize = _size;
	Rank i = 1;
	while(i < _size)
		(find(_elem[i], 0, i) < 0)?i++:remove( i );
	return oldSize - _size; 
}
template <typename T>
int Vector<T>::uniquify()
{
	Rank i = 0,j = 0;
	while ( ++j < _size)
		if( _elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i; shrink();
	return j - i;
}
//有序性甄别
template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for(int i = 1;i < _size; i++)
		if( _elem[i-1] > _elem[i] ) n++;
	return n;//当且仅当n=0时向量有序 
}
//排序

template <typename T> //向量快速排序
void Vector<T>::quickSort ( Rank lo, Rank hi ) { //0 <= lo < hi <= size
   /*DSA*/ //printf ( "\tQUICKsort [%3d, %3d)\n", lo, hi );
   if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
   Rank mi = partition ( lo, hi ); //在[lo, hi)内构造轴点
   quickSort ( lo, mi ); //对前缀递归排序
   quickSort ( mi + 1, hi ); //对后缀递归排序
}

//#define Put( K, s, t ) { if ( 1 < (t) - (s) ) { K.push(s); K.push(t); } }
//#define Get( K, s, t ) { t = K.pop(); s = K.pop(); }
//
//template <typename T> //向量快速排序
//void Vector<T>::quickSort( Rank lo, Rank hi ) { //0 <= lo < hi <= size
//   Stack<Rank> Task; Put( Task, lo, hi );
//   while ( !Task.empty() ) {
//      Get( Task, lo, hi );
//      /*DSA*/ //printf ( "\tQUICKsort: " ); for ( Rank i = 0; i < Task.size(); i+=2 ) printf ( " " ); printf ( " [%3d, %3d)\n", lo, hi );
//      Rank mi = partition( lo, hi ); //在[lo, hi)内构造轴点
//      if ( mi - lo < hi - mi ) {
//         Put( Task, mi+1, hi ); Put( Task, lo, mi );
//      } else {
//         Put( Task, lo, mi ); Put( Task, mi+1, hi );
//      }
//   } //大任务优先入栈（小任务优先出栈执行），可保证递归深度（空间成本）不过O(logn)
//}

template <typename T> 
bool Vector<T>::bubble(Rank lo, Rank hi) { //一趟扫描交换
   bool sorted = true; 
   while (++lo < hi) 
      if (_elem[lo - 1] > _elem[lo]) 
	  {
         sorted = false; 
         swap(_elem[lo - 1], _elem[lo]); 
      }
   return sorted; //返回有序标志
}
template<typename T>
bool Vector<T>::bubble(Rank n, Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1]<_elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);	//交换两个值
		}
	}	
	return sorted;
}
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)	//冒泡排序
{
	while (!bubble(lo, hi--));
}
template<typename T>
void Vector<T>::bubbleSort(Rank n, Rank lo, Rank hi)	//冒泡排序
{
	while (!bubble(n, lo, hi--));
}


template <typename T> //有序向量的归并
void Vector<T>::merge(Rank lo ,Rank mi, Rank hi){
    //以mi 为界，各自有序的子向量[lo,mi) [mi, hi)
    T*  A = _elem + lo; //合并后的向量A[0,hi-lo) = _elem[lo,hi)
    int lb = mi - lo ; T* B = new T[lb] ;//前子向量B[0,lb) = _elem[lo,mi)
    for(Rank i = 0 ; i < lb ;B[i] = A[i++]);//复制前子向量,只有前面的有必要复制，有被覆盖的风险
    int lc = hi-mi ; T* C = _elem + mi;//前子向量C[0,lc) = _elem[mi,hi)
    for(Rank i = 0 , j = 0,k = 0 ; (j < lb)||(k < lc);){
        // 将B[j]和C[k]中的小者续至A的末尾
        if((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
        if((k < lc) && (!(j < lb) || C[k] <= B[j])) A[i++] = C[k++];
    }
    delete []B; //释放临时空间B
} // 归并后得到完整的有序向量 lo,hi



//分治策略
template <typename T> //有序向量的归并排序
void Vector<T>::mergeSort(Rank lo , Rank hi){
    if (hi - lo < 2) return; //一直分治到单元素区间，此时自然顺序
    int mi = (lo + hi) >>1; // 找到中轴点
    mergeSort(lo,mi); mergeSort(mi,hi); merge(lo,mi,hi); //分治，然后归并
}

template <typename T>
void Vector<T>::findem1m2(Rank lo , Rank hi, double m1,double m2){
 Rank count = 0;
 while(lo < hi){
  if(_elem[lo] > m1 &&_elem[lo] < m2){
   _elem[count] = _elem[lo];
   count++;
  }
 lo++;   
 }
 Vector<T>::remove ( count, hi );
}



template <typename T>
void Vector<T>::selectionSort( Rank lo, Rank hi){
	int j,r;
	T a;
	
	for (int i = lo ; i < hi; i++){
		a = _elem[i];
		r=i;
		for ( j = i+1; j < hi; j++){
			if (a > _elem[j]){ a = _elem[j] ;r = j ;}
		}
		
		_elem[r] = _elem[i];
		_elem[i] = a;
	}
}
template <typename T>
void Vector<T>::InsertionSort ( Rank lo, Rank hi){
	Vector<T> B,C;
	int r = 0;
	for(int i = lo;i <hi;i++){
		if (i == lo){
			B.insert(_elem[lo]);
		}
		for (int j = 0; j < i - lo ;j++){
			if (_elem[i] > B[j]){
			 	r = j+1; 
			}
		}
		B.insert(r,_elem[i]);
	}
    for(int i = 0; i < hi - lo; i++){
    	_elem[lo+i] = B[i];
	}}
template <typename T>
Rank Vector<T>::partition (Rank lo, Rank hi ){
 swap (_elem[lo], _elem[lo + rand()%(hi - lo +1 )]);
 T pivot = _elem[lo];
 while ( lo < hi ){
  while (lo < hi)
      if (pivot < _elem[hi] ) 
         hi--;
      else
          {_elem[lo++] = _elem[hi];break;} 
     while ( lo < hi )
         if ( _elem[lo] < pivot )
             lo++;
         else
         {
          {_elem[hi--] = _elem[lo];break;} 
   }
 }
 _elem[lo] = pivot;
 return lo;
} 


#endif 
  




