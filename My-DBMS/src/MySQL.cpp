#include "MySQL.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <io.h>
#include <vector>
using namespace std;
MySQL::MySQL()
{
    //ctor

}

/*******************CreateTable****************************************************************************************/

bool MySQL::IsTableExit(string TableName)
{
    string TrueName = TableName + ".txt";
    if(_access(TrueName.c_str() , 0) == 0) return true;
    else return false;
}

vector<string> MySQL::GetMegCreTab()
{
    vector<string> vec;
    vec.clear();
    string tp;
    while(cin >> tp)
    {
        if(tp == ");")  break;
        else if(tp == "(" || tp == ",") continue;
        else vec.push_back(tp);
    }
    return vec;
}

bool MySQL::CheckAttType(vector<string> vec)
{
    int tp = 1;
    for(auto it : vec)
    {
        if(tp % 2 == 0)
            if(it != "int" && it != "char")return false;
        tp ++;
    }
    return true;
}

void MySQL::WriTabAttFil(vector<string> vec , string TableName)
{
    string TrueName = TableName + "_attribute.txt";
    ofstream outfile(TrueName.c_str());
    for(vector<string>::iterator it = vec.begin() ; it != vec.end() - 1 ; it ++)
    {
        outfile << *it << " ";
    }
    outfile << *(vec.end()-1) << "\n";
    outfile.close();
}

void MySQL::WriTabAttNumFil(vector<string> vec , string TableName)
{
    string TrueName = TableName + "_attribute_num.txt";
    ofstream outfile(TrueName.c_str());
    outfile << (vec.size() / 2) ;
    outfile.close();
}
void MySQL::CreTabFil(vector<string> vec , string TableName)
{
    string TrueName = TableName + ".txt";
    ofstream outfile(TrueName.c_str());
    outfile.close();
}

// Compare attribute and true value
bool MySQL::CheckAttribute(string txt , string check_txt)
{
    //cout << txt << " " << check_txt << endl;
    int len = txt.length();
    string Len = "";
    int tp = 0;
    for(int i = 0 ; i < len ; )
    {
        if(txt[i] == '(')
        {
            tp ++;
            i ++;
            while(i < len && txt[i] != ')')
            {
                Len += txt[i];
                i ++;
            }
            if(i < len && txt[i] == ')')   tp ++;
        }
        else i ++;
    }
    //cout << Len << endl;
    if(tp == 2)
    {
        int cnt = 0;
        for(int i = 0 ; i < check_txt.length() ; i ++)
        {
            if(!isalpha(check_txt[i]))   return false;
            cnt ++;
        }
        int stand_cnt = 0;
        int k = 10;
        for(int i = 0 ; i < Len.length() ; i ++)
            stand_cnt = (Len[i] - '0') + k * stand_cnt;
        //cout << cnt << " " << stand_cnt << endl;
        if(cnt >= stand_cnt)    return false;
        return true;
    }
    else
    {
        int cnt = 0;
        for(int i = 0 ; i < check_txt.length() ; i ++)
        {
            if(!isdigit(check_txt[i])) return false;
            cnt ++;
        }
        if(cnt > 9) return false;
        return true;
    }
}

void MySQL::CreateTable(string TableName)
{
    // Get all attribute message
    vector<string> vec = GetMegCreTab();
    // the number of attribute
    int CntAttribute = vec.size() / 2;
    // Check attribute type
    if(!CheckAttType(vec))
    {
        cout << "Attribute type isn't int or char , you cann't create " << TableName << endl;
        return ;
    }
    //CheckTableExit(FileName);
    if(IsTableExit(TableName))
    {
        cout << TableName << " has exit , you can't create!" << endl;
        return ;
    }
    // Write attribute to file
    WriTabAttFil(vec , TableName);
    WriTabAttNumFil(vec , TableName);
    CreTabFil(vec , TableName);
    cout << "Create table " << TableName << " Success" << endl;
    return ;
}

/*******************DropTable****************************************************************************************/

void MySQL::DropTable(string TableName)
{
    if(!IsTableExit(TableName))
    {
        cout << TableName << " hasn't exit , you can't drop!" << endl;
        return ;
    }
    string TrueName1 = TableName + "_attribute.txt";
    string TrueName2 = TableName + "_attribute_num.txt";
    string TrueName3 = TableName + ".txt";
    string TrueName4 = TableName + "_index.txt";
    string TrueName5 = TableName + "_index_col.txt";
    remove(TrueName1.c_str());
    remove(TrueName2.c_str());
    remove(TrueName3.c_str());
    remove(TrueName4.c_str());
    remove(TrueName5.c_str());
    cout << "Success Drop " << TableName << endl;
    return ;
}

/*******************InsertElement****************************************************************************************/

vector<string> MySQL::GetInsertMsg(string TableName)
{
    vector<string> vec;
    string tp;
    while(cin >> tp)
    {
        if(tp == ");") break;
        else if(tp == "(" || tp == ",") continue;
        else vec.push_back(tp);
    }
    return vec;
}

bool MySQL::JudgeInsertType(vector<string> vec , string TableName)
{
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    int f = 1 , tot = 1;
    string g[3][101] , s;
    while(infile >> s)
    {
        if(f % 2 == 0)
            g[1][tot++] = s;
        f ++;
    }
    infile.close();
    tot = 1;
    for(vector<string>::iterator it = vec.begin() ; it != vec.end() ; it ++)
        g[2][tot++] = *it;
    for(int i = 1 ; i <= tot ; i ++)
        if(g[1][i] == "int")
        {
            if(g[2][i] == "NULL") continue;
            for(int j = 0 ; j < g[2][i].length() ; j ++)    if(!isdigit(g[2][i][j]) )    return false;
        }
    return true;
}

int MySQL::JudgeMoreInsert(vector<string>vec , string TableName)
{
    string TrueName = TableName + "_attribute_num.txt";
    ifstream infile(TrueName.c_str());
    int num;
    infile >> num;
    infile.close();
    if(vec.size() > num)    return -1;
    else if(vec.size() == num) return 0;
    else return num - vec.size();
}


int MySQL::GetAttributeNum(string TableName)
{
    string TrueName2 = TableName + "_attribute_num.txt";
    ifstream infile2(TrueName2.c_str());
    int num;
    infile2 >> num;
    infile2.close();
    return num;
}

void MySQL::WriInsertToTabFil(vector<string>vec ,string TableName)
{
    string TrueName = TableName + ".txt";
    string g[31][31];
    string tp;
    ifstream infile(TrueName.c_str());
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else col ++;
    }
    int f = 1;
    for(vector<string>::iterator it = vec.begin() ; it != vec.end() ; it ++)
        g[row][f++] = *it;

    ofstream outfile(TrueName.c_str());
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j < num ; j ++)
            outfile << g[i][j] << " ";
        outfile << g[i][num] << "\n";
    }
    outfile.close();
}

/*******************UpdateIndex****************************************************************************************/

void MySQL::UpdateIndex(string TableName)
{
    int change_col;
    string TrueName3 = TableName + "_index_col.txt";
    ifstream infile3(TrueName3.c_str());
    infile3 >> change_col;
    infile3.close();

    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    string g2[31][31];
    for(int i = 1 ; i <= row ; i ++)
    {
        g2[i][1] = g[i][change_col];
        g2[i][2] = TransIntToStr(i);
    }
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = i + 1 ; j <= row ; j ++)
        {
            if(g2[i][1] > g2[j][1])
            {
                string tp1 = g2[i][1] , tp2 = g2[i][2];
                g2[i][1] = g2[j][1];
                g2[i][2] = g2[j][2];
                g2[j][1] = tp1;
                g2[j][2] = tp2;

            }
        }
    }

    string TrueName2 = TableName + "_index.txt";
    ofstream outfile(TrueName2.c_str());
    for(int i = 1 ; i <= row ; i ++)
        outfile << g2[i][1] << " " << g2[i][2] << "\n";
    outfile.close();

}

bool CheckQuanXian(string username , int num)
{
    string name = username + "_q.txt";
    ifstream infile(name.c_str());
    string g[31];
    for(int i = 1 ; i <= 4 ; i ++)
        infile >> g[i];
    infile.close();
    if(g[num] == "1") return true;
    else return false;
}

void MySQL::InsertElement(string TableName , string username)
{
    // Get all attribute message
    vector<string> vec = GetInsertMsg(TableName);

    if(JudgeMoreInsert(vec , TableName) == -1)
    {
        cout << "Insert values are too much " << endl;
        return ;
    }

    if(!CheckQuanXian(username , 1))
    {
        cout << "no quanxian" << endl;
        return;
    }
    int tp = JudgeMoreInsert(vec , TableName);
    if(tp != 0 && tp != -1)
    {
        for(int i = 0 ; i < tp ; i ++)
            vec.push_back("NULL");
    }
    if(!JudgeInsertType(vec , TableName))
    {
        cout << "Insert attribute type isn't matching" << endl;
        return ;
    }
    WriInsertToTabFil(vec , TableName);
    if(_access((TableName + "_index.txt").c_str() , 0) == 0)
        UpdateIndex(TableName);
    cout << "Insert record to " << TableName << " Success" << endl;
    return ;
}

/*******************SelectTable****************************************************************************************/

void MySQL::SelectTable(string TableName)
{
    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exist" << endl;
        return ;
    }
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string tp , g[31][31];
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else col ++;
    }
    infile.close();
    if(flag)
        row --;
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j <= num ; j ++)
            cout << g[i][j] << " ";
        cout << endl;
    }
    cout << "Select " << TableName << " success" << endl;
}


/*******************DeleteElement****************************************************************************************/


int GetDelCol(string TableName , string attribute)
{
    int del_col = 1;
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    int f = 1;
    string tp;
    while(infile >> tp)
    {
        if(f % 2 != 0)
        {
            if(tp == attribute)
                return del_col;
            del_col ++;
        }
        f ++;
    }
    infile.close();
    return del_col;
}


void MySQL::DeleteRecord(string TableName , string username)
{
    string s1 , s2 , s3 , tps;
    int ope = 0;
    cin >> s1 >> s2 >> s3 >> tps;
    if(s2 == "=") ope = 1;
    else if(s2 == ">") ope = 2;
    else if(s2 == "<") ope = 3;
    else if(s2 == ">=") ope = 4;
    else if(s2 == "<=") ope = 5;
    else if(s2 == "!=") ope = 6;
    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exist" << endl;
        return ;
    }
    if(!CheckQuanXian(username , 3))
    {
        cout << "no quanxian" << endl;
        return ;
    }
    // Get all element
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string tp , g[31][31];
    int flag = 0 , row = 1 , col = 1;
    int num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else col ++;
    }
    infile.close();
    if(flag)
        row --;

    int del_col = GetDelCol(TableName , s1);
    int vis[31] = {0};
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j <= num ; j ++)
        {
            if(j == del_col && g[i][j] == s3)
            {
                vis[i] = 1;
                break;
            }
        }
    }
    string g2[31][31];
    int new_row = 1 , new_col = 1;
    for(int i = 1 ; i <= row ; i ++)
    {
        if(vis[i] == 0)
        {
            for(int j = 1 ; j <= num ; j ++)
            {
                g2[new_row][j] = g[i][j];
            }
            new_row ++;
        }
    }
    // Wtite to TabFil
    ofstream outfile(TrueName.c_str());
    for(int i = 1 ; i<= new_row ; i ++)
    {
        for(int j = 1 ; j < num ; j ++)
            outfile << g2[i][j] << " ";
        outfile << g2[i][num] << "\n";
    }
    outfile.close();
    if(_access((TableName + "_index.txt").c_str() , 0) == 0)
        UpdateIndex(TableName);
    cout << "Delete " << TableName << " record success" << endl;
}

/*******************UpdateAttribute****************************************************************************************/

int MySQL::Get_col_tablename(string TableName , string att)
{
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    vector<string> vec2;
    string tp;
    while(infile >> tp)
        vec2.push_back(tp);
    infile.close();
    int f = 1 , cnt = 1;
    for(vector<string>::iterator it = vec2.begin() ; it != vec2.end() ; it ++)
    {
        if(f % 2 != 0)
        {
            if((*it) == att)
                return cnt;
        }
        else cnt ++;
        f ++;
    }
}

int MySQL::Get_ope(string ope)
{
    if(ope == "=")  return 0;
    else if(ope == ">") return 1;
    else if(ope == "<") return 2;
    else if(ope == ">=") return 3;
    else if(ope == "<=") return 4;
    else if(ope == "!=") return 5;
}


void MySQL::Equal_zero(string TableName , int *vis , string att_val , int it_col)
{
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(g[i][it_col] == att_val) vis[i] = 1;
        else if(g[i][it_col] != att_val) vis[i] = 0;
    }
}

void MySQL::Equal_one(string TableName , int *vis , string att_val , int it_col)
{
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(g[i][it_col] > att_val) vis[i] = 1;
        else if(g[i][it_col] <= att_val) vis[i] = 0;
    }
}


void MySQL::Equal_two(string TableName , int *vis ,  string att_val , int it_col)
{
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(g[i][it_col] < att_val) vis[i] = 1;
        else if(g[i][it_col] >= att_val) vis[i] = 0;
    }
}


void MySQL::Equal_three(string TableName , int *vis , string att_val , int it_col)
{
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(g[i][it_col] >= att_val) vis[i] = 1;
        else if(g[i][it_col] < att_val) vis[i] = 0;
    }
}
void MySQL::Equal_four(string TableName , int *vis , string att_val , int it_col)
{
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(g[i][it_col] <= att_val) vis[i] = 1;
        else if(g[i][it_col] > att_val) vis[i] = 0;
    }
}
void MySQL::Equal_five(string TableName , int *vis , string att_val , int it_col)
{
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(g[i][it_col] != att_val) vis[i] = 1;
        else vis[i] = 0;
    }
}



void MySQL::UpdateAttribute(string TableName , string username)
{
    // Get UpdateMsg
    string change_att_name , change_att_val , tp , tp2 , Ope[31] , s1 , s2 , s3;
    cin >>  change_att_name >> tp >> change_att_val >> tp2;
    pair<string , string> P[31];
    int id = 1;
    while(cin >> s1)
    {
        if(s1 == ";")  break;
        else if(s1 == ",") continue;
        else
        {
            cin >> s2 >> s3;
            pair<string , string> pp(s1 , s3);
            P[id] = pp;
            Ope[id++] = s2;
        }
    }

    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exit" << endl;
        return ;
    }
    if(!CheckQuanXian(username , 2))
    {
        cout << "no quanxian" << endl;
        return ;
    }
    else if(tp != "=" || tp2 != "where")
    {
        cout << "Sectence erro , please check it" << endl;
        return ;
    }

    int vis[31] = {0} , opei = 1;
    for(int it = 1 ; it <= id ; it ++)
    {
        int col_where = Get_col_tablename(TableName , P[it].first);
        int ope_dig = Get_ope(Ope[opei++]);
        if(ope_dig == 0)    Equal_zero(TableName , vis , P[it].second , col_where);
        else if(ope_dig == 1)    Equal_one(TableName , vis , P[it].second , col_where);
        else if(ope_dig == 2)    Equal_two(TableName , vis , P[it].second , col_where);
        else if(ope_dig == 3)    Equal_three(TableName , vis , P[it].second , col_where);
        else if(ope_dig == 4)    Equal_four(TableName , vis , P[it].second , col_where);
        else if(ope_dig == 5)    Equal_five(TableName , vis , P[it].second , col_where);
    }

    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31];
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    int change_col = Get_col_tablename(TableName , change_att_name);
    for(int i = 1 ; i <= row ; i ++)
        if(vis[i])
            g[i][change_col] = change_att_val;

    ofstream outfile(TrueName.c_str());
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j < num  ; j ++)
            outfile << g[i][j] << " ";
        outfile << g[i][num] << "\n";
    }
    outfile.close();
    delete(vis);
    cout << "Update " << TableName << " success" << endl;
}


/*******************AddAttribute****************************************************************************************/

vector<string> MySQL::AddAttMsg()
{
    vector<string> vec;
    vec.clear();
    string tp;
    while(cin >> tp)
    {
        if(tp == ";")   break;
        else if(tp == ",") continue;
        else vec.push_back(tp);
    }
    return vec;
}



void MySQL::AddAttNum(vector<string> vec , string TableName)
{
    string TrueName = TableName + "_attribute_num.txt";
    ifstream infile(TrueName.c_str());
    int num;
    infile >> num;
    infile.close();
    ofstream outfile(TrueName.c_str());
    outfile << (vec.size() / 2 + num) ;
    outfile.close();
}

bool MySQL::IsSamAtt(vector<string> vec , string TableName)
{
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    vector<string> vec2;
    string tp;
    while(infile >> tp)
        vec2.push_back(tp);
    infile.close();
    int f1 = 1 , f2 = 1;
    for(vector<string>::iterator i = vec2.begin() ; i != vec2.end() ; i ++)
    {
        if(f1 % 2 != 0)
        {
            f2 = 1;
            for(vector<string>::iterator j = vec.begin() ; j != vec.end() ; j ++)
            {
                if(f2 % 2 != 0)
                    if((*i) == (*j))    return true;
                f2 ++;
            }
        }
        f1 ++;
    }
    return false;
}

void MySQL::AddAttToTabAtt(vector<string> vec , string TableName)
{
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    vector<string> vec2;
    string tp;
    while(infile >> tp)
        vec2.push_back(tp);
    infile.close();
    for(vector<string>::iterator it = vec.begin() ; it != vec.end() ; it ++)  vec2.push_back(*it);

    ofstream outfile(TrueName.c_str());
    for(vector<string>::iterator it = vec2.begin() ; it != vec2.end() - 1 ; it ++)
    {
        outfile << *it << " ";
    }
    outfile << *(vec2.end()-1) << "\n";
    outfile.close();
}

void MySQL::AddAttToTab(vector<string> vec , string TableName)
{
    // Judge empty
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    infile.seekg(0 , ios_base::end);
    int length = infile.tellg();
    infile.close();
    if(length == 0) return;
    // Get attribute num
    int num = GetAttributeNum(TableName);
    // Get all element
    string g[31][31] , tp;
    ifstream infile3(TrueName.c_str());
    int row = 1 , col = 1 , flag = 0;

    while(infile3 >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile3.close();
    if(flag)
        row --;
    // Trans element
    for(int i = 1 ; i <= row ; i ++)
        for(int j = num + 1 ; j <= num + vec.size() / 2 ; j ++)
            g[i][j] = "NULL";
    // Write to all new element
    ofstream outfile(TrueName.c_str());
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j < num + vec.size() / 2 ; j ++)
            outfile << g[i][j] << " ";
        outfile << g[i][num + vec.size() / 2] << "\n";
    }
    outfile.close();
}


void MySQL::AddAttribute(string TableName)
{
    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exit" << endl;
        return ;
    }
    // Get addAttribute message
    vector<string> vec = AddAttMsg();

    // Check attribute type
    if(!CheckAttType(vec))
    {
        cout << "Attribute type isn't int or char , you cann't add attribute" << endl;
        return ;
    }
    // Check same attribute
    if(IsSamAtt(vec , TableName))
    {
        cout << "Exist the same attribute , you can't add attribute" << endl;
        return ;
    }

    AddAttToTabAtt(vec , TableName);
    AddAttToTab(vec , TableName);
    AddAttNum(vec , TableName);
    cout << "Add attribute to " << TableName << " success" << endl;

}

/*******************DropAttribute****************************************************************************************/

bool MySQL::IsAttExist(string TableName , string attribute)
{
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    vector<string> vec;
    string tp;
    while(infile >> tp) vec.push_back(tp);
    infile.close();
    int f = 1;
    for(vector<string>::iterator it = vec.begin() ; it != vec.end() ; it ++)
    {
        if(f % 2 != 0)
            if((*it) == attribute) return true;
        f ++;
    }
    return false;
}



int MySQL::DropAttToTabAtt(string TableName , string attribute)
{
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    string tp , vec2[31];
    int col = 1 , f = 1 , id = 1;
    while(infile >> tp)
    {
        if(tp != attribute)
        {
            vec2[id++] = tp;
            infile >> tp;
            vec2[id++] = tp;
        }
        else if(tp == attribute)
        {
            col = f;
            infile >> tp;
        }
        f ++;
    }
    infile.close();

    ofstream outfile(TrueName.c_str());
    for(int i = 1 ; i < id ; i ++)
        outfile << vec2[i] << " ";
    outfile << vec2[id] << "\n";
    outfile.close();
    return col;
}

void MySQL::DropAttNum(string TableName , string attribute)
{
    string TrueName = TableName + "_attribute_num.txt";
    ifstream infile(TrueName.c_str());
    int num;
    infile >> num;
    infile.close();
    ofstream outfile(TrueName.c_str());
    outfile << (num - 1) ;
    outfile.close();
}

void MySQL::DropAttToTab(string TableName , string attribute , int edit_col)
{
    // Judge empty
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    infile.seekg(0 , ios_base::end);
    int length = infile.tellg();
    infile.close();
    if(length == 0) return;
    // Get attribute num
    int num = GetAttributeNum(TableName);
    // Get all element
    string g[31][31] , tp;
    ifstream infile3(TrueName.c_str());
    int row = 1 , col = 1 , flag = 0;
    while(infile3 >> tp)
    {
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else col ++;
    }
    infile3.close();
    if(flag)
        row --;
    // Trans element
    string g2[31][31];
    int new_col = 1;
    for(int i = 1 ; i <= row ; i ++)
    {
        new_col = 1;
        for(int j = 1 ; j <= num ; j ++)
        {
            if(j == edit_col)   continue;
            else  g2[i][new_col++] = g[i][j];
        }
    }
    // Write to all new element
    ofstream outfile(TrueName.c_str());
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j < num - 1 ; j ++)
            outfile << g2[i][j] << " ";
        outfile << g2[i][num - 1] << "\n";
    }
    outfile.close();
}


void MySQL::DropAttribute(string TableName , string attribute)
{
    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exit" << endl;
        return ;
    }
    if(!IsAttExist(TableName , attribute))
    {
        cout << attribute << " isn't exist in " << TableName << endl;
        return ;
    }

    int col = DropAttToTabAtt(TableName , attribute);
    DropAttToTab(TableName , attribute , col);
    DropAttNum(TableName ,attribute);
    cout << TableName << " drop attribute" <<" Success" << endl;
}

/*******************CreateIndex****************************************************************************************/

int CheckAtt(string TableName , string attribute)
{
    int res = -1;
    string TrueName = TableName + "_attribute.txt";
    ifstream infile(TrueName.c_str());
    string tp;
    int col = 1 , f = 1 , id = 1;
    while(infile >> tp)
    {
        if(f % 2 != 0)
        {
            if(attribute == tp)
                res = col;
        }
        else
            infile >> tp;
        f ++;
    }
    return res;
}

string MySQL::TransIntToStr(int n)
{
    string res = "";
    while(n > 0)
    {
        res += (char)((n % 10) + '0');
        n /= 10;
    }
    int len = res.length();
    for(int i = 0 , j = len - 1; i < j ; i++ , j --)
    {
        char ch = res[i];
        res[i] = res[j];
        res[j] = ch;
    }
    return res;
}

void MySQL::CreateIndex(string TableName , string attribute)
{
    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exist" << endl;
        return ;
    }
    if(_access((TableName + "_index.txt").c_str() , 0) == 0)
    {
        cout << TableName << "_index.txt has exist , you can't create" << endl;
        return ;
    }

    int change_col = CheckAtt(TableName , attribute);
    string TrueName3 = TableName + "_index_col.txt";
    ofstream outfile3(TrueName3.c_str());
    outfile3 << change_col;
    outfile3.close();


    if(change_col == -1)
    {
        cout << "Attribute isn't exist" << endl;
        return ;
    }

    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    string g2[31][31];
    for(int i = 1 ; i <= row ; i ++)
    {
        g2[i][1] = g[i][change_col];
        g2[i][2] = TransIntToStr(i);
    }
   for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = i + 1 ; j <= row ; j ++)
        {
            if(g2[i][1] > g2[j][1])
            {
                string tp1 = g2[i][1] , tp2 = g2[i][2];
                g2[i][1] = g2[j][1];
                g2[i][2] = g2[j][2];
                g2[j][1] = tp1;
                g2[j][2] = tp2;
            }
        }
    }

    string TrueName2 = TableName + "_index.txt";
    ofstream outfile(TrueName2.c_str());
    for(int i = 1 ; i <= row ; i ++)
        outfile << g2[i][1] << " " << g2[i][2] << "\n";
    outfile.close();
    cout << "Create " << TableName << " index success" << endl;
}


/*******************Single****************************************************************************************/

void MySQL::SingleSelect(string TableName , vector< pair< string , string > > P , string *Ope)
{

    if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exit" << endl;
        return ;
    }
    int vis[31] = {0} , opei = 1;
    for(vector< pair<string , string> >::iterator it = P.begin() ; it != P.end() ; it ++)
    {
        string tp1 = (*it).first , tp2 = (*it).second;
        int col_where = Get_col_tablename(TableName , tp1);
        int ope_dig = Get_ope(Ope[opei++]);
        if(ope_dig == 0)    Equal_zero(TableName , vis , tp2 , col_where);
        else if(ope_dig == 1)    Equal_one(TableName , vis , tp2 , col_where);
        else if(ope_dig == 2)    Equal_two(TableName , vis , tp2 , col_where);
        else if(ope_dig == 3)    Equal_three(TableName , vis , tp2 , col_where);
        else if(ope_dig == 4)    Equal_four(TableName , vis , tp2 , col_where);
        else if(ope_dig == 5)    Equal_five(TableName , vis , tp2 , col_where);
    }

    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;

    for(int i = 1 ; i <= row ; i ++)
    {
        if(vis[i])
        {
            for(int j = 1 ; j <= num ; j ++)
                cout << g[i][j] << " ";
            cout << endl;
        }
    }
    delete(vis);
    cout << "Single Select success" << endl;
}

void MySQL::SingleTou(string TableName , vector<string> AttributeName)
{
    int Col[31] = {0} , id = 1;
    for(vector<string>::iterator it = AttributeName.begin() ; it != AttributeName.end() ; it ++)
    {
        Col[id++] = Get_col_tablename(TableName , (*it));
    }
    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;
    infile.close();
    for(int i = 1 ; i <= row ; i ++)
    {
        for(int j = 1 ; j <= id ; j ++)
            cout << g[i][Col[j]] << " ";
        cout << endl;
    }
    cout << "Single TouYing success" << endl;
}

void MySQL::SingleSelTou(string TableName , vector<string> AttributeName , vector< pair<string , string> > P , string *Ope)
{
   if(!IsTableExit(TableName))
    {
        cout << TableName << " isn't exit" << endl;
        return ;
    }
    int Col[31] = {0} , id = 1;
    for(vector<string>::iterator it = AttributeName.begin() ; it != AttributeName.end() ; it ++)
    {
        Col[id++] = Get_col_tablename(TableName , (*it));
    }

    int vis[31] = {0} , opei = 1;
    for(vector< pair<string , string> >::iterator it = P.begin() ; it != P.end() ; it ++)
    {
        string tp1 = (*it).first , tp2 = (*it).second;
        int col_where = Get_col_tablename(TableName , tp1);
        int ope_dig = Get_ope(Ope[opei++]);
        if(ope_dig == 0)    Equal_zero(TableName , vis , tp2 , col_where);
        else if(ope_dig == 1)    Equal_one(TableName , vis , tp2 , col_where);
        else if(ope_dig == 2)    Equal_two(TableName , vis , tp2 , col_where);
        else if(ope_dig == 3)    Equal_three(TableName , vis , tp2 , col_where);
        else if(ope_dig == 4)    Equal_four(TableName , vis , tp2 , col_where);
        else if(ope_dig == 5)    Equal_five(TableName , vis , tp2 , col_where);
    }

    string TrueName = TableName + ".txt";
    ifstream infile(TrueName.c_str());
    string g[31][31] , tp;
    int row = 1 , col = 1 , flag = 0 , num = GetAttributeNum(TableName);
    while(infile >> tp)
    {
        if(tp == " ") continue;
        g[row][col] = tp;
        if(col == num)
        {
            flag = 1;
            row ++;
            col = 1;
        }
        else
            col ++;
    }
    infile.close();
    if(flag)
        row --;
    for(int i = 1 ; i <= row ; i ++)
        if(vis[i])
        {
            for(int j = 1 ; j <= id ; j ++)
                cout << g[i][Col[j]] << " ";
            cout << endl;
        }
    delete(vis);
    cout << "Single select and touying success" << endl;
}




/*******************More****************************************************************************************/

string MySQL::SplitTable(string x)
{
    int len = x.length();
    string res = "";
    for(int i = 0 ; i < len ; i ++)
    {
        if(x[i] == '.') return res;
        else res += x[i];
    }
}

string MySQL::SplitAtt(string x)
{
    int len = x.length();
    string res = "";
    for(int i = 0 ; i < len ; i ++)
    {
        if(x[i] == '.')
        {
            for(int j = i + 1 ; j < len ; j ++)
                res += x[j];
            return res;
        }
    }
}

int MySQL::GetTableNameNum(string tablename1 , vector<string>Tablename)
{
    int id = 1;
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
    {
        if((*it) == tablename1) return id;
        else id ++;
    }
}


void MySQL::MoreSelect(vector<string> Tablename , vector< pair<string , string> > P , string *Ope)
{
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
    {
        if(!IsTableExit((*it).c_str()))
        {
            cout << (*it) << " isn't exit" << endl;
            return ;
        }
    }
    string g[61][61];
    string tablename1 = *(Tablename.begin());
    string tablename2 = *(Tablename.begin() + 1);

    string TrueName1 = tablename1 + ".txt";
    ifstream infile1(TrueName1.c_str());
    string g1[31][31] , tp;
    int row1 = 1 , col1 = 1 , flag1 = 0 , num1 = GetAttributeNum(tablename1);
    while(infile1 >> tp)
    {
        if(tp == " ") continue;
        g1[row1][col1] = tp;
        if(col1 == num1)
        {
            flag1 = 1;
            row1 ++;
            col1 = 1;
        }
        else
            col1 ++;
    }
    infile1.close();
    if(flag1)
        row1 --;

    string TrueName2 = tablename2 + ".txt";
    ifstream infile2(TrueName2.c_str());
    string g2[31][31] , tp2;
    int row2 = 1 , col2 = 1 , flag2 = 0 , num2 = GetAttributeNum(tablename2);
    while(infile2 >> tp)
    {
        if(tp2 == " ") continue;
        g2[row2][col2] = tp;
        if(col2 == num2)
        {
            flag2 = 1;
            row2 ++;
            col2 = 1;
        }
        else
            col2 ++;
    }
    infile2.close();
    if(flag2)
        row2 --;


    int new_row = 1 , new_col = 1;
    for(int i = 1 ; i <= row1 ; i ++)
    {
        for(int i2 = 1 ; i2 <= row2 ; i2 ++)
        {
            for(int j = 1 ; j <= num1 ; j ++)
                g[new_row][new_col++] = g1[i][j];
            for(int j = 1 ; j <= num2 ; j ++)
                g[new_row][new_col++] = g2[i2][j];
            new_row ++;
            new_col = 1;
        }
    }
    int n1 = GetAttributeNum(tablename1);
    int n2 = GetAttributeNum(tablename2);
    new_col = n1 + n2;
    new_row --;

    for(vector<string>::iterator it = Tablename.begin() + 2; it != Tablename.end() ; it ++)
    {
        string res_g[61][61];
        string TrueName3 = (*it) + ".txt";
        ifstream infile3(TrueName3.c_str());
        string g3[31][31] , tp3;
        int row3 = 1 , col3 = 1 , flag3 = 0 , num3 = GetAttributeNum((*it));
        while(infile3 >> tp3)
        {
            if(tp3 == " ") continue;
            g3[row3][col3] = tp3;
            if(col3 == num3)
            {
                flag3 = 1;
                row3 ++;
                col3 = 1;
            }
            else
                col3 ++;
        }
        infile3.close();
        if(flag3)
            row3 --;
        int res_row = 1 , res_col = 1;
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int i3 = 1 ; i3 <= row3 ; i3 ++)
            {
                for(int j = 1 ; j <= new_col ; j ++)
                    res_g[res_row][res_col++] = g[i][j];
                for(int j = 1 ; j <= num3 ; j ++)
                    res_g[res_row][res_col++] = g3[i3][j];
                res_row ++;
                res_col = 1;
            }
        }
        new_row = res_row - 1;
        new_col += GetAttributeNum((*it));
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int j = 1 ; j <= new_col ; j ++)
                g[i][j] = res_g[i][j];
        }
    }

    /*
    cout << new_row << " " << new_col << endl;
    for(int i = 1 ; i <= new_row ; i ++)
    {
        for(int j = 1 ; j <= new_col ; j ++)
            cout << g[i][j] << " ";
        cout << endl;
    }
    cout << "Over" << endl;
    */
    int attnum[41] = {0} , id = 1;
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
        attnum[id++] = GetAttributeNum((*it));
    int vis[101] = {0};
    for(vector< pair<string , string> >::iterator it = P.begin() ; it != P.end() ; it ++)
    {
        string tablename1 = SplitTable((*it).first);
        string att1 = SplitAtt((*it).first);
        string tablename2 = SplitTable((*it).second);
        string att2 = SplitAtt((*it).second);

        int tablenum1 = GetTableNameNum(tablename1 , Tablename);
        int tablenum2 = GetTableNameNum(tablename2 , Tablename);
        int base_col1 = 0 , base_col2 = 0;

        if(tablenum1 == 1)
            base_col1 = Get_col_tablename(tablename1 , att1);
        else
        {
            for(int j = 1 ; j < tablenum1 ; j ++)
                base_col1 += attnum[j];
            base_col1 += Get_col_tablename(tablename1 , att1);
        }
        if(tablenum2 == 1)
            base_col2 = Get_col_tablename(tablename2 , att2);
        else
        {
            for(int j = 1 ; j < tablenum2 ; j ++)
                base_col2 += attnum[j];
            base_col2 += Get_col_tablename(tablename2 , att2);
        }
        for(int i = 1 ; i <= new_row ; i ++)
        {
            if(vis[i] == 0 || vis[i] == 1)
            {
                if(g[i][base_col1] == g[i][base_col2])  vis[i] = 1;
                else vis[i] = -1;
            }
        }
    }
    for(int i = 1 ; i <= new_row ; i ++)
    {
        if(vis[i] == 1)
        {
            for(int j = 1 ; j <= new_col ; j ++)
                cout << g[i][j] << " ";
            cout << endl;
        }
    }
    cout << "More select success" << endl;
    delete vis;
}

bool MySQL::CheckAttValue(string x)
{
    int len = x.length();
    if(x[0] == '"' && x[len-1] == '"')  return true;
    return false;
}

void MySQL::MoreSelLian(vector<string> Tablename , vector< pair<string , string> > P , string *Ope)
{
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
    {
        if(!IsTableExit((*it).c_str()))
        {
            cout << (*it) << " isn't exit" << endl;
            return ;
        }
    }
    string g[61][61];
    string tablename1 = *(Tablename.begin());
    string tablename2 = *(Tablename.begin() + 1);

    string TrueName1 = tablename1 + ".txt";
    ifstream infile1(TrueName1.c_str());
    string g1[31][31] , tp;
    int row1 = 1 , col1 = 1 , flag1 = 0 , num1 = GetAttributeNum(tablename1);
    while(infile1 >> tp)
    {
        if(tp == " ") continue;
        g1[row1][col1] = tp;
        if(col1 == num1)
        {
            flag1 = 1;
            row1 ++;
            col1 = 1;
        }
        else
            col1 ++;
    }
    infile1.close();
    if(flag1)
        row1 --;

    string TrueName2 = tablename2 + ".txt";
    ifstream infile2(TrueName2.c_str());
    string g2[31][31] , tp2;
    int row2 = 1 , col2 = 1 , flag2 = 0 , num2 = GetAttributeNum(tablename2);
    while(infile2 >> tp)
    {
        if(tp2 == " ") continue;
        g2[row2][col2] = tp;
        if(col2 == num2)
        {
            flag2 = 1;
            row2 ++;
            col2 = 1;
        }
        else
            col2 ++;
    }
    infile2.close();
    if(flag2)
        row2 --;


    int new_row = 1 , new_col = 1;
    for(int i = 1 ; i <= row1 ; i ++)
    {
        for(int i2 = 1 ; i2 <= row2 ; i2 ++)
        {
            for(int j = 1 ; j <= num1 ; j ++)
                g[new_row][new_col++] = g1[i][j];
            for(int j = 1 ; j <= num2 ; j ++)
                g[new_row][new_col++] = g2[i2][j];
            new_row ++;
            new_col = 1;
        }
    }
    int n1 = GetAttributeNum(tablename1);
    int n2 = GetAttributeNum(tablename2);
    new_col = n1 + n2;
    new_row --;

    for(vector<string>::iterator it = Tablename.begin() + 2; it != Tablename.end() ; it ++)
    {
        string res_g[61][61];
        string TrueName3 = (*it) + ".txt";
        ifstream infile3(TrueName3.c_str());
        string g3[31][31] , tp3;
        int row3 = 1 , col3 = 1 , flag3 = 0 , num3 = GetAttributeNum((*it));
        while(infile3 >> tp3)
        {
            if(tp3 == " ") continue;
            g3[row3][col3] = tp3;
            if(col3 == num3)
            {
                flag3 = 1;
                row3 ++;
                col3 = 1;
            }
            else
                col3 ++;
        }
        infile3.close();
        if(flag3)
            row3 --;
        int res_row = 1 , res_col = 1;
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int i3 = 1 ; i3 <= row3 ; i3 ++)
            {
                for(int j = 1 ; j <= new_col ; j ++)
                    res_g[res_row][res_col++] = g[i][j];
                for(int j = 1 ; j <= num3 ; j ++)
                    res_g[res_row][res_col++] = g3[i3][j];
                res_row ++;
                res_col = 1;
            }
        }
        new_row = res_row - 1;
        new_col += GetAttributeNum((*it));
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int j = 1 ; j <= new_col ; j ++)
                g[i][j] = res_g[i][j];
        }
    }
    int attnum[41] = {0} , id = 1;
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
        attnum[id++] = GetAttributeNum((*it));
    int vis[101] = {0};

    for(vector< pair<string , string> >::iterator it = P.begin() ; it != P.end() ; it ++)
    {
        if(CheckAttValue((*it).second))
        {
            string tablename1 = SplitTable((*it).first);
            string att1 = SplitAtt((*it).first);
            int tablenum1 = GetTableNameNum(tablename1 , Tablename);
            int base_col1 = 0;
            if(tablenum1 == 1)
                base_col1 = Get_col_tablename(tablename1 , att1);
            else
            {
                for(int j = 1 ; j < tablenum1 ; j ++)
                    base_col1 += attnum[j];
                base_col1 += Get_col_tablename(tablename1 , att1);
            }
            string tp = (*it).second;
            int len = (*it).second.length();
            string res = "";
            for(int i = 1 ; i < len - 1 ; i ++) res += tp[i];
            for(int i = 1 ; i <= new_row ; i ++)
            {
                if(vis[i] == 1 || vis[i] == 0)
                {
                    if(g[i][base_col1] == res)  vis[i] = 1;
                    else vis[i] = -1;
                }
            }
        }
        else
        {
            string tablename1 = SplitTable((*it).first);
            string att1 = SplitAtt((*it).first);
            string tablename2 = SplitTable((*it).second);
            string att2 = SplitAtt((*it).second);
            int tablenum1 = GetTableNameNum(tablename1 , Tablename);
            int tablenum2 = GetTableNameNum(tablename2 , Tablename);
            int base_col1 = 0 , base_col2 = 0;
            if(tablenum1 == 1)
                base_col1 = Get_col_tablename(tablename1 , att1);
            else
            {
                for(int j = 1 ; j < tablenum1 ; j ++)
                    base_col1 += attnum[j];
                base_col1 += Get_col_tablename(tablename1 , att1);
            }
            if(tablenum2 == 1)
                base_col2 = Get_col_tablename(tablename2 , att2);
            else
            {
                for(int j = 1 ; j < tablenum2 ; j ++)
                    base_col2 += attnum[j];
                base_col2 += Get_col_tablename(tablename2 , att2);
            }
            for(int i = 1 ; i <= new_row ; i ++)
            {
                if(vis[i] == 0 || vis[i] == 1)
                {
                    if(g[i][base_col1] == g[i][base_col2])  vis[i] = 1;
                    else vis[i] = -1;
                }
            }
        }
    }
    for(int i = 1 ; i <= new_row ; i ++)
    {
        if(vis[i] == 1)
        {
            for(int j = 1 ; j <= new_col ; j ++)
                cout << g[i][j] << " ";
            cout << endl;
        }
    }
    cout << "More select and lianjie success" << endl;
}

int MySQL::GetMoreCol(vector<string> Tablename , string att)
{
    vector<string> Att;
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
    {
        string true_name = (*it) + "_attribute.txt";
        ifstream infile(true_name.c_str());
        string tp;
        while(infile >> tp)
        {
            Att.push_back(tp);
            infile >> tp;
        }
        infile.close();
    }
    int id = 1;
    for(vector<string>::iterator it = Att.begin() ; it != Att.end() ; it ++)
    {
        if((*it) == att) return id;
        else id ++;
    }
}


void MySQL::MoreTouLian(vector<string> att , vector<string> Tablename , vector< pair<string , string> >P , string *Ope)
{
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
    {
        if(!IsTableExit((*it).c_str()))
        {
            cout << (*it) << " isn't exit" << endl;
            return ;
        }
    }
    string g[61][61];
    string tablename1 = *(Tablename.begin());
    string tablename2 = *(Tablename.begin() + 1);

    string TrueName1 = tablename1 + ".txt";
    ifstream infile1(TrueName1.c_str());
    string g1[31][31] , tp;
    int row1 = 1 , col1 = 1 , flag1 = 0 , num1 = GetAttributeNum(tablename1);
    while(infile1 >> tp)
    {
        if(tp == " ") continue;
        g1[row1][col1] = tp;
        if(col1 == num1)
        {
            flag1 = 1;
            row1 ++;
            col1 = 1;
        }
        else
            col1 ++;
    }
    infile1.close();
    if(flag1)
        row1 --;

    string TrueName2 = tablename2 + ".txt";
    ifstream infile2(TrueName2.c_str());
    string g2[31][31] , tp2;
    int row2 = 1 , col2 = 1 , flag2 = 0 , num2 = GetAttributeNum(tablename2);
    while(infile2 >> tp)
    {
        if(tp2 == " ") continue;
        g2[row2][col2] = tp;
        if(col2 == num2)
        {
            flag2 = 1;
            row2 ++;
            col2 = 1;
        }
        else
            col2 ++;
    }
    infile2.close();
    if(flag2)
        row2 --;


    int new_row = 1 , new_col = 1;
    for(int i = 1 ; i <= row1 ; i ++)
    {
        for(int i2 = 1 ; i2 <= row2 ; i2 ++)
        {
            for(int j = 1 ; j <= num1 ; j ++)
                g[new_row][new_col++] = g1[i][j];
            for(int j = 1 ; j <= num2 ; j ++)
                g[new_row][new_col++] = g2[i2][j];
            new_row ++;
            new_col = 1;
        }
    }
    int n1 = GetAttributeNum(tablename1);
    int n2 = GetAttributeNum(tablename2);
    new_col = n1 + n2;
    new_row --;

    for(vector<string>::iterator it = Tablename.begin() + 2; it != Tablename.end() ; it ++)
    {
        string res_g[61][61];
        string TrueName3 = (*it) + ".txt";
        ifstream infile3(TrueName3.c_str());
        string g3[31][31] , tp3;
        int row3 = 1 , col3 = 1 , flag3 = 0 , num3 = GetAttributeNum((*it));
        while(infile3 >> tp3)
        {
            if(tp3 == " ") continue;
            g3[row3][col3] = tp3;
            if(col3 == num3)
            {
                flag3 = 1;
                row3 ++;
                col3 = 1;
            }
            else
                col3 ++;
        }
        infile3.close();
        if(flag3)
            row3 --;
        int res_row = 1 , res_col = 1;
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int i3 = 1 ; i3 <= row3 ; i3 ++)
            {
                for(int j = 1 ; j <= new_col ; j ++)
                    res_g[res_row][res_col++] = g[i][j];
                for(int j = 1 ; j <= num3 ; j ++)
                    res_g[res_row][res_col++] = g3[i3][j];
                res_row ++;
                res_col = 1;
            }
        }
        new_row = res_row - 1;
        new_col += GetAttributeNum((*it));
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int j = 1 ; j <= new_col ; j ++)
                g[i][j] = res_g[i][j];
        }
    }
    int attnum[41] = {0} , id = 1;
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
        attnum[id++] = GetAttributeNum((*it));
    int vis[101] = {0};
    for(vector< pair<string , string> >::iterator it = P.begin() ; it != P.end() ; it ++)
    {
        string tablename1 = SplitTable((*it).first);
        string att1 = SplitAtt((*it).first);
        string tablename2 = SplitTable((*it).second);
        string att2 = SplitAtt((*it).second);

        int tablenum1 = GetTableNameNum(tablename1 , Tablename);
        int tablenum2 = GetTableNameNum(tablename2 , Tablename);
        int base_col1 = 0 , base_col2 = 0;

        if(tablenum1 == 1)
            base_col1 = Get_col_tablename(tablename1 , att1);
        else
        {
            for(int j = 1 ; j < tablenum1 ; j ++)
                base_col1 += attnum[j];
            base_col1 += Get_col_tablename(tablename1 , att1);
        }
        if(tablenum2 == 1)
            base_col2 = Get_col_tablename(tablename2 , att2);
        else
        {
            for(int j = 1 ; j < tablenum2 ; j ++)
                base_col2 += attnum[j];
            base_col2 += Get_col_tablename(tablename2 , att2);
        }
        for(int i = 1 ; i <= new_row ; i ++)
        {
            if(vis[i] == 0 || vis[i] == 1)
            {
                if(g[i][base_col1] == g[i][base_col2])  vis[i] = 1;
                else vis[i] = -1;
            }
        }
    }
    for(int i = 1 ; i <= new_row ; i ++)
    {
        if(vis[i] == 1)
        {
            for(vector<string>::iterator it = att.begin() ; it != att.end() ; it ++)
            {
                int true_col = GetMoreCol(Tablename , (*it));
                cout << g[i][true_col] << " ";
            }
            cout << endl;
        }
    }
    cout << "Tou and lian success" << endl;
}

void MySQL::MoreSelTouLian(vector<string> att , vector<string> Tablename , vector< pair<string , string> > P , string *Ope)
{
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
    {
        if(!IsTableExit((*it).c_str()))
        {
            cout << (*it) << " isn't exit" << endl;
            return ;
        }
    }
    string g[61][61];
    string tablename1 = *(Tablename.begin());
    string tablename2 = *(Tablename.begin() + 1);

    string TrueName1 = tablename1 + ".txt";
    ifstream infile1(TrueName1.c_str());
    string g1[31][31] , tp;
    int row1 = 1 , col1 = 1 , flag1 = 0 , num1 = GetAttributeNum(tablename1);
    while(infile1 >> tp)
    {
        if(tp == " ") continue;
        g1[row1][col1] = tp;
        if(col1 == num1)
        {
            flag1 = 1;
            row1 ++;
            col1 = 1;
        }
        else
            col1 ++;
    }
    infile1.close();
    if(flag1)
        row1 --;

    string TrueName2 = tablename2 + ".txt";
    ifstream infile2(TrueName2.c_str());
    string g2[31][31] , tp2;
    int row2 = 1 , col2 = 1 , flag2 = 0 , num2 = GetAttributeNum(tablename2);
    while(infile2 >> tp)
    {
        if(tp2 == " ") continue;
        g2[row2][col2] = tp;
        if(col2 == num2)
        {
            flag2 = 1;
            row2 ++;
            col2 = 1;
        }
        else
            col2 ++;
    }
    infile2.close();
    if(flag2)
        row2 --;


    int new_row = 1 , new_col = 1;
    for(int i = 1 ; i <= row1 ; i ++)
    {
        for(int i2 = 1 ; i2 <= row2 ; i2 ++)
        {
            for(int j = 1 ; j <= num1 ; j ++)
                g[new_row][new_col++] = g1[i][j];
            for(int j = 1 ; j <= num2 ; j ++)
                g[new_row][new_col++] = g2[i2][j];
            new_row ++;
            new_col = 1;
        }
    }
    int n1 = GetAttributeNum(tablename1);
    int n2 = GetAttributeNum(tablename2);
    new_col = n1 + n2;
    new_row --;

    for(vector<string>::iterator it = Tablename.begin() + 2; it != Tablename.end() ; it ++)
    {
        string res_g[61][61];
        string TrueName3 = (*it) + ".txt";
        ifstream infile3(TrueName3.c_str());
        string g3[31][31] , tp3;
        int row3 = 1 , col3 = 1 , flag3 = 0 , num3 = GetAttributeNum((*it));
        while(infile3 >> tp3)
        {
            if(tp3 == " ") continue;
            g3[row3][col3] = tp3;
            if(col3 == num3)
            {
                flag3 = 1;
                row3 ++;
                col3 = 1;
            }
            else
                col3 ++;
        }
        infile3.close();
        if(flag3)
            row3 --;
        int res_row = 1 , res_col = 1;
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int i3 = 1 ; i3 <= row3 ; i3 ++)
            {
                for(int j = 1 ; j <= new_col ; j ++)
                    res_g[res_row][res_col++] = g[i][j];
                for(int j = 1 ; j <= num3 ; j ++)
                    res_g[res_row][res_col++] = g3[i3][j];
                res_row ++;
                res_col = 1;
            }
        }
        new_row = res_row - 1;
        new_col += GetAttributeNum((*it));
        for(int i = 1 ; i <= new_row ; i ++)
        {
            for(int j = 1 ; j <= new_col ; j ++)
                g[i][j] = res_g[i][j];
        }
    }
    int attnum[41] = {0} , id = 1;
    for(vector<string>::iterator it = Tablename.begin() ; it != Tablename.end() ; it ++)
        attnum[id++] = GetAttributeNum((*it));
    int vis[101] = {0};

    for(vector< pair<string , string> >::iterator it = P.begin() ; it != P.end() ; it ++)
    {
        if(CheckAttValue((*it).second))
        {
            string tablename1 = SplitTable((*it).first);
            string att1 = SplitAtt((*it).first);
            int tablenum1 = GetTableNameNum(tablename1 , Tablename);
            int base_col1 = 0;
            if(tablenum1 == 1)
                base_col1 = Get_col_tablename(tablename1 , att1);
            else
            {
                for(int j = 1 ; j < tablenum1 ; j ++)
                    base_col1 += attnum[j];
                base_col1 += Get_col_tablename(tablename1 , att1);
            }
            string tp = (*it).second;
            int len = (*it).second.length();
            string res = "";
            for(int i = 1 ; i < len - 1 ; i ++) res += tp[i];
            for(int i = 1 ; i <= new_row ; i ++)
            {
                if(vis[i] == 1 || vis[i] == 0)
                {
                    if(g[i][base_col1] == res)  vis[i] = 1;
                    else vis[i] = -1;
                }
            }
        }
        else
        {
            string tablename1 = SplitTable((*it).first);
            string att1 = SplitAtt((*it).first);
            string tablename2 = SplitTable((*it).second);
            string att2 = SplitAtt((*it).second);
            int tablenum1 = GetTableNameNum(tablename1 , Tablename);
            int tablenum2 = GetTableNameNum(tablename2 , Tablename);
            int base_col1 = 0 , base_col2 = 0;
            if(tablenum1 == 1)
                base_col1 = Get_col_tablename(tablename1 , att1);
            else
            {
                for(int j = 1 ; j < tablenum1 ; j ++)
                    base_col1 += attnum[j];
                base_col1 += Get_col_tablename(tablename1 , att1);
            }
            if(tablenum2 == 1)
                base_col2 = Get_col_tablename(tablename2 , att2);
            else
            {
                for(int j = 1 ; j < tablenum2 ; j ++)
                    base_col2 += attnum[j];
                base_col2 += Get_col_tablename(tablename2 , att2);
            }
            for(int i = 1 ; i <= new_row ; i ++)
            {
                if(vis[i] == 0 || vis[i] == 1)
                {
                    if(g[i][base_col1] == g[i][base_col2])  vis[i] = 1;
                    else vis[i] = -1;
                }
            }
        }
    }
    for(int i = 1 ; i <= new_row ; i ++)
    {
        if(vis[i] == 1)
        {
            for(vector<string>::iterator it = att.begin() ; it != att.end() ; it ++)
            {
                int true_col = GetMoreCol(Tablename , (*it));
                cout << g[i][true_col] << " ";
            }
            cout << endl;
        }
    }
    cout << "Select and tou and lian success" << endl;
}

void MySQL::Adduser(string user , string pass)
{
    string g[31][3];
    ifstream infile("admin.txt");
    string tp1 , tp2;
    int row = 1;
    while(infile >> tp1 >> tp2)
    {
        g[row][1] = tp1;
        g[row++][2] = tp2;
    }
    infile.close();
    g[row][1] = user;
    g[row][2] = pass;
    ofstream outfile("admin.txt");
    for(int i = 1 ; i <= row ; i ++)
        outfile << g[i][1] << " " << g[i][2] << "\n";
    outfile.close();

    string TrueName = user + "_q.txt";
    ofstream outfile2(TrueName.c_str());
    for(int i = 1 ; i < 4 ; i ++)
        outfile2 << 1 << " ";
    outfile2 << 1 << "\n";
    outfile2.close();
}
void MySQL::Deluser(string user , string pass)
{
    string g[31][3];
    ifstream infile("admin.txt");
    string tp1 , tp2;
    int row = 1;
    while(infile >> tp1 >> tp2)
    {
        g[row][1] = tp1;
        g[row++][2] = tp2;
    }
    infile.close();
    int vis[31] = {0};
    for(int i = 1 ; i < row; i ++)
    {
        if(user == g[i][1] && pass == g[i][2])
            vis[i] = 1;
    }
    ofstream outfile("admin.txt");
    for(int i = 1 ; i <= row ; i ++)
        if(vis[i] == 0)
            outfile << g[i][1] << " " << g[i][2] << "\n";
    outfile.close();
    string Name = user + "_q.txt";
    remove(Name.c_str());
}

void MySQL::GiveQ(vector<string> quan, string user)
{
    string name = user + "_q.txt";
    ifstream infile(name.c_str());
    string g[31];
    int id = 1;
    while(infile >> g[id])
        id ++;
    infile.close();
    for(vector<string>::iterator it = quan.begin() ; it != quan.end() ; it ++)
    {
        int num;
        if((*it) == "insert") num = 1;
        else if((*it) == "update")  num = 2;
        else if((*it) == "delete") num = 3;
        g[num] = "1";
    }
    ofstream outfile(name.c_str());
    for(int i =1 ; i < 4 ; i++)
        outfile << g[i] << " ";
    outfile << g[4] << "\n";
    outfile.close();
}
void MySQL::DelQ(vector<string> quan, string user)
{
    string name = user + "_q.txt";
    ifstream infile(name.c_str());
    string g[31];
    int id = 1;
    while(infile >> g[id])
        id ++;
    infile.close();
    for(vector<string>::iterator it = quan.begin() ; it != quan.end() ; it ++)
    {
        int num = 4;
        if((*it) == "insert") num = 1;
        else if((*it) == "update")  num = 2;
        else if((*it) == "delete") num = 3;
        g[num] = "0";
    }
    ofstream outfile(name.c_str());
    for(int i =1 ; i < 4 ; i++)
        outfile << g[i] << " ";
    outfile << g[4] << "\n";
    outfile.close();
}


MySQL::~MySQL()
{
    //dtor
}
