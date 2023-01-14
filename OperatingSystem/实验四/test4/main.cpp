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
typedef struct      // һ�ε�ַ
{
	int data[LENGTH];
}Indireone;
typedef struct      //���μ�ַ
{
	Indireone * first[LENGTH];
}Indiretwo;
typedef struct      //���μ�ַ
{
	Indiretwo * second[LENGTH];
}Indirethree;
typedef struct Node
{
	int begin[beginsize];       //ֱ�ӵ�ַ
	Indireone * one;
	Indiretwo * two;
	Indirethree * three;
}Mixtab;            //��������ڵ�

typedef struct NODE
{
	char name[50];
	int type;//���ļ�����Ŀ¼,1�����ļ���0����Ŀ¼
	int size;//������ļ�������С
	struct NODE *next;//�ֵܽ��
	struct NODE * sub;//�ӽڵ�
	struct NODE * father;//���׽ڵ�
	Mixtab * table;
}FCB;
//�ļ����ƿ�
FCB * root;
FCB * present;
FCB * finding;
char stringname[300];
int Bitmap[16][16];//λʾͼ
int leftbit=0;      // �յĿ���
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
//�жϷ������ʱ���ǲ����㹻
int Judgeenough(int n)
{
	if(leftbit>=n)   return 1;
	else return 0;
}
//���ʱ����
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
//ɾ��ʱ����
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
//�����ǲ����Ѿ�����
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
//����Ŀ¼
void Mdlist()
{
	char listname[50];
	cin>>listname;
	FCB * temp;
	if(Isexist(listname,0))
		cout<<"��Ŀ¼���ļ�"<<listname<<"�Ѵ��ڡ�"<<endl;
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
    cout<<"ֱ�ӵ�ַ��"<<endl;
    for(int i=0;i<beginsize;i++)
        if(p->begin[i] != -1)
            cout<<p->begin[i]<<" ";
    cout<<endl;
    if(p->one->data[0] != -1)
    {
        cout<<"һ�μ�ַ:"<<endl;
        for(int i=0;i<LENGTH;i++)
            if(p->one->data[i] != -1)
                cout<<p->one->data[i]<<" ";
        cout<<endl;
        if(p->two->first[0] != -1)
        {
            cout<<"���μ�ַ��"<<endl;
            for(int i=0;i<LENGTH;i++)
                if(p->two->first[i] != -1)
                    cout<<p->two->first[i]<<" ";
            cout<<endl;
            if(p->three->second[0]!=-1)
            {
                cout<<"���μ�ַ��"<<endl;
                for(int i=0;i<LENGTH;i++)
                    if(p->three->second[i] != -1)
                    cout<<p->three->second[i]<<" ";
                cout<<endl;
            }
        }

    }
}
*/




//�����ļ�
void Mkfile()
{//�������ʱ���д���
	char listname[50];
	int length,i,j,k,leg=0;
	cin>>listname;
	FCB * temp;
	if(getchar()=='\n')
		length=0;
	else
		cin>>length;
	if(Isexist(listname,1))
		cout<<"��Ŀ¼���ļ�"<<listname<<"�Ѵ��ڡ�"<<endl;
	else if(Judgeenough(length)==0)
		cout<<"���ʣ��ռ䲻��"<<endl;
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
			{//ֱ�ӵ�ַ����ʱ��
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
			{//��һ��������ʱ��
				for(k=0;k<beginsize;k++)
				{//ֱ�ӵĴ洢��
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
				{//һ����������
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
			{//���ö�������ʱ��
				for(k=0;k<beginsize;k++)
				{//ֱ�ӵĴ洢��
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
				{//һ����������
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
				{	//��ֻ��һ��ʱ��
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
				{//���ж��ʱ��
					leg=0;
					for(int n=0;n<twostep;n++)
					{//���������
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
					//����ɢ��
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


void Dir1(FCB * f,int listnum,int filenum,int allsize)  //�г��ļ�
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
	cout<<"\t   "<<filenum<<"���ļ�\t   "<<allsize<<endl;
	cout<<"\t   "<<listnum<<"��Ŀ¼\t   "<<leftbit<<"����"<<endl;
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
			{//������
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
			cout<<"\t   "<<filenum<<"���ļ�\t   "<<allsize<<endl;
			cout<<"\t   "<<listnum<<"��Ŀ¼\t   "<<leftbit<<"����"<<endl;
		}
	}
}
//ɾ����Ŀ¼
void Delelist()
{
	char listname[50];
	cin>>listname;
	if(Isexist(listname,0)==0)
		cout<<"ϵͳ�Ҳ���ָ�����ļ���"<<endl;
	else
	{//finding
		if(finding->sub!=NULL)
			cout<<"Ŀ¼���ǿյġ�"<<endl;
		else
		{//ɾ��Ŀ¼,�д���
			Delpoint(finding);
		}
	}
}
//ɾ���ļ�
void Delefile()
{
	int x,y;
	char filename[50];
	cin>>filename;
	if(Isexist(filename,1)==0)
		cout<<"ϵͳ�Ҳ���ָ�����ļ���"<<endl;
	else
	{
		Mixtab * mtemp;
		mtemp=finding->table;
		if (mtemp->one==NULL)
		{//���ֻ��ֱ��
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
		{//����һ������
			for (int k=0;k<beginsize;k++)
			{//����ֱ��
				x=(mtemp->begin[k])/16;
				y=(mtemp->begin[k])%16;
				Bitmap[x][y]=0;
			}
			leftbit=leftbit+beginsize;
			//����һ������
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
		{//����
			int k,i,j;
			for (k=0;k<beginsize;k++)
			{//����ֱ��
				x=(mtemp->begin[k])/16;
				y=(mtemp->begin[k])%16;
				Bitmap[x][y]=0;
			}
			leftbit=leftbit+beginsize;
			Indireone * onetemp;
			onetemp=mtemp->one;
			for (k=0;k<LENGTH;k++)
			{//������һ������
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
			//��������ṹ
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
		{//����
		}
		delete(mtemp);
		Delpoint(finding);
	}
}
//�ı�Ŀ¼
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
			cout<<"ϵͳ�Ҳ���ָ����·����"<<endl;
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
			cout<<"ϵͳ�Ҳ���ָ����·����"<<endl;
		else
		{
			present=finding;
			strcat(stringname,"\\");
			strcat(stringname,finding->name);
		}
	}
}
//�����ĵ����Ľڵ�
void Looktree(FCB * f)
{
	int a[100];
	int n=-1;
	FCB * temp;
	if (f->father==present)
	{
		if (f->next==NULL)
			cout<<"����"<<f->name<<endl;
		else
			cout<<"����"<<f->name<<endl;
	}
	else
	{
		temp=f->father;
		while(temp!=present)
		{
			n++;
			if(temp->next==NULL)
			{//��0ʱ������ո�else�������
				a[n]=0;
			}
			else a[n]=1;
			temp=temp->father;
		}
		//��ס��n
		for(int i=n;i>=0;i--)
		{
			if(a[i]==1)
				cout<<"��  ";
			else cout<<"    ";
		}
		if(f->next==NULL)
			cout<<"����"<<f->name<<endl;
		else
			cout<<"����"<<f->name<<endl;
	}
}

void Treeview(FCB * f)//���νṹ�鿴
{//�鿴����Ŀ¼
	FCB * temp,* temp2;
	if(present->sub==NULL)
		cout<<"û�����ļ���"<<endl;
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
	cout<<"Microsoft Windows ���汾 6.1.7601��"<<endl;
	cout<<"��Ȩ���� ��c�� 2009 Microsoft Corporation����������Ȩ����"<<endl;
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
			cout<<"'"<<choice<<"'"<<"�����ڲ����ⲿ���Ҳ���ǿ����еĳ�����������ļ���"<<endl;
		cout<<stringname<<">";
	}
	return 0;
}
