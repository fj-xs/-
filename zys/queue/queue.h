 #include "../List/List.h" //��ListΪ������������
 #include<stdlib.h>
 template <typename T> class Queue: public List<T> { //����ģ����
 public: //ԭ�нӿ�һ������
    void enqueue( T const& e ) { this->insertAsLast( e ); } //��ӣ�β������
    T dequeue() { return this->remove( this->first() ); } //���ӣ��ײ�ɾ��
    T& front() { return this->first()->data; } //����
 };
