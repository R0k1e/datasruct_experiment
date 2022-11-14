#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Node{
	int weight,parent,lc,rc;
	char *code;
}Node;//树各节点的结构 

typedef struct Htree_head{
	char flag[5];
	char last;
	char unused[10];
}Fhead; //元数据结构 

void initHtree(Node *ht)//树的初始化 
{
	for(int i=0;i<512;i++)
	{
		ht[i].weight=0;
		ht[i].lc=-1;
		ht[i].rc=-1;
		ht[i].parent=-1;
		ht[i].code = (char *) calloc(sizeof(char),256);
	}
	
}
int createHtree(Node *ht,int *Num)//创建哈夫曼树 
{
	unsigned char word;
	FILE *fp=fopen("in.txt","rb");
	word=fgetc(fp);
	while(!feof(fp))
	{
		ht[word].weight++;
		Num[word]++;
		word=fgetc(fp);
	}
	fclose(fp);
	/*串联树的各结点，按照哈夫曼编码*/
	int i,j,k,m;
	for(i=256;i<511;i++)
	{
		j=-1,k=-1;
		for(int l=0;l<i;l++)//寻找权最小的两个结点，j结点的权不大于k结点权 
		{
			if(ht[l].parent==-1&&ht[l].weight!=0){
				if(j==-1){
					j=l;
				}
				else if(k==-1){
					k=l;
					if(ht[j].weight>ht[k].weight){
						m=j;
						j=k;
						k=m;
					}
				}
				else if(ht[l].weight<ht[j].weight){
					k=j;
					j=l;
				}
				else if(ht[l].weight<ht[k].weight)
				k=l;
			}
		}
		if(k==-1)//只剩下一个没有双亲的节点，又叫根 
		break;
		ht[j].parent=i;
		ht[k].parent=i;
		ht[i].weight=ht[j].weight+ht[k].weight;
		ht[i].lc=j;
		ht[i].rc=k;
	}
	return j;
}
void getHCode(Node *ht,int root,int index,char *code)//生成哈夫曼编码 
{
	char Code[256];
	strcpy(Code,code);
	if(ht[root].lc!=-1&&ht[root].rc!=-1)
	{
		code[index]='0';
		getHCode(ht,ht[root].lc,index+1,code);
		strcpy(code,Code);
		
		code[index]='1';
		getHCode(ht,ht[root].rc,index+1,code);
		strcpy(code,Code);
	}
	else{
		strcpy(ht[root].code,code);
	}
}

//取最后一个字节的有效位数
int getlastValidBit(Node *ht) {
	int sum = 0;
	int i;
	
	for(i = 0; i < 256; i++) {
		sum += strlen(ht[i].code) * ht[i].weight;
		sum &= 0xFF;
	}
	sum &= 0x7;
		
	return sum == 0 ? 8 : sum;
}

int main()
{
	Node ht[511];
	int root=-1;
	int Num[256]={};
	initHtree(ht);//树的初始化 
	root=createHtree(ht,Num);//创建树并返回根 
	char Code[256]={};//开辟空间用于保存哈夫曼编码 
	getHCode(ht,root,0,Code);//生成哈夫曼编码 
	
	FILE *fpIn=fopen("in.txt","rb");
	FILE *fpOut=fopen("lock.txt","wb");
	
	Fhead filehead;
	strcpy(filehead.flag,"bupt");//标识符，判断是否为该程序生成的加密文件 
	filehead.last=getlastValidBit(ht);//文件最后一个字节的有效长度 
	
	fwrite(&filehead,sizeof(Fhead),1,fpOut);//输入元数据 
	fwrite(Num,sizeof(int),256,fpOut);//输入原文件各字符频度 
	
	/*按位进行哈夫曼编码*/
	int index=0;
	unsigned char word,value=0;
	char *code;
	word=fgetc(fpIn);
	while(!feof(fpIn)){
		code=ht[word].code;
		for(int i=0;code[i];i++){
			if(code[i]=='0'){
				value &= (~(1 << ((index) ^ 7))); //value的index位赋0 
			}else{
				value |= (1 << ((index) ^ 7)); //value的index位赋1 
			}
			index++;
			if(index>=8)
			{
				index=0;
				fwrite(&value,sizeof(char),1,fpOut);
			}
		}
		word=fgetc(fpIn);
	}
	if(index)
	fwrite(&value,sizeof(char),1,fpOut);
	
	fclose(fpIn);
	fclose(fpOut);
	
	return 0;
}
