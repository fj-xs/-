 #ifndef LISTNODE
#define LISTNODE
 typedef int Rank;
 #define ListNodePosi(T) ListNode<T>*
 #include<stdlib.h>
 #include <cstddef>

// template <typename T> struct ListNode;
// template <typename T> using ListNodePosi = ListNode<T>*; //�б��ڵ�λ��
 template <typename T> struct ListNode { //�б��ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
 // ��Ա
    T data; 
	ListNodePosi(T) pred;
    ListNodePosi(T) succ; //��ֵ��ǰ�������
 // ���캯��
    ListNode() {} //���header��trailer�Ĺ���
    ListNode ( T e, ListNodePosi(T) p = NULL,
	ListNodePosi(T) s = NULL )
       : data( e ), pred( p ), succ( s ) {} //Ĭ�Ϲ�����
 // �����ӿ�
   ListNodePosi(T) insertAsPred( T const& e ); //������ǰ�ڵ�֮ǰ�����½ڵ�
   ListNodePosi(T) insertAsSucc( T const& e ); //���浱ǰ�ڵ�֮������½ڵ�
 };
 #endif