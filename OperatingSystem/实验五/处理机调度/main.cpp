#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <stack>
#include <climits>
#include <cstring>
using namespace std;





/*****************************
Define the Array

*****************************/
const int MAX_P = 5;        // 进程个数
int arriveTime[MAX_P];      // 到达时刻
int runTime[MAX_P];         // 运行时间
int startTime[MAX_P];       // 开始时刻
int finishTime[MAX_P];      // 完成时刻
int turnTime[MAX_P];        // 周转时间
double responseTime[MAX_P]; // 响应时间
double averTurnTime;        // 平均周转时间
double averResTime;         // 平均响应时间

set<int> finishProcess;     // 完成进程集合
typedef struct stfNode      // 最短作业有限优先节点
{
    int id;                 // 存进程号
    int arriveTime;         // 当前进程的到达时刻
    int runTime;            // 当前进程的运行时间
}stf;
stf stfArray[MAX_P];        // 最短作业

const int Q = 1;            // 时间片大小




bool cmp(stf x , stf y)
{
    if(x.runTime == y.runTime)
        return x.arriveTime < y.arriveTime;
    else return x.runTime < y.runTime;
}


void init()
{
    for(int i = 0 ; i < MAX_P ; i ++)
        cin >> arriveTime[i];
    for(int i = 0 ; i < MAX_P ; i ++)
        cin >> runTime[i];
}

void FCFS()
{

    startTime[0] = arriveTime[0];
    finishTime[0] = startTime[0] + runTime[0];
    turnTime[0] = finishTime[0] - arriveTime[0];
    responseTime[0] = turnTime[0] / (double)runTime[0];
    averTurnTime = turnTime[0] , averResTime = responseTime[0];
    for(int i = 1 ; i < MAX_P ; i ++)
    {
        startTime[i] = max(finishTime[i-1] , startTime[i]);
        finishTime[i] = startTime[i] + runTime[i];
        turnTime[i] = finishTime[i] - arriveTime[i];
        responseTime[i] = turnTime[i] / (double)runTime[i];
        averTurnTime += turnTime[i];
        averResTime += responseTime[i];
    }
    for(int i = 0 ; i < MAX_P ; i ++)
        cout << arriveTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << runTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << startTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << finishTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << turnTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << responseTime[i] << " ";
    cout << endl;

    cout << "Average TurnTime : " << averTurnTime / MAX_P << endl;
    cout << "Average ResponseTime : " << averResTime / MAX_P << endl;
}


void SJF()
{
    int pos = 0 , lastFinish = INT_MIN;
    while(true)
    {
        if(finishProcess.size() == MAX_P)   break;

        int index = 0;
        for(int i = 0 ; i < MAX_P ; i ++)               // Find the arrive time is small than pos
        {
            if(finishProcess.count(i))  continue;
            if(arriveTime[i] <= pos)
            {
                stfArray[index].id = i;
                stfArray[index].arriveTime = arriveTime[i];
                stfArray[index++].runTime = runTime[i];
            }
        }
        sort(stfArray , stfArray + index , cmp);        // Sort it
        for(int i = 0 ; i < index ; i ++)               // Insert it
        {
            int p = stfArray[i].id;
            finishProcess.insert(p);
            startTime[p] = max(pos , stfArray[i].arriveTime);       // Notice the arrive time
            finishTime[p] = startTime[p] + stfArray[i].runTime;
            pos = finishTime[p];                                    // Update the pos
        }
    }
    averResTime = 0 , averTurnTime = 0;
    for(int i = 0 ; i < MAX_P ; i ++)
    {
        turnTime[i] = finishTime[i] - arriveTime[i];
        responseTime[i] = turnTime[i] / (double)runTime[i];
        averResTime += responseTime[i];
        averTurnTime += turnTime[i];
    }

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << arriveTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << runTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << startTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << finishTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << turnTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << responseTime[i] << " ";
    cout << endl;

    cout << "Average TurnTime : " << averTurnTime / MAX_P << endl;
    cout << "Average ResponseTime : " << averResTime / MAX_P << endl;
}



bool cmpSTF(stf x , stf y)
{
    return x.arriveTime < y.arriveTime;
}

void RRT()
{
    int copy_runtime[MAX_P];
    memset(copy_runtime , 0 , sizeof(copy_runtime));
    memset(stfArray , 0 , sizeof(stfArray));
    memset(finishTime , 0 , sizeof(finishTime));
    memset(startTime , 0 , sizeof(startTime));
    memset(turnTime , 0 , sizeof(turnTime));
    memset(responseTime , 0 , sizeof(responseTime));
    int pos = 0;
    set<int> hasStart;
    hasStart.clear();
    finishProcess.clear();
    while(true)
    {
        if(finishProcess.size() == MAX_P)   break;

        for(int i = 0 ; i < MAX_P ; i ++)
        {
            if(finishProcess.count(i))  continue;
            if(!hasStart.count(i))
            {
                startTime[i] = max(pos , startTime[i]);
                pos = startTime[i];
                hasStart.insert(i);
            }
            for(int j = 0 ; j < Q ; j ++)
            {
                if(copy_runtime[i] == runTime[i] - 1)
                {
                    pos ++;
                    finishTime[i] = pos;
                    finishProcess.insert(i);
                    break;
                }
                else
                {
                    copy_runtime[i] ++;
                    pos ++;
                }
            }
        }
    }

    averResTime = 0 , averTurnTime = 0;
    for(int i = 0 ; i < MAX_P ; i ++)
    {
        turnTime[i] = finishTime[i] - arriveTime[i];
        responseTime[i] = turnTime[i] / (double)runTime[i];
        averResTime += responseTime[i];
        averTurnTime += turnTime[i];
    }

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << arriveTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << runTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << startTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << finishTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << turnTime[i] << " ";
    cout << endl;

    for(int i = 0 ; i < MAX_P ; i ++)
        cout << responseTime[i] << " ";
    cout << endl;

    cout << "Average TurnTime : " << averTurnTime / MAX_P << endl;
    cout << "Average ResponseTime : " << averResTime / MAX_P << endl;

}



void menuDispatch()
{
    cout << "Dispatch Algorithm£º" << endl;
    cout << "1.FCFS" << endl;
    cout << "2.SJF" << endl;
    cout << "3.RR" << endl;
    cout << "4.GoBack" << endl;
}

void selectDispatch()
{
    init();
    menuDispatch();
    while(1)
    {
        int sel;
        cin >> sel;
        switch(sel)
        {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            RRT();
            break;
        case 4:
            exit(0);
        default :
            break;
        }
        menuDispatch();
    }
}

int main()
{
   /* #ifdef DoubleQ
    freopen("in.txt","r",stdin);
    #endif*/
    selectDispatch();
    return 0;
}
