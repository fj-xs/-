# homework
用于提交数据结构作业
文件结构：
   
   zys  
         vector
                  vector.h
         complex
                  complex.h
         homework1
                  homework.cpp
         .......
        
作业一：
定义了向量模板：
大致为以下代码：
   Rank _size; int _capacity, clock;  T* _elem; //规模、容量、数据区
   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand(); //空间不足时扩容
   void shrink(); //装填因子过小时缩容 
   Rank partition ( Rank lo, Rank hi );
   void quickSort ( Rank lo, Rank hi );
   void heapSort ( Rank lo, Rank hi );
   // 构造函数
   void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
   void mergeSort ( Rank lo, Rank hi ); //归并排序算法 
   bool bubble ( Rank lo, Rank hi ); //扫描交换
   bool bubble ( Rank n, Rank lo, Rank hi);
   void bubbleSort ( Rank n, Rank lo, Rank hi);
   void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
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
   void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
   void unsort()
    { unsort ( 0, _size ); } //整体置乱
   int deduplicate(); //无序去重
   int uniquify(); //有序去重
   int check(Rank lo, Rank hi, double m1, double m2);
   // 遍历
   void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
   template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
定义了复数类： 
    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend Complex operator-(const Complex &c1, const Complex &c2);
    friend Complex operator*(const Complex &c1, const Complex &c2);
    friend Complex operator/(const Complex &c1, const Complex &c2);
    friend bool operator> (const Complex &c1, const Complex &c2);
    friend bool operator< (const Complex &c1, const Complex &c2);
    friend bool operator==(const Complex &c1, const Complex &c2);
    friend bool operator!=(const Complex &c1, const Complex &c2);
    Complex & operator+=(const Complex &c);
    Complex & operator-=(const Complex &c);
    Complex & operator*=(const Complex &c);
    Complex & operator/=(const Complex &c);
    void display ();
    double read_Real (double r);
    double read_Imaginary (double i);
    double read_modulus();
    double real() const{ return m_real; }
    double imag() const{ return m_imag; }
    double modulus() const{ return m_modulus; } 
    double m_real;  
    double m_imag;  
    double m_modulus;  
 实现了基于以上两者的代码：
    （1）在主函数中测试无序向量的置乱、查找（实部和虚部均相同）、插入、删除和唯一化的操作
    （2）以复数的模为基准进行排序（模相同的情况下，以实部为基准），比较顺序、乱序、逆序的情况下，起泡排序和归并排序的效率（clock()函数记时）
    （3）在顺序的复数向量中，实现区间查找算法，查找出模介于[m1,m2) 的所有元素，按序存于一个子向量中作为返回值。
