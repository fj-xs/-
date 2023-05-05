#include "..\Queue\Queue.h" //引入队列
#include "..\Stack\Stack.h" //引入栈
 #include<iostream>
#include <stdlib.h>
#ifndef BINNODE
#define BINNODE
 #define BinNodePosi(T) BinNode<T>*
 #define stature( p ) ( ( p ) ? ( p )->height : -1 )
 typedef enum { RB_RED, RB_BLACK} RBColor; //节点颜色
 
// template <typename T> struct BinNode;
// template <typename T> using BinNodePosi = BinNode<T>*; //节点位置

 template <typename T> struct BinNode { //二叉树节点模板类
 // 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
    T data; //数值
    BinNodePosi(T) parent;BinNodePosi(T) lc;BinNodePosi(T) rc; //父节点及左、右孩子
    Rank height; //高度（通用）
    Rank npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）
 // 构造函数
    BinNode() : parent( NULL ), lc( NULL ), rc( NULL ), height( 0 ), npl( 1 ), color( RB_RED ) {}
    BinNode( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL,
             BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED )
       : data( e ), parent( p ), lc( lc ), rc( rc ), height( h ), npl( l ), color( c ) {}
 // 操作接口
    Rank size(); //统计当前节点后代总数，亦即以其为根的子树的规模
    BinNodePosi(T) insertAsLc (T const&); //作为左子树插入
	BinNodePosi(T) insertAsRc (T const&); //作为右子树插入
    BinNodePosi(T) succ(); //取当前节点的直接后继
    template <typename VST> void travLevel( VST& ); //子树层次遍历
    template <typename VST> void travPre( VST& ); //子树先序遍历
    template <typename VST> void travIn( VST& ); //子树中序遍历
    template <typename VST> void travPost( VST& ); //子树后序遍历
 // 比较器、判等器（各列其一，其余自行补充）
    bool operator < (BinNode const& bn){return data < bn.data;}
	bool operator > (BinNode const& bn){return data > bn.data;}
	bool operator <= (BinNode const& bn){return data <= bn.data;}
	bool operator >= (BinNode const& bn){return data >= bn.data;}
	bool operator == (BinNode const& bn){return data == bn.data;}
    bool operator!=(const BinNode& bn) {return data != bn.data; }
 };
 
 template <typename T> 
BinNodePosi(T) BinNode<T>::insertAsLc( T const& e)
{
	return lc = new BinNode( e, this);//left child
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(T const& e)
{//right child
	return rc = new BinNode(e, this);
}

 template <typename T> template <typename VST>//元素类型操作器
 void BinNode<T>::travIn(VST& visit){//二叉树中序遍历统一入口
    //switch( rand() % 5)
	switch(4){
    case 1:travIn_I1(this,visit);break;
    case 2:travIn_I2(this,visit);break;
    case 3:travIn_I3(this,visit);break;
    case 4:travIn_I4(this,visit);break;
    default:travIn_R(this,visit);break;
    }
 }
template <typename T>
int BinNode<T>::size(){
	int s = 1;//计入本身
	if (lc) s += lc->size();
	if (rc) s += rc->size();
	return s;
}


#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))	//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))	//同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)	//兄弟
#define uncle(x) sibling((x)->parent)	//叔叔
#define FromParentTo(x) /*来自父亲的引用*/\
	(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))
 
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))	//外部节点也视作黑节点
#define IsRed(p) (!IsBlack(p))	//非黑即红
#define BlackHeightUpdated(x) (/*RedBlack高度更新条件*/ \
	(stature((x).lc)==stature((x).rc)) && \
	((x).height == (IsRed(&x)?stature((x).lc):stature((x).lc)+1)) \
)

 #endif
