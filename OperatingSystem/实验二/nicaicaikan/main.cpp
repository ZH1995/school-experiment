#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <string>
#include <algorithm>
#include <deque>
#include <queue>
using namespace std;

int N , M;
#define Length 4132
const int maxn = 101;

struct Page
{
    int id;
    int block;
    bool stau;
};

struct Page page_fifo[maxn] , page_lru[maxn] , page_opt[maxn];

int fifo[maxn];
int inva_fifo;

int lru[maxn];
int inva_lru;

int opt[maxn];
int inva_opt;
int cols;

int fifo_2[maxn][maxn] , lru_2[maxn][maxn] , opt_2[maxn][maxn];

bool view[maxn];

int address[maxn];
int add_len;

void out_rate_fifo()
{
    system("cls");
    cout << "FIFO缺页率 ： ";
    cout << inva_fifo  << "/" << add_len << endl;
    cout << endl;
    system("PAUSE");
}

void out_rate_lru()
{
    system("cls");
    cout << "LRU缺页率 ： ";
    cout << inva_lru  << "/" << add_len << endl;
    cout << endl;
    system("PAUSE");
}

void out_rate_opt()
{
    system("cls");
    cout << "OPT缺页率 ： ";
    cout << inva_opt  << "/" << add_len << endl;
    cout << endl;
    system("PAUSE");
}

void out_pageFifo()
{
    system("cls");
    cout << "页表(FIFO)：" << endl;
    for(int i = 0 ; i < M ; i ++)
        cout << page_fifo[i].id << " " << page_fifo[i].block << " " << page_fifo[i].stau << endl;
    cout << endl;
    system("PAUSE");
}


void out_pageLru()
{
    system("cls");
    cout << "页表(LRU)：" << endl;
    for(int i = 0 ; i < M ; i ++)
        cout << page_lru[i].id << " " << page_lru[i].block << " " << page_lru[i].stau << endl;
    cout << endl;
    system("PAUSE");
}


void out_address()
{
    for(int i = 0 ; i < add_len ; i ++)
        cout << address[i] << " ";
    cout << endl;
    cout << "----------------------------------------------" << endl;
}


void out_allFifo()
{
    system("cls");
    cout << "FIFO置换过程" << endl;
    out_address();
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0 ; j < add_len ; j ++)
        {
            if(fifo_2[i][j] == -1)
                cout << "  ";
            else
                cout << fifo_2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    system("PAUSE");
}

void out_allLru()
{
    system("cls");
    cout << "LRU置换过程" << endl;
    out_address();
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0 ; j < add_len ; j ++)
        {
            if(lru_2[i][j] == -1)
                cout << "  ";
            else
                cout << lru_2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    system("PAUSE");
}


void out_allOpt()
{
    system("cls");
    cout << "OPT置换过程" << endl;
    out_address();
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0 ; j < add_len ; j ++)
        {
            if(opt_2[i][j] == -1)
                cout << "  ";
            else
                cout << opt_2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    system("PAUSE");
}

void out_view()
{
    system("cls");
    cout << "位示图：" << endl;
    int cnt = 1;
    for(int i = 0 ; i < 64 ; i ++)
    {
        cout << (view[i] == true ? "1" : "0");
        cout << ((cnt++) % 8 == 0 ? "\n" : " ");
    }
    cout << endl;
    system("PAUSE");
}

void re_view()
{
    for(int i = 0 ; i < M ; i ++)
        if(page_fifo[i].stau)
            view[page_fifo[i].block] = false;
    out_view();
}

void trans_fifo()
{
    int cnt = 0;
    for(int i = N - 1 ; i >= 0 ; i --)
        fifo_2[cnt++][add_len - 1] = fifo[i];
}

void trans_lru()
{
    int cnt = 0;
    for(int i = N - 1 ; i >= 0 ; i --)
        lru_2[cnt++][add_len - 1] = lru[i];
}

void trans_opt()
{
    int cnt = 0;
    for(int i = N - 1 ; i >= 0 ; i --)
        opt_2[cnt++][cols] = opt[i];
    cols ++;
}

void OPT()
{
    inva_opt = 0 , cols = 0;
    for(int i = 0 ; i < N ; i ++)   opt[i] = -1;
    for(int k = 0 ; k < add_len ; k ++)
    {
        int index = address[k] , go = 0;
        for(int i = 0 ; i < N ; i ++)
        {
            if(opt[i] == index)
            {
                go = 1;
                break;
            }
        }
        if(go)
        {
            trans_opt(); continue;
        }
        inva_opt ++;
        int pos = 0 , flag = 0 , pos2 = 0;
        for(int i = 0 ; i < 64 ; i ++)
            if(!view[i])    { pos = i; break;}
        for(int i = 0 ; i < N ; i ++)
            if(opt[i] == -1)    { pos2 = i; flag = 1; break; }
        if(flag)
        {
            page_opt[index].block = pos;
            page_opt[index].stau = true;
            opt[pos2] = page_opt[index].id;
            //view[pos] = true;
        }
        else
        {
            bool vis[maxn] = { false };
            int cnt = 0 , poskey = 0;
            for(int i = k + 1 ; i < add_len ; i ++)
            {
                for(int j = 0 ; j < N ; j ++)
                {
                    if(address[i] == opt[j] && vis[j] == false)
                    {
                        vis[j] = true;
                        cnt ++;
                    }
                }
                if(cnt == N - 1)
                    break;
            }
            for(int i = 0 ; i < N ; i ++)
                if(!vis[i]) { poskey = i ; break; }
            int old_pos = opt[poskey];
            page_opt[old_pos].stau = false;
            page_opt[index].block = page_opt[old_pos].block;
            page_opt[index].stau = true;
            page_opt[old_pos].block = -1;
            opt[poskey] = index;
        }
        trans_opt();
    }
}


void FIFO(int index)
{
    if(page_fifo[index].stau == true)
        { trans_fifo(); return; }
    int pos = 0 , flag = 0 , pos2 = 0;
    for(int i = 0 ; i < 64 ; i ++)
        if(!view[i])    { pos = i; break;}
    for(int i = 0 ; i < N ; i ++)
        if(fifo[i] == -1)   { pos2 = i; flag = 1; break;}
    inva_fifo ++;
    if(flag)
    {
        page_fifo[index].block = pos;
        page_fifo[index].stau = true;
        fifo[pos2] = page_fifo[index].id;
        //view[pos] = true;
    }
    else
    {
        // FIFO置换
        int old_pos = fifo[0];
        page_fifo[old_pos].stau = false;
        page_fifo[index].block = page_fifo[old_pos].block;
        page_fifo[index].stau = true;
        page_fifo[old_pos].block = -1;
        for(int i = 0 ; i < N ; i ++)
            if(i + 1 < N)   fifo[i] = fifo[i+1];
        fifo[N-1] = index;
    }
    trans_fifo();
}


void LRU(int index)
{

    if(page_lru[index].stau == true)
    {
        // LRU置换
        int pos = 0;
        for(int i = 0 ; i < N ; i ++)
            if(lru[i] == index)    { pos = i; break; }
        int temp = lru[pos];
        for(int i = pos ; i < N ; i ++)
            if(i + 1 < N)   lru[i] = lru[i+1];  else    break;
        lru[N-1] = temp;
        trans_lru();
        return;
    }
    int pos = 0 , flag = 0 , pos2 = 0;
    for(int i = 0 ; i < 64 ; i ++)
        if(!view[i])    { pos = i; break;}
    for(int i = 0 ; i < N ; i ++)
        if(lru[i] == -1)   { pos2 = i; flag = 1; break;}
    inva_lru ++;
    if(flag)
    {
        page_lru[index].block = pos;
        page_lru[index].stau = true;
        lru[pos2] = page_lru[index].id;
        view[pos] = true;
    }
    else
    {
        int old_pos = lru[0];
        page_lru[index].stau = true;
        page_lru[index].block = page_lru[old_pos].block;
        page_lru[old_pos].block = -1;
        page_lru[old_pos].stau = false;
        for(int i = 0 ; i < N ; i ++)
            if(i + 1 < N)   lru[i] = lru[i+1];
        lru[N-1] = index;
    }
    trans_lru();
}


void input()
{
    system("cls");
    cout << "请输入地址 ：" << endl;
    int key;
    scanf("%x",&key);
    int index = key / Length;
    if(index >= M)
        cout << "页号越界错误！" << endl;
    else
    {
        address[add_len++] = index;
        FIFO(index);
        LRU(index);
    }
    cout << endl;
    system("PAUSE");
}


void creat()
{
    srand(time(NULL));
    int cnt = 0;
    for(int i = 0 ; i < 64 ; i ++)
    {
        int temp = rand() % 100 + 1;
        if(temp % 2 == 0)
        {
            view[i] = false;
            cnt ++;
        }
        else
            view[i] = true;
    }
    if(cnt < M)
        creat();
}

void init()
{
    for(int i = 0 ; i < M ; i ++)
    {
        page_fifo[i].id = i; page_lru[i].id = i;    page_opt[i].id = i;
        page_fifo[i].block = -1; page_lru[i].block = -1;    page_opt[i].block = -1;
        page_fifo[i].stau = false;   page_lru[i].stau = false;  page_opt[i].stau = false;
    }
    for(int i = 0 ; i < N ; i ++)   { fifo[i] = -1; lru[i] = -1; opt[i] = -1;}
    add_len = 0;
    inva_fifo = 0;
    inva_lru = 0;
}

void menu()
{
    cout << "\t\t\t*******************************" << endl;
    cout << "\t\t\t\t欢迎登陆DoubleQ的操作系统" << endl;
    cout << "\t\t\t*******************************" << "\n\n";
    cout << "\t\t\t1.查位视图" << endl;
    cout << "\t\t\t2.查看FIFO页表" << endl;
    cout << "\t\t\t3.查看LRU页表" << endl;
    cout << "\t\t\t4.查看FIFO表" << endl;
    cout << "\t\t\t5.查看LRU表" << endl;
    cout << "\t\t\t6.查看OPT表" << endl;
    cout << "\t\t\t7.查看FIFO缺页率" << endl;
    cout << "\t\t\t8.查看LRU缺页率" << endl;
    cout << "\t\t\t9.查看OPT缺页率" << endl;
    cout << "\t\t\t10.查看回填位视图" << endl;
    cout << "\t\t\t11.输入地址" << endl;
    cout << "\t\t\t12.退出" << endl;
    cout << "\t\t\t";
}

void solve()
{
    int poss , kuai;
    cout << "请输入进程大小（单位：KB） ： " << endl;
    cin >> poss;
    cout << "请输入每页大小（单位：KB）" << endl;
    cin >> kuai;
    M = poss / kuai + (poss % kuai != 0 ? 1 : 0);
    cout << "请输入内存分配多少块 ： " << endl;
    cin >> N;
    system("PAUSE");
    system("cls");
    init();
    creat();
    bool flag = true;
    while(flag)
    {
        menu();
        int sel;    cin >> sel;
        switch(sel)
        {
        case 1:
            out_view(); break;
        case 2:
            out_pageFifo(); break;
        case 3:
            out_pageLru(); break;
        case 4:
            out_allFifo(); break;
        case 5:
            out_allLru();  break;
        case 6:
            OPT();  out_allOpt();  break;
        case 7:
            out_rate_fifo();    break;
        case 8:
            out_rate_lru(); break;
        case 9:
            OPT(); out_rate_opt(); break;
        case 10:
            re_view(); break;
        case 11:
            input(); break;
        case 12:
            exit(0);
        }
        system("cls");
    }
}

int main()
{
    solve();
    return 0;
}
