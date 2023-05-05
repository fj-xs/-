#include <cstdlib>
#include <cstdio>
#include<iostream>
#include"../../bintree/bintree.h"
#include"../../bintree/Hashtable.h"
#include "../../List/List.h"
#include "../../binmap/binmap.h"
using namespace std;
#define  N_CHAR  (0x80 - 0x20) //���Կɴ�ӡ�ַ�Ϊ��
struct HuffChar{
	char ch; int weight;
	HuffChar(char c = '^', int w = 0) : ch(c), weight( w ){};
	bool operator < (HuffChar const& hc) {return weight > hc.weight;
	}
	bool operator > (HuffChar const& hc) {return weight < hc.weight;
	}
	bool operator <= (HuffChar const& hc) {return weight >= hc.weight;
	}
	bool operator >= (HuffChar const& hc) {return weight <= hc.weight;
	}
	bool operator == ( HuffChar const& hc){return weight == hc.weight;
	}
	bool operator != ( HuffChar const& hc){return weight != hc.weight;
	}
};
#define HuffTree  BinTree<HuffChar>
#include "../../List/List.h" 
typedef  List<HuffTree*> HuffForest;
 #include "../../binmap/binmap.h" //����Bitmapʵ��
typedef  Bitmap HuffCode;
typedef Hashtable<char, char*> HuffTable;
 int* statistics ( char* sample_text_file ) { //ͳ���ַ�����Ƶ��
    int* freq = new int[N_CHAR];  //����ͳ����������ʣ����������¼���ַ����ִ���
    memset ( freq, 0, sizeof ( int ) * N_CHAR ); //����
    FILE* fp = fopen ( sample_text_file, "r" ); //assert: �ļ������ҿ���ȷ��
    for ( char ch; 0 < fscanf ( fp, "%c", &ch ); ) //���ɨ�������ļ��е�ÿ���ַ�
       if ( ch >= 0x20 ) freq[ch - 0x20]++; //�ۼƶ�Ӧ�ĳ��ִ���
    fclose ( fp ); return freq;
 }
 HuffForest* initForest ( int* freq ) { //����Ƶ��ͳ�Ʊ�Ϊÿ���ַ�����һ����
    HuffForest* forest = new HuffForest; //��Listʵ�ֵ�Huffmanɭ��
    for ( int i = 0; i < N_CHAR; i++ ) { //Ϊÿ���ַ�
       forest->insertAsLast ( new HuffTree ); //����һ�����������ַ�����Ƶ��
       forest->last()->data->insertAsRoot ( HuffChar ( 0x20 + i, freq[i] ) ); //��������
    }
    return forest;
 }
HuffTree* minHChar(HuffForest* forest)//��Huffmanɭ�����ҳ�Ȩ����С��Huffman�ַ�
{ 
    ListNodePosi(HuffTree*) m = forest->first(); //���׽ڵ�������������нڵ�
    for (ListNodePosi(HuffTree*) p = m->succ; forest->valid(p); p = p->succ)
    {
        if (m->data->root()->data.weight > p->data->root()->data.weight) //���ϸ���
        {
            m = p; //�ҵ���С�ڵ㣨����Ӧ��Huffman������
        }
    }
    return forest->remove(m); //��ɭ����ȡ����������������
}
HuffTree* generateTree(HuffForest* forest) //Huffman�����㷨
{
    while (1 < forest->size())
    {
        HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
        HuffTree* S = new HuffTree();
        S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    } 
    return forest->first()->data;
    
}
    static void generateCT ( Bitmap* code, int length, HuffTable* table, BinNodePosi (HuffChar) v ) {//ͨ��������ȡ���ַ��ı���
    if ( IsLeaf ( *v ) ) //����Ҷ�ڵ㣨���ж��ַ��������жϣ�
       {  table->put ( v->data.ch, code->bits2string ( length ) ); return;  }
    if ( HasLChild ( *v ) ) //Left = 0
       { code->clear ( length ); generateCT ( code, length + 1, table, v->lc ); }
    if ( HasRChild ( *v ) ) //Right = 1
       { code->set ( length ); generateCT ( code, length + 1, table, v->rc ); }
 }
 
 HuffTable* generateTable ( HuffTree* tree ) { //�����ַ�����ͳһ������ɢ�б�ʵ�ֵı������
    HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
    generateCT ( code, 0, table, tree->root() ); releases ( code ); return table;
 }; //release()
    int encode(HuffTable* table, Bitmap* codeString, char* s) {
	int n = 0; //�����صı��봮�ܳ�n
	for (size_t m = strlen(s), i = 0; i < m; i++) { //���������е�ÿ���ַ�
		char** pCharCode = table->get(s[i]); //ȡ�����Ӧ�ı��봮
		if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a'); //Сд��ĸתΪ��д
		if (!pCharCode) pCharCode = table->get(' '); //�޷�ʶ����ַ�ͳһ�����ո�
		std::cout << *pCharCode;//printf("%s", *pCharCode); //�����ǰ�ַ��ı���
		for (size_t m = strlen(*pCharCode), j = 0; j < m; j++) //����ǰ�ַ��ı��������봮
			'1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
	}
	printf("\n"); return n;
} //�����Ʊ��봮��¼��λͼcodeString��
// ���ݱ������Գ�Ϊn��Bitmap����Huffman����
void decode(HuffTree* tree, Bitmap* code, int n) {
	BinNodePosi(HuffChar) x = tree->root();
	for (int i = 0; i < n; i++) {
		x = code->test(i) ? x->rc : x->lc;
		if (IsLeaf(*x)) { 
			std::cout << x->data.ch << " ";
			//printf("%c", x->data.ch); 
			x = tree->root();
		}
	}
	if (x != tree->root()) std::cout << "...";//printf("...");
	std::cout << std::endl;// printf("\n");
} //��������룬�ڴ�ֱ�Ӵ�ӡ�����ʵ���пɸ�Ϊ������Ҫ�����ϲ������
int main ( int argc, char* argv[] ) { //Huffman�����㷨ͳһ����
    char text[] = "dream";
	char* ch = text;
	char text2[] = "freedom";
	char* ch2 = text2;
    char s[] = "1.txt";
    char t[] = "2.txt";
    int* freq = statistics(t); //���������ļ���ͳ�Ƹ��ַ��ĳ���Ƶ��
    HuffForest* forest = initForest(freq); //����Huffmanɭ��
    releases(freq); 
    HuffTree* tree = generateTree(forest);  //����Huffman������
    releases(forest);
    HuffTable* table = generateTable(tree); //��Huffman������ת��Ϊ�����
    for (int i =N_CHAR-63 ; i < N_CHAR-5; i++) //��������
        printf(" %c: %s\n", i + 0x20, *(table->
		get(i + 0x20)));
    for (int i = 2; i < 3; i++) { //���������д����ÿһ���Ĵ�
        printf("\n���� : %s\n", ch); //���²��Ա���
        Bitmap* codeString = new Bitmap; //�����Ʊ��봮
        int n = encode(table, codeString, text); //�����ݱ�������ɣ�����Ϊn��
        //printf("%s\n", codeString->bits2string(n)); //����ñ��봮
        printf("����: "); //���²��Խ���
        decode(tree, codeString, n); //����Huffman���������Գ���Ϊn�Ķ����Ʊ��봮����
        releases(codeString);
    }
    printf(" \n����: %s\n", ch2); //���²��Ա���
    Bitmap* codeString = new Bitmap; //�����Ʊ��봮
    int n = encode(table, codeString, text2); //�����ݱ�������ɣ�����Ϊn��
    //printf("%s\n", codeString->bits2string(n)); //����ñ��봮
    printf("����: "); //���²��Խ���
    decode(tree, codeString, n); //����Huffman���������Գ���Ϊn�Ķ����Ʊ��봮����
    releases(codeString);
    system("pause");
    releases(table); releases(tree);
    return 0; //�ͷű����������
 } 
 
