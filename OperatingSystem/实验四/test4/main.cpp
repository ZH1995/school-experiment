#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <locale.h>
#include<string>
#include <cstdio>
#include <cstring>
using namespace std;
//
#define beginsize 5
#define LENGTH 3
typedef struct      // 一次地址
{
	int data[LENGTH];
}Indireone;
typedef struct      //二次间址
{
	Indireone * first[LENGTH];
}Indiretwo;
typedef struct      //三次间址
{
	Indiretwo * second[LENGTH];
}Indirethree;
typedef struct Node
{
	int begin[beginsize];       //直接地址
	Indireone * one;
	Indiretwo * two;
	Indirethree * three;
}Mixtab;            //混合索引节点

typedef struct NODE
{
	char name[50];
	int type;//是文件还是目录,1代表文件，0代表目录
	int size;//如果是文件给出大小
	struct NODE *next;//兄弟结点
	struct NODE * sub;//子节点
	struct NODE * father;//父亲节点
	Mixtab * table;
}FCB;
//文件控制块
FCB * root;
FCB * present;
FCB * finding;
char stringname[300];
int Bitmap[16][16];//位示图
int leftbit=0;      // 空的块数
void Initall()
{
	int i,j;
	srand( time(NULL) );
	for(i=0;i<16;i++)
		for(j=0;j<16;j++)
			Bitmap[i][j]=rand()%2;
	root=(FCB *)malloc(sizeof(FCB));
	strcpy(root->name,"\\");
	root->type=0;
	root->size=0;
	root->next=NULL;
	root->father=root;
	root->sub=NULL;
	for(i=0;i<16;i++)
		for(j=0;j<16;j++)
			if(Bitmap[i][j]==0) leftbit++;
}
//判断分配外存时候是不是足够
int Judgeenough(int n)
{
	if(leftbit>=n)   return 1;
	else return 0;
}
//添加时候用
void Addpoint(FCB * f)
{
	FCB * temp;
	if(present->sub==NULL)
		present->sub=f;
	else
	{
		temp=present->sub;
		while(temp->next!=NULL)     temp=temp->next;
		temp->next=f;
		f->next=NULL;
	}
}
//删除时候用
void Delpoint(FCB *f)
{
	FCB * temp=present->sub;
	if(temp==f)
	{
		present->sub=temp->next;
		delete(f);
	}
	else
	{
		while(temp->next!=f)
			temp=temp->next;
		temp->next=f->next;
		delete(f);
	}
}
//查找是不是已经存在
int Isexist(char ary[],int x)
{
	FCB * temp;
	if(present->sub==NULL)  return 0;
	else
	{
		temp=present->sub;
		while(temp!=NULL)
		{
			if((!strcmp(temp->name,ary))&&(temp->type==x))
			{
				finding=temp;
				return 1;
			}
			temp=temp->next;
		}
		return 0;
	}
}
//创建目录
void Mdlist()
{
	char listname[50];
	cin>>listname;
	FCB * temp;
	if(Isexist(listname,0))
		cout<<"子目录或文件"<<listname<<"已存在。"<<endl;
	else
	{
		temp=(FCB *)malloc(sizeof (FCB));
		temp->father=present;
		strcpy(temp->name,listname);
		temp->next=NULL;
		temp->sub=NULL;
		temp->type=0;
		temp->size=0;
		Addpoint(temp);
	}
}

/*
void outMixNode(Mixtab *p)
{
    cout<<"直接地址："<<endl;
    for(int i=0;i<beginsize;i++)
        if(p->begin[i] != -1)
            cout<<p->begin[i]<<" ";
    cout<<endl;
    if(p->one->data[0] != -1)
    {
        cout<<"一次间址:"<<endl;
        for(int i=0;i<LENGTH;i++)
            if(p->one->data[i] != -1)
                cout<<p->one->data[i]<<" ";
        cout<<endl;
        if(p->two->first[0] != -1)
        {
            cout<<"二次间址："<<endl;
            for(int i=0;i<LENGTH;i++)
                if(p->two->first[i] != -1)
                    cout<<p->two->first[i]<<" ";
            cout<<endl;
            if(p->three->second[0]!=-1)
            {
                cout<<"三次间址："<<endl;
                for(int i=0;i<LENGTH;i++)
                    if(p->three->second[i] != -1)
                    cout<<p->three->second[i]<<" ";
                cout<<endl;
            }
        }

    }
}
*/




//创建文件
void Mkfile()
{//处理二级时候有错误
	char listname[50];
	int length,i,j,k,leg=0;
	cin>>listname;
	FCB * temp;
	if(getchar()=='\n')
		length=0;
	else
		cin>>length;
	if(Isexist(listname,1))
		cout<<"子目录或文件"<<listname<<"已存在。"<<endl;
	else if(Judgeenough(length)==0)
		cout<<"外存剩余空间不足"<<endl;
	else
	{
		temp=(FCB *)malloc(sizeof (FCB));
		temp->father=present;
		strcpy(temp->name,listname);
		temp->next=NULL;
		temp->sub=NULL;
		temp->type=1;
		temp->size=length;
		Addpoint(temp);
		if(length!=0)
		{
			leftbit=leftbit-length;
			Mixtab * m=(Mixtab *)malloc(sizeof (Mixtab));
			for (k=0;k<beginsize;k++)
				m->begin[k]=-1;
			m->one=NULL;
			m->two=NULL;
			m->three=NULL;
			if(length<=beginsize)
			{//直接地址够用时候
 				for(k=0;k<length;k++)
				{
					for(i=0;i<16;i++)
					{
						for(j=0;j<16;j++)
						{
							if(Bitmap[i][j]==0)
							{
								m->begin[k]=i*16+j;
								Bitmap[i][j]=1;
								leg=1;
								break;
							}
						}
						if(leg==1)
						{
							leg=0;
							break;
						}
					}
				}
			}
			else if(length<=(beginsize+LENGTH))
			{//用一级索引的时候
				for(k=0;k<beginsize;k++)
				{//直接的存储上
					for(i=0;i<16;i++)
					{
						for(j=0;j<16;j++)
						{
							if(Bitmap[i][j]==0)
							{
								m->begin[k]=i*16+j;
								Bitmap[i][j]=1;
								leg=1;
								break;
							}
						}
						if(leg==1)
						{
							leg=0;
							break;
						}
					}
				}
				leg=0;
				Indireone * tempone=(Indireone *)malloc(sizeof (Indireone));
				for (k=0;k<LENGTH;k++)
					tempone->data[k]=-1;
				for(k=0;k<(length-beginsize);k++)
				{//一级索引分配
					for(i=0;i<16;i++)
					{
						for(j=0;j<16;j++)
						{
							if(Bitmap[i][j]==0)
							{
								tempone->data[k]=i*16+j;
								Bitmap[i][j]=1;
								leg=1;
								break;
							}
						}
						if(leg==1)
						{
							leg=0;
							break;
						}
					}
				}
				m->one=tempone;
			}
			else if(length<=(beginsize+LENGTH+LENGTH*LENGTH))
			{//当用二级索引时候
				for(k=0;k<beginsize;k++)
				{//直接的存储上
					for(i=0;i<16;i++)
					{
						for(j=0;j<16;j++)
						{
							if(Bitmap[i][j]==0)
							{
								m->begin[k]=i*16+j;
								Bitmap[i][j]=1;
								leg=1;
								break;
							}
						}
						if(leg==1)
						{
							leg=0;
							break;
						}
					}
				}
				leg=0;
				Indireone * tempone=(Indireone *)malloc(sizeof (Indireone));
				for(k=0;k<LENGTH;k++)
				{//一级索引分配
					for(i=0;i<16;i++)
					{
						for(j=0;j<16;j++)
						{
							if(Bitmap[i][j]==0)
							{
								tempone->data[k]=i*16+j;
								Bitmap[i][j]=1;
								leg=1;
								break;
							}
						}
						if(leg==1)
						{
							leg=0;
							break;
						}
					}
				}
				m->one=tempone;
				leg=0;
				Indiretwo * temptwo=(Indiretwo *)malloc(sizeof (Indiretwo));
				int twostep=(length-beginsize-LENGTH)/LENGTH;
				for(k=0;k<LENGTH;k++)
					temptwo->first[k]=NULL;
				if(twostep==0)
				{	//当只有一层时候
					Indireone * tone=(Indireone *)malloc(sizeof (Indireone));
					for (k=0;k<LENGTH;k++)
					{
						tone->data[k]=-1;
					}
					for(k=0;k<(length-beginsize-LENGTH);k++)
					{
						for(i=0;i<16;i++)
						{
							for(j=0;j<16;j++)
							{
								if(Bitmap[i][j]==0)
								{
									tone->data[k]=i*16+j;
									Bitmap[i][j]=1;
									leg=1;
									break;
								}
							}
							if(leg==1)
							{
								leg=0;
								break;
							}
						}
					}
					temptwo->first[twostep]=tone;
				}
				else
				{//当有多层时候
					leg=0;
					for(int n=0;n<twostep;n++)
					{//对整层分配
						Indireone * tone=(Indireone *)malloc(sizeof (Indireone));
						for(k=0;k<LENGTH;k++)
						{
							for(i=0;i<16;i++)
							{
								for(j=0;j<16;j++)
								{
									if(Bitmap[i][j]==0)
									{
										tone->data[k]=i*16+j;
										Bitmap[i][j]=1;
										leg=1;
										break;
									}
								}
								if(leg==1)
								{
									leg=0;
									break;
								}
							}
							temptwo->first[n]=tone;
						}
					}
					leg=0;
					//分配散的
					Indireone * teone=(Indireone *)malloc(sizeof (Indireone));
					for (k=0;k<LENGTH;k++)
					{
						teone->data[k]=-1;
					}
					for(k=0;k<(length-beginsize-LENGTH-twostep*LENGTH);k++)
					{
						for(i=0;i<16;i++)
						{
							for(j=0;j<16;j++)
							{
								if(Bitmap[i][j]==0)
								{
									teone->data[k]=i*16+j;
									Bitmap[i][j]=1;
									leg=1;
									break;
								}
							}
							if(leg==1)
							{
								leg=0;
								break;
							}
						}
					}
					temptwo->first[twostep]=teone;
				}
				m->two=temptwo;
			}//else if(length<=(beginsize+LENGTH+LENGTH*LENGTH))
			temp->table=m;
            //outMixNode(m);
		}//if(length!=0)
		else
		{
			temp->table=NULL;
		}

	}
}
//
void Showtime()
{
	setlocale(LC_TIME,"");
    time_t TIME;
    struct tm *TM;
    char ch1[81];
    time(&TIME);
    TM=gmtime(&TIME);
    strftime(ch1,80,"%x",TM);
    cout<<ch1;
}


void Dir1(FCB * f,int listnum,int filenum,int allsize)  //列出文件
{
	FCB * temp,* temp2;
	if(f->sub!=NULL)
	{
		temp=f->sub;
		Showtime();
		if(temp->type==0)
		{
			cout<<"\t<DIR>\t\t"<<temp->name<<endl;
			listnum++;
		}
		else
		{
			cout<<"\t\t  "<<temp->size<<"\t"<<temp->name<<endl;
			filenum++;
			allsize+=temp->size;
		}
		if(temp->next!=NULL)
		{
			temp2=temp->next;
			while(temp2!=NULL)
			{
				Showtime();
				if(temp2->type==0)
				{
					cout<<"\t<DIR>\t\t"<<temp2->name<<endl;
					listnum++;
				}
				else
				{
					cout<<"\t\t  "<<temp2->size<<"\t"<<temp2->name<<endl;
					filenum++;
					allsize+=temp2->size;
				}
				temp2=temp2->next;
			}
		}
	}
	else
	{
			cout<<"\t  "<<f->size<<"\t"<<f->name<<endl;
			filenum++;
			allsize+=f->size;
	}
	cout<<"\t   "<<filenum<<"个文件\t   "<<allsize<<endl;
	cout<<"\t   "<<listnum<<"个目录\t   "<<leftbit<<"可用"<<endl;
}
//
void Dirall()
{
	int listnum=2;
	int filenum=0;
	int allsize=0;
	int i;
	char filename[50];
	Showtime();
	cout<<"\t<DIR>"<<"\t\t."<<endl;
	Showtime();
	cout<<"\t<DIR>"<<"\t\t.."<<endl;
	if(getchar()=='\n')
		Dir1(present,listnum,filenum,allsize);
	else
	{
		cin>>filename;
		if ((!strcmp(filename,".")))
		{
			Dir1(present,listnum,filenum,allsize);
		}
		else if (!strcmp(filename,".."))
		{
			Dir1(present->father,listnum,filenum,allsize);
		}
		else
		{
			if(Isexist(filename,0)||Isexist(filename,1))
			{//处理单个
			//	Dir1(finding,listnum,filenum,allsize);
				if(finding->type==0)
				{
					cout<<"\t<DIR>\t\t"<<finding->name<<endl;
					listnum++;
				}
				else
				{
					cout<<"\t  "<<finding->size<<"\t"<<finding->name<<endl;
					filenum++;
					allsize+=finding->size;
				}
			}
			cout<<"\t   "<<filenum<<"个文件\t   "<<allsize<<endl;
			cout<<"\t   "<<listnum<<"个目录\t   "<<leftbit<<"可用"<<endl;
		}
	}
}
//删除子目录
void Delelist()
{
	char listname[50];
	cin>>listname;
	if(Isexist(listname,0)==0)
		cout<<"系统找不到指定的文件。"<<endl;
	else
	{//finding
		if(finding->sub!=NULL)
			cout<<"目录不是空的。"<<endl;
		else
		{//删除目录,有错误
			Delpoint(finding);
		}
	}
}
//删除文件
void Delefile()
{
	int x,y;
	char filename[50];
	cin>>filename;
	if(Isexist(filename,1)==0)
		cout<<"系统找不到指定的文件。"<<endl;
	else
	{
		Mixtab * mtemp;
		mtemp=finding->table;
		if (mtemp->one==NULL)
		{//如果只存直接
			int start=0;
			while ((mtemp->begin[start]!=-1)&&(start<beginsize))
			{
				x=(mtemp->begin[start])/16;
				y=(mtemp->begin[start])%16;
				Bitmap[x][y]=0;
				start++;
				leftbit++;
			}
		}
		else if ((mtemp->one!=NULL)&&(mtemp->two==NULL))
		{//存了一级索引
			for (int k=0;k<beginsize;k++)
			{//处理直接
				x=(mtemp->begin[k])/16;
				y=(mtemp->begin[k])%16;
				Bitmap[x][y]=0;
			}
			leftbit=leftbit+beginsize;
			//处理一级索引
			Indireone * onetemp;
			onetemp=mtemp->one;
			int start =0;
			while((onetemp->data[start]!=-1)&&(start<LENGTH))
			{
				x=(onetemp->data[start])/16;
				y=(onetemp->data[start])%16;
				Bitmap[x][y]=0;
				start++;
				leftbit++;
			}
		}
		else if (mtemp->two!=NULL)
		{//二级
			int k,i,j;
			for (k=0;k<beginsize;k++)
			{//处理直接
				x=(mtemp->begin[k])/16;
				y=(mtemp->begin[k])%16;
				Bitmap[x][y]=0;
			}
			leftbit=leftbit+beginsize;
			Indireone * onetemp;
			onetemp=mtemp->one;
			for (k=0;k<LENGTH;k++)
			{//处理了一级索引
				//
				x=(onetemp->data[k])/16;
				y=(onetemp->data[k])%16;
				Bitmap[x][y]=0;
			}
			leftbit=leftbit+LENGTH;
			Indiretwo * twotemp;
			twotemp=mtemp->two;
			onetemp=twotemp->first[0];
			//
			int flg=0;
			//处理二级结构
			for (flg=0;flg<LENGTH;flg++)
			{//
				if (twotemp->first[flg]==NULL)
				{//
					break;
				}
			}
			if(flg>1)
			{
				for (i=0;i<flg-1;i++)
				{
					for (j=0;j<LENGTH;j++)
					{
						x=(twotemp->first[i]->data[j])/16;
						y=(twotemp->first[i]->data[j])%16;
						Bitmap[x][y]=0;
					}
				}
				leftbit=leftbit+(flg-1)*LENGTH;
			}
			int start=0;
			while ((twotemp->first[flg-1]->data[start]!=-1)&&(start<LENGTH))
			{
				x=(twotemp->first[flg-1]->data[start])/16;
				y=(twotemp->first[flg-1]->data[start])%16;
				Bitmap[x][y]=0;
				leftbit++;
				start++;
			}
			//=
		}
		else
		{//三级
		}
		delete(mtemp);
		Delpoint(finding);
	}
}
//改变目录
void ChangeFile()
{
	char listname[50];
	cin>>listname;
	if(present==root)
	{
		if((!strcmp(listname,"."))||(!strcmp(listname,"..")))   {}
		else if(Isexist(listname,0))
		{
			present=finding;
			strcat(stringname,"\\");
			strcat(stringname,finding->name);
		}
		else
			cout<<"系统找不到指定的路径。"<<endl;
	}
	else
	{
		if(!strcmp(listname,".."))
		{
			char temp[50];
			int loc1,loc2;
			loc1=strlen(stringname);
			loc2=strlen(present->name);
			strncpy(temp,stringname,loc1-loc2);
			temp[loc1-loc2-1]='\0';
			strcpy(stringname,temp);
			present=present->father;
		}
		else if(!strcmp(listname,"."))  {}
		else if(!strcmp(listname,"\\"))
		{
			present=root;
			strcpy(stringname,"\\");
		}
		else if(Isexist(listname,0)==0)
			cout<<"系统找不到指定的路径。"<<endl;
		else
		{
			present=finding;
			strcat(stringname,"\\");
			strcat(stringname,finding->name);
		}
	}
}
//分析的单独的节点
void Looktree(FCB * f)
{
	int a[100];
	int n=-1;
	FCB * temp;
	if (f->father==present)
	{
		if (f->next==NULL)
			cout<<"└─"<<f->name<<endl;
		else
			cout<<"├─"<<f->name<<endl;
	}
	else
	{
		temp=f->father;
		while(temp!=present)
		{
			n++;
			if(temp->next==NULL)
			{//是0时候输出空格，else输出竖线
				a[n]=0;
			}
			else a[n]=1;
			temp=temp->father;
		}
		//记住了n
		for(int i=n;i>=0;i--)
		{
			if(a[i]==1)
				cout<<"│  ";
			else cout<<"    ";
		}
		if(f->next==NULL)
			cout<<"└─"<<f->name<<endl;
		else
			cout<<"├─"<<f->name<<endl;
	}
}

void Treeview(FCB * f)//树形结构查看
{//查看的是目录
	FCB * temp,* temp2;
	if(present->sub==NULL)
		cout<<"没有子文件夹"<<endl;
	else
	{
		temp=f->sub;
		while(temp!=NULL)
		{
			Looktree(temp);
			if(temp->sub!=NULL)//==
			{
				temp2=temp->sub;
				while(temp2!=NULL)
				{
					Looktree(temp2);
					Treeview(temp2);
					temp2=temp2->next;
				}
			}
			temp=temp->next;
		}
	}
}
//
void Show()
{
	int i,j;
	for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
			cout<<Bitmap[i][j]<<" ";
		cout<<endl;
    }
}
//
void Help()
{
	cout<<"Microsoft Windows 【版本 6.1.7601】"<<endl;
	cout<<"版权所有 （c） 2009 Microsoft Corporation。保留所有权利。"<<endl;
}
//
int main()
{
	char choice[30];
	Initall();
	present=root;
	Help();
	strcpy(stringname,"\\");
	cout<<stringname;
	cout<<">";
	while(true)
	{
		cin>>choice;
		if(!strcmp(choice,"help"))
			Help();
		else if(!strcmp(choice,"cd"))
			ChangeFile();
		else if(!strcmp(choice,"md"))
			Mdlist();
		else if(!strcmp(choice,"rd"))
			Delelist();
		else if(!strcmp(choice,"dir"))
			Dirall();
		else if(!strcmp(choice,"mk"))
			 Mkfile();
		else if(!strcmp(choice,"del"))
			Delefile();
		else if(!strcmp(choice,"exit"))
			exit(0);
		else if(!strcmp(choice,"tree"))
			Treeview(present);
		else if(!strcmp(choice,"cls"))
			system("cls");
		else if(!strcmp(choice,"show"))
			Show();
		else
			cout<<"'"<<choice<<"'"<<"不是内部或外部命令，也不是可运行的程序或批处理文件。"<<endl;
		cout<<stringname<<">";
	}
	return 0;
}
