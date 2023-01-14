#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <list>
using namespace std;

struct empt  // Define the empty table
{
    int start;
    int len;
};

list<struct empt> emptable;

bool cmp(struct empt a , struct empt b)
{
    if(a.len == b.len)
        return a.start < b.start;
    return a.len < b.len;
}

void init_empt_head()  // Init the empty table
{
    struct empt temp;
    temp.start = 0;
    temp.len = 1000;
    emptable.push_back(temp);   // It length is 1000
    emptable.sort(cmp);
}

typedef struct node
{
    string name;        // The name of process
    int cnt = 0;        // The number of process
    struct node *next; // To the next process
    int start;
    int len;          // Address length
}PCB , *ready , *run , *await;

ready Lready;        // Three staus
run Lrun;
await Lwait;

void init_link_ready(ready &L)   // Init ready
{
    L = new PCB;
    L->next = NULL;
}

void init_link_run(run &L)        // Init run
{
    L = new PCB;
    L->next = NULL;
}

void init_link_wait(await &L)        // Init wait
{
    L = new PCB;
    L->next = NULL;
}

void init()             // Init all
{
    init_empt_head();
    init_link_ready(Lready);
    init_link_run(Lrun);
    init_link_wait(Lwait);
}


bool check(PCB *temp)
{
    for(list<struct empt>::iterator it = emptable.begin() ; it != emptable.end() ; it ++)
    {
        if((*it).len >= temp->len)
        {
            temp->start = (*it).start;
            if((*it).len - temp->len <= 2)
            {
                temp->len = (*it).len;
                emptable.erase(it);
                emptable.sort(cmp);
            }
            else
            {
                (*it).len -= temp->len;
                (*it).start += temp->len;
            }
            return true;
        }
    }
    return false;
}

void receive(PCB *temp)
{
    /*
    list<struct empt>::iterator it = emptable.begin();
    bool flag = false;
    if((*it).start == 0)
        flag = true;
    if(flag)
    {
    */
        for(list<struct empt>::iterator it = emptable.begin() ; it != emptable.end() ; it ++)
        {
            list<struct empt>::iterator it2 = it;
            it2 ++;
            list<struct empt>::iterator it3 = it;
            it3 --;
            if((*it).start + (*it).len == temp->start)
            {
                if((*it2).start == temp->start + temp->len)
                {
                    (*it).len += (*it2).len + temp->len;
                    emptable.erase(it2);
                    emptable.sort(cmp);
                    return;
                }
                else
                {
                    (*it).len += temp->len;
                    emptable.sort(cmp);
                    return;
                }
            }
            else if(temp->start + temp->len == (*it).start)
            {
                if((*it3).len + (*it3).start == temp->start)
                {
                    (*it3).len += temp->len + (*it).len;
                     emptable.erase(it);
                     emptable.sort(cmp);
                     return;
                }
                else
                {
                    (*it).start = temp->start;
                    (*it).len += temp->len;
                     emptable.sort(cmp);
                     return;
                }
            }

            /*
            // Up empty and down not empty
            if((*it).start + (*it).len == temp->start && temp->start + temp->len < (*it2).start)
            {
                (*it).len += temp->len;
                emptable.sort(cmp);
                return ;
            }
            // Up not empty and down empty
            else if((*it3).start + (*it3).len < temp->start && temp->start + temp->len == (*it).start)
            {
                (*it).start = temp->start;
                (*it).len += temp->len;
                emptable.sort(cmp);
                return ;
            }
            // Up and down empty
            else if((*it).start + (*it).len == temp->start && temp->start + temp->len == (*it2).start)
            {
                (*it).len += temp->len + (*it2).len;
                 emptable.erase(it2);
                 emptable.sort(cmp);
                 return ;
            }
            // Up and down all not empty
            else if((*it).start + (*it).len < temp->start && temp->start + temp->len < (*it2).start)
            {
                struct empt temp2;
                temp2.start = temp->start;
                temp2.len = temp->len;
                emptable.push_back(temp2);
                emptable.sort(cmp);
                return ;
            }
            */
        }
        struct empt temp2;
        temp2.start = temp->start;
        temp2.len = temp->len;
        emptable.push_back(temp2);
    /*
    }
    else
    {
        for(list<struct empt>::iterator it = emptable.begin() ; it != emptable.end() ; it ++)
        {
            list<struct empt>::iterator it2 = it;
            it2 ++;
            list<struct empt>::iterator it3 = it;
            it3 --;
            // Up empty and down not empty
            if((*it).start + (*it).len == temp->start && temp->start + temp->len != (*it2).start)
            {
                (*it).len += temp->len;
                 emptable.sort(cmp);
                 return ;
            }
            // Up not empty and down empty
            else if((*it).start == temp->start + temp->len && (*it3).start + (*it3).len != temp->start)
            {
                (*it).len += temp->len;
                (*it).start = temp->start;
                emptable.sort(cmp);
                return ;
            }
            // Up and down empty
            else if((*it).start + (*it).len == temp->start && temp->start + temp->len == (*it2).start)
            {
                (*it).len += temp->len + (*it2).len;
                emptable.erase(it2);
                emptable.sort(cmp);
                return ;
            }
            // Up and down all not empty
            else if(temp->start > (*it).start + (*it).len && temp->start + temp->len < (*it2).start + (*it2).len)
            {
                struct empt temp2;
                temp2.start = temp->start;
                temp2.len = temp->len;
                emptable.push_back(temp2);
                emptable.sort(cmp);
                return ;
            }
        }
    }
    */
}

void creat()        // Creat a process
{
    PCB *temp = new PCB;
    cin >> temp->name >> temp->len;
    if(!check(temp))     // Can't distribution
    {
        cout << "Erro!" << endl;
        getchar();getchar();
        return ;
    }
    if(Lready->next == NULL)
    {
        if(Lrun->next == NULL)  // If run is null,we directly put the new process to the run stau.
        {
            Lrun->cnt ++;
            temp->next = Lrun->next;
            Lrun->next = temp;
        }
        else                   // Put th new process to the ready syau.
        {
            Lready->cnt ++;
            temp->next = Lready->next;
            Lready->next = temp;
        }
    }
    else                        // Ready isn't null.so we have to find it's tail and contact with the new process.
    {
        Lready->cnt ++;
        PCB *L = Lready;
        while(L->next)
            L = L->next;
        temp->next = L->next;
        L->next = temp;
    }
}

void running()
{
    if(Lrun->cnt == 1)    // If run stau is working,we can't push a new process
    {
        cout << "Run Erro!" << endl;
        getchar();getchar();
    }
    else
    {
        PCB *temp = Lready->next;
        if(temp == NULL)            // If run is relaxing and ready is empty,we can't push a new process
        {
            cout << "Erro!" << endl;
            getchar();getchar();
        }
        else            // Build a new process to run stau
        {
            while(temp->next->next)
            {
                temp = temp->next;
            }
            PCB *temp_last = temp->next;
            temp->next = NULL;
            Lrun->cnt ++;
            Lready->cnt --;
            temp_last->next = Lrun->next;
            Lrun->next = temp_last;
        }
    }
}

void stop()
{
    if(Lrun->cnt == 0)
    {
        cout << "Erro!" << endl;
        getchar();getchar();
        //cout << "执行态为空，命令错误！" << endl;
    }
    else
    {
        // Delete process in run stau and the number of run staus decrease
        PCB *temp = Lrun->next;
        Lrun->next = NULL;
        Lrun->cnt --;
        // If wait stau is empty,we diretly link this process to it
        if(Lwait->next == NULL)
        {
            temp->next = Lwait->next;
            Lwait->next = temp;
            Lwait->cnt ++;
        }
        else
        {
            PCB *L = Lwait;
            while(L->next)
                L = L->next;
            temp->next = L->next;
            L->next = temp;
            Lwait->cnt ++;
        }
        // If ready stau isn't,we choose the first process to the run stau
        PCB *new_runpro = Lready->next;
        if(new_runpro)
        {
            Lready->next = new_runpro->next;;
            Lready->cnt --;
            new_runpro->next = Lrun->next;
            Lrun->next = new_runpro;
            Lrun->cnt ++;
        }

    }
}

void recover()
{
    if(Lwait->next == NULL)
    {
        cout << "Erro!" << endl;
        getchar();getchar();
        //cout << "阻塞态为空，命令错误！" << endl;
    }
    else
    {
        // Delete the first process in wait stau
        PCB *temp = Lwait->next;
        Lwait->next = temp->next;
        Lwait->cnt --;
        // Put this process to the ready stau's tail
        PCB *L = Lready;
        while(L->next)
            L = L->next;
        temp->next = L->next;
        L->next = temp;
        Lready->cnt ++;
        if(Lrun->next == NULL)      // If run stau is empty , choose the first ready node to it
        {
            PCB *temp2 = Lready->next;
            Lready->next = temp2->next;
            Lready->cnt --;
            temp2->next = Lrun->next;
            Lrun->next = temp2;
            Lrun->cnt ++;
        }
    }
}

void time()
{
    if(Lrun->next == NULL)      // If run stau is empty , we can't select it to ready stau
    {
        cout << "Erro!" << endl;
        getchar();getchar();
        return ;
    }
    if(Lready->next == NULL)
    {
        PCB *temp = Lrun->next;
        Lrun->next = NULL;
        Lrun->cnt --;
        temp->next = Lready->next;
        Lready->next = temp;
        Lready->cnt ++;
    }
    else
    {
        PCB *L = Lready;
        while(L->next)
            L = L->next;
        PCB *temp = Lrun->next;
        L->next = temp;
        temp->next = NULL;
        PCB *temp2 = Lready->next;
        Lrun->next = temp2;
        Lready->next = temp2->next;
        temp2->next = NULL;
    }
}

void finish()
{
    if(Lrun->next == NULL)      // Run stau is empty
    {
        cout << "Erro!" << endl;
        getchar();getchar();
        return ;
    }
    PCB *temp = Lrun->next;
    receive(temp);
    Lrun->cnt --;
    Lrun->next = NULL;
    if(Lready->next != NULL)
    {
        Lrun->next = Lready->next;
        Lready->next = Lready->next->next;
        Lrun->next->next = NULL;
        Lready->cnt --;
        Lrun->cnt ++;
    }
}

void print_ready(ready Lready)   // Print ready stau
{
    PCB *temp = Lready->next;
    cout << "Ready process count: " << Lready->cnt << endl;
    while(temp)
    {
        cout << "ready process name : " << temp->name << endl;
        temp = temp->next;
    }
}

void print_run(run Lrun)        // Print run stau
{
    PCB *temp = Lrun->next;
    cout << "Run process count : " << Lrun->cnt << endl;
    while(temp)
    {
        cout << "Run process name : " << temp->name << endl;
        temp = temp->next;
    }
}

void print_wait(await Lwait)     // Print wait stau
{
    PCB *temp = Lwait->next;
    cout << "Stop process count : " << Lwait->cnt << endl;
    while(temp)
    {
        cout << "Stop process name : " << temp->name << endl;
        temp = temp->next;
    }
}

void print()            // Print reault
{
    cout << "---------------------------------------" << endl;
    print_ready(Lready);
    cout << "---------------------------------------" << endl;
    print_run(Lrun);
    cout << "---------------------------------------" << endl;
    print_wait(Lwait);
    cout << "---------------------------------------" << endl;
}

void print_mem()
{
    while(1)
    {
        int flag = 1;
        for(list<struct empt>::iterator it = emptable.begin() ; it != emptable.end() ; it ++)
        {
            list<struct empt>::iterator it2 = it;
            it2 ++;
            if((*it).start + (*it).len == (*it2).start)
            {
                (*it).len += (*it2).len;
                emptable.erase(it2);
                emptable.sort(cmp);
                flag = 0;
            }
        }
        if(flag)   break;
    }

    for(list<struct empt>::iterator it = emptable.begin() ; it != emptable.end() ; it ++)
    {
        cout << "Start Adress : " << (*it).start << " " << "Address Length : " << (*it).len << endl;
    }
}

void display()
{
    cout << "---------------------------------------" << endl;
    cout << "Welocme to DoubleQ's OS" << endl;
    cout << "c ---- Creat a process" << endl;
    cout << "r ---- Run a process" << endl;
    cout << "s ---- Stop a process" << endl;
    cout << "g ---- Recover a process" << endl;
    cout << "t ---- Current process's time has gone" << endl;
    cout << "f ---- Finish a process" << endl;
    cout << "h ---- View the help" << endl;
    cout << "m ---- View the memory" << endl;
    cout << "e ---- Exit" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Please input command : " << endl;
}

void menu()
{
    init();
    display();
    string com;
    while(1)
    {
        cout << "< " << endl;
        cin >> com;
        if(com == "c")
        {
            creat();
            system("CLS");
            print();
            print_mem();
        }
        else if(com == "r")
        {
            running();
            system("CLS");
            print();
        }
        else if(com == "s")
        {
            stop();
            system("CLS");
            print();
        }
        else if(com == "g")
        {
            recover();
            system("CLS");
            print();
        }
        else if(com == "t")
        {
            time();
            system("CLS");
            print();
        }
        else if(com == "f")
        {
            finish();
            system("CLS");
            print();
            print_mem();
        }
        else if(com == "h")
        {
            system("CLS");
            display();
        }
        else if(com == "e")
        {
            break;
        }
        else if(com == "m")
        {
            system("CLS");
            print_mem();
        }
        else
            cout << "Input Erro！ Please try again!" << endl;
    }
}


int main()
{
    menu();
    return 0;
}
