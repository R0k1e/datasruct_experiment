#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//输入文件名为lock.txt
//输出文件名为out.txt 
typedef struct Node{
	int weight,parent,lc,rc;
	char *code;
}Node;

typedef struct Htree_head{
	char flag[5];
	char last;
	char unused[10];
}Fhead;

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
int createHtree(Node *ht,int *Num)//生成哈夫曼树 
{
	for(int i=0;i<256;i++){
		ht[i].weight=Num[i];
	} //由Num数组传回的字符频度赋给树的各元素weight 
	
	int i,j,k,m;
	for(i=256;i<511;i++)//串起树的各元素 
	{
		j=-1,k=-1;
		for(int l=0;l<i;l++)
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
		if(k==-1)//只剩下一个元素没有双亲，它不是根谁是 
		break;
		/*给i和j找双亲*/
		ht[j].parent=i;
		ht[k].parent=i;
		ht[i].weight=ht[j].weight+ht[k].weight;
		ht[i].lc=j;
		ht[i].rc=k;
	}
	if(k!=-1)
	return i;
	else 
	return j;//返回根节点 
}
void getHCode(Node *ht,int root,int index,char *code)//生成哈夫曼码 
{
	char Code[256];//用于调用函数后恢复code 
	strcpy(Code,code);
	if(ht[root].lc!=-1&&ht[root].rc!=-1)
	{
		code[index]='0';
		getHCode(ht,ht[root].lc,index+1,code);
		strcpy(code,Code);//code返回调用前 
		
		code[index]='1';
		getHCode(ht,ht[root].rc,index+1,code);
		strcpy(code,Code);//同上 
	}
	else{
		strcpy(ht[root].code,code);//将哈夫曼码传给树 
	}
}

void Hdecoding(Node *ht,int root,char last)//解码函数 
{
	FILE *fpIn=fopen("lock.txt","rb");
	FILE *fpOut=fopen("out.txt","wb");
	fseek(fpIn,0L,SEEK_END);//跳到文件尾 
	long fileSize = ftell(fpIn);//文件总长度 
	fseek(fpIn,16+sizeof(int)*256,SEEK_SET);//跳过元数据 
	long curLocation = ftell(fpIn);//记下当前位置 
	
	unsigned char value,valueOut;
	int index=0,i=root,j;
	fread(&value,sizeof(unsigned char),1,fpIn);
	
	bool finished=false;
	while(!finished)
	{
		if(ht[i].lc==-1&&ht[i].rc==-1){
			valueOut=i;
			fwrite(&valueOut,sizeof(unsigned char),1,fpOut);
			i=root;
			if(curLocation>=fileSize&&index>=last)
			break;
		}
		
		j=(value & (1 << ((index) ^ 7)));
		if(j==0)
		i=ht[i].lc;
		else
		i=ht[i].rc;
		
		if(++index>=8){
			index=0;
			if(curLocation>=fileSize){
				break;//强制退出：避免因bug而出现死循环 （你可别往后读了啊！） 
			}
			fread(&value,sizeof(unsigned char),1,fpIn);
			curLocation=ftell(fpIn);
		}
	}
	printf("Coding success!\n");//解码成功，奖励自己 
	fclose(fpIn);
	fclose(fpOut);
}

int main()
{
	FILE *fpIn=fopen("lock.txt","rb");//打开加密文件 
	/*识别元数据*/ 
	Fhead head;
	int Num[256];
	fread(&head,sizeof(Fhead),1,fpIn);//读取元数据 
	if(head.flag[0]!='b'||head.flag[1]!='u'||head.flag[2]!='p'||head.flag[3]!='t')//根据元数据判断是否为本程序可解码的加密文件 
	{
		printf("Error:It is not file which I can understand.\n");//这个加密文件不是我所能解的，量力而行 
		return 0;
	}
	fread(Num,sizeof(int),256,fpIn);//读取加密文件中各字符频度，用于生成哈夫曼树和哈夫曼编码 
	fclose(fpIn);//有打开当然有关闭 
	/*哈夫曼树、哈夫曼码的初始化*/
	Node ht[511];
	int root,last=head.last;//此处为bug出现后的修补，数初始化后head数据会出错（数据溢出？） 
	initHtree(ht);//树的初始化 
	root=createHtree(ht,Num);//生成哈夫曼树并返回根节点 
	char code[256];//为每个字符开辟哈夫曼码的存储空间 
	getHCode(ht,root,0,code);//生成哈夫曼码并传入Node
	
	Hdecoding(ht,root,last);//解码加密文件 
	
	return 0;
}
