
/* Huffman Code */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <bitset>
#include <fstream>
#include <time.h> 
#define CharCount 256 
using namespace std;
 
/*哈夫曼树*/
struct TreeNode{
	int value;
	int alpha;
	string code;
	TreeNode * lChild;
	TreeNode * rChild;
	TreeNode(){	value = 0;	alpha = 0;	lChild = rChild = NULL;	code="";} //构造函数
};
 
/*链表结点，辅助构造Huffman树*/
struct ListNode{
	TreeNode huffNode;
	ListNode * child;
	ListNode(){	child = NULL;} //构造函数		
};
 
//保存输入文件的统计信息，hash表
struct hashTable{
	int value;
	int alpha;
	hashTable(){alpha=0; value=0;}
}Ascii[CharCount];
 
 
//qsort的排序函数
int Comp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}
 
TreeNode * CreateHuffmanTree(hashTable ascii[])
{
	/*初始化建立二叉树森林，每个树只有一个结点,并把这些森林串到一个链表中*/
	ListNode * root = new ListNode;
	ListNode * next = root; 	//root指向第一个节点，此节点有信息
	
	for(int i=0; ; i++)
	{
		if(ascii[i].value == 0)
			continue;
			
		next->huffNode.value = ascii[i].value;
		next->huffNode.alpha = ascii[i].alpha;
 
		if(i == CharCount-1) 
			break;
		
		next->child = new ListNode;
		next = next->child;
	}
	
	//如果森林中的树>1，就继续处理，直到森林（链表）中只有一颗树，这时Huffman树也已建成
	while(root->child != NULL)
	{
		ListNode * p = new ListNode;
		/*把新结点的权值设为最小两个结点的权值之和*/
		p->huffNode.value = root->huffNode.value + root->child->huffNode.value;
 
		/*把新结点中的Huffman节点中的左右子树设置为两个较小节点中的Huffman节点*/
		p->huffNode.lChild =  &(root->huffNode);
		p->huffNode.rChild = &(root->child->huffNode);
		
		/*从链表中删除最小的两个结点，但是内存不能释放，因为还要用这些节点构造Huffman树*/
		root = root->child->child;
		 
		/*把新建的这个结点插入到合适的位置，保证链表的升序*/
		next = root;
		ListNode * parent = NULL;
		while( next != NULL  && p->huffNode.value >= next->huffNode.value )//新结点大于next
		{
			parent = next;
			next = next->child;
		}
		if(parent == NULL) // 小于next插入开头
		{
			p->child = next;
			root = p;
		}
		else // 否则插入到中间
		{
			p->child = next;
			parent->child = p;
		}
	}
	return &(root->huffNode);
}
 
/*字符-Huffman码表*/
string charHuffmanTable[CharCount];
 
/*字符串栈，用来在遍历Huffman树时得到Huffman编码*/
string stack;
 
/*树的前序遍历  递归调用*/
void preord(TreeNode * root)
{
		if(root->lChild == NULL && root->rChild == NULL)
		{
			charHuffmanTable[root->alpha] = stack;
			stack.erase(stack.length()-1);
			return;	
		}
		stack.append("0");
		preord(root->lChild);     //左孩子为0
		
		stack.append("1");
		preord(root->rChild);     //右孩子为1

		if(!stack.empty())
			stack.erase(stack.length()-1);
} 
 
//传进来一个"10101001"的字符串，返回一个对应的ASCII字符
unsigned char StrToBin(string str)
{
	int a = atoi(str.c_str());
	int b = 1;
	int ans = 0;
	while(a != 0)
	{
		ans += a%10 * b;
		b *= 2;
		a /= 10;
	}
	return (unsigned char)ans;
}
 
//把unsigned char类型转换为2进制字符串
string BinToStr(unsigned char c)
{	
	string ans;
	while(c != 0)
	{
		ans.insert(ans.begin(), unsigned char(c%2 + '0'));
		c /= 2;
	}
	
	if(ans.length() < 8)
	{
		ans.insert(ans.begin(), 8-ans.length(), '0');
	}
	return ans;
}
 
/*译码,返回译出的字符，删除string中已经用过的串  */
char decode(TreeNode * root, string & code)
{
	for(int i=0; i<code.length(); i++)
	{
		if(root->alpha == 0)
			root = (code[i]-'0') ? root->rChild : root->lChild;
		else
		{
			code.erase(0,i);
			return root->alpha;
		}
	}
 
	if(root->alpha != 0)
	{
		code.erase(0,i);
		return root->alpha;
	}
	code.erase();
	return '\0';
}
/*void writetxt()
{ printf("777");
	int m=rand()%1000+1;//生成1-1000的随机数
    char soufile[1001],wrifile[2000];
	FILE* pfr = fopen("dna.txt", "r");
	if (NULL == pfr)
	{
		perror("open file dna.txt");
	}

/*不断的从源文件中读取字符并写入目的文件中*/
/*	while(!feof(pfr))
	{
		fgets(soufile+m,1001,pfr);
		printf("666\n");
		printf("%s",soufile+m);
		for(int k=0;k<1001;k++){
		wrifile[k]=soufile[k+m];	
		}
		printf("\n888\n");
	}
	printf("%s^^^",wrifile);
	FILE* pfw = fopen("source.txt", "w");
	fputs(wrifile,pfw);
	fputc('\n',pfw);
//关闭流
	fclose(pfr);
	fclose(pfw);
	pfr = NULL;
	pfw = NULL;
}*/
 
int main(void)  //主函数
{
//	writetxt();
	/*读取文件并统计字符*/
	FILE * fin = fopen("source.txt", "r");
	int z;
	while( (z=fgetc(fin)) != EOF )
	{
		Ascii[z].alpha = z;
		Ascii[z].value++;
	}
	puts("");
	
	qsort(Ascii, sizeof(Ascii)/sizeof(Ascii[0]), sizeof(Ascii[0]), Comp);
	
	/*构造Huffman树*/
	TreeNode * HuffmanRoot = CreateHuffmanTree(Ascii);
	
	/*建立字符-Huffman码表,结果存到charHuffmanTable[]*/
	preord(HuffmanRoot);
 
	//打印出统计信息
	cout << "Char\tTimes\tCode\n";
	for(int i=0; i<CharCount; i++)
	{
		if(Ascii[i].value != 0)
		{
			cout << (char)Ascii[i].alpha << "\t" << Ascii[i].value << "\t" << charHuffmanTable[Ascii[i].alpha] << endl;
		}
	}
	
	/*编码并输出到文件中*/
	FILE * fout = fopen("code.dat","w");
	rewind(fin);	//重置文件指针
	
	string buf;
	
	while( (z=fgetc(fin)) != EOF )
	{
		buf += charHuffmanTable[z];
		if(buf.length() >= 8)
		{
			fputc(StrToBin(buf.substr(0, 8)), fout);
			buf.erase(0, 8);
		}
		
	}
 
	int appendZero = 0;		//附加0的数量
	if(!buf.empty())
	{
		appendZero = 8 - buf.length();
		buf.append(appendZero, '0');
		fputc(StrToBin(buf.substr(0, 8)), fout);
		buf.erase(0, 8);
	}
 
	fclose(fin);
	fclose(fout);
	
	/*译码并输出到文件中*/
	fin = fopen("code.dat", "rb");
	fout = fopen("target.txt", "w");
	int uc;
	while( (uc=fgetc(fin)) != EOF ) 
	{		
		buf += BinToStr(uc);
	}
	
	while(buf.length()-appendZero != 0 && !buf.empty())
	{
		//搜索Huffman树并译码
		fputc(decode(HuffmanRoot, buf),fout);
	}
	fclose(fin);
	fclose(fout);
	//printf("Time used: %d ms", clock());
    /*验证两文件是否一致*/
	int q,j=0;
	char a[1001],b[1001];
	FILE *f1 = fopen("source.txt","r");
	for(q=0;!feof(f1);q++){
	   fscanf(f1,"%s",&a[q]);
	}
	fclose(f1);
	FILE *f2 = fopen("target.txt","r");
	for(q=0;!feof(f2);q++){
	   fscanf(f2,"%s",&b[q]);
	}
	fclose(f2);
	for(j;j<q;j++)
		if(a[j]!=b[j]){
		printf("different position is %s",b[j]);
		}
		else
		printf("%s and %s are the same\n","source.txt","target.txt");
		return 0;
}
   
   
