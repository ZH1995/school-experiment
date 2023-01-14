#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
//通道

typedef struct PCB
{
    string name;
    struct PCB *next;
}PCB;


typedef struct CHCT{
   string name;				//通道名
   bool stau;
   PCB *process;		//占用该通道的进程
   PCB *waitinglist;	//等待该通道的进程队列
   struct CHCT *next;			//下一个通道
}CHCT;

typedef struct COCT{
   string name;
   bool stau;
   CHCT *chct;			//控制器的上级通道
   PCB *process;		//占用该控制器的进程
   PCB *waitinglist;	//等待该控制器的进程队列
   struct COCT *next;			//下一个控制器
}COCT;

typedef struct DCT{
   string name;
   string type;
   bool stau;
   COCT *coct;
   PCB *process;		//占用该设备的进程
   PCB *waitinglist;
   struct DCT *next;
}DCT;

typedef struct SDT
{
    string name;
    string type;
    DCT *dct;
    struct SDT * next;
}SDT;


CHCT *channels;			//通道队列头节点
COCT *controllers;		//控制器队列头节点
DCT *devices;			//设备队列头节点
SDT *system;



void init()
{
    CHCT *ch1 = new CHCT;   CHCT *ch2 = new CHCT;
    ch1->name = "ch1";  ch1->stau = false;  ch1->waitinglist = NULL;    ch1->process = NULL;
    ch2->name = "ch2";  ch2->stau = false;  ch2->waitinglist = NULL;    ch2->process = NULL;
    PCB *ch1_pcb = new PCB; PCB *ch2_pcb = new PCB;
    ch1_pcb->next = NULL;   ch2_pcb->next = NULL;
    ch1->waitinglist = ch1_pcb; ch2->waitinglist = ch2_pcb;
    PCB *ch1pro = new PCB;  PCB *ch2pro = new PCB;
    ch1pro->next = NULL;    ch2pro->next = NULL;
    ch1->process = ch1pro;  ch2->process = ch2pro;
    channels = new CHCT;
    channels->next = ch1;  ch1->next = ch2;    ch2->next = NULL;

    COCT *co1 = new COCT;   COCT *co2 = new COCT;   COCT *co3 = new COCT;
    co1->name = "co1";  co2->name = "co2";  co3->name = "co3";
    co1->stau = false; co2->stau = false; co3->stau = false;
    PCB *co1_pcb = new PCB; PCB *co2_pcb = new PCB; PCB *co3_pcb = new PCB;
    co1_pcb->next = NULL;   co2_pcb->next = NULL;   co3_pcb->next = NULL;
    co1->waitinglist = co1_pcb;  co2->waitinglist = co2_pcb;  co3->waitinglist = co3_pcb;
    PCB *co1pro = new PCB;  PCB *co2pro = new PCB;  PCB *co3pro = new PCB;
    co1pro->next = NULL;    co2pro->next = NULL;    co3pro->next = NULL;
    co1->process = co3pro;  co2->process = co3pro;  co3->process = co3pro;
    co1->chct = ch1;    co2->chct = ch1;    co3->chct = ch2;
    controllers = new COCT;
    controllers->next = co1; co1->next = co2;    co2->next = co3;    co3->next = NULL;

    DCT *dc1 = new DCT; DCT *dc2 = new DCT; DCT *dc3 = new DCT; DCT *dc4 = new DCT;
    dc1->name = "dc1";  dc2->name = "dc2";  dc3->name = "dc3";  dc4->name = "dc4";
    dc1->type = "dc1_type"; dc2->type = "dc2_type"; dc3->type = "dc3_type"; dc4->type = "dc4_type";
    dc1->stau = false;  dc2->stau = false;  dc3->stau = false;  dc4->stau = false;
    PCB *dc1_pcb = new PCB;  PCB *dc2_pcb = new PCB;  PCB *dc3_pcb = new PCB;  PCB *dc4_pcb = new PCB;
    dc1_pcb->next = NULL;   dc2_pcb->next = NULL;   dc3_pcb->next = NULL;   dc4_pcb->next = NULL;
    dc1->waitinglist = dc1_pcb;  dc2->waitinglist = dc2_pcb;  dc3->waitinglist = dc3_pcb;  dc4->waitinglist = dc4_pcb;
    PCB *dc1pro = new PCB;  PCB *dc2pro = new PCB;  PCB *dc3pro = new PCB;  PCB *dc4pro = new PCB;
    dc1pro->next = NULL;    dc2pro->next = NULL;    dc3pro->next = NULL;    dc4pro->next = NULL;
    dc1->process = dc1pro;  dc2->process = dc2pro;  dc3->process = dc3pro;  dc4->process = dc4pro;
    dc1->coct = co1;    dc2->coct = co1;    dc3->coct = co2;    dc4->coct = co3;
    devices = new DCT;
    devices->next = dc1; dc1->next = dc2;    dc2->next = dc3;    dc3->next = dc4;   dc4->next = NULL;

    SDT *sd1 = new SDT; SDT *sd2 = new SDT; SDT *sd3 = new SDT; SDT *sd4 = new SDT;
    sd1->name = "sd1";  sd2->name = "sd2";  sd3->name = "sd3";  sd4->name = "sd4";
    sd1->type = "sd1_type"; sd2->type = "sd2_type"; sd3->type = "sd3_type"; sd4->type = "sd4_type";
    sd1->dct = dc1; sd2->dct = dc2; sd3->dct = dc3; sd4->dct = dc4;
    system = new SDT;
    system->next = sd1; sd1->next = sd2;    sd2->next = sd3;    sd3->next = sd4;    sd4->next = NULL;
}

void seeAll()
{
    SDT *sdt = system;
    while(sdt->next)
    {
        sdt = sdt->next;
        DCT *dct = sdt->dct;
        COCT *coct = dct->coct;
        CHCT *chct = coct->chct;
        cout << sdt->name << "\t" << sdt->type << "\t"<<  dct->name << "[" << dct->stau << "]\t" << coct->name << "[" << coct->stau << "]\t" << chct->name << "[" << chct->stau << "]" << endl;
    }
}


bool check_DevName(string dev_name)
{
    SDT *sdt = system;
    while(sdt->next)
    {
        sdt = sdt->next;
        if(sdt->name == dev_name)
            return true;
    }
    return false;
}


CHCT *select_chct(string name)
{
    CHCT *chct = channels;
    while(chct->next)
    {
        chct = chct->next;
        if(chct->name == name)
            return chct;
    }
}

COCT *select_coct(string name)
{
    COCT *coct = controllers;
    while(coct->next)
    {
        coct = coct->next;
        if(coct->name == name)
            return coct;
    }
}


void add_COCT(COCT *key)
{
    COCT *coct = controllers;
    while(coct->next)
        coct = coct->next;
    coct->next = key;
    key->next = NULL;
}

void add_DCT(DCT *key)
{
    DCT *dct = devices;
    while(dct->next)
        dct = dct->next;
    dct->next = key;
    key->next = NULL;
}

void add_SDT(SDT *key)
{
    SDT *sdt = system;
    while(sdt->next)
        sdt = sdt->next;
    sdt->next = key;
    key->next = NULL;
}

void addDev()
{
    cout << "请输入新设备名称：" << endl;
    string dev_name;
    cin >> dev_name;
    if(check_DevName(dev_name))
        {cout << "设备已存在，添加失败！" << endl;  return;}
    else
    {
        SDT *new_sdt = new SDT;
        new_sdt->name = dev_name;
        cout << "请输入设备类型：" << endl;
        string dev_type;
        cin >> dev_type;
        new_sdt->type = dev_type;

        DCT *new_dct = new DCT;
        new_dct->name = dev_name;
        new_dct->type = dev_type;
        new_dct->stau = false;
        PCB *tk = new PCB;
        tk->next = NULL;
        new_dct->process = tk;
        PCB *tl = new PCB;
        tl->next = NULL;
        new_dct->waitinglist = tl;

        cout << "是否创建新的控制器？(y/n)" << endl;
        string sel;
        cin >> sel;
        if(sel == "y" || sel == "Y")
        {
            cout << "请输入控制器名称：" << endl;
            string new_conName;
            cin >> new_conName;
            COCT *new_con = new COCT;
            new_con->name = new_conName;
            new_con->stau = false;
            PCB *ty = new PCB;
            ty->next = NULL;
            new_con->process = ty;
            PCB *tt = new PCB;
            tt->next = NULL;
            new_con->waitinglist = tt;

            cout << "请选择通道(1/2)：" << endl;
            string sel2;
            cin >> sel2;
            if(sel2 == "1")
                new_con->chct = select_chct("ch1");
            else
                new_con->chct = select_chct("ch2");
            new_dct->coct = new_con;
            new_sdt->dct = new_dct;

            add_COCT(new_con);
        }
        else
        {
            cout << "请输入控制器名称：" << endl;
            string con_name;
            cin >> con_name;
            COCT *temp_coct = select_coct(con_name);
            cout << "请选择通道(1/2)：" << endl;
            string sel2;
            cin >> sel2;
            if(sel2 == "1")
                temp_coct->chct = select_chct("ch1");
            else
                temp_coct->chct = select_chct("ch2");
            new_dct->coct = temp_coct;
            new_sdt->dct = new_dct;
        }
        add_SDT(new_sdt);
        add_DCT(new_dct);
        cout << "设备" << dev_name << "添加成功！" << endl;
    }
}

bool check_DevType(string type)
{
    SDT *sdt = system;
    while(sdt->next)
    {
        sdt = sdt->next;
        if(sdt->type == type && sdt->dct->stau == false)
           return true;
    }
    return false;
}

SDT *find_BlockDevType(string type)
{
    SDT *sdt = system;
    while(sdt->next)
    {
        sdt = sdt->next;
        if(sdt->type == type)
            return sdt;
    }
}

SDT *find_DevType(string type)
{
    SDT *sdt = system;
    while(sdt->next)
    {
        sdt = sdt->next;
        if(sdt->type == type && sdt->dct->stau == false)
            return sdt;
    }
}

void add_DCTwait(DCT *dct , PCB *pcb)
{
    PCB *temp = dct->waitinglist;
    while(temp->next)
        temp = temp->next;
    temp->next = pcb;
    pcb->next = NULL;
}

void add_COCTwait(COCT *coct , PCB *pcb)
{
    PCB *temp = coct->waitinglist;
    while(temp->next)
        temp = temp->next;
    temp->next = pcb;
    pcb->next = NULL;
}


void add_CHCTwait(CHCT *chct , PCB *pcb)
{
    PCB *temp = chct->waitinglist;
    while(temp->next)
        temp = temp->next;
    temp->next = pcb;
    pcb->next = NULL;
}

/*

void out(DCT *dct)
{
    PCB *temp = dct->waitinglist;
    while(temp->next)
    {
        temp = temp->next;
        cout << temp->name << endl;
    }
}
*/


void out_dctWait(DCT *dct)
{
    cout << "DCT等待队列：" << endl;
    PCB *pcb = dct->waitinglist;
    while(pcb->next)
    {
        pcb = pcb->next;
        cout << pcb->name << endl;
    }
}

void out_coctWait(COCT *coct)
{
    cout << "COCT等待队列：" << endl;
    PCB *pcb = coct->waitinglist;
    while(pcb->next)
    {
        pcb = pcb->next;
        cout << pcb->name << endl;
    }
}

void out_chctWait(CHCT *chct)
{
    cout << "CHCT等待队列：" << endl;
    PCB *pcb = chct->waitinglist;
    while(pcb->next)
    {
        pcb = pcb->next;
        cout << pcb->name << endl;
    }
}



void appDev()
{
    cout << "请输入进程名称：" << endl;
    string pro_name;
    cin >> pro_name;
    cout << "请输入所申请设备的类型：" << endl;
    string dev_type;
    cin >> dev_type;
    PCB *pcb = new PCB;
    pcb->name = pro_name;
    pcb->next = NULL;
//cout << "ef" << endl;
    if(check_DevType(dev_type))
    {//cout << "1" << endl;
        SDT *sdt = find_DevType(dev_type);
        DCT *dct = sdt->dct;
        dct->stau = true;
        dct->process->next = pcb;
        COCT *coct = dct->coct;
        if(coct->stau == false)
        {
//cout << "2" << endl;
            coct->stau = true;
            CHCT *chct = coct->chct;
            coct->process->next = pcb;
            if(chct->stau == false)
            {

                //cout << dct->name << "\t" << coct->name << "\t" << chct->name << endl;
                chct->stau = true;
                chct->process->next = pcb;


                cout << "进程" << pro_name << "申请设备成功！" << endl;

               // out_dctWait(dct);
               // out_coctWait(coct);
               // out_chctWait(chct);
            }
            else
            {

                add_CHCTwait(chct , pcb);
                cout << "进程" << pro_name << "挂在了" << chct->name << "等待队列上" << endl;

               // out_chctWait(chct);

            }
        }
        else
        {
            add_COCTwait(coct , pcb);
            cout << "进程" << pro_name << "挂在了" << coct->name << "等待队列上" << endl;

            //out_coctWait(coct);

        }
    }
    else
    {//cout << "rt" << endl;
        SDT *sdt = find_BlockDevType(dev_type);
        DCT *dct = sdt->dct;
        dct->stau = true;
        add_DCTwait(dct , pcb);
        cout << "进程" << pro_name << "挂在了" << dct->name << "等待队列上" << endl;

        //out_dctWait(dct);

    }

}


SDT *get_RecDevName(string dev_name)
{
    SDT *sdt = system;
    while(sdt->next)
    {
        sdt = sdt->next;
        if(sdt->name == dev_name)
            return sdt;
    }
}






void update_coct(COCT *coct , PCB *pcb , SDT *sdt)
{
    CHCT *chct = coct->chct;
    if(chct->waitinglist->next == NULL)
    {
        chct->process->next = pcb;
        cout << "设备" << sdt->name << "回收成功" << endl;
    }
    else
    {
        add_CHCTwait(chct , pcb);
        cout << "进程" << pcb->name << "挂在了" << chct->name << "的阻塞队列上" << endl;
    }
}



void update_dct(DCT *dct , PCB *pcb , SDT *sdt)
{
    COCT *coct = dct->coct;
    if(coct->waitinglist->next == NULL)
    {
        coct->process->next = pcb;
        CHCT *chct = coct->chct;
        if(chct->waitinglist->next == NULL)
        {
            chct->process->next = pcb;
            cout << "设备" << sdt->name << "回收成功" << endl;
        }
        else
        {
            add_CHCTwait(chct , pcb);
            cout << "进程" << pcb->name << "挂在了" << chct->name << "的阻塞队列上" << endl;
        }
    }
    else
    {
        add_COCTwait(coct , pcb);
        cout << "进程" << pcb->name << "挂在了" << coct->name << "的阻塞队列上" << endl;
    }
}



// When a process is run in DCT, it can't do to COCT. Eventhough COCT is relax.
void recDev()
{
    cout << "请输入所回收设备名称：" << endl;
    string dev_name;
    cin >> dev_name;
    if(!check_DevName(dev_name))
    {
        cout << "设备" << dev_name << "回收请求错误！" << endl;
        return;
    }

    SDT *sdt = get_RecDevName(dev_name);
    DCT *dct = sdt->dct;
    if(dct->waitinglist->next == NULL)
    {
        dct->stau = false;
        dct->process->next = NULL;
        COCT *coct = dct->coct;

        if(coct->waitinglist->next == NULL)
        {
            coct->stau = false;
            coct->process->next = NULL;
            CHCT *chct = coct->chct;
            if(chct->waitinglist->next == NULL)
            {
                chct->stau = false;
                chct->process->next = NULL;
                cout << "设备" << sdt->name << "回收成功！" << endl;
            }
            else
            {
                PCB *pcb = chct->waitinglist;
                chct->waitinglist->next = chct->waitinglist->next->next;
                chct->process->next = pcb;
                cout << "进程" << pcb->name << "挂在了" << chct->name << "的阻塞队列上" << endl;
            }
        }
        else
        {
            PCB *pcb = coct->waitinglist->next;
            coct->waitinglist->next = coct->waitinglist->next;
            coct->process->next = pcb;
            update_coct(coct , pcb , sdt);
        }
    }
    else
    {
        PCB *pcb = dct->waitinglist->next;
        dct->waitinglist->next = dct->waitinglist->next->next;
        dct->process->next = pcb;
        update_dct(dct , pcb , sdt);
    }

    out_dctWait(dct);
    out_coctWait(dct->coct);
    out_chctWait(dct->coct->chct);

}


bool check_delCon(DCT *dct , COCT *coct)
{
    DCT *temp = devices;
    while(temp->next)
    {
        temp = temp->next;
        if(temp->name == dct->name) continue;
        if(temp->coct == coct)  return true;
    }
    return false;
}

void del_SDT(SDT *sdt)
{
    SDT *temp = system;
    SDT *pre = system;
    while(temp->next)
    {
        temp = temp->next;
        if(temp->name == sdt->name)
        {
            pre->next = temp->next;
            break;
        }
        pre = temp;
    }
}

void del_DCT(DCT *dct)
{
    DCT *temp = devices;
    DCT *pre = devices;
    while(temp->next)
    {
        temp = temp->next;
        if(temp->name == dct->name)
        {
            pre->next = temp->next;
            break;
        }
        pre = temp;
    }
}

void del_COCT(COCT *coct)
{
    COCT *temp = controllers;
    COCT *pre = controllers;
    while(temp->next)
    {
        temp = temp->next;
        if(temp->name == coct->name)
        {
            pre->next = temp->next;
            break;
        }
        pre = temp;
    }
}

void delDev()
{
    cout << "请输入要删除设备的名称：" << endl;
    string dev_name;
    cin >> dev_name;
    if(!check_DevName(dev_name))
    {
        cout << "您要删除的设备" << dev_name << "不存在，删除失败！" << endl;
        return;
    }
    SDT *sdt = get_RecDevName(dev_name);
    DCT *dct = sdt->dct;
    COCT *coct = dct->coct;
    if(check_delCon(dct , coct)) // Con-Dev can't delete
    {
        del_DCT(dct);
        del_SDT(sdt);
    }
    else // Can delete
    {
        del_COCT(coct);
        del_DCT(dct);
        del_SDT(sdt);
    }
    cout << "删除设备" << dev_name << "成功！" << endl;
}


void menu()
{
    cout << "1.添加设备" << endl;
    cout << "2.删除设备" << endl;
    cout << "3.申请设备" << endl;
    cout << "4.回收设备" << endl;
    cout << "5.查看设备" << endl;
}

void solve()
{
    init();
    while(true)
    {
        menu();
        int sel;
        cin >> sel;
        switch(sel)
        {
        case 1:
            addDev();break;
        case 2:
            delDev();break;
        case 3:
            appDev();break;
        case 4:
            recDev();break;
        case 5:
            seeAll();break;
        default:
            cout << "输入错误，请重新输入！" << endl;break;
        }
    }
}

int main()
{
    solve();
    return 0;
}
