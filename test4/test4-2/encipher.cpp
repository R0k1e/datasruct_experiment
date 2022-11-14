#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Node{
	int weight,parent,lc,rc;
	char *code;
}Node;//�����ڵ�Ľṹ 

typedef struct Htree_head{
	char flag[5];
	char last;
	char unused[10];
}Fhead; //Ԫ���ݽṹ 

void initHtree(Node *ht)//���ĳ�ʼ�� 
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
int createHtree(Node *ht,int *Num)//������������ 
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
	/*�������ĸ���㣬���չ���������*/
	int i,j,k,m;
	for(i=256;i<511;i++)
	{
		j=-1,k=-1;
		for(int l=0;l<i;l++)//Ѱ��Ȩ��С��������㣬j����Ȩ������k���Ȩ 
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
		if(k==-1)//ֻʣ��һ��û��˫�׵Ľڵ㣬�ֽи� 
		break;
		ht[j].parent=i;
		ht[k].parent=i;
		ht[i].weight=ht[j].weight+ht[k].weight;
		ht[i].lc=j;
		ht[i].rc=k;
	}
	return j;
}
void getHCode(Node *ht,int root,int index,char *code)//���ɹ��������� 
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

//ȡ���һ���ֽڵ���Чλ��
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
	initHtree(ht);//���ĳ�ʼ�� 
	root=createHtree(ht,Num);//�����������ظ� 
	char Code[256]={};//���ٿռ����ڱ������������ 
	getHCode(ht,root,0,Code);//���ɹ��������� 
	
	FILE *fpIn=fopen("in.txt","rb");
	FILE *fpOut=fopen("lock.txt","wb");
	
	Fhead filehead;
	strcpy(filehead.flag,"bupt");//��ʶ�����ж��Ƿ�Ϊ�ó������ɵļ����ļ� 
	filehead.last=getlastValidBit(ht);//�ļ����һ���ֽڵ���Ч���� 
	
	fwrite(&filehead,sizeof(Fhead),1,fpOut);//����Ԫ���� 
	fwrite(Num,sizeof(int),256,fpOut);//����ԭ�ļ����ַ�Ƶ�� 
	
	/*��λ���й���������*/
	int index=0;
	unsigned char word,value=0;
	char *code;
	word=fgetc(fpIn);
	while(!feof(fpIn)){
		code=ht[word].code;
		for(int i=0;code[i];i++){
			if(code[i]=='0'){
				value &= (~(1 << ((index) ^ 7))); //value��indexλ��0 
			}else{
				value |= (1 << ((index) ^ 7)); //value��indexλ��1 
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
