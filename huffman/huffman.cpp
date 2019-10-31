
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
 
/*��������*/
struct TreeNode{
	int value;
	int alpha;
	string code;
	TreeNode * lChild;
	TreeNode * rChild;
	TreeNode(){	value = 0;	alpha = 0;	lChild = rChild = NULL;	code="";} //���캯��
};
 
/*�����㣬��������Huffman��*/
struct ListNode{
	TreeNode huffNode;
	ListNode * child;
	ListNode(){	child = NULL;} //���캯��		
};
 
//���������ļ���ͳ����Ϣ��hash��
struct hashTable{
	int value;
	int alpha;
	hashTable(){alpha=0; value=0;}
}Ascii[CharCount];
 
 
//qsort��������
int Comp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}
 
TreeNode * CreateHuffmanTree(hashTable ascii[])
{
	/*��ʼ������������ɭ�֣�ÿ����ֻ��һ�����,������Щɭ�ִ���һ��������*/
	ListNode * root = new ListNode;
	ListNode * next = root; 	//rootָ���һ���ڵ㣬�˽ڵ�����Ϣ
	
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
	
	//���ɭ���е���>1���ͼ�������ֱ��ɭ�֣�������ֻ��һ��������ʱHuffman��Ҳ�ѽ���
	while(root->child != NULL)
	{
		ListNode * p = new ListNode;
		/*���½���Ȩֵ��Ϊ��С��������Ȩֵ֮��*/
		p->huffNode.value = root->huffNode.value + root->child->huffNode.value;
 
		/*���½���е�Huffman�ڵ��е�������������Ϊ������С�ڵ��е�Huffman�ڵ�*/
		p->huffNode.lChild =  &(root->huffNode);
		p->huffNode.rChild = &(root->child->huffNode);
		
		/*��������ɾ����С��������㣬�����ڴ治���ͷţ���Ϊ��Ҫ����Щ�ڵ㹹��Huffman��*/
		root = root->child->child;
		 
		/*���½�����������뵽���ʵ�λ�ã���֤���������*/
		next = root;
		ListNode * parent = NULL;
		while( next != NULL  && p->huffNode.value >= next->huffNode.value )//�½�����next
		{
			parent = next;
			next = next->child;
		}
		if(parent == NULL) // С��next���뿪ͷ
		{
			p->child = next;
			root = p;
		}
		else // ������뵽�м�
		{
			p->child = next;
			parent->child = p;
		}
	}
	return &(root->huffNode);
}
 
/*�ַ�-Huffman���*/
string charHuffmanTable[CharCount];
 
/*�ַ���ջ�������ڱ���Huffman��ʱ�õ�Huffman����*/
string stack;
 
/*����ǰ�����  �ݹ����*/
void preord(TreeNode * root)
{
		if(root->lChild == NULL && root->rChild == NULL)
		{
			charHuffmanTable[root->alpha] = stack;
			stack.erase(stack.length()-1);
			return;	
		}
		stack.append("0");
		preord(root->lChild);     //����Ϊ0
		
		stack.append("1");
		preord(root->rChild);     //�Һ���Ϊ1

		if(!stack.empty())
			stack.erase(stack.length()-1);
} 
 
//������һ��"10101001"���ַ���������һ����Ӧ��ASCII�ַ�
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
 
//��unsigned char����ת��Ϊ2�����ַ���
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
 
/*����,����������ַ���ɾ��string���Ѿ��ù��Ĵ�  */
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
	int m=rand()%1000+1;//����1-1000�������
    char soufile[1001],wrifile[2000];
	FILE* pfr = fopen("dna.txt", "r");
	if (NULL == pfr)
	{
		perror("open file dna.txt");
	}

/*���ϵĴ�Դ�ļ��ж�ȡ�ַ���д��Ŀ���ļ���*/
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
//�ر���
	fclose(pfr);
	fclose(pfw);
	pfr = NULL;
	pfw = NULL;
}*/
 
int main(void)  //������
{
//	writetxt();
	/*��ȡ�ļ���ͳ���ַ�*/
	FILE * fin = fopen("source.txt", "r");
	int z;
	while( (z=fgetc(fin)) != EOF )
	{
		Ascii[z].alpha = z;
		Ascii[z].value++;
	}
	puts("");
	
	qsort(Ascii, sizeof(Ascii)/sizeof(Ascii[0]), sizeof(Ascii[0]), Comp);
	
	/*����Huffman��*/
	TreeNode * HuffmanRoot = CreateHuffmanTree(Ascii);
	
	/*�����ַ�-Huffman���,����浽charHuffmanTable[]*/
	preord(HuffmanRoot);
 
	//��ӡ��ͳ����Ϣ
	cout << "Char\tTimes\tCode\n";
	for(int i=0; i<CharCount; i++)
	{
		if(Ascii[i].value != 0)
		{
			cout << (char)Ascii[i].alpha << "\t" << Ascii[i].value << "\t" << charHuffmanTable[Ascii[i].alpha] << endl;
		}
	}
	
	/*���벢������ļ���*/
	FILE * fout = fopen("code.dat","w");
	rewind(fin);	//�����ļ�ָ��
	
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
 
	int appendZero = 0;		//����0������
	if(!buf.empty())
	{
		appendZero = 8 - buf.length();
		buf.append(appendZero, '0');
		fputc(StrToBin(buf.substr(0, 8)), fout);
		buf.erase(0, 8);
	}
 
	fclose(fin);
	fclose(fout);
	
	/*���벢������ļ���*/
	fin = fopen("code.dat", "rb");
	fout = fopen("target.txt", "w");
	int uc;
	while( (uc=fgetc(fin)) != EOF ) 
	{		
		buf += BinToStr(uc);
	}
	
	while(buf.length()-appendZero != 0 && !buf.empty())
	{
		//����Huffman��������
		fputc(decode(HuffmanRoot, buf),fout);
	}
	fclose(fin);
	fclose(fout);
	//printf("Time used: %d ms", clock());
    /*��֤���ļ��Ƿ�һ��*/
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
   
   
