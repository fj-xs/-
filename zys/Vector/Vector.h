#include"../stack/stack.h"
#ifndef VECTOR
#define VECTOR
typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
#include<stdlib.h>
#include<iostream>
template <typename T> class Vector { //����ģ����
protected:
   Rank _size; int _capacity, clock;  T* _elem; //��ģ��������������
   void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
   void expand(); //�ռ䲻��ʱ����
   void shrink(); //װ�����ӹ�Сʱ���� 
   void heapSort ( Rank lo, Rank hi );
public:
// ���캯��
   void merge ( Rank lo, Rank mi, Rank hi ); //�鲢�㷨
   void mergeSort ( Rank lo, Rank hi ); //�鲢�����㷨 
   bool bubble ( Rank lo, Rank hi ); //ɨ�轻��
   bool bubble ( Rank n, Rank lo, Rank hi);
   void bubbleSort ( Rank n, Rank lo, Rank hi);
   void bubbleSort ( Rank lo, Rank hi ); //���������㷨
   void selectionSort ( Rank lo, Rank hi );
   void quickSort ( Rank lo, Rank hi );
   void InsertionSort ( Rank lo, Rank hi);
   Rank partition ( Rank lo, Rank hi );
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) {
   //����Ϊc����ģΪs������Ԫ�س�ʼΪv 
   _elem = new T[_capacity = c]; 
   for( _size = 0; _size < s; _elem[_size++] = v );} //s<=c
   Vector ( T const* A, Rank n ) 
  	    { copyFrom ( A, 0, n ); } //�������帴��
   Vector ( T const* A, Rank lo, Rank hi )
    	{ copyFrom ( A, lo, hi ); } //����
   Vector ( Vector<T> const& V )
    	{ copyFrom ( V._elem, 0, V._size ); } //�������帴��
   Vector ( Vector<T> const& V, Rank lo, Rank hi )
   	    { copyFrom ( V._elem, lo, hi ); } //����
// ��������
   ~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�
// ֻ�����ʽӿ�
   Rank size() const { return _size; } //��ģ
   bool empty() const { return !_size; } //�п�
   int disordered() const; //�ж������Ƿ�������
   Rank find ( T const& e ) const { return find ( e, 0, _size ); } //���������������
   Rank find ( T const& e, Rank lo, Rank hi ) const; //���������������
   void findem1m2(Rank lo , Rank hi, double m1,double m2);
   Rank search ( T const& e ) const //���������������
   { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
   Rank search ( T const& e, Rank lo, Rank hi ) const; //���������������
// ��д���ʽӿ�
   T& operator [] ( Rank r ) const; //�����±������������������������ʽ���ø�Ԫ��
   Vector<T>& operator = ( Vector<T> const& ); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
   T remove ( Rank r ); //ɾ����Ϊr��Ԫ��
   int remove ( Rank lo, Rank hi ); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
   Rank insert ( Rank r, T const& e ); //����Ԫ��
   Rank insert ( T const& e ) 
   { return insert ( _size, e ); } //Ĭ����ΪĩԪ�ز���
   void output ( Vector<T> & V );
   void unsort ( Rank lo, Rank hi ); //��[lo, hi)����
   void unsort()
    { unsort ( 0, _size ); } //��������
   int deduplicate(); //����ȥ��
   int uniquify(); //����ȥ��
   int check(Rank lo, Rank hi, double m1, double m2);
// ����
void traverse ( void (* ) ( T& ) ); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
template <typename VST> void traverse ( VST& ); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector
//������������������������������������������������������������������������������������������������������������// 
//copyfrom
template <typename T>
void Vector<T>::copyFrom(T const*A, Rank lo, Rank hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo<hi)
		_elem[_size++] = A[lo++];
}

//template <typename T>
//Vector<T>& Vector<T>::operator=(Vector<T> const& V)
//{
//	if (_elem) delete []_elem;
//	copyFrom (V._elem,0,V._size());
//	return *this;
//}//=������,��������Ҫ�� 

template <typename T>
T& Vector<T>::operator [] ( Rank  r) const {  //�����±������
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
//����expand
template <typename T>
void Vector<T>::expand()
{
	if(_size < _capacity) return;//δ�� ������ 
	if(_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY; //��֤������ԭ�������� 
	T *oldElem = _elem; _elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete []oldElem;//�ͷ�ԭ�ռ� 
}

//����shrink
template <typename T>
void Vector<T>::shrink()
{
	if(_capacity < DEFAULT_CAPACITY << 1)return;
	if(_size << 2 > _capacity)return;
	T* oldElem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete []oldElem;
}
//���� 
template <typename T>
Rank Vector<T>::insert ( Rank r, T const& e )
{
	expand();//����Ҫ�������� 
	for(int i=_size; i>r; i--)
		_elem[i] = _elem[i-1];
	_elem[r] = e;
	_size++;
	return r;
}
//����
template <typename T> 
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const
{
	while ((lo < hi--)&&(e != _elem[hi] ) );
	return hi;
}
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo,Rank hi)//���ֲ��� 
{
	while(1<hi - lo)
	{
		Rank mi = (lo < hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;
	}
	return (e == A[lo]) ? lo : -1;
}

//���� 
template <typename T>
void Vector<T>::unsort ( Rank lo, Rank hi )
{
	T* V = _elem + lo;
	for(Rank i = hi - lo;i > 0; i--)
		swap(V[i-1],V[rand() % i]);
} //��[lo, hi)����

//����ɾ��
template <typename T>
int Vector<T>::remove ( Rank lo, Rank hi )
{
	if( lo == hi)return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();//����Ҫ ���� 
	return hi - lo; 
 } 
 //��Ԫ��ɾ��
template <typename T>
T Vector<T>::remove ( Rank r )
{
	T e = _elem[r];//���ݱ�ɾ����Ԫ�� 
	remove(r, r+1);
	return e;
}
//Ψһ��
template <typename T>
int Vector<T>::deduplicate() //����ȥ��
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
//���������
template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for(int i = 1;i < _size; i++)
		if( _elem[i-1] > _elem[i] ) n++;
	return n;//���ҽ���n=0ʱ�������� 
}
//����

template <typename T> //������������
void Vector<T>::quickSort ( Rank lo, Rank hi ) { //0 <= lo < hi <= size
   /*DSA*/ //printf ( "\tQUICKsort [%3d, %3d)\n", lo, hi );
   if ( hi - lo < 2 ) return; //��Ԫ��������Ȼ���򣬷���...
   Rank mi = partition ( lo, hi ); //��[lo, hi)�ڹ������
   quickSort ( lo, mi ); //��ǰ׺�ݹ�����
   quickSort ( mi + 1, hi ); //�Ժ�׺�ݹ�����
}

//#define Put( K, s, t ) { if ( 1 < (t) - (s) ) { K.push(s); K.push(t); } }
//#define Get( K, s, t ) { t = K.pop(); s = K.pop(); }
//
//template <typename T> //������������
//void Vector<T>::quickSort( Rank lo, Rank hi ) { //0 <= lo < hi <= size
//   Stack<Rank> Task; Put( Task, lo, hi );
//   while ( !Task.empty() ) {
//      Get( Task, lo, hi );
//      /*DSA*/ //printf ( "\tQUICKsort: " ); for ( Rank i = 0; i < Task.size(); i+=2 ) printf ( " " ); printf ( " [%3d, %3d)\n", lo, hi );
//      Rank mi = partition( lo, hi ); //��[lo, hi)�ڹ������
//      if ( mi - lo < hi - mi ) {
//         Put( Task, mi+1, hi ); Put( Task, lo, mi );
//      } else {
//         Put( Task, lo, mi ); Put( Task, mi+1, hi );
//      }
//   } //������������ջ��С�������ȳ�ջִ�У����ɱ�֤�ݹ���ȣ��ռ�ɱ�������O(logn)
//}

template <typename T> 
bool Vector<T>::bubble(Rank lo, Rank hi) { //һ��ɨ�轻��
   bool sorted = true; 
   while (++lo < hi) 
      if (_elem[lo - 1] > _elem[lo]) 
	  {
         sorted = false; 
         swap(_elem[lo - 1], _elem[lo]); 
      }
   return sorted; //���������־
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
			swap(_elem[lo - 1], _elem[lo]);	//��������ֵ
		}
	}	
	return sorted;
}
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)	//ð������
{
	while (!bubble(lo, hi--));
}
template<typename T>
void Vector<T>::bubbleSort(Rank n, Rank lo, Rank hi)	//ð������
{
	while (!bubble(n, lo, hi--));
}


template <typename T> //���������Ĺ鲢
void Vector<T>::merge(Rank lo ,Rank mi, Rank hi){
    //��mi Ϊ�磬���������������[lo,mi) [mi, hi)
    T*  A = _elem + lo; //�ϲ��������A[0,hi-lo) = _elem[lo,hi)
    int lb = mi - lo ; T* B = new T[lb] ;//ǰ������B[0,lb) = _elem[lo,mi)
    for(Rank i = 0 ; i < lb ;B[i] = A[i++]);//����ǰ������,ֻ��ǰ����б�Ҫ���ƣ��б����ǵķ���
    int lc = hi-mi ; T* C = _elem + mi;//ǰ������C[0,lc) = _elem[mi,hi)
    for(Rank i = 0 , j = 0,k = 0 ; (j < lb)||(k < lc);){
        // ��B[j]��C[k]�е�С������A��ĩβ
        if((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
        if((k < lc) && (!(j < lb) || C[k] <= B[j])) A[i++] = C[k++];
    }
    delete []B; //�ͷ���ʱ�ռ�B
} // �鲢��õ��������������� lo,hi



//���β���
template <typename T> //���������Ĺ鲢����
void Vector<T>::mergeSort(Rank lo , Rank hi){
    if (hi - lo < 2) return; //һֱ���ε���Ԫ�����䣬��ʱ��Ȼ˳��
    int mi = (lo + hi) >>1; // �ҵ������
    mergeSort(lo,mi); mergeSort(mi,hi); merge(lo,mi,hi); //���Σ�Ȼ��鲢
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
  




